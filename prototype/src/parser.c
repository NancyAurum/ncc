/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END = 0,
     SCOPE = 258,
     IDENTIFIER = 259,
     I_CONSTANT = 260,
     F_CONSTANT = 261,
     STRING_LITERAL = 262,
     FUNC_NAME = 263,
     SIZEOF = 264,
     PTR_OP = 265,
     INC_OP = 266,
     DEC_OP = 267,
     LEFT_OP = 268,
     RIGHT_OP = 269,
     LE_OP = 270,
     GE_OP = 271,
     EQ_OP = 272,
     NE_OP = 273,
     AND_OP = 274,
     OR_OP = 275,
     MUL_ASSIGN = 276,
     DIV_ASSIGN = 277,
     MOD_ASSIGN = 278,
     ADD_ASSIGN = 279,
     SUB_ASSIGN = 280,
     LEFT_ASSIGN = 281,
     RIGHT_ASSIGN = 282,
     AND_ASSIGN = 283,
     XOR_ASSIGN = 284,
     OR_ASSIGN = 285,
     TYPEDEF_NAME = 286,
     ENUMERATION_CONSTANT = 287,
     TYPEDEF = 288,
     EXTERN = 289,
     STATIC = 290,
     AUTO = 291,
     REGISTER = 292,
     T_INLINE = 293,
     CONST = 294,
     T_RESTRICT = 295,
     VOLATILE = 296,
     BOOL = 297,
     CHAR = 298,
     SHORT = 299,
     INT = 300,
     LONG = 301,
     SIGNED = 302,
     UNSIGNED = 303,
     FLOAT = 304,
     DOUBLE = 305,
     VOID = 306,
     COMPLEX = 307,
     IMAGINARY = 308,
     TYPEOF = 309,
     CLASS = 310,
     STRUCT = 311,
     UNION = 312,
     ENUM = 313,
     ELLIPSIS = 314,
     CASE = 315,
     DEFAULT = 316,
     IF = 317,
     ELSE = 318,
     SWITCH = 319,
     WHILE = 320,
     DO = 321,
     FOR = 322,
     GOTO = 323,
     CONTINUE = 324,
     BREAK = 325,
     RETURN = 326,
     ALIGNAS = 327,
     ALIGNOF = 328,
     ATOMIC = 329,
     GENERIC = 330,
     NORETURN = 331,
     STATIC_ASSERT = 332,
     THREAD_LOCAL = 333
   };
#endif
/* Tokens.  */
#define END 0
#define SCOPE 258
#define IDENTIFIER 259
#define I_CONSTANT 260
#define F_CONSTANT 261
#define STRING_LITERAL 262
#define FUNC_NAME 263
#define SIZEOF 264
#define PTR_OP 265
#define INC_OP 266
#define DEC_OP 267
#define LEFT_OP 268
#define RIGHT_OP 269
#define LE_OP 270
#define GE_OP 271
#define EQ_OP 272
#define NE_OP 273
#define AND_OP 274
#define OR_OP 275
#define MUL_ASSIGN 276
#define DIV_ASSIGN 277
#define MOD_ASSIGN 278
#define ADD_ASSIGN 279
#define SUB_ASSIGN 280
#define LEFT_ASSIGN 281
#define RIGHT_ASSIGN 282
#define AND_ASSIGN 283
#define XOR_ASSIGN 284
#define OR_ASSIGN 285
#define TYPEDEF_NAME 286
#define ENUMERATION_CONSTANT 287
#define TYPEDEF 288
#define EXTERN 289
#define STATIC 290
#define AUTO 291
#define REGISTER 292
#define T_INLINE 293
#define CONST 294
#define T_RESTRICT 295
#define VOLATILE 296
#define BOOL 297
#define CHAR 298
#define SHORT 299
#define INT 300
#define LONG 301
#define SIGNED 302
#define UNSIGNED 303
#define FLOAT 304
#define DOUBLE 305
#define VOID 306
#define COMPLEX 307
#define IMAGINARY 308
#define TYPEOF 309
#define CLASS 310
#define STRUCT 311
#define UNION 312
#define ENUM 313
#define ELLIPSIS 314
#define CASE 315
#define DEFAULT 316
#define IF 317
#define ELSE 318
#define SWITCH 319
#define WHILE 320
#define DO 321
#define FOR 322
#define GOTO 323
#define CONTINUE 324
#define BREAK 325
#define RETURN 326
#define ALIGNAS 327
#define ALIGNOF 328
#define ATOMIC 329
#define GENERIC 330
#define NORETURN 331
#define STATIC_ASSERT 332
#define THREAD_LOCAL 333




/* Copy the first part of user declarations.  */
#line 5 "src/parser.y"


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





