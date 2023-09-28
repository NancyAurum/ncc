%{
//cat data/alice.txt | ./lib/wc | sort | sed 's/^[0]*//'
#include <stdio.h>
#include <ctype.h>

#include "common.h"

hsh_dcl(ht,cstr,char*,int)

ht htbl = HSH_INIT;
int nwords;

void downcase(char *p) {
  for ( ; *p; ++p) *p = tolower(*p);
}


%}

ID_LETTER   [A-Za-z_]
DIGIT       [0-9]
ID          {ID_LETTER}({ID_LETTER}|{DIGIT})*


%%

{ID} {
    char *t = strdup(yytext);
    downcase(t);
    *htAdd(&htbl,t,0) += 1;
    nwords++;
  }


.   {}

"\n" {}

%%

int yywrap() {return 1;}

static void init() {
  nwords = 0;
}

int main(int argc, char **argv) {
  init();
  yylex();
  int collisions = 0;
  hsh_for(char*k, int v, &htbl) {
    //printf("%s = %010d\n", k, v);
    printf("%010d = %s\n", v, k);
    collisions += htCollides(&htbl,k);
  }
  printf("Total words: %d\n", nwords);
  printf("Unique words: %d\n", htbl.used);
  printf("Table size: %d\n", htbl.size);
  printf("Collisions: %f\n", (float)collisions/htbl.used*100.0);

  return 0;
}