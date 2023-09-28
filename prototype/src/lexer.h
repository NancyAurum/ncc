#ifndef LEXER_H
#define LEXER_H

void init_lexer(char *input);

void yyerror(const char *s);
int yylex();

#endif
