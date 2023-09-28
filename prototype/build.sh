#yacc -d c.y && lex c.l && cc y.tab.c lex.yy.c -o ../lib/cext
# -O2
bison -d src/parser.y -o src/parser.c && lex -o src/lexer.c src/lexer.l \
   && cc  -std=c99 --pedantic \
          -Iinclude/ \
          src/main.c src/sym.c src/lexer.c src/parser.c \
          src/patch.c src/cnode.c src/patchgen.c src/util.c \
          src/stb_ds.c \
         -o ./lib/ncc
