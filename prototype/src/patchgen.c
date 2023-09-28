#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "cnode.h"
#include "parser.h"
#include "util.h"
#include "sym.h"
#include "patch.h"
#include "patchgen.h"


static int idcount = 0;

char *genid() {
  char buf[32];
  sprintf(buf, "%d", idcount++);
  return strdup(buf);
}


static int *break_levels = 0;

void open_break_level() {
  arrput(break_levels, scope_depth());
}

void close_break_level() {
  arrpop(break_levels);
}

int break_level() {
  if (!break_levels) return 0;
  return arrlast(break_levels);
}

static cnode_t **block_stack = 0;
static int *block_levels = 0;


void open_block(cnode_t *block) {
  push_block();
  arrput(block_stack, block);
  arrput(block_levels, scope_depth());
}

void close_block() {
  arrpop(block_stack);
  arrpop(block_levels);
  pop_block();
}

cnode_t *cur_block() {
  if (!block_stack) return 0;
  return arrlast(block_stack);
}

cnode_t *find_label(cnode_t *n) {
  if (!n) return 0;
  if (n->id == N_LABEL) return n;
  cnode_t *l = find_label(n->head);
  if (l) return l;
  return find_label(n->tail);
}

int find_label_level(char *name, cnode_t **label) {
  for (int i = arrlen(block_stack)-1; i >= 0; i--) {
    cnode_t *l = find_label(block_stack[i]);
    if (!l) continue;
    if (strcmp(l->head->text, name)) continue;
    *label = l;
    return block_levels[i];
  }
  return -1;
}

static char *in;

static sym_t *pg_var(char *name, char *tname, int ptr, int is_ref);

cnode_t *cn_isref(cnode_t *n) {
  for (; n; n = n->tail) if (n->id == N_REF) return n;
  return 0;
}

int decl_plain_id(cnode_t *decl) {
  return decl->head && decl->head->id == (IDENTIFIER|N_TERM);
}

int cn_direct(cnode_t *decl) {
  return !ptr_level(decl) && !cn_isref(decl) && decl_plain_id(decl);
}


int cn_isref_name(char *name) {
  sym_t *s = lookup(name);
  if (!s) return 0;
  return !(s->flags&SYM_REFHACK) && cn_isref(s->decl);
}

void pg_patch_ref_decl(cnode_t *decl) {
  if (cn_isref(decl)) {
    patch_t *p = new_patch(P_REF_DECL, decl->sofs);
    p->as[0].i = decl->eofs;
  }
}

int ptr_level(cnode_t *n) {
  int level = 0;
  for (cnode_t *x = n->tail; x; x = x->tail) {
    if (x->id == N_PTR) level++;
  }
  for (cnode_t *x = n->head; x; x = x->head) {
    if (x->id == N_ARRAY) level++;
    else break;
  }
  return level;
}

#define STRUCT_KIND(n) ((n)->head->head)
#define STRUCT_NAME(n) ((n)->head->tail)

char *cn_typename(cnode_t *xs) {
  for (cnode_t *x = xs; x; x = x->tail) {
    cnode_t *n = x->head;

    if (n->id == N_STRUCT) {
      return STRUCT_NAME(n)->text;
    } else if (x->id==N_TYPE_STOR) {
    } else if (x->id==N_TYPE_SPEC) {
      return n->text;
    } else if (x->id==N_TYPE_QUAL) {
    }
  }
  return 0;
}


#define FN_TYPE(n) ((n)->tail->head)
#define FN_DECLARATOR(n) ((n)->head)
#define FN_ARGS(n) ((n)->head->tail)
#define FN_BODY(n) ((n)->tail->tail)
#define ARG_TYPE(n) ((n)->head)
#define ARG_DECL(n) ((n)->tail)



static void pg_decl(cnode_t *n);


int pg_declof_ptr_lv;
int pg_declof_isfield;
int pg_declof_lval;

