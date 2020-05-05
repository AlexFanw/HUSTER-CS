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
     DOT = 274,
     PLUS = 275,
     MINUS = 276,
     STAR = 277,
     DIV = 278,
     MOD = 279,
     ASSIGNOP = 280,
     PLUSASSIGNOP = 281,
     MINUSASSIGNOP = 282,
     STARASSIGNOP = 283,
     DIVASSIGNOP = 284,
     MODASSIGNOP = 285,
     AND = 286,
     OR = 287,
     NOT = 288,
     AUTOPLUS = 289,
     AUTOMINUS = 290,
     IF = 291,
     ELSE = 292,
     WHILE = 293,
     BREAK = 294,
     CONTINUE = 295,
     STRUCT = 296,
     RETURN = 297,
     FOR = 298,
     SWITCH = 299,
     CASE = 300,
     COLON = 301,
     DEFAULT = 302,
     EXT_DEF_LIST = 303,
     EXT_VAR_DEF = 304,
     FUNC_DEF = 305,
     FUNC_DEC = 306,
     EXT_DEC_LIST = 307,
     PARAM_LIST = 308,
     PARAM_DEC = 309,
     VAR_DEF = 310,
     DEC_LIST = 311,
     DEF_LIST = 312,
     COMP_STM = 313,
     STM_LIST = 314,
     EXP_STMT = 315,
     IF_THEN = 316,
     IF_THEN_ELSE = 317,
     FUNC_CALL = 318,
     ARGS = 319,
     FUNCTION = 320,
     PARAM = 321,
     ARG = 322,
     CALL = 323,
     LABEL = 324,
     GOTO = 325,
     JLT = 326,
     JLE = 327,
     JGT = 328,
     JGE = 329,
     EQ = 330,
     NEQ = 331,
     ARRAY_LIST = 332,
     ARRAY_ID = 333,
     UMINUS = 334,
     LOWER_THEN_ELSE = 335
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
#define DOT 274
#define PLUS 275
#define MINUS 276
#define STAR 277
#define DIV 278
#define MOD 279
#define ASSIGNOP 280
#define PLUSASSIGNOP 281
#define MINUSASSIGNOP 282
#define STARASSIGNOP 283
#define DIVASSIGNOP 284
#define MODASSIGNOP 285
#define AND 286
#define OR 287
#define NOT 288
#define AUTOPLUS 289
#define AUTOMINUS 290
#define IF 291
#define ELSE 292
#define WHILE 293
#define BREAK 294
#define CONTINUE 295
#define STRUCT 296
#define RETURN 297
#define FOR 298
#define SWITCH 299
#define CASE 300
#define COLON 301
#define DEFAULT 302
#define EXT_DEF_LIST 303
#define EXT_VAR_DEF 304
#define FUNC_DEF 305
#define FUNC_DEC 306
#define EXT_DEC_LIST 307
#define PARAM_LIST 308
#define PARAM_DEC 309
#define VAR_DEF 310
#define DEC_LIST 311
#define DEF_LIST 312
#define COMP_STM 313
#define STM_LIST 314
#define EXP_STMT 315
#define IF_THEN 316
#define IF_THEN_ELSE 317
#define FUNC_CALL 318
#define ARGS 319
#define FUNCTION 320
#define PARAM 321
#define ARG 322
#define CALL 323
#define LABEL 324
#define GOTO 325
#define JLT 326
#define JLE 327
#define JGT 328
#define JGE 329
#define EQ 330
#define NEQ 331
#define ARRAY_LIST 332
#define ARRAY_ID 333
#define UMINUS 334
#define LOWER_THEN_ELSE 335




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "parser.y"
{
	int    type_int;
        char   type_char;
	float  type_float;
	char   type_id[32];
	struct ASTNode *ptr;
}
/* Line 1529 of yacc.c.  */
#line 217 "parser.tab.h"
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