/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 313 "src/parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  81
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   2759

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  103
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  301
/* YYNRULES -- Number of states.  */
#define YYNSTATES  521

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   333

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    93,     2,     2,     2,    95,    88,     2,
      79,    80,    89,    90,    81,    91,    85,    94,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    82,   102,
      96,   101,    97,   100,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    83,     2,    84,    98,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    86,    99,    87,    92,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,     9,    13,    15,    17,    19,
      21,    23,    25,    27,    34,    36,    40,    44,    48,    50,
      55,    59,    64,    68,    72,    75,    78,    85,    93,    95,
      99,   101,   104,   107,   110,   113,   118,   123,   125,   127,
     129,   131,   133,   135,   137,   142,   144,   148,   152,   156,
     158,   162,   166,   168,   172,   176,   178,   182,   186,   190,
     194,   196,   200,   204,   206,   210,   212,   216,   218,   222,
     224,   228,   230,   234,   236,   242,   244,   248,   250,   252,
     254,   256,   258,   260,   262,   264,   266,   268,   270,   272,
     276,   278,   281,   285,   287,   290,   292,   295,   298,   300,
     303,   305,   308,   310,   313,   315,   317,   321,   325,   327,
     329,   331,   333,   335,   337,   339,   341,   343,   345,   347,
     349,   351,   353,   355,   357,   359,   361,   363,   365,   367,
     369,   371,   376,   378,   380,   385,   391,   394,   396,   398,
     400,   403,   406,   410,   412,   415,   417,   420,   422,   424,
     428,   431,   435,   437,   442,   448,   454,   461,   464,   466,
     470,   474,   476,   481,   483,   485,   487,   489,   491,   493,
     498,   503,   506,   508,   510,   512,   516,   520,   525,   532,
     538,   544,   551,   557,   562,   567,   572,   576,   581,   585,
     588,   591,   593,   597,   600,   603,   605,   609,   612,   615,
     617,   619,   622,   626,   628,   630,   634,   637,   640,   642,
     644,   648,   651,   653,   656,   658,   660,   664,   667,   671,
     677,   682,   688,   693,   697,   701,   705,   710,   717,   723,
     729,   736,   741,   746,   749,   753,   757,   762,   766,   771,
     773,   776,   778,   783,   787,   790,   792,   795,   799,   802,
     810,   812,   814,   816,   818,   820,   822,   826,   831,   835,
     838,   842,   844,   847,   849,   851,   853,   856,   864,   870,
     876,   882,   890,   897,   905,   912,   920,   924,   927,   930,
     933,   937,   939,   942,   944,   945,   947,   952,   956,   962,
     964,   967,   969,   971,   975,   981,   988,   993,   997,  1001,
    1005,  1007
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     179,     0,    -1,     4,    -1,   105,    -1,   107,    -1,    79,
     129,    80,    -1,   108,    -1,     5,    -1,     6,    -1,    32,
      -1,     4,    -1,     7,    -1,     8,    -1,    75,    79,   127,
      81,   109,    80,    -1,   110,    -1,   109,    81,   110,    -1,
     160,    82,   127,    -1,    61,    82,   127,    -1,   104,    -1,
     111,    83,   129,    84,    -1,   111,    79,    80,    -1,   111,
      79,   112,    80,    -1,   111,    85,     4,    -1,   111,    10,
       4,    -1,   111,    11,    -1,   111,    12,    -1,    79,   160,
      80,    86,   164,    87,    -1,    79,   160,    80,    86,   164,
      81,    87,    -1,   127,    -1,   112,    81,   127,    -1,   111,
      -1,    11,   113,    -1,    12,   113,    -1,   114,   115,    -1,
       9,   113,    -1,     9,    79,   160,    80,    -1,    73,    79,
     160,    80,    -1,    88,    -1,    89,    -1,    90,    -1,    91,
      -1,    92,    -1,    93,    -1,   113,    -1,    79,   160,    80,
     115,    -1,   115,    -1,   116,    89,   115,    -1,   116,    94,
     115,    -1,   116,    95,   115,    -1,   116,    -1,   117,    90,
     116,    -1,   117,    91,   116,    -1,   117,    -1,   118,    13,
     117,    -1,   118,    14,   117,    -1,   118,    -1,   119,    96,
     118,    -1,   119,    97,   118,    -1,   119,    15,   118,    -1,
     119,    16,   118,    -1,   119,    -1,   120,    17,   119,    -1,
     120,    18,   119,    -1,   120,    -1,   121,    88,   120,    -1,
     121,    -1,   122,    98,   121,    -1,   122,    -1,   123,    99,
     122,    -1,   123,    -1,   124,    19,   123,    -1,   124,    -1,
     125,    20,   124,    -1,   125,    -1,   125,   100,   129,    82,
     126,    -1,   126,    -1,   113,   128,   127,    -1,   101,    -1,
      21,    -1,    22,    -1,    23,    -1,    24,    -1,    25,    -1,
      26,    -1,    27,    -1,    28,    -1,    29,    -1,    30,    -1,
     127,    -1,   129,    81,   127,    -1,   126,    -1,   132,   102,
      -1,   132,   133,   102,    -1,   168,    -1,   135,   132,    -1,
     135,    -1,   136,   132,    -1,   136,    85,    -1,   136,    -1,
     149,   132,    -1,   149,    -1,   150,   132,    -1,   150,    -1,
     151,   132,    -1,   151,    -1,   134,    -1,   133,    81,   134,
      -1,   152,   101,   163,    -1,   152,    -1,    33,    -1,    34,
      -1,    35,    -1,    78,    -1,    36,    -1,    37,    -1,    51,
      -1,    43,    -1,    44,    -1,    45,    -1,    46,    -1,    49,
      -1,    50,    -1,    47,    -1,    48,    -1,    42,    -1,    52,
      -1,    53,    -1,   148,    -1,   138,    -1,   145,    -1,    31,
      -1,    54,    79,   129,    80,    -1,     4,    -1,    31,    -1,
     139,    86,   140,    87,    -1,   139,   137,    86,   140,    87,
      -1,   139,   137,    -1,    56,    -1,    57,    -1,   141,    -1,
     140,   141,    -1,   142,   102,    -1,   142,   143,   102,    -1,
     168,    -1,   136,   142,    -1,   136,    -1,   149,   142,    -1,
     149,    -1,   144,    -1,   143,    81,   144,    -1,    82,   130,
      -1,   152,    82,   130,    -1,   152,    -1,    58,    86,   146,
      87,    -1,    58,    86,   146,    81,    87,    -1,    58,     4,
      86,   146,    87,    -1,    58,     4,    86,   146,    81,    87,
      -1,    58,     4,    -1,   147,    -1,   146,    81,   147,    -1,
     106,   101,   130,    -1,   106,    -1,    74,    79,   160,    80,
      -1,    39,    -1,    40,    -1,    41,    -1,    74,    -1,    38,
      -1,    76,    -1,    72,    79,   160,    80,    -1,    72,    79,
     130,    80,    -1,   154,   153,    -1,   153,    -1,     4,    -1,
       7,    -1,    79,   152,    80,    -1,   153,    83,    84,    -1,
     153,    83,    89,    84,    -1,   153,    83,    35,   155,   127,
      84,    -1,   153,    83,    35,   127,    84,    -1,   153,    83,
     155,    89,    84,    -1,   153,    83,   155,    35,   127,    84,
      -1,   153,    83,   155,   127,    84,    -1,   153,    83,   155,
      84,    -1,   153,    83,   127,    84,    -1,   153,    79,   156,
      80,    -1,   153,    79,    80,    -1,   153,    79,   159,    80,
      -1,    89,   155,   154,    -1,    89,   155,    -1,    89,   154,
      -1,    89,    -1,    88,   155,   154,    -1,    88,   155,    -1,
      88,   154,    -1,    88,    -1,    98,   155,   154,    -1,    98,
     155,    -1,    98,   154,    -1,    98,    -1,   149,    -1,   155,
     149,    -1,   157,    81,    59,    -1,   157,    -1,   158,    -1,
     157,    81,   158,    -1,   132,   152,    -1,   132,   161,    -1,
     132,    -1,     4,    -1,   159,    81,     4,    -1,   142,   161,
      -1,   142,    -1,   154,   162,    -1,   154,    -1,   162,    -1,
      79,   161,    80,    -1,    83,    84,    -1,    83,    89,    84,
      -1,    83,    35,   155,   127,    84,    -1,    83,    35,   127,
      84,    -1,    83,   155,    35,   127,    84,    -1,    83,   155,
     127,    84,    -1,    83,   155,    84,    -1,    83,   127,    84,
      -1,   162,    83,    84,    -1,   162,    83,    89,    84,    -1,
     162,    83,    35,   155,   127,    84,    -1,   162,    83,    35,
     127,    84,    -1,   162,    83,   155,   127,    84,    -1,   162,
      83,   155,    35,   127,    84,    -1,   162,    83,   155,    84,
      -1,   162,    83,   127,    84,    -1,    79,    80,    -1,    79,
     156,    80,    -1,   162,    79,    80,    -1,   162,    79,   156,
      80,    -1,    86,   164,    87,    -1,    86,   164,    81,    87,
      -1,   127,    -1,   165,   163,    -1,   163,    -1,   164,    81,
     165,   163,    -1,   164,    81,   163,    -1,   166,   101,    -1,
     167,    -1,   166,   167,    -1,    83,   130,    84,    -1,    85,
       4,    -1,    77,    79,   130,    81,     7,    80,   102,    -1,
     170,    -1,   171,    -1,   174,    -1,   175,    -1,   176,    -1,
     177,    -1,     4,    82,   169,    -1,    60,   130,    82,   169,
      -1,    61,    82,   169,    -1,    86,    87,    -1,    86,   172,
      87,    -1,   173,    -1,   172,   173,    -1,   131,    -1,   169,
      -1,   102,    -1,   129,   102,    -1,    62,    79,   129,    80,
     169,    63,   169,    -1,    62,    79,   129,    80,   169,    -1,
      64,    79,   129,    80,   169,    -1,    65,    79,   129,    80,
     169,    -1,    66,   169,    65,    79,   129,    80,   102,    -1,
      67,    79,   174,   174,    80,   169,    -1,    67,    79,   174,
     174,   129,    80,   169,    -1,    67,    79,   131,   174,    80,
     169,    -1,    67,    79,   131,   174,   129,    80,   169,    -1,
      68,     4,   102,    -1,    69,   102,    -1,    70,   102,    -1,
      71,   102,    -1,    71,   129,   102,    -1,   180,    -1,   178,
     180,    -1,   178,    -1,    -1,   184,    -1,    55,    93,     4,
     102,    -1,    55,     4,   102,    -1,    55,     4,    86,   140,
      87,    -1,   131,    -1,   154,   183,    -1,     4,    -1,     7,
      -1,   136,    85,   182,    -1,   136,    85,   182,    79,    80,
      -1,   136,    85,   182,    79,   156,    80,    -1,   132,   152,
     185,   171,    -1,   132,   152,   171,    -1,   132,   181,   171,
      -1,   132,   181,   102,    -1,   131,    -1,   185,   131,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    84,    84,    85,    89,    93,    97,   101,   102,   103,
     107,   111,   112,   116,   120,   121,   125,   126,   130,   134,
     138,   142,   146,   150,   154,   158,   162,   166,   173,   177,
     184,   188,   192,   196,   200,   204,   208,   215,   216,   217,
     218,   219,   220,   224,   228,   235,   239,   243,   247,   254,
     258,   262,   269,   273,   277,   284,   288,   292,   296,   300,
     307,   311,   315,   322,   326,   333,   337,   344,   348,   355,
     359,   366,   370,   377,   381,   389,   393,   400,   401,   402,
     403,   404,   405,   406,   407,   408,   409,   410,   414,   418,
     425,   429,   433,   439,   443,   447,   451,   455,   459,   463,
     467,   471,   475,   479,   483,   490,   494,   501,   505,   512,
     513,   514,   515,   516,   517,   521,   522,   523,   524,   525,
     526,   527,   528,   529,   530,   531,   532,   533,   534,   535,
     536,   537,   543,   543,   546,   550,   554,   561,   562,   566,
     570,   577,   581,   585,   589,   593,   597,   601,   608,   612,
     619,   620,   624,   631,   632,   633,   634,   635,   639,   640,
     644,   645,   649,   653,   654,   655,   656,   660,   661,   665,
     666,   670,   674,   681,   682,   687,   691,   692,   693,   694,
     695,   696,   697,   698,   699,   703,   707,   711,   718,   722,
     726,   730,   734,   738,   742,   746,   750,   754,   758,   762,
     769,   770,   775,   779,   786,   790,   797,   801,   805,   812,
     813,   817,   821,   828,   832,   836,   843,   844,   845,   846,
     847,   848,   849,   850,   851,   852,   853,   854,   855,   856,
     857,   858,   859,   860,   861,   862,   863,   867,   871,   875,
     882,   886,   890,   894,   901,   905,   906,   910,   911,   915,
     919,   920,   921,   922,   923,   924,   928,   932,   936,   943,
     947,   954,   958,   965,   969,   976,   977,   984,   989,   993,
    1000,  1004,  1008,  1013,  1018,  1023,  1031,  1035,  1039,  1043,
    1047,  1054,  1058,  1065,  1070,  1075,  1076,  1081,  1086,  1091,
    1096,  1103,  1104,  1112,  1116,  1120,  1128,  1129,  1133,  1140,
    1151,  1152
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "SCOPE", "IDENTIFIER",
  "I_CONSTANT", "F_CONSTANT", "STRING_LITERAL", "FUNC_NAME", "SIZEOF",
  "PTR_OP", "INC_OP", "DEC_OP", "LEFT_OP", "RIGHT_OP", "LE_OP", "GE_OP",
  "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN",
  "AND_ASSIGN", "XOR_ASSIGN", "OR_ASSIGN", "TYPEDEF_NAME",
  "ENUMERATION_CONSTANT", "TYPEDEF", "EXTERN", "STATIC", "AUTO",
  "REGISTER", "T_INLINE", "CONST", "T_RESTRICT", "VOLATILE", "BOOL",
  "CHAR", "SHORT", "INT", "LONG", "SIGNED", "UNSIGNED", "FLOAT", "DOUBLE",
  "VOID", "COMPLEX", "IMAGINARY", "TYPEOF", "CLASS", "STRUCT", "UNION",
  "ENUM", "ELLIPSIS", "CASE", "DEFAULT", "IF", "ELSE", "SWITCH", "WHILE",
  "DO", "FOR", "GOTO", "CONTINUE", "BREAK", "RETURN", "ALIGNAS", "ALIGNOF",
  "ATOMIC", "GENERIC", "NORETURN", "STATIC_ASSERT", "THREAD_LOCAL", "'('",
  "')'", "','", "':'", "'['", "']'", "'.'", "'{'", "'}'", "'&'", "'*'",
  "'+'", "'-'", "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'",
  "'?'", "'='", "';'", "$accept", "primary_expression", "constant",
  "enumeration_constant", "string", "generic_selection",
  "generic_assoc_list", "generic_association", "postfix_expression",
  "argument_expression_list", "unary_expression", "unary_operator",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "assignment_operator",
  "expression", "constant_expression", "declaration",
  "declaration_specifiers", "init_declarator_list", "init_declarator",
  "storage_class_specifier", "type_specifier", "id_or_typedef",
  "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "atomic_type_specifier", "type_qualifier", "function_specifier",
  "alignment_specifier", "declarator", "direct_declarator", "pointer",
  "type_qualifier_list", "parameter_type_list", "parameter_list",
  "parameter_declaration", "identifier_list", "type_name",
  "abstract_declarator", "direct_abstract_declarator", "initializer",
  "initializer_list", "designation", "designator_list", "designator",
  "static_assert_declaration", "statement", "labeled_statement",
  "compound_statement", "block_item_list", "block_item",
  "expression_statement", "selection_statement", "iteration_statement",
  "jump_statement", "translation_unit", "top", "external_declaration",
  "method_declarator", "method_name", "method_direct_declarator",
  "function_definition", "declaration_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,    40,
      41,    44,    58,    91,    93,    46,   123,   125,    38,    42,
      43,    45,   126,    33,    47,    37,    60,    62,    94,   124,
      63,    61,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   103,   104,   104,   104,   104,   104,   105,   105,   105,
     106,   107,   107,   108,   109,   109,   110,   110,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   112,   112,
     113,   113,   113,   113,   113,   113,   113,   114,   114,   114,
     114,   114,   114,   115,   115,   116,   116,   116,   116,   117,
     117,   117,   118,   118,   118,   119,   119,   119,   119,   119,
     120,   120,   120,   121,   121,   122,   122,   123,   123,   124,
     124,   125,   125,   126,   126,   127,   127,   128,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   129,   129,
     130,   131,   131,   131,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   133,   133,   134,   134,   135,
     135,   135,   135,   135,   135,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   137,   137,   138,   138,   138,   139,   139,   140,
     140,   141,   141,   141,   142,   142,   142,   142,   143,   143,
     144,   144,   144,   145,   145,   145,   145,   145,   146,   146,
     147,   147,   148,   149,   149,   149,   149,   150,   150,   151,
     151,   152,   152,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   154,   154,
     154,   154,   154,   154,   154,   154,   154,   154,   154,   154,
     155,   155,   156,   156,   157,   157,   158,   158,   158,   159,
     159,   160,   160,   161,   161,   161,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   162,   162,   163,   163,   163,
     164,   164,   164,   164,   165,   166,   166,   167,   167,   168,
     169,   169,   169,   169,   169,   169,   170,   170,   170,   171,
     171,   172,   172,   173,   173,   174,   174,   175,   175,   175,
     176,   176,   176,   176,   176,   176,   177,   177,   177,   177,
     177,   178,   178,   179,   179,   180,   180,   180,   180,   180,
     181,   182,   182,   183,   183,   183,   184,   184,   184,   184,
     185,   185
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     6,     1,     3,     3,     3,     1,     4,
       3,     4,     3,     3,     2,     2,     6,     7,     1,     3,
       1,     2,     2,     2,     2,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     5,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     2,     3,     1,     2,     1,     2,     2,     1,     2,
       1,     2,     1,     2,     1,     1,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     1,     4,     5,     2,     1,     1,     1,
       2,     2,     3,     1,     2,     1,     2,     1,     1,     3,
       2,     3,     1,     4,     5,     5,     6,     2,     1,     3,
       3,     1,     4,     1,     1,     1,     1,     1,     1,     4,
       4,     2,     1,     1,     1,     3,     3,     4,     6,     5,
       5,     6,     5,     4,     4,     4,     3,     4,     3,     2,
       2,     1,     3,     2,     2,     1,     3,     2,     2,     1,
       1,     2,     3,     1,     1,     3,     2,     2,     1,     1,
       3,     2,     1,     2,     1,     1,     3,     2,     3,     5,
       4,     5,     4,     3,     3,     3,     4,     6,     5,     5,
       6,     4,     4,     2,     3,     3,     4,     3,     4,     1,
       2,     1,     4,     3,     2,     1,     2,     3,     2,     7,
       1,     1,     1,     1,     1,     1,     3,     4,     3,     2,
       3,     1,     2,     1,     1,     1,     2,     7,     5,     5,
       5,     7,     6,     7,     6,     7,     3,     2,     2,     2,
       3,     1,     2,     1,     0,     1,     4,     3,     5,     1,
       2,     1,     1,     3,     5,     6,     4,     3,     3,     3,
       1,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
     284,   130,   109,   110,   111,   113,   114,   167,   163,   164,
     165,   124,   116,   117,   118,   119,   122,   123,   120,   121,
     115,   125,   126,     0,     0,   137,   138,     0,     0,   166,
     168,     0,   112,   289,     0,    95,    98,   128,     0,   129,
     127,   100,   102,   104,    93,   283,     0,   281,   285,     0,
       0,     0,   157,     0,     0,     0,     0,   173,   174,     0,
     195,   191,   199,    91,     0,   105,   108,   172,     0,     0,
      94,    97,    96,   132,   133,     0,   136,    99,   101,   103,
     282,     1,     2,     7,     8,    11,    12,     0,     0,     0,
       9,     0,     0,     0,    37,    38,    39,    40,    41,    42,
      18,     3,     4,     6,    30,    43,     0,    45,    49,    52,
      55,    60,    63,    65,    67,    69,    71,    73,    75,    88,
       0,     0,   287,     0,     0,    10,   161,     0,   158,    43,
      90,     0,   145,   212,   147,     0,     0,     0,     0,     0,
     166,   200,   194,   193,   190,   189,   198,   197,     0,    92,
       0,     0,   300,     0,   297,     0,     0,     0,     0,     0,
     171,   290,   299,   298,     0,   139,     0,   143,     0,     0,
      34,     0,    31,    32,     0,     0,     0,     0,     0,    24,
      25,     0,     0,     0,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    77,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   131,     0,     0,   286,
       0,     0,     0,   153,   170,   144,     0,     0,   214,   211,
     215,   146,   169,   162,     0,   175,   201,   192,   188,   196,
     106,   108,     2,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   259,   265,     0,   263,   264,   250,
     251,     0,   261,   252,   253,   254,   255,     0,   239,   107,
     301,   296,   209,   186,   208,     0,   203,   204,     0,     0,
     176,    38,     0,     0,     0,   134,   140,     0,   141,     0,
     148,   152,     0,     0,     0,     0,     0,     5,     0,    23,
      20,     0,    28,     0,    22,    76,    46,    47,    48,    50,
      51,    53,    54,    58,    59,    56,    57,    61,    62,    64,
      66,    68,    70,    72,     0,    89,   288,     0,   155,   160,
     154,   159,   233,     0,     0,     0,   217,    38,     0,     0,
     213,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   277,   278,   279,     0,   266,   260,   262,
       0,     0,   241,     0,     0,     0,   245,     0,   206,   214,
     207,   185,     0,   187,     0,     0,     0,   177,   184,     0,
     183,    38,     0,   291,   292,   293,   150,     0,   142,     0,
     135,    35,     0,    36,     0,     0,    44,    21,     0,    19,
       0,   156,   234,   216,     0,     0,   218,   224,     0,   223,
       0,   235,     0,     0,   225,    38,     0,     0,     0,   256,
       0,   258,     0,     0,     0,     0,     0,     0,   276,   280,
       0,   248,     0,   237,   240,   244,   246,   202,   205,   210,
     179,     0,     0,   180,   182,     0,   149,   151,     0,     0,
      14,     0,     0,    29,    74,   220,     0,     0,   222,   236,
       0,     0,   226,   232,     0,   231,     0,   249,   257,     0,
       0,     0,     0,     0,     0,   247,   238,   243,     0,   178,
     181,   294,     0,     0,    13,     0,     0,     0,    26,   219,
     221,   228,     0,     0,   229,   268,   269,   270,     0,     0,
       0,     0,     0,   242,   295,    17,    15,    16,    27,   227,
     230,     0,     0,   274,     0,   272,     0,   267,   271,   275,
     273
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   100,   101,   126,   102,   103,   449,   450,   104,   301,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   195,   256,   131,    33,   274,
      64,    65,    35,    36,    76,    37,    38,   164,   165,   133,
     289,   290,    39,   127,   128,    40,    41,    42,    43,   138,
      67,   139,   143,   333,   276,   277,   278,   451,   334,   230,
     362,   363,   364,   365,   366,    44,   258,   259,   260,   261,
     262,   263,   264,   265,   266,    45,    46,    47,    69,   385,
     161,    48,   155
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -336
static const yytype_int16 yypact[] =
{
    2476,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,  -336,  -336,   -43,    19,  -336,  -336,    16,     2,    63,
    -336,    98,  -336,  -336,   147,  2570,  2327,  -336,    42,  -336,
    -336,  2570,  2570,  2570,  -336,  2476,    96,  -336,  -336,  1831,
     -14,   162,   115,   199,  1003,  2685,  1831,  -336,  -336,   312,
     375,   375,   375,  -336,   -38,  -336,  1991,   160,   450,   112,
    -336,  -336,  -336,  -336,  -336,  2610,   137,  -336,  -336,  -336,
    -336,  -336,  -336,  -336,  -336,  -336,  -336,  1853,  1875,  1875,
    -336,   153,   158,  1003,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,  -336,  -336,  -336,    74,   412,  1831,  -336,   117,   -63,
     202,    41,   229,   167,   163,   164,   240,    -1,  -336,  -336,
     193,  2610,  -336,   180,   199,  -336,   165,   -49,  -336,  -336,
    -336,   189,  2685,   314,  2685,   204,   220,   228,   233,   126,
    -336,  -336,  -336,   375,  -336,   375,  -336,   375,   312,  -336,
     514,  1585,  -336,   147,  -336,  2273,  1943,  1093,    63,   236,
     160,  -336,  -336,  -336,  2120,  -336,   226,  -336,  2610,  1003,
    -336,  1003,  -336,  -336,  2685,  1831,   196,   243,   327,  -336,
    -336,  1607,  1831,   333,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,  -336,  -336,  -336,  -336,  1831,  -336,  1831,  1831,  1831,
    1831,  1831,  1831,  1831,  1831,  1831,  1831,  1831,  1831,  1831,
    1831,  1831,  1831,  1831,  1831,  1831,  -336,  1831,  2169,  -336,
     -26,  1831,    26,  -336,  -336,  -336,  2060,  1115,   161,  -336,
     175,  -336,  -336,  -336,   335,  -336,  -336,  -336,  -336,  -336,
    -336,   252,   262,  1831,   264,   281,   283,   286,   753,   290,
     381,   277,   292,   797,  -336,  -336,   -37,  -336,  -336,  -336,
    -336,   606,  -336,  -336,  -336,  -336,  -336,  1563,  -336,  -336,
    -336,  -336,  -336,  -336,   260,   316,   317,  -336,   206,  1429,
    -336,   315,   320,  1205,    97,  -336,  -336,  1831,  -336,    54,
    -336,   323,  2218,   329,   331,   339,   332,  -336,  1697,  -336,
    -336,   215,  -336,   176,  -336,  -336,  -336,  -336,  -336,   117,
     117,   -63,   -63,   202,   202,   202,   202,    41,    41,   229,
     167,   163,   164,   240,   216,  -336,  -336,    37,  -336,  -336,
    -336,  -336,  -336,   340,   342,  1429,  -336,   341,   346,  1227,
     175,  2380,  1317,   344,   753,   362,   753,  1831,  1831,  1831,
     380,   698,   345,  -336,  -336,  -336,    59,  -336,  -336,  -336,
    1831,   442,  -336,    84,  1585,   -35,  -336,   915,  -336,    91,
    -336,  -336,  2524,  -336,   446,   368,  1429,  -336,  -336,  1831,
    -336,   369,   371,  -336,  -336,   377,  -336,   268,  -336,  1831,
    -336,   373,   373,  -336,  2649,  1563,  -336,  -336,  1831,  -336,
    1831,  -336,  -336,  -336,   376,  1429,  -336,  -336,  1831,  -336,
     378,  -336,   385,  1429,  -336,   383,   384,  1339,   367,  -336,
     753,  -336,   230,   237,   245,   392,   845,   845,  -336,  -336,
     388,  -336,  1451,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,   390,   391,  -336,  -336,  2428,  -336,  -336,   394,   249,
    -336,   395,   132,  -336,  -336,  -336,   396,   398,  -336,  -336,
     399,  1429,  -336,  -336,  1831,  -336,   400,  -336,  -336,   753,
     753,   753,  1831,  1719,  1741,  -336,  -336,  -336,  1585,  -336,
    -336,  -336,   406,  1831,  -336,  2649,  1831,  1473,  -336,  -336,
    -336,  -336,   403,   404,  -336,   415,  -336,  -336,   253,   753,
     291,   753,   293,  -336,  -336,  -336,  -336,  -336,  -336,  -336,
    -336,   753,   387,  -336,   753,  -336,   753,  -336,  -336,  -336,
    -336
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -336,  -336,  -336,  -336,  -336,  -336,  -336,    -6,  -336,  -336,
     -19,  -336,   -90,   183,   184,    87,   181,   280,   294,   279,
     296,   297,  -336,   -25,    53,  -336,   -46,   -22,   -44,    17,
    -336,   364,  -336,   -42,  -336,  -336,  -336,   -50,  -124,    88,
    -336,   123,  -336,   408,  -208,  -336,   -54,  -336,  -336,   -32,
     -57,    15,   -52,  -141,  -336,   143,  -336,   -30,  -129,  -223,
    -133,   121,  -335,  -336,   168,   -21,   -93,  -336,   -24,  -336,
     266,  -277,  -336,  -336,  -336,  -336,  -336,   483,  -336,  -336,
    -336,  -336,  -336
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     134,   134,    66,   120,   229,   340,   141,   141,   141,   145,
     147,   160,   132,   132,   331,   275,   196,    34,   269,   214,
      52,   134,   152,    50,   135,   136,   159,   200,   201,   130,
     125,   130,   222,   132,   137,   129,    49,   129,   223,   134,
     286,   125,   154,   148,   217,   163,    73,   176,   360,    68,
     361,   132,    70,    72,   167,   327,   204,   205,    77,    78,
      79,   328,    34,   177,   149,   357,   435,   134,   170,   172,
     173,   218,   121,    74,   427,   142,   144,   146,   134,   132,
     134,    54,   160,   153,   178,   179,   180,   129,   122,   236,
     132,   236,   132,   236,   286,    57,    81,   478,    58,   215,
     167,   383,    53,   141,   384,   283,   257,   306,   307,   308,
     134,   270,    51,   330,   134,   134,   241,   134,   292,   331,
     134,   241,   132,   176,   401,   176,   132,   132,    75,   132,
      57,   271,   132,    58,   291,   387,   303,   206,   207,   293,
     217,   294,    55,   167,   295,   370,   340,   167,   228,   473,
     474,    57,   478,   181,    58,   350,   388,   182,   237,   183,
     238,   429,   239,   166,   134,   432,   123,   153,   286,   324,
     367,   433,   153,   141,   227,   339,   132,    56,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   130,   167,   150,   329,
     412,   124,   129,   125,   268,    59,   197,   356,   396,   166,
     282,   198,   199,   487,   162,   202,   203,   257,   130,   488,
     225,   345,   231,   168,   129,   141,    59,   376,   296,   236,
      57,   434,   174,    58,   302,    60,    61,   175,   134,   156,
     226,   228,   368,   157,   227,    62,   208,   209,   305,    63,
     132,   419,   166,   421,   341,   210,   166,   217,   342,   213,
     399,   211,   130,   212,    57,   386,   221,    58,   129,   224,
     325,   167,    57,   216,   217,    58,   297,   217,   153,   129,
     338,   141,   219,   405,   232,   236,   373,   374,   141,   369,
     417,   313,   314,   315,   316,   397,   398,   217,   400,   477,
     233,   422,   423,   424,   482,    59,   166,   426,   287,   234,
     469,   217,   160,   235,    60,    61,    57,   470,   217,    58,
     268,   284,   236,   298,    62,   471,   217,   468,   288,   484,
     485,   299,   375,   512,   217,   130,   382,   304,   430,   367,
     134,   129,   343,   227,   344,   503,   346,    59,    60,    61,
     287,   236,   132,   151,   477,   291,    60,    61,    62,   141,
     347,   461,   348,   236,   130,   349,    62,   447,   153,   351,
     129,   514,   217,   516,   217,   454,   495,   496,   497,   353,
     166,   129,   369,   309,   310,   352,   311,   312,   404,   317,
     318,    59,   410,   226,   354,   416,   371,   227,   372,   377,
      60,    61,    60,    61,   378,   389,   513,   236,   515,   391,
      62,   392,    62,   394,     8,     9,    10,   268,   517,   393,
     402,   519,   403,   520,   418,   406,   498,   500,   502,   441,
     407,   134,   442,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   132,   420,   425,   431,   428,   268,   140,
     439,   453,   440,   443,    57,   444,   445,    58,   456,   395,
     455,   457,   458,    60,    61,   459,   460,   462,   463,   467,
     466,   472,   475,    62,   479,   480,   483,   486,   511,   506,
     489,     1,   490,   491,   494,   268,   504,   509,   510,   518,
     319,   321,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,   320,    25,    26,    27,   322,
     446,   323,   240,   194,   492,   438,   452,   493,   242,    83,
      84,    85,    86,    87,   158,    88,    89,   359,    80,    59,
       0,   268,   220,   436,     0,     0,   505,     0,     0,   507,
     268,     0,     0,     0,     0,     1,    90,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,     0,
      25,    26,    27,     0,   243,   244,   245,     0,   246,   247,
     248,   249,   250,   251,   252,   253,    28,    91,    29,    92,
      30,    31,    32,    93,     0,     0,     0,     0,     0,     0,
     150,   254,    94,    95,    96,    97,    98,    99,     0,     0,
     242,    83,    84,    85,    86,    87,   255,    88,    89,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     1,    90,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,     0,    25,    26,    27,     0,   243,   244,   245,     0,
     246,   247,   248,   249,   250,   251,   252,   253,    28,    91,
      29,    92,    30,    31,    32,    93,     0,     0,     0,     0,
       0,     0,   150,   358,    94,    95,    96,    97,    98,    99,
       0,     0,    82,    83,    84,    85,    86,    87,   255,    88,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     1,
      90,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,     0,    25,    26,    27,   242,    83,    84,
      85,    86,    87,     0,    88,    89,     0,     0,     0,     0,
      28,    91,    29,    92,    30,    31,    32,    93,     0,     0,
       0,     0,     0,     0,     0,    90,    94,    95,    96,    97,
      98,    99,     0,     0,     0,     0,     0,     0,     0,     0,
     255,    82,    83,    84,    85,    86,    87,     0,    88,    89,
       0,     0,     0,   243,   244,   245,     0,   246,   247,   248,
     249,   250,   251,   252,   253,     0,    91,     0,    92,    90,
       0,     0,    93,     0,     0,     0,     0,     0,     0,   150,
       0,    94,    95,    96,    97,    98,    99,     0,     0,    82,
      83,    84,    85,    86,    87,   255,    88,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,     0,    92,     0,     0,     0,    93,    90,     0,     0,
       0,     0,     0,     0,     0,    94,    95,    96,    97,    98,
      99,     0,     0,     0,     0,     0,     0,     0,     0,   355,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    91,    57,
      92,     0,    58,     0,    93,     0,     0,     0,     0,     0,
       0,     0,     0,    94,    95,    96,    97,    98,    99,     0,
       0,     0,     0,     0,     0,     0,     1,   255,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       0,    25,    26,    27,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,     0,    29,
       0,    30,     0,    32,   367,   332,     0,     0,   227,     0,
       0,     0,     0,    60,    61,     0,     0,    82,    83,    84,
      85,    86,    87,    62,    88,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     1,    90,     0,     0,     0,     0,
       0,     0,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     0,    25,
      26,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    91,    29,    92,     0,
       0,     0,    93,     0,     0,     0,     0,     0,     0,     0,
       0,    94,    95,    96,    97,    98,    99,    82,    83,    84,
      85,    86,    87,     0,    88,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
      83,    84,    85,    86,    87,    90,    88,    89,   279,     0,
       0,     0,     8,     9,    10,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    90,     0,     0,
     335,     0,     0,     0,     8,     9,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    91,   140,    92,     0,
       0,     0,    93,     0,     0,     0,     0,   280,     0,     0,
       0,    94,   281,    96,    97,    98,    99,     0,    91,   140,
      92,     0,     0,     0,    93,     0,     0,     0,     0,   336,
       0,     0,     0,    94,   337,    96,    97,    98,    99,    82,
      83,    84,    85,    86,    87,     0,    88,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    82,    83,    84,    85,    86,    87,    90,    88,    89,
     379,     0,     0,     0,     8,     9,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    90,
       0,     0,   408,     0,     0,     0,     8,     9,    10,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    91,   140,
      92,     0,     0,     0,    93,     0,     0,     0,     0,   380,
       0,     0,     0,    94,   381,    96,    97,    98,    99,     0,
      91,   140,    92,     0,     0,     0,    93,     0,     0,     0,
       0,   409,     0,     0,     0,    94,    95,    96,    97,    98,
      99,    82,    83,    84,    85,    86,    87,     0,    88,    89,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    82,    83,    84,    85,    86,    87,    90,
      88,    89,   413,     0,     0,     0,     8,     9,    10,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    90,     0,     0,   464,     0,     0,     0,     8,     9,
      10,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,   140,    92,     0,     0,     0,    93,     0,     0,     0,
       0,   414,     0,     0,     0,    94,   415,    96,    97,    98,
      99,     0,    91,   140,    92,     0,     0,     0,    93,     0,
       0,     0,     0,   465,     0,     0,     0,    94,    95,    96,
      97,    98,    99,    82,    83,    84,    85,    86,    87,     0,
      88,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,    83,    84,    85,    86,
      87,    90,    88,    89,     0,     0,     0,     0,     8,     9,
      10,     0,     0,     0,     0,     0,     0,    82,    83,    84,
      85,    86,    87,    90,    88,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    91,   140,    92,    90,     0,     0,    93,     0,
       0,     0,     0,     0,     0,     0,     0,    94,    95,    96,
      97,    98,    99,     0,    91,     0,    92,     0,     0,     0,
      93,     0,     0,     0,   360,     0,   361,   267,   476,    94,
      95,    96,    97,    98,    99,     0,    91,     0,    92,     0,
       0,     0,    93,     0,     0,     0,   360,     0,   361,   267,
     508,    94,    95,    96,    97,    98,    99,    82,    83,    84,
      85,    86,    87,     0,    88,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
      83,    84,    85,    86,    87,    90,    88,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    82,    83,    84,    85,    86,    87,    90,    88,    89,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    91,     0,    92,    90,
       0,     0,    93,     0,     0,     0,   360,     0,   361,   267,
       0,    94,    95,    96,    97,    98,    99,     0,    91,     0,
      92,     0,     0,     0,    93,     0,     0,     0,     0,     0,
       0,   267,     0,    94,    95,    96,    97,    98,    99,     0,
      91,     0,    92,     0,     0,     0,    93,   300,     0,     0,
       0,     0,     0,     0,     0,    94,    95,    96,    97,    98,
      99,    82,    83,    84,    85,    86,    87,     0,    88,    89,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    82,    83,    84,    85,    86,    87,    90,
      88,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    82,    83,    84,    85,    86,
      87,    90,    88,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,     0,    92,    90,     0,     0,    93,     0,     0,     0,
       0,     0,     0,   395,     0,    94,    95,    96,    97,    98,
      99,     0,    91,     0,    92,     0,     0,     0,    93,   499,
       0,     0,     0,     0,     0,     0,     0,    94,    95,    96,
      97,    98,    99,     0,    91,     0,    92,     0,     0,     0,
      93,   501,     0,     0,     0,     0,     0,     0,     0,    94,
      95,    96,    97,    98,    99,    82,    83,    84,    85,    86,
      87,     0,    88,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    82,    83,    84,
      85,    86,    87,    90,    88,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    82,
      83,    84,    85,    86,    87,    90,    88,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,     0,    92,    90,     0,     0,
      93,     0,     0,     0,     0,     0,     0,     0,     0,    94,
      95,    96,    97,    98,    99,     0,    91,     0,    92,     0,
       0,     0,   169,     0,     0,     0,     0,     0,     0,     0,
       0,    94,    95,    96,    97,    98,    99,   272,    91,     0,
      92,     0,     0,     0,   171,     0,     0,     0,     0,     0,
       0,     0,     0,    94,    95,    96,    97,    98,    99,     0,
       0,     0,     0,     0,     1,     0,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     0,    25,
      26,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,     0,    29,     0,    30,
       0,    32,     1,   273,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,     0,    25,    26,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    28,     0,    29,     0,    30,    31,    32,
       0,     0,     0,     0,     0,     0,     0,   150,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,   151,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     0,    25,    26,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,     0,    29,     0,    30,     0,    32,   226,
     332,     0,     0,   227,     0,     0,     0,     0,    60,    61,
       0,     1,     0,     0,     0,     0,     0,     0,    62,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     0,    25,    26,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,     0,     0,    31,     0,     0,
       1,     0,     0,     0,     0,     0,     0,   285,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,     0,    25,    26,    27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,     0,     0,    31,     0,     0,     1,
       0,     0,     0,     0,     0,     0,   326,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,     0,    25,    26,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    29,     0,     0,    31,     0,     0,     0,     0,
       0,     0,     0,     0,     1,   390,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,     0,    25,
      26,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,     0,    29,     0,    30,
      31,    32,     0,     0,     0,     0,     0,     0,     1,   150,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,     0,    25,    26,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
       0,    29,     0,    30,     0,    32,     0,     0,     0,     0,
       0,     1,    71,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     0,    25,    26,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,     0,    29,     0,    30,     0,    32,     1,
     411,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,     0,    25,    26,    27,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      28,     0,    29,     0,    30,     0,    32,     1,   481,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,     0,
      29,     0,    30,    31,    32,     1,     0,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,     0,
      25,    26,    27,   437,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,    29,     0,
      30,     1,    32,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     0,    25,    26,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,    28,     0,    29,     0,    30,     0,    32,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,     0,    25,    26,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     0,     0,     0,    29,     0,     0,    31,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,     0,    25,    26,    27,     0,     0,
     448,     0,     0,     0,     0,     0,     1,     0,     0,     0,
       0,     0,     0,    29,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       0,    25,    26,    27,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29
};