//FIXME: this should really be cn_declof
sym_t *pg_declof2(cnode_t *n) {
  if (!n) return 0;
  if (n->id == N_BLOCK) { //for GCC block expressions
    return 0;
  } else if (n->id == (IDENTIFIER|N_TERM)) {
    sym_t *s = lookup(n->text);
    if (s) {
      pg_declof_lval = 1;
      return s;
    } else {
      return 0;
    }
  } else if (n->id == N_EXPR) {
    return 0;
  } else if (n->id == N_BEXPR) {
    for (; n && n->id==N_BEXPR ; n = n->tail) {
      sym_t *decl = pg_declof2(n->head);
      if (decl) return decl;
    }
    if (n) {
      return pg_declof2(n);
    }
    return 0;
  } else if (n->id == N_DECL) {
    return 0;
  } else if (n->id == N_UNARY) {
    char c = n->head->text[0];
    if (c == '*') pg_declof_ptr_lv--;
    else if (c == '&') pg_declof_ptr_lv++;
    return pg_declof2(n->tail);
  } else if (n->id == N_INDEX) {
    cnode_t *obj = n->head;
    cnode_t *key = n->tail;
    int sptr = pg_declof_ptr_lv;
    sym_t *s = pg_declof2(obj);
    int objptr = pg_declof_ptr_lv;
    pg_declof_ptr_lv = sptr;
    if (s && !(ptr_level(s->decl)+objptr) && decl_plain_id(s->decl)) {
      char *tn = cn_typename(s->type);
      char *mname = sjoin(tn, "_m_\"[]\"");
      sym_t *sm = 0;
      if (get_method(mname)) sm = lookup(mname);
      free(mname);
      if (sm) return sm;
    }
    //else usual non-redefined []
    pg_declof_ptr_lv--;
    return s;
  } else if (n->id & N_TERM) {
    return 0;
  } else if (n->id == N_SIZEOF) {
    return lookup("_cext__int");
  } else if (n->id == N_CAST) {
    cnode_t *type = n->head->tail;
    cnode_t *decl = n->head->head;
    if (decl) decl = decl->tail;
    yyltype_t loc;
    memset(&loc, 0, sizeof(loc));
    cnode_t *ident = cnode(IDENTIFIER|N_TERM, 0, 0, &loc);
    ident->text = strdup("_cext__tmp");
    cnode_t *d = cnode(N_DECLARATOR ,ident, decl, &loc);
    return push_decl(type, d);
  } else if (n->id == N_LIT) {
    if (n->head->id == (I_CONSTANT|N_TERM)) {
      return lookup("_cext__int");
    } else if (n->head->id == (F_CONSTANT|N_TERM)) {
      if (n->head->text[strlen(n->head->text)-1] == 'f') {
        return lookup("_cext__float");
      } else {
        return lookup("_cext__double");
      }
    } else if (n->head->id == (STRING_LITERAL|N_TERM)) {
      return lookup("_cext__char_ptr");
    } else if (n->head->id == N_SIZEOF) {
      return lookup("_cext__int");
    }
    return 0;
  } else if (n->id == N_DOT || n->id == N_ARROW) {
    sym_t *s = 0;
    int slval = pg_declof_lval;
    int sptr = pg_declof_ptr_lv;
    pg_declof_ptr_lv = 0;
    sym_t *l = pg_declof2(n->head);
    int expr_plv = pg_declof_ptr_lv;
    pg_declof_ptr_lv = sptr;
    if (!l) goto dot_end;
    char *name = n->tail->text;
    char *tname = cn_typename(l->type);
    if (!tname) goto dot_end;
    char *mname;
    int plv = ptr_level(l->decl) + expr_plv;
    if ((n->id == N_DOT && plv != 1) || (n->id == N_ARROW && plv == 1)) {
      mname = sjoin3(tname, "_mf_", name); //field accessor
      s = lookup(mname);
      free(mname);
      if (s) {
        slval = 1; //fields are l-values.
        goto dot_end;
      }
    }
    mname = sjoin3(tname, "_m_", name);
    s = lookup(mname);
    free(mname);
dot_end:
    pg_declof_ptr_lv = sptr;
    pg_declof_lval = slval;
    return s;
  } else if (n->id == N_CALL) {
    sym_t *s = 0;
    int slval = pg_declof_lval;
    int sptr = pg_declof_ptr_lv;
    if (n->head->id != N_DOT) {
      s = pg_declof2(n->head);
      goto call_end;
    }
    n = n->head;
    sym_t *l = pg_declof2(n->head);
    if (!l) goto call_end;
    //sptr += ptr_level(l->decl);
    char *name = n->tail->text;
    char *tname = cn_typename(l->type);
    if (!tname) goto call_end;
    char *mname;
    mname = sjoin3(tname, "_m_", name);
    s = lookup(mname);
    free(mname);
call_end:;
    pg_declof_ptr_lv = sptr;
    pg_declof_lval = slval;
    return s;
  }
  return 0;
}

