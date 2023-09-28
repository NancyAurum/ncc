#ifndef SYM_H
#define SYM_H

#include <stdint.h>

#include "cnode.h"

typedef struct {
  char *name;
  uint32_t flags;
  cnode_t *type; //type part of the symbol (int, float, etc..)
  cnode_t *decl; //declaration part of the symbol (*variable_name)
  int ref_hack;
} sym_t;

//sym_t.flags bits:
#define SYM_TYPEDEF   0x01
#define SYM_FIELD     0x02
#define SYM_REFHACK   ((uint32_t)0x100)
#define SYM_SBRM      0x04

void add_typedef_id(char *id);
void set_method(char *name, cnode_t *node);
cnode_t *get_method(char *name);
void push_block();
void pop_block();
int scope_depth(); //0=top level, 1=function args, 2=function body
int is_classname(char *name);
void add_classname(char *name);
sym_t *push_decl2(char *name, cnode_t *type, cnode_t *decl);
sym_t *push_decl(cnode_t *type, cnode_t *decl);
sym_t *lookup(char *name);
cnode_t *is_typedef(cnode_t *xs);
void handle_typedef(cnode_t *type, cnode_t *vars);
cnode_t *decl_name(cnode_t *n);
void init_symtable();
sym_t **sbrm_above(int level);
sym_t **sbrm_above_or_below_offset(int level, int ofs);

typedef struct {
  cnode_t *type;
  cnode_t *decl;
} class_field_t;

class_field_t *get_fields(char *cname);
void set_fields(char *cname, class_field_t *fields);


#endif
