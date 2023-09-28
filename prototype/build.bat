@echo off
set PATH=C:\Program Files\mingw-w64\x86_64-6.3.0-posix-seh-rt_v5-rev2\mingw64\bin;%PATH%
set cflags= -O2 -std=c99 --pedantic -DWINDOWS -Iinclude/
set srcs=src/main.c src/sym.c src/lexer.c src/parser.c
set srcs=%srcs% src/patch.c src/cnode.c src/patchgen.c src/util.c
set srcs=%srcs% src/stb_ds.c
gcc %cflags% %srcs% -o ./lib/ncc