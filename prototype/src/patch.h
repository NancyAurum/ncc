#ifndef PATCH_H
#define PATCH_H

#include <stdint.h>
#include <stdio.h>

#include "cnode.h"

//patch types
enum {
   P_MCALL
  ,P_MDEF
  ,P_CLASS
  ,P_CLASS_END
  ,P_FIELD_ID
  ,P_NOT_CLASS
  ,P_CLASS_TD
  ,P_PRAGMA
  ,P_SCALL
  ,P_AUTO
  ,P_OLD_OPEN
  ,P_OLD_CLOSE
  ,P_REF
  ,P_REF_DECL
  ,P_REM_REF
  ,P_CTOR
  ,P_DTOR_RET
  ,P_DTOR_RET2
  ,P_DTOR_BLOCK
  ,P_DTOR_RET_COPY
  ,P_STOR
  ,P_INDEX
  ,P_INJECT
  ,P_ERASE
};


#define PF_REF   0x1000
#define PF_FIELD 0x2000
#define PF_LVAL  0x4000
#define PF_SINK  0x8000


typedef struct patch_t {
  int type;
  union patch_arg_t {
    int i;
    char *s;
    void *p;
    cnode_t *n;
  } as[6];
  struct patch_t *next;
} patch_t;

void init_patcher(int sz);
void gen_patch(cnode_t *xs);
patch_t *new_patch(int type, int ofs);
int has_patch(int type, int ofs);

int apply_patch(uint8_t *in, int start, int end, FILE *out);

#endif
