#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "patch.h"
#include "util.h"
#include "sym.h"

static patch_t **patch_map;


patch_t *new_patch(int type, int ofs) {
  patch_t *p = malloc(sizeof(patch_t));
  memset(p, 0, sizeof(patch_t));
  p->type = type;
  p->next = 0;
  patch_t *q =  patch_map[ofs];
  if (!q) patch_map[ofs] = p;
  else {
    while(q->next) q = q->next;
    q->next = p;
  }
  return p;
}

int has_patch(int type, int ofs) {
  patch_t *q =  patch_map[ofs];
  for(; q ; q = q->next) {
    if (q->type == type) return 1;
  }
  return 0;
}

static char *quotetbl[128];

void init_patcher(int sz) {
  patch_map = malloc(sizeof(patch_t*)*sz);
  memset(patch_map, 0, sizeof(patch_t*)*sz);

  quotetbl['='] =  "set";
  quotetbl['+'] =  "plus";
  quotetbl['-'] =  "minus";
  quotetbl['*'] =  "mul";
  quotetbl['/'] =  "div";
  quotetbl['.'] =  "dot";
  quotetbl['['] =  "ob";
  quotetbl[']'] =  "cb";
}

static char *arrputs2(char *r, char *s) {
  for (; *s; s++) arrput(r, *s);
  return r;
}
#define arrputs(r,s) (r = arrputs2(r,s))

char *normalize_method_name(char *p) {
  char *r = 0;
  for ( ; *p; p++) {
    if (*p == '\"') continue;
    if (*p == '[' && p[1] == ']') {
      if (p[2] == '=') {
        arrputs(r, "_set_");
        p++;
      } else {
        arrputs(r, "_get_");
      }
      p++;
      continue;
    }

    char *s = (uint32_t)*p < 128 ? quotetbl[*p] : 0;
    if (!s) {
      arrput(r, *p);
    } else {
      arrput(r, '_');
      for (; *s; s++) arrput(r, *s);
      arrput(r, '_');
    }
  }
  arrput(r, 0);
  return r;
}

int patch_quoted_method_name(uint8_t *in, int i, FILE *out) {
  char *p = (char*)in;
  char *r = NULL;
  for (i++ ; in[i] != '\"'; i++) {
    arrput(r, in[i]);
  }
  arrput(r, 0);
  i++;
  fprintf(out, "%s", normalize_method_name(r));
  return i;
}


static int issymchr(int c) {
  return isalnum(c) || c == '_';
}

//FIXME: has_proto_tbl should be part of apply_patch state.
struct { char *key; int value; } *has_proto_tbl = NULL;

