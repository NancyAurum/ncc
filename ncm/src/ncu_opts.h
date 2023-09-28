#ifndef NCU_OPTS_H
#define NCU_OPTS_H

#ifndef INCLUDE_STB_DS_H
#include "stb_ds.h"
#endif

#ifdef WINDOWS
static char *strndup(char *str, int chars) {
  char *buffer;
  int n;

  buffer = (char *) malloc(chars +1);
  if (buffer)
  {
      for (n = 0; ((n < chars) && (str[n] != 0)) ; n++) buffer[n] = str[n];
      buffer[n] = 0;
  }

  return buffer;
}
#endif

typedef struct { char *key; char **value; } opts_table_t;

static opts_table_t *opts_parse(int argc, char **argv, char ***opts_list) {
  opts_table_t *ot = NULL;
  char **ol = NULL;
  for (int i = 1; i < argc; i++) {
    char *p = strchr(argv[i], '=');
    if (p) {
      char *key = strndup(argv[i],p-argv[i]);
      char *value = strdup(p+1);
      char **xs = shget(ot,key);
      arrput(xs, value);
      shput(ot, key, xs);
    } else {
      arrput(ol, argv[i]);
    }
  }
  if (opts_list) *opts_list = ol;
  return ot;
}


#endif
