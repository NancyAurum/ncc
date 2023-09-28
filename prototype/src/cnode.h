#ifndef CNODE_H
#define CNODE_H

#include <stdint.h>


#define N_TERM 0x80000000
#define N_TOKEN(x) ((x)&0xFFFFFF)

//cnode_t.id types
enum node_ids {
#define D(x) x
#include "cnode_ids.h"
#undef D
};

//cons node
//basically the CONS-pair from LISP wid additional metadata
typedef struct cnode_t {
  uint32_t id;
  int srow, scol, erow, ecol, sofs, eofs;
  char *text;
  struct cnode_t *head;
  struct cnode_t *tail;
} cnode_t;

typedef struct {
  int srow;
  int scol;
  int sofs;
  int erow;
  int ecol;
  int eofs;
} yyltype_t;


//make it the YACC semantic type
#define YYSTYPE cnode_t*

//YACC location type
#define YYLTYPE yyltype_t

cnode_t *cnode(int id, void *head, void *tail, void *loc_in);

/*
prints cnode_t as
  (ROW,COL:ID:   //see cnode_ids.h for the list of ids
     HEAD
   TAIL)
*/
void cnode_print(cnode_t *n);

cnode_t *cn_flip(cnode_t *xs);

cnode_t *cn_isref(cnode_t *n);
int cn_isref_name(char *name);
int ptr_level(cnode_t *n);
char *cn_typename(cnode_t *xs);

extern char *node_idt[];


#endif