static const yytype_int16 yycheck[] =
{
      54,    55,    34,    49,   133,   228,    60,    61,    62,    61,
      62,    68,    54,    55,   222,   156,   106,     0,   151,    20,
       4,    75,    66,     4,    54,    55,    68,    90,    91,    54,
       4,    56,    81,    75,    56,    54,    79,    56,    87,    93,
     164,     4,    66,    81,    81,    69,     4,    93,    83,    34,
      85,    93,    35,    36,    75,    81,    15,    16,    41,    42,
      43,    87,    45,    93,   102,   102,   101,   121,    87,    88,
      89,   121,    86,    31,   351,    60,    61,    62,   132,   121,
     134,    79,   139,    66,    10,    11,    12,   106,   102,   143,
     132,   145,   134,   147,   218,     4,     0,   432,     7,   100,
     121,     4,    86,   157,     7,   157,   150,   197,   198,   199,
     164,   155,    93,    87,   168,   169,   148,   171,   168,   327,
     174,   153,   164,   169,    87,   171,   168,   169,    86,   171,
       4,   155,   174,     7,   166,    81,   182,    96,    97,   169,
      81,   171,    79,   164,   174,   274,   369,   168,   133,   426,
     427,     4,   487,    79,     7,   248,   102,    83,   143,    85,
     145,   102,   147,    75,   218,    81,     4,   150,   292,   215,
      79,    87,   155,   227,    83,   227,   218,    79,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   221,   218,    86,   221,
     341,    86,   221,     4,   151,    79,    89,   253,   298,   121,
     157,    94,    95,    81,   102,    13,    14,   261,   243,    87,
     132,   243,   134,    86,   243,   279,    79,   279,   175,   283,
       4,   364,    79,     7,   181,    88,    89,    79,   292,    79,
      79,   226,   274,    83,    83,    98,    17,    18,   195,   102,
     292,   344,   164,   346,    79,    88,   168,    81,    83,    19,
      84,    98,   287,    99,     4,   287,   101,     7,   287,    80,
     217,   292,     4,    80,    81,     7,    80,    81,   261,   298,
     227,   335,   102,   335,    80,   339,    80,    81,   342,   274,
     342,   204,   205,   206,   207,    80,    81,    81,    82,   432,
      80,   347,   348,   349,   445,    79,   218,   351,    82,    81,
      80,    81,   369,    80,    88,    89,     4,    80,    81,     7,
     267,    85,   376,    80,    98,    80,    81,   420,   102,    80,
      81,     4,   279,    80,    81,   360,   283,     4,   360,    79,
     394,   360,     7,    83,    82,   478,    82,    79,    88,    89,
      82,   405,   394,   101,   487,   387,    88,    89,    98,   413,
      79,   413,    79,   417,   389,    79,    98,   389,   351,    79,
     389,    80,    81,    80,    81,   400,   469,   470,   471,   102,
     292,   400,   367,   200,   201,     4,   202,   203,   335,   208,
     209,    79,   339,    79,   102,   342,    80,    83,    81,    84,
      88,    89,    88,    89,    84,    82,   499,   461,   501,    80,
      98,    80,    98,    81,    39,    40,    41,   364,   511,    80,
      80,   514,    80,   516,    80,    84,   472,   473,   474,   376,
      84,   485,   379,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,   485,    82,    65,     4,   102,   395,    74,
       4,   398,    84,    84,     4,    84,    79,     7,   405,    86,
      84,   408,    84,    88,    89,    80,   413,    84,    84,   102,
     417,    79,    84,    98,    84,    84,    82,    82,    63,   485,
      84,    31,    84,    84,    84,   432,    80,    84,    84,   102,
     210,   212,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,   211,    56,    57,    58,   213,
     387,   214,   148,   101,   461,   372,   395,   464,     4,     5,
       6,     7,     8,     9,    74,    11,    12,   261,    45,    79,
      -1,   478,   124,   365,    -1,    -1,   483,    -1,    -1,   486,
     487,    -1,    -1,    -1,    -1,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      56,    57,    58,    -1,    60,    61,    62,    -1,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    91,    92,    93,    -1,    -1,
       4,     5,     6,     7,     8,     9,   102,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    -1,    56,    57,    58,    -1,    60,    61,    62,    -1,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    90,    91,    92,    93,
      -1,    -1,     4,     5,     6,     7,     8,     9,   102,    11,
      12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    56,    57,    58,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    79,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    88,    89,    90,    91,
      92,    93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      -1,    -1,    -1,    60,    61,    62,    -1,    64,    65,    66,
      67,    68,    69,    70,    71,    -1,    73,    -1,    75,    32,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    -1,    86,
      -1,    88,    89,    90,    91,    92,    93,    -1,    -1,     4,
       5,     6,     7,     8,     9,   102,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    -1,    75,    -1,    -1,    -1,    79,    32,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,     4,
      75,    -1,     7,    -1,    79,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,   102,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    74,
      -1,    76,    -1,    78,    79,    80,    -1,    -1,    83,    -1,
      -1,    -1,    -1,    88,    89,    -1,    -1,     4,     5,     6,
       7,     8,     9,    98,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    32,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    -1,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,
       5,     6,     7,     8,     9,    32,    11,    12,    35,    -1,
      -1,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,
      35,    -1,    -1,    -1,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    75,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    84,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,    -1,    73,    74,
      75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    84,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,     4,
       5,     6,     7,     8,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     4,     5,     6,     7,     8,     9,    32,    11,    12,
      35,    -1,    -1,    -1,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    35,    -1,    -1,    -1,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
      75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    84,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    -1,
      73,    74,    75,    -1,    -1,    -1,    79,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     4,     5,     6,     7,     8,     9,    32,
      11,    12,    35,    -1,    -1,    -1,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    -1,    35,    -1,    -1,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,    75,    -1,    -1,    -1,    79,    -1,    -1,    -1,
      -1,    84,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,    -1,    73,    74,    75,    -1,    -1,    -1,    79,    -1,
      -1,    -1,    -1,    84,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,     4,     5,     6,     7,     8,     9,    -1,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     4,     5,     6,     7,     8,
       9,    32,    11,    12,    -1,    -1,    -1,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,
       7,     8,     9,    32,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    74,    75,    32,    -1,    -1,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    -1,    73,    -1,    75,    -1,    -1,    -1,
      79,    -1,    -1,    -1,    83,    -1,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    -1,    73,    -1,    75,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    83,    -1,    85,    86,
      87,    88,    89,    90,    91,    92,    93,     4,     5,     6,
       7,     8,     9,    -1,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,
       5,     6,     7,     8,     9,    32,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     4,     5,     6,     7,     8,     9,    32,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,    75,    32,
      -1,    -1,    79,    -1,    -1,    -1,    83,    -1,    85,    86,
      -1,    88,    89,    90,    91,    92,    93,    -1,    73,    -1,
      75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    -1,    88,    89,    90,    91,    92,    93,    -1,
      73,    -1,    75,    -1,    -1,    -1,    79,    80,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    88,    89,    90,    91,    92,
      93,     4,     5,     6,     7,     8,     9,    -1,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     4,     5,     6,     7,     8,     9,    32,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     4,     5,     6,     7,     8,
       9,    32,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    -1,    75,    32,    -1,    -1,    79,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    -1,    88,    89,    90,    91,    92,
      93,    -1,    73,    -1,    75,    -1,    -1,    -1,    79,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,    89,    90,
      91,    92,    93,    -1,    73,    -1,    75,    -1,    -1,    -1,
      79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,     4,     5,     6,     7,     8,
       9,    -1,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,     6,
       7,     8,     9,    32,    11,    12,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,
       5,     6,     7,     8,     9,    32,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    -1,    75,    32,    -1,    -1,
      79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    88,
      89,    90,    91,    92,    93,    -1,    73,    -1,    75,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    88,    89,    90,    91,    92,    93,     4,    73,    -1,
      75,    -1,    -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    88,    89,    90,    91,    92,    93,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    -1,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    -1,    74,    -1,    76,
      -1,    78,    31,    80,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    -1,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    -1,    74,    -1,    76,    77,    78,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,   101,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    56,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    74,    -1,    76,    -1,    78,    79,
      80,    -1,    -1,    83,    -1,    -1,    -1,    -1,    88,    89,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    98,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    56,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    77,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    87,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    -1,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    -1,    -1,    77,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    87,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    56,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    87,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    -1,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    -1,    74,    -1,    76,
      77,    78,    -1,    -1,    -1,    -1,    -1,    -1,    31,    86,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    -1,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      -1,    74,    -1,    76,    -1,    78,    -1,    -1,    -1,    -1,
      -1,    31,    85,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    56,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    74,    -1,    76,    -1,    78,    31,
      80,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    -1,    56,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    -1,    74,    -1,    76,    -1,    78,    31,    80,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,
      74,    -1,    76,    77,    78,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    -1,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    74,    -1,
      76,    31,    78,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    56,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    72,    -1,    74,    -1,    76,    -1,    78,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    -1,    56,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    74,    -1,    -1,    77,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    -1,    56,    57,    58,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      -1,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    31,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    72,    74,
      76,    77,    78,   131,   132,   135,   136,   138,   139,   145,
     148,   149,   150,   151,   168,   178,   179,   180,   184,    79,
       4,    93,     4,    86,    79,    79,    79,     4,     7,    79,
      88,    89,    98,   102,   133,   134,   152,   153,   154,   181,
     132,    85,   132,     4,    31,    86,   137,   132,   132,   132,
     180,     0,     4,     5,     6,     7,     8,     9,    11,    12,
      32,    73,    75,    79,    88,    89,    90,    91,    92,    93,
     104,   105,   107,   108,   111,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     129,    86,   102,     4,    86,     4,   106,   146,   147,   113,
     126,   130,   136,   142,   149,   160,   160,   130,   152,   154,
      74,   149,   154,   155,   154,   155,   154,   155,    81,   102,
      86,   101,   131,   132,   171,   185,    79,    83,    74,   136,
     153,   183,   102,   171,   140,   141,   142,   168,    86,    79,
     113,    79,   113,   113,    79,    79,   129,   160,    10,    11,
      12,    79,    83,    85,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,   101,   128,   115,    89,    94,    95,
      90,    91,    13,    14,    15,    16,    96,    97,    17,    18,
      88,    98,    99,    19,    20,   100,    80,    81,   140,   102,
     146,   101,    81,    87,    80,   142,    79,    83,   154,   161,
     162,   142,    80,    80,    81,    80,   149,   154,   154,   154,
     134,   152,     4,    60,    61,    62,    64,    65,    66,    67,
      68,    69,    70,    71,    87,   102,   129,   131,   169,   170,
     171,   172,   173,   174,   175,   176,   177,    86,   127,   163,
     131,   171,     4,    80,   132,   156,   157,   158,   159,    35,
      84,    89,   127,   155,    85,    87,   141,    82,   102,   143,
     144,   152,   140,   160,   160,   160,   127,    80,    80,     4,
      80,   112,   127,   129,     4,   127,   115,   115,   115,   116,
     116,   117,   117,   118,   118,   118,   118,   119,   119,   120,
     121,   122,   123,   124,   129,   127,    87,    81,    87,   130,
      87,   147,    80,   156,   161,    35,    84,    89,   127,   155,
     162,    79,    83,     7,    82,   130,    82,    79,    79,    79,
     169,    79,     4,   102,   102,   102,   129,   102,    87,   173,
      83,    85,   163,   164,   165,   166,   167,    79,   152,   154,
     161,    80,    81,    80,    81,   127,   155,    84,    84,    35,
      84,    89,   127,     4,     7,   182,   130,    81,   102,    82,
      87,    80,    80,    80,    81,    86,   115,    80,    81,    84,
      82,    87,    80,    80,   127,   155,    84,    84,    35,    84,
     127,    80,   156,    35,    84,    89,   127,   155,    80,   169,
      82,   169,   129,   129,   129,    65,   131,   174,   102,   102,
     130,     4,    81,    87,   163,   101,   167,    59,   158,     4,
      84,   127,   127,    84,    84,    79,   144,   130,    61,   109,
     110,   160,   164,   127,   126,    84,   127,   127,    84,    80,
     127,   155,    84,    84,    35,    84,   127,   102,   169,    80,
      80,    80,    79,   174,   174,    84,    87,   163,   165,    84,
      84,    80,   156,    82,    80,    81,    82,    81,    87,    84,
      84,    84,   127,   127,    84,   169,   169,   169,   129,    80,
     129,    80,   129,   163,    80,   127,   110,   127,    87,    84,
      84,    63,    80,   169,    80,   169,    80,   169,   102,   169,
     169
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif


  /* User initialization code.  */
#line 77 "src/parser.y"
{
  memset(&yylloc, 0, sizeof(yylloc));
}
/* Line 1078 of yacc.c.  */
#line 2340 "src/parser.c"
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 86 "src/parser.y"
    {
      (yyval) = cnode(N_LIT, (yyvsp[(1) - (1)]), 0, &(yyloc));
    ;}
    break;

  case 4:
#line 90 "src/parser.y"
    {
      (yyval) = cnode(N_LIT, (yyvsp[(1) - (1)]), 0, &(yyloc));
    ;}
    break;

  case 5:
#line 94 "src/parser.y"
    {
      (yyval) = cnode(N_BEXPR, (yyvsp[(2) - (3)]), 0, &(yyloc));
    ;}
    break;

  case 18:
#line 131 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 19:
#line 135 "src/parser.y"
    {
      (yyval) = cnode(N_INDEX, (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), &(yyloc));
    ;}
    break;

  case 20:
#line 139 "src/parser.y"
    {
      (yyval) = cnode(N_CALL, (yyvsp[(1) - (3)]), 0, &(yyloc));
    ;}
    break;

  case 21:
#line 143 "src/parser.y"
    {
      (yyval) = cnode(N_CALL, (yyvsp[(1) - (4)]), cn_flip((yyvsp[(3) - (4)])), &(yyloc));
    ;}
    break;

  case 22:
#line 147 "src/parser.y"
    {
      (yyval) = cnode(N_DOT, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), &(yyloc));
    ;}
    break;

  case 23:
#line 151 "src/parser.y"
    {
      (yyval) = cnode(N_ARROW, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), &(yyloc));
    ;}
    break;

  case 24:
#line 155 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(1) - (2)]), 0, &(yyloc));
    ;}
    break;

  case 25:
#line 159 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(1) - (2)]), 0, &(yyloc));
    ;}
    break;

  case 26:
#line 163 "src/parser.y"
    {
      (yyval) = (yyvsp[(5) - (6)]);
    ;}
    break;

  case 27:
#line 167 "src/parser.y"
    {
      (yyval) = (yyvsp[(5) - (7)]);
    ;}
    break;

  case 28:
#line 174 "src/parser.y"
    {
      (yyval) = cnode(N_BEXPR, (yyvsp[(1) - (1)]), 0, &(yyloc));
    ;}
    break;

  case 29:
#line 178 "src/parser.y"
    {
      (yyval) = cnode(N_BEXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 30:
#line 185 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 31:
#line 189 "src/parser.y"
    {
      (yyval) = (yyvsp[(2) - (2)]);
    ;}
    break;

  case 32:
#line 193 "src/parser.y"
    {
      (yyval) = (yyvsp[(2) - (2)]);
    ;}
    break;

  case 33:
#line 197 "src/parser.y"
    {
      (yyval) = cnode(N_UNARY, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), &(yyloc));
    ;}
    break;

  case 34:
#line 201 "src/parser.y"
    {
      (yyval) = cnode(N_SIZEOF, (yyvsp[(2) - (2)]), 0, &(yyloc));
    ;}
    break;

  case 35:
#line 205 "src/parser.y"
    {
      (yyval) = cnode(N_LIT, cnode(N_SIZEOF, (yyvsp[(3) - (4)]), 0, &(yyloc)), 0, &(yyloc));
    ;}
    break;

  case 36:
#line 209 "src/parser.y"
    {
      (yyval) = cnode(N_LIT, cnode(N_ALIGNOF, (yyvsp[(3) - (4)]), 0, &(yyloc)), 0, &(yyloc));
    ;}
    break;

  case 43:
#line 225 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 44:
#line 229 "src/parser.y"
    {
      (yyval) = cnode(N_CAST, (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]), &(yyloc));
    ;}
    break;

  case 45:
