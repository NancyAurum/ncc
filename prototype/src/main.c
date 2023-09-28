#include <stdio.h>
#include "common.h"
#include "parse.h"
#include "patchgen.h"

#include "ncu_opts.h"
#include "ncu_file.h"

#define NCM_IMPLEMENTATION
#include "../../ncm/src/ncm.h"


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

  char **ppfn = shget(opts, "pp");
  char **iopt = shget(opts, "i");
  char **paths = adup(iopt);
  arrput(paths, 0);

  ncm_options_t o = ncm_default_options();
  o.file_exist = cbFileExist;
  o.file_get = cbFileGet;
  o.command = cbCommand;
  o.err_fatal = cbFatal;
  o.paths = paths;

  //if (shget(opts, "kc")) o.flags |= NCM_KEEP_COMMENTS;

  o.mchar = '#';

#define P(...) fprintf(stderr, __VA_ARGS__)
  if (arrlen(files) != 2) {
    P("NCC: The New C Compiler\n");
    P("     (c) 2021 Nikita Sadkov <nashgold85@gmail.com>. All Rights Reserved.\n");
    P("\n");
    P("USAGE: ncc [OPTIONS] <infile> <outfile>\n");
    P("\n");
    P("OPTIONS:\n");
    P("  i=<folder>              Adds folder to the list of include paths.\n");
    P("  =no_nc_h                Don't include nc.h by default.\n");
    P("  pp=<filename>           Save the result of macroexpansion to file.\n");
    return 0;
  }
  FILE *of = fopen(files[1], "wb");
  if (!of) {
    fprintf(stderr, "Couldn't write %s", files[1]);
    return -1;
  }

  //preprocess
  char *p = ncm_expand_file(&o, files[0]);
  U32 sz = strlen(p);
  if (arrlen(ppfn)) {
    FILE *ppf = fopen(ppfn[0], "wb");
    if (!ppf) {
      fprintf(stderr, "Couldn't write %s", ppfn[0]);
      return -1;
    }
    fwrite(p, 1, sz, ppf);
    fclose(ppf);
  }

  //init translator
  init_symtable();
  init_lexer(p);
  init_parser(p);
  init_patcher(sz);

  //translate into C99
  cnode_t *ast = parser_run();
  if (ast) patchgen(p, ast);
  //cnode_print(ast);
  apply_patch((uint8_t*)p, 0, sz, of);

  fclose(of);
  ncm_free_result(p);

  return 0;
}
