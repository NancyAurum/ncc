#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#:cat

<<<
void say_imp_(int count, ...) {
  va_list ap;
  va_start(ap, count);
  for (int i = 0; i < count; i++) {
    char *s = va_arg(ap, char*);
    printf("%s", s);
  }
  printf("\n");
  va_end(ap);
}

char *cat_imp_(char *a0, ...) {
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
  char *o = mAlloc(size);

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
>>>