//FIXME: use #line directive. it would require wrapping in inside getc.
int apply_patch(uint8_t *in, int start, int end, FILE *out) {
  int i;
  for (i = start; i < end; i++) {
    patch_t *p = patch_map[i];
    if (p) {
      patch_map[i] = p->next;
    } else {
      fputc(in[i], out);
      continue;
    }
    if (p->type == P_MCALL) {
      uint32_t flags = p->as[4].i;
      int is_lval = (flags&PF_LVAL) && (flags&PF_REF);
      int is_mp = !(flags&PF_LVAL) && (flags&PF_REF);
      int is_sink = flags&PF_SINK;
      char *mclass = is_sink ? p->as[5].s : p->as[2].s;
      if (is_mp && !is_sink) {
        fprintf(out, "%s_mp_%s(", mclass, p->as[3].s);
      } else {
        fprintf(out, "%s_m_%s(", mclass, p->as[3].s);
      }
      if (is_sink) {
        if (is_mp) {
          fprintf(out, "%s_mp__dot_(", p->as[2].s);
        } else {
          fprintf(out, "%s_m__dot_(", p->as[2].s);
        }
      }
      if (is_lval) fprintf(out, "&(");
      int j = p->as[0].i;
      i = apply_patch(in, i, j, out);
      if (is_lval) fprintf(out, ")");
      if (is_sink) fprintf(out, ")");
      if (flags&PF_FIELD) fprintf(out, ")");
      if ((flags&0xFF) == 1) fprintf(out, ",");
      i = p->as[1].i-1;
      if (flags&PF_FIELD) i -= 1;
    } else if (p->type == P_SCALL) { //setter call
      cnode_t *rval = p->as[1].p;
      fprintf(out, "%s_m_", p->as[2].s);
      patch_quoted_method_name((uint8_t*)p->as[3].s, 0, out);
      fprintf(out, "(");
      if (p->as[4].i&PF_REF) fprintf(out, "&(");
      int j = p->as[0].i;
      i = apply_patch(in, i, j, out);
      if (p->as[4].i&PF_REF) fprintf(out, ")");
      cnode_t *key = p->as[5].p;
      if (key) {
        fprintf(out, ",");
        apply_patch(in, key->sofs, key->eofs, out);
      }
      fprintf(out, ",");
      i = apply_patch(in, rval->sofs, rval->eofs, out); //copy r-value
      fprintf(out, ")");
      i -= 1;
    } else if (p->type == P_MDEF) {
      //FIXME: emit line numbers
      char *name = p->as[5].s;
      int got_proto = shget(has_proto_tbl,name);
      int si = i;
      int is_proto = 0;

      while (in[i]!='{' && in[i]!=';' && i < end) i++;
      int proto_end = i;
      if (in[i]==';') {
        is_proto = 1;
      }

      if (got_proto) {
        is_proto = 0;
      }
      for (int j = 0; j < 4; j++) {
        //j==0: prototype of the original method
        //j==1: arglist of the _mp_ method
        //j==2: body of the _mp_ method
        //j==3: original method
        if (is_proto && j == 3) continue;
        if (got_proto && j != 3) continue;
        i = si;
        int k = i;
        int needs_static = 1;
        int needs_return = 1;
        while (in[k]!='.') {
          if (!issymchr(in[k])) {
            k++;
            continue;
          }
          if (begins_with("static ", (char*)&in[k])) {
            needs_static = 0;
            k += 7;
            continue;
          } else if (begins_with("void ", (char*)&in[k])) {
            k += 5;
            while (isspace(in[k])) k++;
            if (issymchr(in[k])) needs_return = 0;
            continue;
          } else {
            while (issymchr(in[k])) k++; //skip this symbol
          }
        }
        if (j == 1 && needs_static) fprintf(out, "static ");

        if (j == 2) {
          while (in[i]!='.') i++;
          fprintf(out, "%s", p->as[0].s);
        } else {
          for (; in[i]!='.'; i++) {
            if (in[i] == '&') fputc('*', out);
            else fputc(in[i], out);
            
          }
        }

        if (j!=1) fprintf(out, "_m_");
        else fprintf(out, "_mp_");
        i++;
        while (in[i] == ' ') i++;
        if (in[i] == '\"') {
          i = patch_quoted_method_name(in, i, out);
        }
        while (in[i] != '(' && in[i] != '{' && in[i] != ';'
               && !(in[i] == ' ' && in[i+1] == '{')) {
          fputc(in[i++], out);
        }
        char *this;
        if (j==0 || j==3) this = "*this";
        else if (j == 2) this = "&this";
        else this = "this";
        int isfield = 0;
        if (in[i] == '(') {
          fputc(in[i], out);
          if (j != 2) {
            fprintf(out, "%s %s", p->as[0].s, this);
          } else {
            fprintf(out, "%s", this);
          }
          if (p->as[4].i) fprintf(out, ",");
        } else {
          isfield = 1;
          if (j != 2) {
            fprintf(out, "(%s %s)", p->as[0].s, this);
          } else {
            fprintf(out, "(%s)", this);
          }
          i--;
        }
        if (j==0 || j==1) {
          i++;
          for (; in[i] != ';' && in[i] != '{'; i++) {
            if (in[i] == '&') fputc('*', out);
            else fputc(in[i], out);
          }
        } else if (j==2) {
          i++;
          while (in[i] != ';' && in[i] != '{') {
            if (in[i] == ',' || in[i] == ')') {
              int k = i-1;
              while (isspace(in[k])) --k;
              int e = k;
              while (issymchr(in[k])) --k;
              k++;
              e++;
              while (k < e) fputc(in[k++], out);
              if (in[i] == ',') fputc(in[i++], out);
            }
            i++;
          }
        }
        if (j==0) {
          fprintf(out, ";");
        } else if (j == 1) {
          if (needs_return) {
            fprintf(out, "{return ");
          } else {
            fprintf(out, "{");
          }
        } else if (j == 2) {
          if (!isfield) fprintf(out, ")");
          fprintf(out, ";}");
        }
      }
      if (is_proto) {
        shput(has_proto_tbl,name,1);
        i = proto_end;
      }
    } else if (p->type == P_NOT_CLASS) {
      i = p->as[0].i-1;
    } else if (p->type == P_CLASS_TD) {
      fprintf(out, "typedef struct %s %s", p->as[1].s, p->as[1].s);
      i = p->as[0].i-1;
    } else if (p->type == P_CLASS) {
      fprintf(out, "typedef struct ");
      i = p->as[0].i-1;
    } else if (p->type == P_CLASS_END) {
      char *cname = p->as[0].s;
      fprintf(out, " %s;", cname);
      class_field_t *fs = get_fields(cname);

      fprintf(out, " static void %s_m_ctors_(%s *this){", cname, cname);
      for (int i = 0; i < arrlen(fs); i++) {
        cnode_t *type = fs[i].type;
        cnode_t *decl = fs[i].decl;
        if (!cn_isref(type) && !ptr_level(decl)) {
          char *tn = cn_typename(type);
          if (tn) {
            cnode_t *name = decl_name(decl);
            char *mname = sjoin(tn, "_m_ctor");
            if (get_method(mname)) {
              fprintf(out, "%s_m_ctor(&this->%s);", tn, name->text);
            }
          }
        }
      }
      fprintf(out, "}");

      fprintf(out, " static void %s_m_dtors_(%s *this){", cname, cname);
      for (int i = (int)arrlen(fs)-1; i >= 0; i--) {
        cnode_t *type = fs[i].type;
        cnode_t *decl = fs[i].decl;
        if (!cn_isref(type) && !ptr_level(decl)) {
          char *tn = cn_typename(type);
          if (tn) {
            cnode_t *name = decl_name(decl);
            char *mname = sjoin(tn, "_m_dtor");
            if (get_method(mname)) {
              fprintf(out, "%s_m_dtor(&this->%s);", tn, name->text);
            }
          }
        }
      }
      fprintf(out, "}");

      fputc(in[i], out);
    } else if (p->type == P_OLD_OPEN || p->type == P_OLD_CLOSE) {
      i = p->as[0].i-1;
    } else if (p->type == P_AUTO) {
      fprintf(out, "%s", p->as[0].s);
      i = p->as[1].i-1;
    } else if (p->type == P_REF) {
      fprintf(out, "(*");
      i = apply_patch(in, i, p->as[0].i, out);
      fprintf(out, ")");
      i--;
    } else if (p->type == P_REF_DECL) {
      int eofs = p->as[0].i;
      for ( ; i < eofs; i++) {
        if (in[i] == '&') fputc('*', out);
        else fputc(in[i], out);
      }
      i--;
    } else if (p->type == P_REF) {
      i = p->as[0].i-1;
    } else if (p->type == P_FIELD_ID) {
      fprintf(out, "this->");
      i--;
    } else if (p->type == P_CTOR) {
      fprintf(out, "%s(&%s);", p->as[1].s, p->as[2].s);
      i--;
    } else if (p->type == P_DTOR_RET || p->type == P_DTOR_BLOCK) {
      sym_t **ss = p->as[1].p;
      char *exclude = p->as[2].s;
      if (p->type == P_DTOR_RET) fprintf(out, "{");
      for (int k = 0; k < arrlen(ss); k++) {
        sym_t *s = ss[k];
        char *tn = cn_typename(s->type);
        char *dn = s->name;
        //exclude the value returned
        if (exclude && !strcmp(exclude, dn)) continue;
        fprintf(out, "%s_m_dtor(&%s);", tn, dn);
      }
      i--;
    } else if (p->type == P_DTOR_RET2) {
      fprintf(out, "}");
      i--;
    } else if (p->type == P_DTOR_RET_COPY) {
      fprintf(out, "%s %s = ", p->as[5].s, p->as[4].s);
      i = apply_patch(in, p->as[2].i, p->as[3].i, out);
      fprintf(out, ";");
      fprintf(out, "%s %sr;", p->as[5].s, p->as[4].s);
      fprintf(out, "%s(&(%sr),&(%s));", p->as[6].s, p->as[4].s, p->as[4].s);
      sym_t **ss = p->as[1].p;
      if (p->type == P_DTOR_RET) fprintf(out, "{");
      for (int k = 0; k < arrlen(ss); k++) {
        sym_t *s = ss[k];
        char *tn = cn_typename(s->type);
        char *dn = s->name;
        fprintf(out, "%s_m_dtor(&%s);", tn, dn);
      }
      fprintf(out, "return %sr;", p->as[4].s);
      i = p->as[0].i;
      i--;
    } else if (p->type == P_STOR) {
      fprintf(out, "%s(&(", normalize_method_name(p->as[3].s));
      i = apply_patch(in, i, p->as[0].i, out); 
      fprintf(out, "),(");
      i = apply_patch(in, p->as[1].i, p->as[2].i, out); 
      fprintf(out, "))");
      i--;
    } else if (p->type == P_INDEX) {
      cnode_t *obj = p->as[1].p;
      cnode_t *key = p->as[2].p;
      fprintf(out, "%s(&", normalize_method_name(p->as[3].s));
      i = apply_patch(in, obj->sofs, obj->eofs, out);
      fprintf(out, ",");
      i = apply_patch(in, key->sofs, key->eofs, out);
      fprintf(out, ")");
      i = p->as[0].i;
      i--;
    } else if (p->type == P_INJECT) {
      fprintf(out, "%s", p->as[0].s);
      i--;
    } else if (p->type == P_ERASE) {
      i = p->as[0].i;
      i--;
    }
  }
  return i;
}
