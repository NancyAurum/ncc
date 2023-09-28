/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

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

extern YYLTYPE yylloc;