sym_t *pg_declof(cnode_t *n) {
  pg_declof_ptr_lv = 0;
  pg_declof_isfield = 0;
  pg_declof_lval = 0;
  return pg_declof2(n);
}

void pg_expr(cnode_t *n);

patch_t *pg_mcall2(cnode_t *m, cnode_t *d, cnode_t *args, cnode_t *obj, sym_t *s
              ,uint32_t flags) {
  cnode_t *mname = d->tail;
  patch_t *p = new_patch(P_MCALL, m->sofs);
  p->as[0].i = obj->eofs;
  p->as[1].i = args ? args->sofs : d->eofs+1;
  p->as[2].s = strdup(cn_typename(s->type));
  p->as[3].s = strdup(mname->text);
  p->as[4].i = args ? 1 : 0;
  p->as[4].i |= flags;
  return p;
}

int pg_mcall(cnode_t *n, cnode_t *d, cnode_t *args, uint32_t flags) {
  cnode_t *obj = d->head;
  sym_t *s = pg_declof(obj);
  int dolv = pg_declof_lval;

  if (!s) return 0;

  if (ptr_level(s->decl)+pg_declof_ptr_lv == 1) {
    pg_mcall2(n, d, args, obj, s, flags);
    return 1;
  }

  char *tname = cn_typename(s->type);
  if (!tname) return 0;
  char *name = d->tail->text;
  char *mname = sjoin3(tname, "_m_", name);

  int is_mcall = 0;
  if (get_method(mname)) {
    is_mcall = 1;
    flags |= PF_REF;
    if (dolv) flags |= PF_LVAL;
    pg_mcall2(n, d, args, obj, s, flags);
  }
  free(mname);
  if (is_mcall) return is_mcall;

  mname = sjoin(tname, "_m_\".\"");
  if (get_method(mname)) {
    sym_t *ms = lookup(mname);
    if (ms) {
      is_mcall = 1;
      flags |= PF_REF;
      if (dolv) flags |= PF_LVAL;
      flags |= PF_SINK;
      patch_t *p = pg_mcall2(n, d, args, obj, s, flags);
      p->as[5].s = cn_typename(ms->type);
      return 1;
    }
  }

  return 0;
}

void pg_call(cnode_t *n) {
  cnode_t *d = n->head;
  cnode_t *args = n->tail;
  int is_mcall = 0;
  if (d->id == N_DOT) {
    is_mcall = pg_mcall(n, d, args, 0);
  }
  if (is_mcall) {
    pg_expr(d->head);
  } else {
    pg_expr(d);
  }

  for (cnode_t *x = args; x; x = x->tail) {
    pg_expr(x->head);
  }
}

void pg_dot(cnode_t *d) {
  pg_mcall(d, d, 0, PF_FIELD);
  pg_expr(d->head);
}

//setter method call
patch_t *pg_mcalls(cnode_t *m, char *name, cnode_t *rvl, cnode_t *obj, sym_t *s
                        , int is_ref) {
  patch_t *p = new_patch(P_SCALL, m->sofs);
  p->as[0].i = obj->eofs;
  p->as[1].p = rvl;
  p->as[2].s = strdup(cn_typename(s->type));
  p->as[3].s = strdup(name);
  p->as[4].i = 0;
  if (is_ref) p->as[4].i |= PF_REF;
  return p;
}

void pg_index(cnode_t *n) {
  cnode_t *obj = n->head;
  cnode_t *key = n->tail;
  sym_t *s = pg_declof(obj);

  if (s && !(ptr_level(s->decl)+pg_declof_ptr_lv) && decl_plain_id(s->decl)) {
    char *tn = cn_typename(s->type);
    char *mname = sjoin(tn, "_m_\"[]\"");
    if (get_method(mname)) {
      //first patch references
      sym_t *sm = lookup(mname);
      if (!has_patch(P_REF, n->sofs)) {
        if (sm && cn_isref(sm->decl)) {
          patch_t *p = new_patch(P_REF, n->sofs);
          p->as[0].i = n->eofs;
        }
      }
      //now patch the index itself
      patch_t *p = new_patch(P_INDEX, n->sofs);
      p->as[0].i = n->eofs;
      p->as[1].p = obj;
      p->as[2].p = key;
      p->as[3].s = mname;
    }
  }

  pg_expr(obj);
  pg_expr(key);
}