#line 236 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 46:
#line 240 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 47:
#line 244 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 48:
#line 248 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 49:
#line 255 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 50:
#line 259 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 51:
#line 263 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 52:
#line 270 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 53:
#line 274 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 54:
#line 278 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 55:
#line 285 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 56:
#line 289 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 57:
#line 293 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 58:
#line 297 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 59:
#line 301 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 60:
#line 308 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 61:
#line 312 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 62:
#line 316 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 63:
#line 323 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 64:
#line 327 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 65:
#line 334 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 66:
#line 338 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 67:
#line 345 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 68:
#line 349 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 69:
#line 356 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 70:
#line 360 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 71:
#line 367 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 72:
#line 371 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 73:
#line 378 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 74:
#line 382 "src/parser.y"
    {
      cnode_t *n = cnode(N_EXPR, (yyvsp[(5) - (5)]), 0, &(yyloc));
      (yyval) = cnode(N_EXPR, (yyvsp[(1) - (5)]), cnode(N_EXPR, (yyvsp[(3) - (5)]), n, &(yyloc)), &(yyloc));
    ;}
    break;

  case 75:
#line 390 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 76:
#line 394 "src/parser.y"
    {
      (yyval) = cnode(N_ASSIGN, (yyvsp[(1) - (3)]), cnode(N_CONS, (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), &(yyloc)), &(yyloc));
    ;}
    break;

  case 88:
