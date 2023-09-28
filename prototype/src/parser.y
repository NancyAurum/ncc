/* Grammar by jutta@pobox.com
 * Origin: http://www.quut.com/c/ANSI-C-grammar-y-2011.html
 */

%{

#include <stdio.h>
#include "parse.h"

//after the parser finishes, the result will be placed into this var
static cnode_t *yyparse_result;

static void print_token_value (FILE *file, int type, YYSTYPE value) {
}

#define YYPRINT(File, Type, Value)   \
  print_token_value (File, Type, Value)

#define YYLLOC_DEFAULT(Cur, Rhs, N)                       \
do                                                        \
  if (N)                                                  \
    {                                                     \
      (Cur).srow         = YYRHSLOC(Rhs, 1).srow;         \
      (Cur).scol         = YYRHSLOC(Rhs, 1).scol;         \
      (Cur).sofs         = YYRHSLOC(Rhs, 1).sofs;         \
      (Cur).erow         = YYRHSLOC(Rhs, N).erow;         \
      (Cur).ecol         = YYRHSLOC(Rhs, N).ecol;         \
      (Cur).eofs         = YYRHSLOC(Rhs, N).eofs;         \
    }                                                     \
  else                                                    \
    {                                                     \
      (Cur).srow = (Cur).erow = YYRHSLOC(Rhs, 0).erow;    \
      (Cur).scol = (Cur).ecol = YYRHSLOC(Rhs, 0).ecol;    \
      (Cur).sofs = (Cur).eofs = YYRHSLOC(Rhs, 0).eofs;    \
    }                                                     \
while (0)



%}

//%define "parse.error" "custom"

//%debug

%error-verbose //print elaborate errors instead of "syntax error"

%locations

%token SCOPE
//%nonassoc LOWER_THAN_SCOPE

//following line for nicer error messages instead of "$end"
%token        END      0 "end of file"

%token	IDENTIFIER I_CONSTANT F_CONSTANT STRING_LITERAL FUNC_NAME SIZEOF
%token	PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token	AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token	SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token	XOR_ASSIGN OR_ASSIGN
%token	TYPEDEF_NAME ENUMERATION_CONSTANT

%token	TYPEDEF EXTERN STATIC AUTO REGISTER T_INLINE
%token	CONST T_RESTRICT VOLATILE
%token	BOOL CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOID
%token	COMPLEX IMAGINARY 
%token	TYPEOF CLASS STRUCT UNION ENUM ELLIPSIS

%token	CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token	ALIGNAS ALIGNOF ATOMIC GENERIC NORETURN STATIC_ASSERT THREAD_LOCAL


%start top

%initial-action
{
  memset(&@$, 0, sizeof(@$));
};

%%

primary_expression
	: IDENTIFIER
	| constant
    {
      $$ = cnode(N_LIT, $1, 0, &@$);
    }
	| string
    {
      $$ = cnode(N_LIT, $1, 0, &@$);
    }
	| '(' expression ')'
    {
      $$ = cnode(N_BEXPR, $2, 0, &@$);
    }
	| generic_selection
	;

constant
	: I_CONSTANT		/* includes character_constant */
	| F_CONSTANT
	| ENUMERATION_CONSTANT	/* after it has been defined as such */
	;

enumeration_constant		/* before it has been defined as such */
	: IDENTIFIER
	;

string
	: STRING_LITERAL
	| FUNC_NAME
	;

generic_selection
	: GENERIC '(' assignment_expression ',' generic_assoc_list ')'
	;

generic_assoc_list
	: generic_association
	| generic_assoc_list ',' generic_association
	;

generic_association
	: type_name ':' assignment_expression
	| DEFAULT ':' assignment_expression
	;