void pg_assign(cnode_t *n) {
  cnode_t *d = n->head;
  cnode_t *op = n->tail->head;
  cnode_t *r = n->tail->tail;

  int sid = d->id;
  sym_t *sd = pg_declof(d);
  if (!sd) {
    pg_expr(d);
    pg_expr(r);
    return;
  }

  if (d->id != N_DOT && d->id != N_INDEX) {
    char *tn = cn_typename(sd->type);
    char *top = sjoin3("\"", op->text, "\"");
    char *mname = sjoin3(tn, "_m_", top);

    if (get_method(mname)) {
      patch_t *p = new_patch(P_STOR, n->sofs);
      p->as[0].i = op->sofs;
      p->as[1].i = r->sofs;
      p->as[2].i = n->eofs;
      p->as[3].s = mname;
    }
    goto end;
  }

  if (ptr_level(d) > 0) goto end;

  d->id = N_BEXPR; //hack to make pg_expr process it properly.

  cnode_t *obj = d->head;
  sym_t *s = pg_declof(obj);
  int dpl = pg_declof_ptr_lv;
  if (!s) goto end;

  char *name = d->tail->text;

  if (sid == N_INDEX) {
    if (ptr_level(s->decl)+dpl) goto end;
    char *tname = cn_typename(s->type);
    char *top = sjoin4("\"", name, "[]=", "\"");
    char *mname = sjoin3(tname, "_m_", top);
    if (get_method(mname)) {
      patch_t *p = pg_mcalls(n, top, r, obj, s, 1);
      p->as[5].p = d->tail;
    } else {
      d->id = sid; //have to process it as a usual []
    }
    goto end;
  }

  char *top = sjoin4("\"", name, op->text, "\"");

  if (ptr_level(s->decl)+dpl == 1) {
    pg_mcalls(n, top, r, obj, s, 0);
  } else {
    char *tname = cn_typename(s->type);
    char *mname = sjoin3(tname, "_m_", top);
    if (get_method(mname)) {
      pg_mcalls(n, top, r, obj, s, 1);
    }
    free(mname);
  }
  free(top);

end:;
  int ref_assign = 0;

  if (d->id == N_UNARY && d->head->id == ('&'|N_TERM)) {
    if (sd) {
      patch_t *p = new_patch(P_REM_REF, d->head->sofs);
      p->as[0].i = d->head->eofs;
      ref_assign = 1;
      sd->flags |= SYM_REFHACK;
    }
  }
  pg_expr(d);
  pg_expr(r);

  d->id = sid;

  if (!ref_assign && !has_patch(P_REF, d->sofs)) {
    if (sd && cn_isref(sd->decl)) {
      patch_t *p = new_patch(P_REF, d->sofs);
      p->as[0].i = d->eofs;
    }
  }
  if (ref_assign) {
    sd->flags &= ~SYM_REFHACK;
  }
}


void pg_block(cnode_t *xs) {
  open_block(xs);

  for (cnode_t *n = xs->head; n ; n = n->tail) {
    pg_expr(n->head);
  }

  sym_t **ss = sbrm_above(scope_depth()-1);
  if (ss) {
    patch_t *p = new_patch(P_DTOR_BLOCK, xs->eofs-1);
    p->as[0].i = xs->eofs;
    p->as[1].p = ss;
  }

  close_block();
}