#line 415 "src/parser.y"
    {
      (yyval) = cnode(N_BEXPR, (yyvsp[(1) - (1)]), 0, &(yyloc));
    ;}
    break;

  case 89:
#line 419 "src/parser.y"
    {
      (yyval) = cnode(N_BEXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 91:
#line 430 "src/parser.y"
    {
      (yyval) = cnode(N_DECL,(yyvsp[(1) - (2)]),0,&(yyloc));
    ;}
    break;

  case 92:
#line 434 "src/parser.y"
    {
      cnode_t *n = cnode(N_DECL,(yyvsp[(1) - (3)]),cn_flip((yyvsp[(2) - (3)])),&(yyloc));
      handle_typedef(n->head,n->tail);
      (yyval) = n;
    ;}
    break;

  case 94:
#line 444 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_STOR,(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),&(yyloc));
    ;}
    break;

  case 95:
#line 448 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_STOR,(yyvsp[(1) - (1)]),0,&(yyloc));
    ;}
    break;

  case 96:
#line 452 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_SPEC,(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),&(yyloc));
    ;}
    break;

  case 97:
#line 456 "src/parser.y"
    {
      (yyval) = cnode(N_MSCOPE,(yyvsp[(1) - (2)]),0,&(yyloc));
    ;}
    break;

  case 98:
