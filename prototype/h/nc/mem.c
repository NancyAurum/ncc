#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#:mem


char *char.dup {
  char *d = mAlloc(strlen(this)+1);
  strcpy(d,this);
  return d;
}