postfix_expression
	: primary_expression
    {
      $$ = $1;
    }
	| postfix_expression '[' expression ']'
    {
      $$ = cnode(N_INDEX, $1, $3, &@$);
    }
	| postfix_expression '(' ')'
    {
      $$ = cnode(N_CALL, $1, 0, &@$);
    }
	| postfix_expression '(' argument_expression_list ')'
    {
      $$ = cnode(N_CALL, $1, cn_flip($3), &@$);
    }
	| postfix_expression '.' IDENTIFIER
    {
      $$ = cnode(N_DOT, $1, $3, &@$);
    }
	| postfix_expression PTR_OP IDENTIFIER
    {
      $$ = cnode(N_ARROW, $1, $3, &@$);
    }
	| postfix_expression INC_OP
    {
      $$ = cnode(N_EXPR, $1, 0, &@$);
    }
	| postfix_expression DEC_OP
    {
      $$ = cnode(N_EXPR, $1, 0, &@$);
    }
	| '(' type_name ')' '{' initializer_list '}'
    {
      $$ = $5;
    }
	| '(' type_name ')' '{' initializer_list ',' '}'
    {
      $$ = $5;
    }
	;

argument_expression_list
	: assignment_expression
    {
      $$ = cnode(N_BEXPR, $1, 0, &@$);
    }
	| argument_expression_list ',' assignment_expression
    {
      $$ = cnode(N_BEXPR, $3, $1, &@$);
    }
	;

unary_expression
	: postfix_expression
    {
      $$ = $1;
    }
	| INC_OP unary_expression
    {
      $$ = $2;
    }
	| DEC_OP unary_expression
    {
      $$ = $2;
    }
	| unary_operator cast_expression
    {
      $$ = cnode(N_UNARY, $1, $2, &@$);
    }
	| SIZEOF unary_expression
    {
      $$ = cnode(N_SIZEOF, $2, 0, &@$);
    }
	| SIZEOF '(' type_name ')'
    {
      $$ = cnode(N_LIT, cnode(N_SIZEOF, $3, 0, &@$), 0, &@$);
    }
	| ALIGNOF '(' type_name ')'
    {
      $$ = cnode(N_LIT, cnode(N_ALIGNOF, $3, 0, &@$), 0, &@$);
    }
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression
    {
      $$ = $1;
    }
	| '(' type_name ')' cast_expression
    {
      $$ = cnode(N_CAST, $2, $4, &@$);
    }
	;

multiplicative_expression
	: cast_expression
    {
      $$ = $1;
    }
	| multiplicative_expression '*' cast_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	| multiplicative_expression '/' cast_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	| multiplicative_expression '%' cast_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	;

additive_expression
	: multiplicative_expression
    {
      $$ = $1;
    }
	| additive_expression '+' multiplicative_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	| additive_expression '-' multiplicative_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	;

shift_expression
	: additive_expression
    {
      $$ = $1;
    }
	| shift_expression LEFT_OP additive_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	| shift_expression RIGHT_OP additive_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	;

relational_expression
	: shift_expression
    {
      $$ = $1;
    }
	| relational_expression '<' shift_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	| relational_expression '>' shift_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	| relational_expression LE_OP shift_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	| relational_expression GE_OP shift_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	;

equality_expression
	: relational_expression
    {
      $$ = $1;
    }
	| equality_expression EQ_OP relational_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	| equality_expression NE_OP relational_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	;

and_expression
	: equality_expression
    {
      $$ = $1;
    }
	| and_expression '&' equality_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	;

exclusive_or_expression
	: and_expression
    {
      $$ = $1;
    }
	| exclusive_or_expression '^' and_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	;

inclusive_or_expression
	: exclusive_or_expression
    {
      $$ = $1;
    }
	| inclusive_or_expression '|' exclusive_or_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	;

logical_and_expression
	: inclusive_or_expression
    {
      $$ = $1;
    }
	| logical_and_expression AND_OP inclusive_or_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	;

logical_or_expression
	: logical_and_expression
    {
      $$ = $1;
    }
	| logical_or_expression OR_OP logical_and_expression
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	;

conditional_expression
	: logical_or_expression
    {
      $$ = $1;
    }
	| logical_or_expression '?' expression ':' conditional_expression
    {
      cnode_t *n = cnode(N_EXPR, $5, 0, &@$);
      $$ = cnode(N_EXPR, $1, cnode(N_EXPR, $3, n, &@$), &@$);
    }
	;

