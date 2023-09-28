/* Grammar by jutta@pobox.com
 * Origin: http://www.quut.com/c/ANSI-C-grammar-l-2011.html
 */

/*
The following %-parameters are the minimum sizes needed for real Lex.
%e	number of parsed tree nodes
%p	number of positions
%n	number of states
%k	number of packed character classes
%a	number of transitions
%o	size of output array
*/

%e  1019
%p  2807
%n  371
%k  284
%a  1213
%o  1117

O   [0-7]
D   [0-9]
NZ  [1-9]
L   [a-zA-Z_]
A   [a-zA-Z_0-9]
H   [a-fA-F0-9]
HP  (0[xX])
E   ([Ee][+-]?{D}+)
P   ([Pp][+-]?{D}+)
FS  (f|F|l|L)
IS  (((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))
CP  (u|U|L)
SP  (u8|u|U|L)
ES  (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
WS  [ \t\v\n\f]

%{
//"
#include <stdio.h>
#include "parse.h"
#include "parser.h"

extern YYSTYPE yylval;
extern YYLTYPE yylloc;

extern YYSTYPE cnode(int id, void *head, void *tail, void *loc_in);

#define RET(token) \
  if (ncc_depth <= 0) {YY_BREAK;} \
  yylval=cnode((token)|N_TERM, 0, 0, &yylloc); \
  yylval->text = strdup(yytext); \
  return(token);

extern void yyerror(const char *);  /* prints grammar violation message */

extern int sym_type(const char *);  /* returns type from symbol table */

//#define sym_type(identifier) IDENTIFIER /* with no symbol table, fake it */

static void comment(void);
static int check_type(void);
static void skip_attribute();

// if below 1, the code is copied as is
static int ncc_depth = 1;

#define YY_USER_ACTION \
  yylloc.sofs = yylloc.eofs; \
  yylloc.srow = yylloc.erow; \
  yylloc.scol = yylloc.ecol; \
  for(int i_ = 0; yytext[i_] != '\0'; i_++) { \
    yylloc.eofs++; \
    if(yytext[i_] == '\n') { \
        yylloc.erow++; \
        yylloc.ecol = 0; \
    } \
    else { \
        yylloc.ecol++; \
    } \
  }



%}

%%

"<<<"      { patch_t *p = new_patch(P_OLD_OPEN, yylloc.sofs);
            p->as[0].i = yylloc.eofs;
            ncc_depth--; }
">>>"     { patch_t *p = new_patch(P_OLD_CLOSE, yylloc.sofs);
            p->as[0].i = yylloc.eofs;
            ncc_depth++; }
^"#".*$   {}
"/*"                                    { comment(); }
"//".*                                    { /* consume //-comment */ }

"auto"          { RET(AUTO); }
"break"         { RET(BREAK); }
"case"          { RET(CASE); }
"char"          { RET(CHAR); }
"class"         { RET(CLASS); }
"const"         { RET(CONST); }
"continue"      { RET(CONTINUE); }
"default"       { RET(DEFAULT); }
"do"            { RET(DO); }
"double"        { RET(DOUBLE); }
"else"          { RET(ELSE); }
"enum"          { RET(ENUM); }
"extern"        { RET(EXTERN); }
"float"         { RET(FLOAT); }
"for"           { RET(FOR); }
"goto"          { RET(GOTO); }
"if"            { RET(IF); }
"inline"        { RET(T_INLINE); }
"int"           { RET(INT); }
"long"          { RET(LONG); }
"register"      { RET(REGISTER); }
"restrict"      { RET(T_RESTRICT); }
"return"        { RET(RETURN); }
"short"         { RET(SHORT); }
"signed"        { RET(SIGNED); }
"sizeof"        { RET(SIZEOF); }
"static"        { RET(STATIC); }
"struct"        { RET(STRUCT); }
"switch"        { RET(SWITCH); }
"typedef"       { RET(TYPEDEF); }
"union"         { RET(UNION); }
"unsigned"      { RET(UNSIGNED); }
"void"          { RET(VOID); }
"volatile"      { RET(VOLATILE); }
"while"         { RET(WHILE); }
"typeof"        { RET(TYPEOF); }
"_Alignas"            { RET(ALIGNAS); }
"_Alignof"            { RET(ALIGNOF); }
"_Atomic"             { RET(ATOMIC); }
"_Bool"               { RET(BOOL); }
"_Complex"            { RET(COMPLEX); }
"_Generic"            { RET(GENERIC); }
"_Imaginary"          { RET(IMAGINARY); }
"_Noreturn"           { RET(NORETURN); }
"_Static_assert"      { RET(STATIC_ASSERT); }
"_Thread_local"       { RET(THREAD_LOCAL); }
"__func__"            { RET(FUNC_NAME); }
"__attribute__"       { skip_attribute(); }
"__asm"               { skip_attribute(); }
"_Nonnull"            { }

{L}{A}*          { int t=check_type(); RET(t); }

{HP}{H}+{IS}?        { RET(I_CONSTANT); }
{NZ}{D}*{IS}?        { RET(I_CONSTANT); }
"0"{O}*{IS}?        { RET(I_CONSTANT); }
{CP}?"'"([^'\\\n]|{ES})+"'"    { RET(I_CONSTANT); }

{D}+{E}{FS}?        { RET(F_CONSTANT); }
{D}*"."{D}+{E}?{FS}?      { RET(F_CONSTANT); }
{D}+"."{E}?{FS}?      { RET(F_CONSTANT); }
{HP}{H}+{P}{FS}?      { RET(F_CONSTANT); }
{HP}{H}*"."{H}+{P}{FS}?      { RET(F_CONSTANT); }
{HP}{H}+"."{P}{FS}?      { RET(F_CONSTANT); }

({SP}?\"([^"\\\n]|{ES})*\"{WS}*)+  { RET(STRING_LITERAL); }

"..."          { RET(ELLIPSIS); }
"::"          { RET(SCOPE); }
">>="          { RET(RIGHT_ASSIGN); }
"<<="          { RET(LEFT_ASSIGN); }
"+="          { RET(ADD_ASSIGN); }
"-="          { RET(SUB_ASSIGN); }
"*="          { RET(MUL_ASSIGN); }
"/="          { RET(DIV_ASSIGN); }
"%="          { RET(MOD_ASSIGN); }
"&="          { RET(AND_ASSIGN); }
"^="          { RET(XOR_ASSIGN); }
"|="          { RET(OR_ASSIGN); }
">>"          { RET(RIGHT_OP); }
"<<"          { RET(LEFT_OP); }
"++"          { RET(INC_OP); }
"--"          { RET(DEC_OP); }
"->"          { RET(PTR_OP); }
"&&"          { RET(AND_OP); }
"||"          { RET(OR_OP); }
"<="          { RET(LE_OP); }
">="          { RET(GE_OP); }
"=="          { RET(EQ_OP); }
"!="          { RET(NE_OP); }
";"          { RET(';'); }
("{"|"<%")        { RET('{'); }
("}"|"%>")        { RET('}'); }
","          { RET(','); }
":"          { RET(':'); }
"="          { RET('='); }
"("          { RET('('); }
")"          { RET(')'); }
("["|"<:")        { RET('['); }
("]"|":>")        { RET(']'); }
"."          { RET('.'); }
"&"          { RET('&'); }
"!"          { RET('!'); }
"~"          { RET('~'); }
"-"          { RET('-'); }
"+"          { RET('+'); }
"*"          { RET('*'); }
"/"          { RET('/'); }
"%"          { RET('%'); }
"<"          { RET('<'); }
">"          { RET('>'); }
"^"          { RET('^'); }
"|"          { RET('|'); }
"?"          { RET('?'); }


{WS}+          { /* whitespace separates tokens */ }
.          { /* discard bad characters */ }

%%

int yywrap(void)        /* called at end of input */
{
    return 1;           /* terminate now */
}

int cinput() {
  int c = input();
  yylloc.eofs++;
  if(c == '\n') {
    yylloc.erow++;
    yylloc.ecol = 0;
  }
  else {
    yylloc.ecol++;
  }
  return c;
}

static void comment() {
  int c;
  while ((c = cinput()) != 0) {
    if (c == '*') {
        while ((c = cinput()) == '*') ;
        if (c == '/') return;
        if (c == 0) break;
    }
  }
  yyerror("unterminated comment");
}

static void skip_attribute() {
  int c;
  int depth = 0;
  int inside_string = 0;
  while ((c = cinput()) != 0) {
    if (inside_string) {
      if (c == '\"') { //"
        inside_string = 0;
      }
      continue;
    } else if (c == '\"') { //"
      inside_string = 1;
      continue;
    } else if (c == '(') {
      depth++;
    } else if (c == ')') {
      depth--;
      if (!depth) return;
    }
  }
  yyerror("unterminated attribute");
}


static int check_type(void)
{
    switch (sym_type(yytext))
    {
    case TYPEDEF_NAME:                /* previously defined */
        return TYPEDEF_NAME;
    case ENUMERATION_CONSTANT:        /* previously defined */
        return ENUMERATION_CONSTANT;
    default:                          /* includes undefined */
        return IDENTIFIER;
    }
}

void init_lexer(char *input) {
  yy_scan_string(input);
  memset(&yylloc, 0, sizeof(yylloc));
}
