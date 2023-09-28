#include <stdlib.h>
#include <stdio.h>
#include "parse.h"

char *node_idt[] = {
#define H(x) x
#define D(x) H(#x)
#include "cnode_ids.h"
#undef D
#undef H
};

cnode_t *cnode(int id, void *head, void *tail, void *loc_in) {
  YYLTYPE *loc = (YYLTYPE *)loc_in;
  cnode_t *n = (cnode_t *)malloc(sizeof(cnode_t));
  n->id = id;
  n->sofs = loc->sofs;
  n->eofs = loc->eofs;
  n->srow = loc->srow;
  n->scol = loc->scol;
  n->erow = loc->erow;
  n->ecol = loc->ecol;
  n->head = head;
  n->tail = tail;
  n->text = "";
  return n;
}

cnode_t *cn_flip(cnode_t *xs) {
  cnode_t *ys = 0;
  cnode_t *next = 0;
  for (cnode_t *x = xs; x; x = next) {
    next = x->tail;
    x->tail = ys;
    ys = x;
  }
  return ys;
}

#define cnlog(...)  fprintf(stderr, __VA_ARGS__)

int indts = 0;

static void indt() {
  for (int i = 0; i < indts; i++) {
    cnlog(" ");
  }
}

void cnode_print2(cnode_t *n) {
  if (!n) return;

  int is_list = n->head || n->tail;

  if (is_list) {
    if (indts>=0) cnlog("\n");
    indts++;
    indt();
    cnlog("(");
  } else {
    cnlog(" ");
  }

  indts++;
  for (cnode_t *x = n; x; x = x->tail) {
    cnlog("%d,%d:", x->srow, x->scol);
    if (x->id&N_TERM) cnlog("%s", x->text);
    else cnlog("%s", node_idt[x->id]+2);
    if (is_list) {
      cnlog(":");
    }

    cnode_print2(x->head);

    if (x->tail) {
      cnlog("\n");
      indt();
    }
  }
  indts--;

  if (is_list) {
    cnlog(")");
    indts--;
  }
}

void cnode_print(cnode_t *n) {
  indts = -1;
  cnode_print2(n);
  cnlog("\n");
}