assignment_expression
	: conditional_expression
    {
      $$ = $1;
    }
	| unary_expression assignment_operator assignment_expression
    {
      $$ = cnode(N_ASSIGN, $1, cnode(N_CONS, $2, $3, &@$), &@$);
    }
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
    {
      $$ = cnode(N_BEXPR, $1, 0, &@$);
    }
	| expression ',' assignment_expression
    {
      $$ = cnode(N_BEXPR, $3, $1, &@$);
    }
	;

constant_expression
	: conditional_expression	/* with constraints */
	;

declaration
	: declaration_specifiers ';'
    {
      $$ = cnode(N_DECL,$1,0,&@$);
    }
	| declaration_specifiers init_declarator_list ';'
    {
      cnode_t *n = cnode(N_DECL,$1,cn_flip($2),&@$);
      handle_typedef(n->head,n->tail);
      $$ = n;
    }
	| static_assert_declaration
	;

declaration_specifiers
	: storage_class_specifier declaration_specifiers
    {
      $$ = cnode(N_TYPE_STOR,$1,$2,&@$);
    }
	| storage_class_specifier
    {
      $$ = cnode(N_TYPE_STOR,$1,0,&@$);
    }
	| type_specifier declaration_specifiers
    {
      $$ = cnode(N_TYPE_SPEC,$1,$2,&@$);
    }
	| type_specifier '.'
    {
      $$ = cnode(N_MSCOPE,$1,0,&@$);
    }
	| type_specifier
    {
      $$ = cnode(N_TYPE_SPEC,$1,0,&@$);
    }
	| type_qualifier declaration_specifiers
    {
      $$ = cnode(N_TYPE_QUAL,$1,$2,&@$);
    }
	| type_qualifier
    {
      $$ = cnode(N_TYPE_QUAL,$1,0,&@$);
    }
	| function_specifier declaration_specifiers
    {
      $$ = cnode(N_TYPE_FN_SPEC,$1,$2,&@$);
    }
	| function_specifier
    {
      $$ = cnode(N_TYPE_FN_SPEC,$1,0,&@$);
    }
	| alignment_specifier declaration_specifiers
    {
      $$ = cnode(N_TYPE_FN_SPEC,$1,$2,&@$);
    }
	| alignment_specifier
    {
      $$ = cnode(N_TYPE_FN_SPEC,$1,0,&@$);
    }
	;

init_declarator_list
	: init_declarator
    {
      $$ = cnode(N_VARS,$1,0,&@$);
    }
	| init_declarator_list ',' init_declarator
    {
      $$ = cnode(N_VARS,$3,$1,&@$);
    }
	;

init_declarator
	: declarator '=' initializer
    {
      $$ = cnode(N_VAR_DEF,$1,$3,&@$);
    }
	| declarator
    {
      $$ = cnode(N_VAR_DEF,$1,0,&@$);
    }
	;

storage_class_specifier
	: TYPEDEF	/* identifiers must be flagged as TYPEDEF_NAME */
	| EXTERN
	| STATIC
	| THREAD_LOCAL
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	| CHAR
	| SHORT
	| INT
	| LONG
	| FLOAT
	| DOUBLE
	| SIGNED
	| UNSIGNED
	| BOOL
	| COMPLEX
	| IMAGINARY	  	/* non-mandated extension */
	| atomic_type_specifier
	| struct_or_union_specifier
	| enum_specifier
	| TYPEDEF_NAME		/* after it has been defined as such */
  | TYPEOF '(' expression ')'
    {
      $$ = cnode(N_TYPEOF, $3, 0, &@$);
    }
	;

id_or_typedef: IDENTIFIER | TYPEDEF_NAME