void pg_expr(cnode_t *n) {
  if (!n) return;
  switch(n->id) {
  case N_BLOCK:
    pg_block(n);
    break;
  case IDENTIFIER|N_TERM: {
    if (cn_isref_name(n->text)) {
      patch_t *p = new_patch(P_REF, n->sofs);
      p->as[0].i = n->eofs;
    }
    sym_t *s = lookup(n->text);
    if (s && (s->flags&SYM_FIELD)) {
      patch_t *p = new_patch(P_FIELD_ID, n->sofs);
      p->as[0].i = n->eofs;
    }
    break;}
  case N_EXPR:
  case N_BEXPR:
    for (; n; n = n->tail) {
      if (!(n->id==N_EXPR || n->id == N_BEXPR)) break;
      pg_expr(n->head);
    }
    if (n) {
      pg_expr(n);
    }
    break;
  case N_ASSIGN:
    pg_assign(n);
    break;
  case N_DECL:
    pg_decl(n);
    break;
  case N_UNARY:
    pg_expr(n->tail);
    break;
  case N_INDEX:
    pg_index(n);
    break;
  case N_CAST:
    pg_expr(n->tail);
    break;
  case N_SIZEOF:
    pg_expr(n->head);
    break;
  case N_LIT:
    break;
  case N_DOT: {
    sym_t *s = pg_declof(n);
    if (s && !(s->flags&SYM_REFHACK) && cn_isref(s->decl)) {
      patch_t *p = new_patch(P_REF, n->sofs);
      p->as[0].i = n->eofs;
    }
    pg_dot(n);
    break;}
  case N_ARROW:
    pg_expr(n->head);
    if (n->tail->id != (IDENTIFIER|N_TERM)) pg_expr(n->tail);
    break;
  case N_CALL:
    pg_call(n);
    break;
  case N_RETURN: {
    sym_t **ss = sbrm_above(1);
    if (ss) {
      sym_t *rs = pg_declof(n->head);
      int ret_copy = 0;
      char *tn = 0;
      char *exclude = 0;
      if (rs && cn_direct(rs->decl)) tn = cn_typename(rs->type);
      if (tn && is_classname(tn)) {
        char *mname = sjoin3(tn, "_m_ctor_", tn);
        if (get_method(mname)) {
          ret_copy = 1;
          patch_t *p = new_patch(P_DTOR_RET_COPY, n->sofs);
          p->as[0].i = n->eofs;
          p->as[1].p = ss;
          p->as[2].i = n->head->sofs;
          p->as[3].i = n->head->eofs;
          p->as[4].s = sjoin("_ret__", genid());
          p->as[5].s = tn;
          p->as[6].s = mname;
        } else {
          char *mname = sjoin(tn, "_m_ctor");
          if (get_method(mname)) {
            exclude = decl_name(rs->decl)->text;
          }
        }
      }
      if (!ret_copy) {
        patch_t *p = new_patch(P_DTOR_RET, n->sofs);
        p->as[0].i = n->eofs;
        p->as[1].p = ss;
        p->as[2].s = exclude;
      }
      patch_t *p = new_patch(P_DTOR_RET2, n->eofs);
    }
    pg_expr(n->head);
    break;}
  case N_BREAK:
  case N_CONTINUE: {
    sym_t **ss = sbrm_above(break_level());
    if (ss) {
      patch_t *p = new_patch(P_DTOR_RET, n->sofs);
      p->as[0].i = n->eofs;
      p->as[1].p = ss;

      p = new_patch(P_DTOR_RET2, n->eofs);
    }
    pg_expr(n->head);
    break;}
  case N_GOTO: {
    cnode_t *label;
    int level = find_label_level(n->head->text, &label);
    if (level == -1) return;
    sym_t **ss = sbrm_above_or_below_offset(level, label->sofs);
    if (ss) {
      patch_t *p = new_patch(P_DTOR_RET, n->sofs);
      p->as[0].i = n->eofs;
      p->as[1].p = ss;

      p = new_patch(P_DTOR_RET2, n->eofs);
    }
    break;}
  case N_IF:
    pg_expr(n->head);
    pg_expr(n->tail->head);
    pg_expr(n->tail->tail);
    break;
  case N_SWITCH:
    open_break_level();
    pg_expr(n->head);
    pg_expr(n->tail);
    close_break_level();
    break;
  case N_WHILE:
    open_break_level();
    pg_expr(n->head);
    pg_expr(n->tail);
    close_break_level();
    break;
  case N_DOWHILE:
    open_break_level();
    pg_expr(n->head);
    pg_expr(n->tail);
    close_break_level();
    break;
  case N_FOR:
    open_break_level();
    pg_expr(n->head);
    pg_expr(n->tail);
    close_break_level();
    break;
  case N_CONS:
    pg_expr(n->head);
    pg_expr(n->tail);
    break;
  case N_LABEL:
    pg_expr(n->tail);
    break;
  default:
    if (n->id&N_TERM) {
      break;
    }
    break;
  }
}

