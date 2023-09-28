mkdir -p lib/
cc -ggdb0 -g0 -std=c99 --pedantic -O2 src/main.c -o ./ncm
strip ./ncm
strip -x -N -S ./ncm