struct_or_union_specifier
	: struct_or_union '{' struct_declaration_list '}'
    {
      $$ = cnode(N_STRUCT, cnode(0, $1,0, &@$), cn_flip($3), &@$);
    }
	| struct_or_union id_or_typedef '{' struct_declaration_list '}'
    {
      $$ = cnode(N_STRUCT, cnode(0, $1,$2, &@$), cn_flip($4), &@$);
    }
	| struct_or_union id_or_typedef
    {
      $$ = cnode(N_STRUCT, cnode(0, $1,$2, &@$), 0, &@$);
    }
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
    {
      $$ = cnode(N_STRUCT_FIELD,$1,0,&@$);
    }
	| struct_declaration_list struct_declaration
    {
      $$ = cnode(N_STRUCT_FIELD,$2,$1,&@$);
    }
	;

struct_declaration
	: specifier_qualifier_list ';'	/* for anonymous struct/union */
    {
      $$ = cnode(N_STRUCT_DECL,cn_flip($1),0,&@$);
    }
	| specifier_qualifier_list struct_declarator_list ';'
    {
      $$ = cnode(N_STRUCT_DECL,cn_flip($1),$2,&@$);
    }
	| static_assert_declaration
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
    {
      $$ = cnode(N_TYPE_SPEC,$1,$2,&@$);
    }
	| type_specifier
    {
      $$ = cnode(N_TYPE_SPEC,$1,0,&@$);
    }
	| type_qualifier specifier_qualifier_list
    {
      $$ = cnode(N_TYPE_QUAL,$1,$2,&@$);
    }
	| type_qualifier
    {
      $$ = cnode(N_TYPE_QUAL,$1,0,&@$);
    }
	;

struct_declarator_list
	: struct_declarator
    {
      $$ = cnode(0,$1,0,&@$);
    }
	| struct_declarator_list ',' struct_declarator
    {
      $$ = cnode(0,$3,$1,&@$);
    }
	;

struct_declarator
	: ':' constant_expression
	| declarator ':' constant_expression
    {
      $$ = $1;
    }
	| declarator
    {
      $$ = $1;
    }
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM '{' enumerator_list ',' '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator	/* identifiers must be flagged as ENUMERATION_CONSTANT */
	: enumeration_constant '=' constant_expression
	| enumeration_constant
	;

atomic_type_specifier
	: ATOMIC '(' type_name ')'
	;

type_qualifier
	: CONST
	| T_RESTRICT
	| VOLATILE
	| ATOMIC
	;

function_specifier
	: T_INLINE
	| NORETURN
	;

alignment_specifier
	: ALIGNAS '(' type_name ')'
	| ALIGNAS '(' constant_expression ')'
	;

declarator
	: pointer direct_declarator
    {
      $$ = cnode(N_DECLARATOR, $2, $1, &@$);
    }
	| direct_declarator
    {
      $$ = cnode(N_DECLARATOR, $1, 0, &@$);
    }
	;

direct_declarator
	: IDENTIFIER
  | STRING_LITERAL
    {
      $1->id = IDENTIFIER|N_TERM;
      $$ = $1
    }
	| '(' declarator ')'
    {
      $$ = $1;
    }
	| direct_declarator '[' ']'
	| direct_declarator '[' '*' ']'
	| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']'
	| direct_declarator '[' STATIC assignment_expression ']'
	| direct_declarator '[' type_qualifier_list '*' ']'
	| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']'
	| direct_declarator '[' type_qualifier_list assignment_expression ']'
	| direct_declarator '[' type_qualifier_list ']'
	| direct_declarator '[' assignment_expression ']'
    {
      $$ = cnode(N_ARRAY, $1, 0, &@$);
    }
	| direct_declarator '(' parameter_type_list ')'
    {
      $$ = cnode(N_DECL_FN, $1, $3, &@$);
    }
	| direct_declarator '(' ')'
    {
      $$ = cnode(N_DECL_FN, $1, 0, &@$);
    }
	| direct_declarator '(' identifier_list ')'
    {
      $$ = cnode(N_DECL_FN, $1, $3, &@$);
    }
	;