static cnode_t *pg_scope(cnode_t *xs) {
  for (cnode_t *x = xs; x; x = x->tail) {
    if (x->id==N_MSCOPE) return x->head;
  }
  return 0;
}

static void pg_fn_args(cnode_t *n) {
  n = n->head;
  if (n->id != N_DECL_FN) return;
  for (cnode_t *m = n->tail; m; m = m->tail) {
    cnode_t *a = m->head;
    if (a && a->tail) {
      cnode_t *type = a->head;
      cnode_t *decl = a->tail;
      push_decl(type, decl);
      pg_patch_ref_decl(decl);
    } else {
      //FIXME
    }
  }
}

static int pg_fn_count_args(cnode_t *n) {
  n = n->head;
  if (n->id != N_DECL_FN) return 0;
  int c = 0;
  for (cnode_t *m = n->tail; m; m = m->tail) {
    c++;
  }
  return c;
}


static yyltype_t cnode_loc(cnode_t *n) {
  yyltype_t l;
  l.srow = n->srow;
  l.scol = n->scol;
  l.sofs = n->sofs;
  l.erow = n->erow;
  l.ecol = n->ecol;
  l.eofs = n->eofs;
  return l;
}


static void pg_fn(cnode_t *n) {
  cnode_t *scope = pg_scope(FN_TYPE(n));

  char *name = decl_name(n->head)->text;

  if (scope) {
    name = sjoin3(scope->text, "_m_", name);
    char *q = name+strlen(name)-1;
    while (q>name && isspace(*q)) {
      *q = 0;
      q--;
    }

    push_decl2(name, FN_TYPE(n), n->head);
    yyltype_t loc = cnode_loc(n);
    cnode_t *ident = cnode(IDENTIFIER|N_TERM, 0, 0, &loc);
    ident->text = strdup("this");
    cnode_t *d =
      cnode(N_DECLARATOR
         ,ident
         ,cnode(N_PTR, 0, 0, &loc)
         ,&loc);
    cnode_t *tdn = cnode(TYPEDEF_NAME|N_TERM, 0, 0, &loc);
    tdn->text = strdup(scope->text);
    cnode_t *t = cnode(N_TYPE_SPEC, tdn, 0, &loc);
    push_decl(t, d);
  } else {
    pg_patch_ref_decl(n->head);
    push_decl2(name, FN_TYPE(n), n->head);
  }

  push_block();

  if (scope) {
    class_field_t *fs = get_fields(scope->text);
    for (int i = 0; i < arrlen(fs); i++) {
      cnode_t *type = fs[i].type;
      cnode_t *decl = fs[i].decl;
      sym_t *s = push_decl(type, decl);
      s->flags |= SYM_FIELD;
    }
  }


  pg_fn_args(n->head);
  pg_expr(FN_BODY(n));
  pop_block();

  if (scope) {
    patch_t *p = new_patch(P_MDEF, n->sofs);
    set_method(name, n);
    p->as[0].s = strdup(scope->text);
    p->as[1].i = scope->sofs;
    p->as[2].i = n->head->sofs; //args start
    p->as[3].i = n->head->eofs; //args end
    p->as[4].i = pg_fn_count_args(n->head);
    p->as[5].s = strdup(name);
  }
}

static void pg_vars(cnode_t *type, cnode_t *xs) {
  for (cnode_t *x = xs; x; x = x->tail) { //x->id==N_VARS list
    cnode_t *n = x->head;
    cnode_t *decl = n->head;

    sym_t *s = push_decl(type,decl);
    pg_patch_ref_decl(decl);

    char *tn = cn_typename(type);
    cnode_t *init_expr = n->tail;

    if (init_expr) {
      pg_expr(init_expr);
    }
    if (is_classname(tn)) {
      char *mname = sjoin(tn, "_m_ctor");
      sym_t *ms = lookup(mname);
      if (ms && cn_direct(decl) && scope_depth()>1) {
        s->flags |= SYM_SBRM;
        if (!init_expr) {
          char *q = in+xs->eofs;
          while(*q && *q != ';') q++;
          if (*q == ';') q++;
          patch_t *p = new_patch(P_CTOR, q-in);
          p->as[0].i = n->eofs;
          p->as[1].s = strdup(mname);
          p->as[2].s = strdup(decl_name(decl)->text);
        }
      }
    }
  }
}

