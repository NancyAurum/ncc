#ifndef CEXT_H
#define CEXT_H

#include "common.h"

#include "cnode.h"
#include "patch.h"
#include "sym.h"

#include "lexer.h"

void init_parser();
cnode_t *parser_run();

#endif