pointer
	: '*' type_qualifier_list pointer
    {
      $$ = cnode(N_PTR, $2, $3, &@$);
    }
	| '*' type_qualifier_list
    {
      $$ = cnode(N_PTR, $2, 0, &@$);
    }
	| '*' pointer
    {
      $$ = cnode(N_PTR, 0, $2, &@$);
    }
	| '*'
    {
      $$ = cnode(N_PTR, 0, 0, &@$);
    }
	| '&' type_qualifier_list pointer
    {
      $$ = cnode(N_REF, $2, $3, &@$);
    }
	| '&' type_qualifier_list
    {
      $$ = cnode(N_REF, $2, 0, &@$);
    }
	| '&' pointer
    {
      $$ = cnode(N_REF, 0, $2, &@$);
    }
	| '&'
    {
      $$ = cnode(N_REF, 0, 0, &@$);
    }
	| '^' type_qualifier_list pointer
    {
      $$ = cnode(N_PTR, $2, $3, &@$);
    }
	| '^' type_qualifier_list
    {
      $$ = cnode(N_PTR, $2, 0, &@$);
    }
	| '^' pointer
    {
      $$ = cnode(N_PTR, 0, $2, &@$);
    }
	| '^'
    {
      $$ = cnode(N_PTR, 0, 0, &@$);
    }
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


parameter_type_list
	: parameter_list ',' ELLIPSIS
    {
      $$ = cn_flip($1);
    }
	| parameter_list
    {
      $$ = cn_flip($1);
    }
	;

parameter_list
	: parameter_declaration
    {
      $$ = cnode(N_PARAM_LIST,$1,0,&@$);
    }
	| parameter_list ',' parameter_declaration
    {
      $$ = cnode(N_PARAM_LIST,$3,$1,&@$);
    }
	;

parameter_declaration
	: declaration_specifiers declarator
    {
      $$ = cnode(N_PARAM, $1, $2, &@$);
    }
	| declaration_specifiers abstract_declarator
    {
      $$ = cnode(N_PARAM, $1, $2, &@$);
    }
	| declaration_specifiers
    {
      $$ = cnode(N_PARAM, $1, 0, &@$);
    }
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list abstract_declarator
    {
      $$ = cnode(N_TYPENAME,$2,cn_flip($1),&@$);
    }
	| specifier_qualifier_list
    {
      $$ = cnode(N_TYPENAME,0,cn_flip($1),&@$);
    }
	;

abstract_declarator
	: pointer direct_abstract_declarator
    {
      $$ = cnode(N_DECLARATOR, $2, $1, &@$);
    }
	| pointer
    {
      $$ = cnode(N_DECLARATOR, 0, $1, &@$);
    }
	| direct_abstract_declarator
    {
      $$ = cnode(N_DECLARATOR, $1, 0, &@$);
    }
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' '*' ']'
	| '[' STATIC type_qualifier_list assignment_expression ']'
	| '[' STATIC assignment_expression ']'
	| '[' type_qualifier_list STATIC assignment_expression ']'
	| '[' type_qualifier_list assignment_expression ']'
	| '[' type_qualifier_list ']'
	| '[' assignment_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' '*' ']'
	| direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
	| direct_abstract_declarator '[' STATIC assignment_expression ']'
	| direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
	| direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
	| direct_abstract_declarator '[' type_qualifier_list ']'
	| direct_abstract_declarator '[' assignment_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: '{' initializer_list '}'
    {
      $$ = $2;
    }
	| '{' initializer_list ',' '}'
    {
      $$ = $2;
    }
	| assignment_expression
    {
      $$ = $1;
    }
	;

initializer_list
	: designation initializer
    {
      $$ = $2;
    }
	| initializer
    {
      $$ = $1;
    }
	| initializer_list ',' designation initializer
    {
      $$ = cnode(N_EXPR, $4, $1, &@$);
    }
	| initializer_list ',' initializer
    {
      $$ = cnode(N_EXPR, $3, $1, &@$);
    }
	;

designation
	: designator_list '='
	;

designator_list
	: designator
	| designator_list designator
	;

designator
	: '[' constant_expression ']'
	| '.' IDENTIFIER
	;

static_assert_declaration
	: STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';'
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
    {
      $$ = cnode(N_LABEL, $1, $3, &@$);
    }
	| CASE constant_expression ':' statement
    {
      $$ = $4;
    }
	| DEFAULT ':' statement
    {
      $$ = $3;
    }
	;

