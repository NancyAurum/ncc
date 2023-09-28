#include <stdio.h>
#include "common.h"

#include "sym.h"
#include "parser.h"


#define MAX_SCOPE_DEPTH 1000


static int depth = 0; //scope depth

static sym_t **symtbl[MAX_SCOPE_DEPTH];

static struct { char *key; cnode_t *value; } *metbl = NULL;

void set_method(char *name, cnode_t *node) {
  shput(metbl, name, node);
}

cnode_t *get_method(char *name) {
  return shget(metbl, name);
}

static struct { char *key; class_field_t *value; } *fi_tbl = NULL;

class_field_t *get_fields(char *cname) {
  return shget(fi_tbl, cname);
}

void set_fields(char *cname, class_field_t *fields) {
  shput(fi_tbl, cname, fields);
}

static struct { char *key; int value; } *cnames_tbl = NULL;
void add_classname(char *name) {
  shput(cnames_tbl, name, 1);
}

int is_classname(char *name) {
  return shget(cnames_tbl, name);
}

static void clear_level() {
  sym_t **l = symtbl[depth];
  if (l) {
    for (int i = 0; i < arrlen(l); i++) free(l[i]);
    arrfree(l);
    symtbl[depth] = 0;
  }
}

void push_block() {
  depth++;
}

void pop_block() {
  //we don't free the symbols, since they are still in used down to patch.c
  sym_t **l = symtbl[depth];
  symtbl[depth] = 0;
  arrfree(l);
  depth--;
}

int scope_depth() {
  return depth;
}

static struct { char *key; int value; } *tdtbl = NULL;

void add_typedef_id(char *id) {
  shput(tdtbl, id, 1);
}

int sym_type(const char *name) {
  return shget(tdtbl, name) ? TYPEDEF_NAME : IDENTIFIER;
}

cnode_t *is_typedef(cnode_t *xs) {
  for (cnode_t *x = xs; x; x = x->tail) {
    cnode_t *n = x->head;
    if (x->id==N_TYPE_STOR && n->id == (TYPEDEF|N_TERM)) return n;
  }
  return 0;
}


cnode_t *decl_name2(cnode_t *n) {
  if (!n) return 0;
  if (N_TOKEN(n->id) == IDENTIFIER) {
    return n;
  } else if (n->id == N_DECL_FN) {
    return decl_name2(n->head);
  } else if (n->id == N_ARRAY) {
    return decl_name2(n->head);
  }
  return 0;
}

//FIXME: rename to decl_id
cnode_t *decl_name(cnode_t *n) {
  return decl_name2(n->head);
}

void handle_typedef(cnode_t *type, cnode_t *vars) {
  if (!is_typedef(type)) return;
  for (cnode_t *x = vars; x; x = x->tail) {
    cnode_t *var = x->head;
    cnode_t *name = decl_name(var->head); 
    if (!name) continue;
    add_typedef_id(name->text);
  }
}


//rename this to sym_declare
//since it declares the symbol in the current scope
sym_t *push_decl2(char *name, cnode_t *type, cnode_t *decl) {
  if (!type || !decl) return 0;
  sym_t *sym = malloc(sizeof(sym_t));
  sym->name = name;
  sym->type = type;
  sym->decl = decl;
  sym->flags = 0;
  sym->ref_hack = 0;
  if (is_typedef(type)) sym->flags |= SYM_TYPEDEF;
  arrput(symtbl[depth], sym);
  return arrlast(symtbl[depth]);
}

sym_t *push_decl(cnode_t *type, cnode_t *decl) {
  cnode_t *n = decl_name(decl);
  if (!n) return 0;
  return push_decl2(n->text, type, decl);
}

sym_t *lookup(char *name) {
  int i, j;
  for (j = depth; j >= 0; j--) {
    for (i = arrlen(symtbl[j])-1; i >= 0; i--) {
      sym_t *s = symtbl[j][i];
      if (!strcmp(name,s->name)) return s;
    }
  }
  return 0;
}

sym_t **sbrm_above(int level) {
  sym_t **r = NULL;
  int i, j;
  for (j = depth; j > level; j--) {
    for (i = arrlen(symtbl[j])-1; i >= 0; i--) {
      sym_t *s = symtbl[j][i];
      if (s->flags&SYM_SBRM) arrput(r,s);
    }
  }
  return r;
}

sym_t **sbrm_above_or_below_offset(int level, int ofs) {
  sym_t **r = NULL;
  int i, j;
  for (j = depth; j > level-1; j--) {
    for (i = arrlen(symtbl[j])-1; i >= 0; i--) {
      sym_t *s = symtbl[j][i];
      if (s->flags&SYM_SBRM) {
        if (j > level || s->decl->sofs > ofs) {
          arrput(r,s);
        }
      }
    }
  }
  return r;
}


void init_symtable() {
  for (int i = 0; i < MAX_SCOPE_DEPTH; i++) {
    symtbl[i] = 0;
  }
  add_typedef_id("uint8_t");
  add_typedef_id("uint16_t");
  add_typedef_id("uint32_t");
  add_typedef_id("uint64_t");
  add_typedef_id("int8_t");
  add_typedef_id("int16_t");
  add_typedef_id("int32_t");
  add_typedef_id("int64_t");
  add_typedef_id("size_t");
  add_typedef_id("FILE");
}
