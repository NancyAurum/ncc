#include <stdio.h>
#include <stdint.h>
#include "ncu_opts.h"
#include "ncu_file.h"

#define NCM_IMPLEMENTATION
#include "ncm.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

static uint8_t *cbFileGet(void *handle, uint32_t *rsize, char *filename) {
  return fileGet(rsize, filename);
}

static int cbFileExist(void *handle, char *filename) {
  return fileExist(filename);
}

static char *cbCommand(void *handle, char *cmd) {
  if (!strncmp(cmd,"say ", 4)) {
    printf("%s\n", cmd+4);
    return 0;
  }
  return execCommand(cmd);
}

static void cbFatal(void *ncm, char *macro
                        ,char *file, int row, int col, char *text) {

  fprintf(stderr, "%s:%d:%d\n", file, row+1, col);
  if (macro)
    fprintf(stderr, "  During macro expansion `%s`\n", macro);
  fprintf(stderr, "  Fatal: %s\n", text);
  exit(-1);
}

int main(int argc, char **argv) {
  char **files = NULL;
  opts_table_t *opts = opts_parse(argc, argv, &files);
  
  char **iopt = shget(opts, "i");
  char **paths = adup(iopt);
  arrput(paths, 0);

  char **mc = shget(opts, "c");
  int mchar = '#';
  if (mc && *mc[0]) mchar = *mc[0];

  ncm_options_t o = ncm_default_options();
  o.file_exist = cbFileExist;
  o.file_get = cbFileGet;
  o.command = cbCommand;
  o.err_fatal = cbFatal;
  o.paths = paths;
  if (shget(opts, "kc")) o.flags |= NCM_KEEP_COMMENTS;

  o.mchar = mchar;


  char **es = shget(opts, "e");
  if (es) {
    o.flags |= NCM_NO_LINE_NUMS;
    for (int i = 0; i < alen(es); i++) {
      char *result = ncm_eval(&o, "<root>", es[i]);
      printf("%s\n", result);
      ncm_free_result(result);
    }
    return 0;
  }
#define P(...) fprintf(stderr, __VA_ARGS__)
  if (arrlen(files) != 2) {
    P("NCM: The New C Macroprocessor\n");
    P("     (c) 2023 Nancy Sadkov <nangld85@gmail.com>. All Rights Reserved.\n");
    P("\n");
    P("USAGE: ncm [OPTIONS] <infile> <outfile>\n");
    P("\n");
    P("OPTIONS:\n");
    P("  e=<expression>          Evaluate expression.\n");
    P("  i=<folder>              Adds folder to the list of include paths.\n");
    P("  c=<char>                Char replaces # as the macro character.\n");
    P("  kc=1                    Keep comments.\n");
    return 0;
  }
  FILE *of = fopen(files[1], "wb");
  if (!of) {
    fprintf(stderr, "Couldn't write %s", files[1]);
    return -1;
  }

  char *result = ncm_expand_file(&o, files[0]);
  fwrite(result, 1, arrlen(result)-1, of);
  fclose(of);
  ncm_free_result(result);

  return 0;
}