compound_statement
	: '{' '}'
    {
      $$ = 0;
    }
	| '{'  block_item_list '}'
    {
      $$ = cnode(N_BLOCK, cn_flip($2), 0, &@$);
    }
	;

block_item_list
	: block_item
    {
      $$ = cnode(N_CONS, $1, 0, &@$);
    }
	| block_item_list block_item
    {
      $$ = cnode(N_CONS, $2, $1, &@$);
    }
	;

block_item
	: declaration
    {
      $$ = $1;
    }
	| statement
    {
      $$ = $1;
    }
	;

expression_statement
	: ';'
	| expression ';'
    {
      $$ = cn_flip($1);
    }
	;

selection_statement
	: IF '(' expression ')' statement ELSE statement
    {
      cnode_t *n = cnode(N_CONS, $7, 0, &@$);
      $$ = cnode(N_IF, $3, cnode(N_CONS, $5, n, &@$), &@$);
    }
	| IF '(' expression ')' statement
    {
      $$ = cnode(N_IF, $3, cnode(N_CONS, $5, 0, &@$), &@$);
    }
	| SWITCH '(' expression ')' statement
    {
      $$ = cnode(N_SWITCH, $3, $5, &@$);
    }
	;

iteration_statement
	: WHILE '(' expression ')' statement
    {
      $$ = cnode(N_WHILE, $3, $5, &@$);
    }
	| DO statement WHILE '(' expression ')' ';'
    {
      $$ = cnode(N_DOWHILE, $2, $5, &@$);
    }
	| FOR '(' expression_statement expression_statement ')' statement
    {
      cnode_t *n = cnode(N_CONS, $6, 0, &@$);
      $$ = cnode(N_FOR, $3, cnode(N_CONS, $4, n, &@$), &@$);
    }
	| FOR '(' expression_statement expression_statement expression ')' statement
    {
      cnode_t *n = cnode(N_CONS, $5, cnode(N_CONS, $7, 0, &@$), &@$);
      $$ = cnode(N_FOR, $3, cnode(N_CONS, $4, n, &@$), &@$);
    }
	| FOR '(' declaration expression_statement ')' statement
    {
      cnode_t *n = cnode(N_CONS, $6, 0, &@$);
      $$ = cnode(N_FOR, $3, cnode(N_CONS, $4, n, &@$), &@$);
    }
	| FOR '(' declaration expression_statement expression ')' statement
    {
      cnode_t *n = cnode(N_CONS, $5, cnode(N_CONS, $7, 0, &@$), &@$);
      $$ = cnode(N_FOR, $3, cnode(N_CONS, $4, n, &@$), &@$);
    }
	;

jump_statement
	: GOTO IDENTIFIER ';'
    {
      $$ = cnode(N_GOTO,$2,0,&@$);
    }
	| CONTINUE ';'
    {
      $$ = cnode(N_CONTINUE,0,0,&@$);
    }
	| BREAK ';'
    {
      $$ = cnode(N_BREAK,0,0,&@$);
    }
	| RETURN ';'
    {
      $$ = cnode(N_RETURN,0,0,&@$);
    }
	| RETURN expression ';'
    {
      $$ = cnode(N_RETURN,$2,0,&@$);
    }
	;

translation_unit
	: external_declaration
    {
      $$ = cnode(N_TOP,$1,0,&@$);
    }
	| translation_unit external_declaration
    {
      $$ = cnode(N_TOP,$2,$1,&@$);
    }
	;

top
  : translation_unit
    {
      yyparse_result = cn_flip($1);
    }
  | 
    {
      yyparse_result = 0;
    }

external_declaration
	: function_definition
	| CLASS '!' IDENTIFIER ';'
    {
      add_typedef_id($3->text);
      $$ = cnode(N_NOT_CLASS, $3, 0, &@$);
    }
	| CLASS IDENTIFIER ';'
    {
      add_typedef_id($2->text);
      $$ = cnode(N_CLASS, $2, 0, &@$);
    }
	| CLASS IDENTIFIER '{' struct_declaration_list '}'
    {
      add_typedef_id($2->text);
      $$ = cnode(N_CLASS, $2, cn_flip($4), &@$);
    }
	| declaration
	;


