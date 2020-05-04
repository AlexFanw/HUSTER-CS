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
     CHAR = 258,
     INT = 259,
     ID = 260,
     STRING = 261,
     RELOP = 262,
     TYPE = 263,
     FLOAT = 264,
     DPLUS = 265,
     LP = 266,
     RP = 267,
     LC = 268,
     RC = 269,
     LB = 270,
     RB = 271,
     SEMI = 272,
     COMMA = 273,
     PLUS = 274,
     MINUS = 275,
     STAR = 276,
     DIV = 277,
     MOD = 278,
     ASSIGNOP = 279,
     PLUSASSIGNOP = 280,
     MINUSASSIGNOP = 281,
     STARASSIGNOP = 282,
     DIVASSIGNOP = 283,
     MODASSIGNOP = 284,
     AND = 285,
     OR = 286,
     NOT = 287,
     AUTOPLUS = 288,
     AUTOMINUS = 289,
     IF = 290,
     ELSE = 291,
     WHILE = 292,
     RETURN = 293,
     FOR = 294,
     SWITCH = 295,
     CASE = 296,
     COLON = 297,
     DEFAULT = 298,
     EXT_DEF_LIST = 299,
     EXT_VAR_DEF = 300,
     FUNC_DEF = 301,
     FUNC_DEC = 302,
     EXT_DEC_LIST = 303,
     PARAM_LIST = 304,
     PARAM_DEC = 305,
     VAR_DEF = 306,
     DEC_LIST = 307,
     DEF_LIST = 308,
     COMP_STM = 309,
     STM_LIST = 310,
     EXP_STMT = 311,
     IF_THEN = 312,
     IF_THEN_ELSE = 313,
     FUNC_CALL = 314,
     ARGS = 315,
     FUNCTION = 316,
     PARAM = 317,
     ARG = 318,
     CALL = 319,
     LABEL = 320,
     GOTO = 321,
     JLT = 322,
     JLE = 323,
     JGT = 324,
     JGE = 325,
     EQ = 326,
     NEQ = 327,
     UMINUS = 328,
     LOWER_THEN_ELSE = 329
   };
#endif
/* Tokens.  */
#define CHAR 258
#define INT 259
#define ID 260
#define STRING 261
#define RELOP 262
#define TYPE 263
#define FLOAT 264
#define DPLUS 265
#define LP 266
#define RP 267
#define LC 268
#define RC 269
#define LB 270
#define RB 271
#define SEMI 272
#define COMMA 273
#define PLUS 274
#define MINUS 275
#define STAR 276
#define DIV 277
#define MOD 278
#define ASSIGNOP 279
#define PLUSASSIGNOP 280
#define MINUSASSIGNOP 281
#define STARASSIGNOP 282
#define DIVASSIGNOP 283
#define MODASSIGNOP 284
#define AND 285
#define OR 286
#define NOT 287
#define AUTOPLUS 288
#define AUTOMINUS 289
#define IF 290
#define ELSE 291
#define WHILE 292
#define RETURN 293
#define FOR 294
#define SWITCH 295
#define CASE 296
#define COLON 297
#define DEFAULT 298
#define EXT_DEF_LIST 299
#define EXT_VAR_DEF 300
#define FUNC_DEF 301
#define FUNC_DEC 302
#define EXT_DEC_LIST 303
#define PARAM_LIST 304
#define PARAM_DEC 305
#define VAR_DEF 306
#define DEC_LIST 307
#define DEF_LIST 308
#define COMP_STM 309
#define STM_LIST 310
#define EXP_STMT 311
#define IF_THEN 312
#define IF_THEN_ELSE 313
#define FUNC_CALL 314
#define ARGS 315
#define FUNCTION 316
#define PARAM 317
#define ARG 318
#define CALL 319
#define LABEL 320
#define GOTO 321
#define JLT 322
#define JLE 323
#define JGT 324
#define JGE 325
#define EQ 326
#define NEQ 327
#define UMINUS 328
#define LOWER_THEN_ELSE 329




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 17 "parser.y"
{
	int    type_int;
        char   type_char;
	float  type_float;
	char   type_id[32];
	struct ASTNode *ptr;
}
/* Line 1529 of yacc.c.  */
#line 205 "parser.tab.h"
	YYSTYPE;
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