static void pg_reg_class_fields(char *cname, cnode_t *xs, int isclass) {
  class_field_t *fields = NULL;

  for (cnode_t *x = xs; x; x = x->tail) {
    cnode_t *sd = x->head; //struct_declaration
    if (!sd->tail) continue;
    cnode_t *type = sd->head;
    for (cnode_t *y = sd->tail; y; y = y->tail) {
      cnode_t *decl = y->head; //struct_declarator
      pg_patch_ref_decl(decl);
      cnode_t *name = decl_name(decl);
      if (!name) continue;
      char *mname = sjoin3(cname, "_mf_", name->text);
      push_decl2(mname, type, decl);
      class_field_t f;
      f.type = type;
      f.decl = decl;
      arrput(fields, f);
    }
  }
  if (isclass) set_fields(cname, fields);
}

static void pg_class(cnode_t *n) {
  char *name = n->head->text;

  add_classname(name);

  if (!n->tail) {
    patch_t *p = new_patch(P_CLASS_TD, n->sofs);
    p->as[0].i = n->eofs;
    p->as[1].s = strdup(name);
    return;
  }

  pg_reg_class_fields(name, n->tail, 1);

  patch_t *p = new_patch(P_CLASS, n->sofs);
  p->as[0].i = n->head->sofs;

  p = new_patch(P_CLASS_END, n->eofs);
  p->as[0].s = strdup(name);
}

int anon_struct_count;

static void pg_struct(cnode_t *n, cnode_t *type, cnode_t *vars) {
  cnode_t *nnode = STRUCT_NAME(n);
  int anonymous = 0;
  char buf[128];

  char *name;
  if (nnode) {
    name = nnode->text;
  } else {
    anonymous = 1;
    sprintf(buf, "___anon_struct_%d", anon_struct_count++);
    name = buf;
  }

  if (!n->tail) {
    return;
  }

  if (!anonymous) {
    pg_reg_class_fields(name, n->tail, 0);
  }

  if (!is_typedef(type)) return;
  for (cnode_t *x = vars; x; x = x->tail) {
    cnode_t *var = x->head;
    if (ptr_level(var->head)) continue;
    cnode_t *tdname = decl_name(var->head); 
    if (!tdname) continue;
    if (!strcmp(tdname->text, name)) continue;
    pg_reg_class_fields(tdname->text, n->tail, 0);
  }
}


static cnode_t *is_struct(cnode_t *xs) {
  for (cnode_t *x = xs; x; x = x->tail) {
    cnode_t *n = x->head;
    if (x->id==N_TYPE_SPEC && n->id == N_STRUCT) return n;
  }
  return 0;
}

static void pg_vars_auto(char *tname, cnode_t *xs, int ptr, int is_ref) {
  for (cnode_t *x = xs; x; x = x->tail) { //x->id==N_VARS list
    cnode_t *n = x->head;
    cnode_t *name = decl_name(n->head);
    pg_var(name->text, tname, ptr, is_ref);
    if (n->tail) {
      pg_expr(n->tail);
    }
  }
}


static void pg_decl(cnode_t *n) {
  cnode_t *type = n->head;
  cnode_t *vars = n->tail;
  cnode_t *strc = is_struct(type);
  if (strc) {
    pg_struct(strc, type, vars);
    return;
  }
  if (!(   (type->id==N_TYPE_STOR && type->head->id == (AUTO|N_TERM))
        || (type->id==N_TYPE_SPEC && type->head->id == N_TYPEOF))) {
normal:
    pg_vars(type, vars);
    return;
  }
  
  int is_typeof = type->head->id == N_TYPEOF;
  cnode_t *expr = is_typeof ? type->head->head : vars->head->tail;
  sym_t *s = pg_declof(expr);
  if (!s) goto normal;
  int ptrc = pg_declof_ptr_lv;

  ptrc += ptr_level(s->decl);
  if (ptrc < 0) ptrc = 0;
  int is_ref = cn_isref(s->decl) != 0;

  if (vars->head && vars->head->head) { //"auto &var"
    cnode_t *decl = vars->head->head;
    cnode_t *ref = cn_isref(decl);
    if (ref) {
      if (ref) is_ref = 1;
      patch_t *p = new_patch(P_ERASE, ref->sofs);
      p->as[0].i = ref->eofs;
    }
  }

  char *tname = cn_typename(s->type);
  char *ps = malloc(ptrc+2);
  int i;
  for (i = 0; i < ptrc; i++) ps[i] = '*';
  if (is_ref) ps[i++] = '*';
  ps[i] = 0;
  char *ts = sjoin(tname,ps);
  free(ps);
  patch_t *p = new_patch(P_AUTO, n->sofs);
  p->as[0].s = ts;
  p->as[1].i = type->eofs;
  p->as[2].i = -1;
  if (is_ref && vars->head && vars->head->tail) {
    cnode_t *m = vars->head->tail;
    patch_t *p = new_patch(P_INJECT, m->sofs);
    p->as[0].s = "&";
  }
  pg_vars_auto(tname, vars, ptrc, is_ref);
}

