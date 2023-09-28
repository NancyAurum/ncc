#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "util.h"

char *_hidden_cat_(char *a0, ...) {
  char *a;
  va_list ap;
  int size = strlen(a0);
  va_start(ap, a0);
  for (;;) {
    a = va_arg(ap, char*);
    if (!a) break;
    size += strlen(a);
  }
  va_end(ap);
  size += 1;

  char *o = malloc(size);

  //fprintf(stdout, "%d\n", size);

  char *p = o;

  a = a0;
  while (*a) *p++ = *a++;

  va_start(ap, a0);
  for (;;) {
    a = va_arg(ap, char*);
    if (!a) break;
    while (*a) *p++ = *a++;
  }
  va_end(ap);

  *p++ = 0;

  return o;
}


char *sjoin(char *a, char *b) {
  int al = strlen(a);
  int bl = strlen(b);
  char *p = malloc(al+bl+1);
  strcpy(p, a);
  strcpy(p+al, b);
  return p;
}

char *sjoin3(char *a, char *b, char *c) {
  int al = strlen(a);
  int bl = strlen(b);
  int cl = strlen(c);
  char *p = malloc(al+bl+cl+1);
  strcpy(p, a);
  strcpy(p+al, b);
  strcpy(p+al+bl, c);
  return p;
}

char *sjoin4(char *a, char *b, char *c, char *d) {
  int al = strlen(a);
  int bl = strlen(b);
  int cl = strlen(c);
  int dl = strlen(d);
  char *p = malloc(al+bl+cl+dl+1);
  strcpy(p, a);
  strcpy(p+al, b);
  strcpy(p+al+bl, c);
  strcpy(p+al+bl+cl, d);
  return p;
}


int begins_with(const char *head, const char *string) {
  return !strncmp(head,string,strlen(head));
}




//#define log(...) fprintf(stderr, __VA_ARGS__)
#define log(...) 

int indent_size = 0;

static void indent() {
  for (int i = 0; i < indent_size; i++) {
    log(" ");
  }
}