#line 460 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_SPEC,(yyvsp[(1) - (1)]),0,&(yyloc));
    ;}
    break;

  case 99:
#line 464 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_QUAL,(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),&(yyloc));
    ;}
    break;

  case 100:
#line 468 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_QUAL,(yyvsp[(1) - (1)]),0,&(yyloc));
    ;}
    break;

  case 101:
#line 472 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_FN_SPEC,(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),&(yyloc));
    ;}
    break;

  case 102:
#line 476 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_FN_SPEC,(yyvsp[(1) - (1)]),0,&(yyloc));
    ;}
    break;

  case 103:
#line 480 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_FN_SPEC,(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),&(yyloc));
    ;}
    break;

  case 104:
#line 484 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_FN_SPEC,(yyvsp[(1) - (1)]),0,&(yyloc));
    ;}
    break;

  case 105:
#line 491 "src/parser.y"
    {
      (yyval) = cnode(N_VARS,(yyvsp[(1) - (1)]),0,&(yyloc));
    ;}
    break;

  case 106:
#line 495 "src/parser.y"
    {
      (yyval) = cnode(N_VARS,(yyvsp[(3) - (3)]),(yyvsp[(1) - (3)]),&(yyloc));
    ;}
    break;

  case 107:
#line 502 "src/parser.y"
    {
      (yyval) = cnode(N_VAR_DEF,(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),&(yyloc));
    ;}
    break;

  case 108:
#line 506 "src/parser.y"
    {
      (yyval) = cnode(N_VAR_DEF,(yyvsp[(1) - (1)]),0,&(yyloc));
    ;}
    break;

  case 131:
#line 538 "src/parser.y"
    {
      (yyval) = cnode(N_TYPEOF, (yyvsp[(3) - (4)]), 0, &(yyloc));
    ;}
    break;

  case 134:
#line 547 "src/parser.y"
    {
      (yyval) = cnode(N_STRUCT, cnode(0, (yyvsp[(1) - (4)]),0, &(yyloc)), cn_flip((yyvsp[(3) - (4)])), &(yyloc));
    ;}
    break;

  case 135:
#line 551 "src/parser.y"
    {
      (yyval) = cnode(N_STRUCT, cnode(0, (yyvsp[(1) - (5)]),(yyvsp[(2) - (5)]), &(yyloc)), cn_flip((yyvsp[(4) - (5)])), &(yyloc));
    ;}
    break;

  case 136:
#line 555 "src/parser.y"
    {
      (yyval) = cnode(N_STRUCT, cnode(0, (yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]), &(yyloc)), 0, &(yyloc));
    ;}
    break;

  case 139:
#line 567 "src/parser.y"
    {
      (yyval) = cnode(N_STRUCT_FIELD,(yyvsp[(1) - (1)]),0,&(yyloc));
    ;}
    break;

  case 140:
#line 571 "src/parser.y"
    {
      (yyval) = cnode(N_STRUCT_FIELD,(yyvsp[(2) - (2)]),(yyvsp[(1) - (2)]),&(yyloc));
    ;}
    break;

  case 141:
#line 578 "src/parser.y"
    {
      (yyval) = cnode(N_STRUCT_DECL,cn_flip((yyvsp[(1) - (2)])),0,&(yyloc));
    ;}
    break;

  case 142:
#line 582 "src/parser.y"
    {
      (yyval) = cnode(N_STRUCT_DECL,cn_flip((yyvsp[(1) - (3)])),(yyvsp[(2) - (3)]),&(yyloc));
    ;}
    break;

  case 144:
#line 590 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_SPEC,(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),&(yyloc));
    ;}
    break;

  case 145:
#line 594 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_SPEC,(yyvsp[(1) - (1)]),0,&(yyloc));
    ;}
    break;

  case 146:
#line 598 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_QUAL,(yyvsp[(1) - (2)]),(yyvsp[(2) - (2)]),&(yyloc));
    ;}
    break;

  case 147:
#line 602 "src/parser.y"
    {
      (yyval) = cnode(N_TYPE_QUAL,(yyvsp[(1) - (1)]),0,&(yyloc));
    ;}
    break;

  case 148:
#line 609 "src/parser.y"
    {
      (yyval) = cnode(0,(yyvsp[(1) - (1)]),0,&(yyloc));
    ;}
    break;

  case 149:
#line 613 "src/parser.y"
    {
      (yyval) = cnode(0,(yyvsp[(3) - (3)]),(yyvsp[(1) - (3)]),&(yyloc));
    ;}
    break;

  case 151:
#line 621 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (3)]);
    ;}
    break;

  case 152:
#line 625 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 171:
#line 671 "src/parser.y"
    {
      (yyval) = cnode(N_DECLARATOR, (yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]), &(yyloc));
    ;}
    break;

  case 172:
#line 675 "src/parser.y"
    {
      (yyval) = cnode(N_DECLARATOR, (yyvsp[(1) - (1)]), 0, &(yyloc));
    ;}
    break;

  case 174:
#line 683 "src/parser.y"
    {
      (yyvsp[(1) - (1)])->id = IDENTIFIER|N_TERM;
      (yyval) = (yyvsp[(1) - (1)])
    ;}
    break;

  case 175:
#line 688 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (3)]);
    ;}
    break;

  case 184:
#line 700 "src/parser.y"
    {
      (yyval) = cnode(N_ARRAY, (yyvsp[(1) - (4)]), 0, &(yyloc));
    ;}
    break;

  case 185:
#line 704 "src/parser.y"
    {
      (yyval) = cnode(N_DECL_FN, (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), &(yyloc));
    ;}
    break;

  case 186:
#line 708 "src/parser.y"
    {
      (yyval) = cnode(N_DECL_FN, (yyvsp[(1) - (3)]), 0, &(yyloc));
    ;}
    break;

  case 187:
#line 712 "src/parser.y"
    {
      (yyval) = cnode(N_DECL_FN, (yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]), &(yyloc));
    ;}
    break;

  case 188:
#line 719 "src/parser.y"
    {
      (yyval) = cnode(N_PTR, (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), &(yyloc));
    ;}
    break;

  case 189:
#line 723 "src/parser.y"
    {
      (yyval) = cnode(N_PTR, (yyvsp[(2) - (2)]), 0, &(yyloc));
    ;}
    break;

  case 190:
#line 727 "src/parser.y"
    {
      (yyval) = cnode(N_PTR, 0, (yyvsp[(2) - (2)]), &(yyloc));
    ;}
    break;

  case 191:
#line 731 "src/parser.y"
    {
      (yyval) = cnode(N_PTR, 0, 0, &(yyloc));
    ;}
    break;

  case 192:
#line 735 "src/parser.y"
    {
      (yyval) = cnode(N_REF, (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), &(yyloc));
    ;}
    break;

  case 193:
#line 739 "src/parser.y"
    {
      (yyval) = cnode(N_REF, (yyvsp[(2) - (2)]), 0, &(yyloc));
    ;}
    break;

  case 194:
#line 743 "src/parser.y"
    {
      (yyval) = cnode(N_REF, 0, (yyvsp[(2) - (2)]), &(yyloc));
    ;}
    break;

  case 195:
#line 747 "src/parser.y"
    {
      (yyval) = cnode(N_REF, 0, 0, &(yyloc));
    ;}
    break;

  case 196:
#line 751 "src/parser.y"
    {
      (yyval) = cnode(N_PTR, (yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]), &(yyloc));
    ;}
    break;

  case 197:
#line 755 "src/parser.y"
    {
      (yyval) = cnode(N_PTR, (yyvsp[(2) - (2)]), 0, &(yyloc));
    ;}
    break;

  case 198:
#line 759 "src/parser.y"
    {
      (yyval) = cnode(N_PTR, 0, (yyvsp[(2) - (2)]), &(yyloc));
    ;}
    break;

  case 199:
#line 763 "src/parser.y"
    {
      (yyval) = cnode(N_PTR, 0, 0, &(yyloc));
    ;}
    break;

  case 202:
#line 776 "src/parser.y"
    {
      (yyval) = cn_flip((yyvsp[(1) - (3)]));
    ;}
    break;

  case 203:
#line 780 "src/parser.y"
    {
      (yyval) = cn_flip((yyvsp[(1) - (1)]));
    ;}
    break;

  case 204:
#line 787 "src/parser.y"
    {
      (yyval) = cnode(N_PARAM_LIST,(yyvsp[(1) - (1)]),0,&(yyloc));
    ;}
    break;

  case 205:
#line 791 "src/parser.y"
    {
      (yyval) = cnode(N_PARAM_LIST,(yyvsp[(3) - (3)]),(yyvsp[(1) - (3)]),&(yyloc));
    ;}
    break;

  case 206:
#line 798 "src/parser.y"
    {
      (yyval) = cnode(N_PARAM, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), &(yyloc));
    ;}
    break;

  case 207:
#line 802 "src/parser.y"
    {
      (yyval) = cnode(N_PARAM, (yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]), &(yyloc));
    ;}
    break;

  case 208:
#line 806 "src/parser.y"
    {
      (yyval) = cnode(N_PARAM, (yyvsp[(1) - (1)]), 0, &(yyloc));
    ;}
    break;

  case 211:
#line 818 "src/parser.y"
    {
      (yyval) = cnode(N_TYPENAME,(yyvsp[(2) - (2)]),cn_flip((yyvsp[(1) - (2)])),&(yyloc));
    ;}
    break;

  case 212:
#line 822 "src/parser.y"
    {
      (yyval) = cnode(N_TYPENAME,0,cn_flip((yyvsp[(1) - (1)])),&(yyloc));
    ;}
    break;

  case 213:
#line 829 "src/parser.y"
    {
      (yyval) = cnode(N_DECLARATOR, (yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]), &(yyloc));
    ;}
    break;

  case 214:
#line 833 "src/parser.y"
    {
      (yyval) = cnode(N_DECLARATOR, 0, (yyvsp[(1) - (1)]), &(yyloc));
    ;}
    break;

  case 215:
#line 837 "src/parser.y"
    {
      (yyval) = cnode(N_DECLARATOR, (yyvsp[(1) - (1)]), 0, &(yyloc));
    ;}
    break;

  case 237:
#line 868 "src/parser.y"
    {
      (yyval) = (yyvsp[(2) - (3)]);
    ;}
    break;

  case 238:
#line 872 "src/parser.y"
    {
      (yyval) = (yyvsp[(2) - (4)]);
    ;}
    break;

  case 239:
#line 876 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 240:
#line 883 "src/parser.y"
    {
      (yyval) = (yyvsp[(2) - (2)]);
    ;}
    break;

  case 241:
#line 887 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 242:
#line 891 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(4) - (4)]), (yyvsp[(1) - (4)]), &(yyloc));
    ;}
    break;

  case 243:
#line 895 "src/parser.y"
    {
      (yyval) = cnode(N_EXPR, (yyvsp[(3) - (3)]), (yyvsp[(1) - (3)]), &(yyloc));
    ;}
    break;

  case 256:
#line 929 "src/parser.y"
    {
      (yyval) = cnode(N_LABEL, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]), &(yyloc));
    ;}
    break;

  case 257:
#line 933 "src/parser.y"
    {
      (yyval) = (yyvsp[(4) - (4)]);
    ;}
    break;

  case 258:
#line 937 "src/parser.y"
    {
      (yyval) = (yyvsp[(3) - (3)]);
    ;}
    break;

  case 259:
#line 944 "src/parser.y"
    {
      (yyval) = 0;
    ;}
    break;

  case 260:
#line 948 "src/parser.y"
    {
      (yyval) = cnode(N_BLOCK, cn_flip((yyvsp[(2) - (3)])), 0, &(yyloc));
    ;}
    break;

  case 261:
#line 955 "src/parser.y"
    {
      (yyval) = cnode(N_CONS, (yyvsp[(1) - (1)]), 0, &(yyloc));
    ;}
    break;

  case 262:
#line 959 "src/parser.y"
    {
      (yyval) = cnode(N_CONS, (yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]), &(yyloc));
    ;}
    break;

  case 263:
#line 966 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 264:
#line 970 "src/parser.y"
    {
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 266:
#line 978 "src/parser.y"
    {
      (yyval) = cn_flip((yyvsp[(1) - (2)]));
    ;}
    break;

  case 267:
#line 985 "src/parser.y"
    {
      cnode_t *n = cnode(N_CONS, (yyvsp[(7) - (7)]), 0, &(yyloc));
      (yyval) = cnode(N_IF, (yyvsp[(3) - (7)]), cnode(N_CONS, (yyvsp[(5) - (7)]), n, &(yyloc)), &(yyloc));
    ;}
    break;

  case 268:
#line 990 "src/parser.y"
    {
      (yyval) = cnode(N_IF, (yyvsp[(3) - (5)]), cnode(N_CONS, (yyvsp[(5) - (5)]), 0, &(yyloc)), &(yyloc));
    ;}
    break;

  case 269:
#line 994 "src/parser.y"
    {
      (yyval) = cnode(N_SWITCH, (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]), &(yyloc));
    ;}
    break;

  case 270:
#line 1001 "src/parser.y"
    {
      (yyval) = cnode(N_WHILE, (yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]), &(yyloc));
    ;}
    break;

  case 271:
#line 1005 "src/parser.y"
    {
      (yyval) = cnode(N_DOWHILE, (yyvsp[(2) - (7)]), (yyvsp[(5) - (7)]), &(yyloc));
    ;}
    break;

  case 272:
#line 1009 "src/parser.y"
    {
      cnode_t *n = cnode(N_CONS, (yyvsp[(6) - (6)]), 0, &(yyloc));
      (yyval) = cnode(N_FOR, (yyvsp[(3) - (6)]), cnode(N_CONS, (yyvsp[(4) - (6)]), n, &(yyloc)), &(yyloc));
    ;}
    break;

  case 273:
#line 1014 "src/parser.y"
    {
      cnode_t *n = cnode(N_CONS, (yyvsp[(5) - (7)]), cnode(N_CONS, (yyvsp[(7) - (7)]), 0, &(yyloc)), &(yyloc));
      (yyval) = cnode(N_FOR, (yyvsp[(3) - (7)]), cnode(N_CONS, (yyvsp[(4) - (7)]), n, &(yyloc)), &(yyloc));
    ;}
    break;

  case 274:
#line 1019 "src/parser.y"
    {
      cnode_t *n = cnode(N_CONS, (yyvsp[(6) - (6)]), 0, &(yyloc));
      (yyval) = cnode(N_FOR, (yyvsp[(3) - (6)]), cnode(N_CONS, (yyvsp[(4) - (6)]), n, &(yyloc)), &(yyloc));
    ;}
    break;

  case 275:
#line 1024 "src/parser.y"
    {
      cnode_t *n = cnode(N_CONS, (yyvsp[(5) - (7)]), cnode(N_CONS, (yyvsp[(7) - (7)]), 0, &(yyloc)), &(yyloc));
      (yyval) = cnode(N_FOR, (yyvsp[(3) - (7)]), cnode(N_CONS, (yyvsp[(4) - (7)]), n, &(yyloc)), &(yyloc));
    ;}
    break;

  case 276:
#line 1032 "src/parser.y"
    {
      (yyval) = cnode(N_GOTO,(yyvsp[(2) - (3)]),0,&(yyloc));
    ;}
    break;

  case 277:
#line 1036 "src/parser.y"
    {
      (yyval) = cnode(N_CONTINUE,0,0,&(yyloc));
    ;}
    break;

  case 278:
#line 1040 "src/parser.y"
    {
      (yyval) = cnode(N_BREAK,0,0,&(yyloc));
    ;}
    break;

  case 279:
#line 1044 "src/parser.y"
    {
      (yyval) = cnode(N_RETURN,0,0,&(yyloc));
    ;}
    break;

  case 280:
#line 1048 "src/parser.y"
    {
      (yyval) = cnode(N_RETURN,(yyvsp[(2) - (3)]),0,&(yyloc));
    ;}
    break;

  case 281:
#line 1055 "src/parser.y"
    {
      (yyval) = cnode(N_TOP,(yyvsp[(1) - (1)]),0,&(yyloc));
    ;}
    break;

  case 282:
#line 1059 "src/parser.y"
    {
      (yyval) = cnode(N_TOP,(yyvsp[(2) - (2)]),(yyvsp[(1) - (2)]),&(yyloc));
    ;}
    break;

  case 283:
#line 1066 "src/parser.y"
    {
      yyparse_result = cn_flip((yyvsp[(1) - (1)]));
    ;}
    break;

  case 284:
#line 1070 "src/parser.y"
    {
      yyparse_result = 0;
    ;}
    break;

  case 286:
#line 1077 "src/parser.y"
    {
      add_typedef_id((yyvsp[(3) - (4)])->text);
      (yyval) = cnode(N_NOT_CLASS, (yyvsp[(3) - (4)]), 0, &(yyloc));
    ;}
    break;

  case 287:
#line 1082 "src/parser.y"
    {
      add_typedef_id((yyvsp[(2) - (3)])->text);
      (yyval) = cnode(N_CLASS, (yyvsp[(2) - (3)]), 0, &(yyloc));
    ;}
    break;

  case 288:
#line 1087 "src/parser.y"
    {
      add_typedef_id((yyvsp[(2) - (5)])->text);
      (yyval) = cnode(N_CLASS, (yyvsp[(2) - (5)]), cn_flip((yyvsp[(4) - (5)])), &(yyloc));
    ;}
    break;

  case 290:
#line 1097 "src/parser.y"
    {
      (yyval) = cnode(N_DECLARATOR, (yyvsp[(2) - (2)]), (yyvsp[(1) - (2)]), &(yyloc));
    ;}
    break;

  case 292:
#line 1105 "src/parser.y"
    {
      (yyvsp[(1) - (1)])->id = IDENTIFIER|N_TERM;
      (yyval) = (yyvsp[(1) - (1)]);
    ;}
    break;

  case 293:
#line 1113 "src/parser.y"
    {
      (yyval) = cnode(N_MSCOPE,(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),&(yyloc));
    ;}
    break;

  case 294:
#line 1117 "src/parser.y"
    {
      (yyval) = cnode(N_MSCOPE,(yyvsp[(1) - (5)]),(yyvsp[(3) - (5)]),&(yyloc));
    ;}
    break;

  case 295:
#line 1121 "src/parser.y"
    {
      cnode_t *decl = cnode(N_DECL_FN, (yyvsp[(3) - (6)]), (yyvsp[(5) - (6)]), &(yyloc));
      (yyval) = cnode(N_MSCOPE,(yyvsp[(1) - (6)]),decl,&(yyloc));
    ;}
    break;

  case 297:
#line 1130 "src/parser.y"
    {
      (yyval) = cnode(N_FN_DEF,(yyvsp[(2) - (3)]),cnode(N_FN_DEF,(yyvsp[(1) - (3)]),(yyvsp[(3) - (3)]),&(yyloc)),&(yyloc));
    ;}
    break;

  case 298:
#line 1134 "src/parser.y"
    {
      cnode_t *scope = (yyvsp[(2) - (3)])->head;
      (yyvsp[(2) - (3)])->head = scope->tail;
      scope->tail = (yyvsp[(1) - (3)]);
      (yyval) = cnode(N_FN_DEF,(yyvsp[(2) - (3)]),cnode(N_FN_DEF,scope,(yyvsp[(3) - (3)]),&(yyloc)),&(yyloc));
    ;}
    break;

  case 299:
#line 1141 "src/parser.y"
    {
      cnode_t *scope = (yyvsp[(2) - (3)])->head;
      (yyvsp[(2) - (3)])->head = scope->tail;
      scope->tail = (yyvsp[(1) - (3)]);
      (yyval) = cnode(N_FN_DEF,(yyvsp[(2) - (3)]),cnode(N_FN_DEF,scope,(yyvsp[(3) - (3)]),&(yyloc)),&(yyloc));
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 3729 "src/parser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 1155 "src/parser.y"

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