static sym_t *pg_var(char *name, char *tname, int ptr, int is_ref) {
  yyltype_t loc;
  memset(&loc, 0, sizeof(loc));
  cnode_t *ident = cnode(IDENTIFIER|N_TERM, 0, 0, &loc);
  ident->text = strdup(name);
  cnode_t *ptr_node = 0;
  if (ptr) ptr_node = cnode(N_PTR, 0, 0, &loc);
  if (is_ref) ptr_node = cnode(N_REF, 0, ptr_node, &loc);
  cnode_t *d = cnode(N_DECLARATOR ,ident, ptr_node, &loc);
  cnode_t *tdn = cnode(TYPEDEF_NAME|N_TERM, 0, 0, &loc);
  tdn->text = strdup(tname);
  cnode_t *t = cnode(N_TYPE_SPEC, tdn, 0, &loc);
  return push_decl(t, d);
}

static void pg_push_default_types() {
  pg_var("_cext__char_ptr", "char", 1, 0);
  pg_var("_cext__int", "int", 0, 0);
  pg_var("_cext__float", "float", 0, 0);
  pg_var("_cext__double", "double", 0, 0);
}

//special case for handling a method prototype
static void pg_meth_proto(cnode_t *n) {
  cnode_t *scope = n->head->tail->head;
  cnode_t *type = n->head;
  cnode_t *decl = n->tail->head->head;
  if (decl->head->id != N_DECL_FN) { //no arglist version?
    yyltype_t loc = cnode_loc(decl->head);
    cnode_t *dfn = cnode(N_DECL_FN, decl->head, 0, &loc);
    dfn->text = strdup("");
    decl->head = dfn;
  }
  char *scopename = scope->text;
  char *methname = decl->head->head->text;

  char *name = sjoin3(scopename, "_m_", methname);

  push_decl2(name, type, decl);

  patch_t *p = new_patch(P_MDEF, n->sofs);
  set_method(name, n); //FIXME: incorrect, but currently `n` is unused
                       //       get_method only checks for existence
  p->as[0].s = strdup(scopename);
  p->as[1].i = scope->sofs;
  p->as[2].i = decl->head->head->eofs; //args start
  p->as[3].i = decl->eofs; //args end
  p->as[4].i = pg_fn_count_args(decl);
  p->as[5].s = strdup(name);
}


void patchgen(char *text, cnode_t *xs) {
  in = text;
  pg_push_default_types();
  for (cnode_t *x = xs; x; x = x->tail) { //x->id==N_TOP
    cnode_t *n = x->head;
    if (n->id == N_FN_DEF) {
      pg_fn(n);
    } else if (n->id == N_CLASS) {
      pg_class(n);
    } else if (n->id == N_NOT_CLASS) {
      patch_t *p = new_patch(P_NOT_CLASS,n->sofs);
      p->as[0].i = n->eofs;
    } else if (n->id == N_DECL) {
      cnode_t *h = n->head;
      if (h->id == N_TYPE_SPEC && h->tail && h->tail->id == N_MSCOPE) {
        cnode_t *t = n->tail;
        if (t->id == N_VARS && t->head->id == N_VAR_DEF
            && t->head->head->id == N_DECLARATOR) {
          pg_meth_proto(n);
          continue;
        }
      }
      pg_decl(n);
    }
  }
}