method_declarator
  : pointer method_direct_declarator
    {
      $$ = cnode(N_DECLARATOR, $2, $1, &@$);
    }
  ;

method_name
  : IDENTIFIER
  | STRING_LITERAL
    {
      $1->id = IDENTIFIER|N_TERM;
      $$ = $1;
    }
  ;

method_direct_declarator
  : type_specifier '.' method_name
    {
      $$ = cnode(N_MSCOPE,$1,$3,&@$);
    }
  | type_specifier '.' method_name '(' ')'
    {
      $$ = cnode(N_MSCOPE,$1,$3,&@$);
    }
  | type_specifier '.' method_name '(' parameter_type_list ')'
    {
      cnode_t *decl = cnode(N_DECL_FN, $3, $5, &@$);
      $$ = cnode(N_MSCOPE,$1,decl,&@$);
    }


function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement
    {
      $$ = cnode(N_FN_DEF,$2,cnode(N_FN_DEF,$1,$3,&@$),&@$);
    }
	| declaration_specifiers method_declarator compound_statement
    {
      cnode_t *scope = $2->head;
      $2->head = scope->tail;
      scope->tail = $1;
      $$ = cnode(N_FN_DEF,$2,cnode(N_FN_DEF,scope,$3,&@$),&@$);
    }
	| declaration_specifiers method_declarator ';'
    {
      cnode_t *scope = $2->head;
      $2->head = scope->tail;
      scope->tail = $1;
      $$ = cnode(N_FN_DEF,$2,cnode(N_FN_DEF,scope,$3,&@$),&@$);
    }

	;

declaration_list
	: declaration
	| declaration_list declaration
	;

%%
#include <stdio.h>
#include <stdlib.h>

#include "util.h"

static char *semsg = "syntax error, ";
static char *in = 0;


void yyerror(const char *s) {
	fflush(stdout);
  if (begins_with(semsg, s)) s += strlen(semsg);
  int i, j;
  int ofs = 0;
  char *filename = "<unknown>";
  int nrows = 0;
#if 0
  for (i = yylloc.sofs; i >= 0; i--) {
    if (!((in[i] == '#' && in[i+1] == ' ') && (!i || in[i-1]=='\n'))) {
      if (in[i] == '\n') nrows++;
      continue;
    }
    ofs = atoi(in+i+2) + nrows - 1;
    for ( ; in[i] != '\"' && i < yylloc.sofs; i++) {
    }
    if (in[i] != '\"') break;
    for (j = i+1 ; in[j] != '\"' && j < yylloc.sofs; j++) {
      if (in[j] == '\\' && in[j]=='\"') {
        j++;
        continue;
      }
    }
    int l = j-i;
    filename = malloc(l*2 + 1);
    strncpy(filename, in+i+1, l-1);
    filename[l] = 0;
    break;
  }
#else
  for (i = yylloc.sofs; i >= 0; i--) {
    if ((!i || in[i-1]=='\n') && !strncmp(in+i, "#line ", 6)) {
    } else {
      if (in[i] == '\n') nrows++;
      continue;
    }
    ofs = atoi(in+i+6) + nrows - 1;
    for ( ; in[i] != '\"' && i < yylloc.sofs; i++) {
    }
    if (in[i] != '\"') break;
    for (j = i+1 ; in[j] != '\"' && j < yylloc.sofs; j++) {
      if (in[j] == '\\' && in[j]=='\"') {
        j++;
        continue;
      }
    }
    int l = j-i;
    filename = malloc(l*2 + 1);
    strncpy(filename, in+i+1, l-1);
    filename[l] = 0;
    break;
  }
#endif
	fprintf(stderr, "%s:%d,%d: %s\n", filename,ofs, yylloc.scol+1, s);
  exit(-1);
}

void init_parser(char *input) {
  in = input;
}

cnode_t *parser_run() {
  //yydebug = 1;
  yyparse_result = 0;
  yyparse();
  return yyparse_result;
}