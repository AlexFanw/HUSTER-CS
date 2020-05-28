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
     INT = 258,
     ID = 259,
     RELOP = 260,
     TYPE = 261,
     CHAR = 262,
     FLOAT = 263,
     LP = 264,
     RP = 265,
     LB = 266,
     RB = 267,
     LC = 268,
     RC = 269,
     SEMI = 270,
     COMMA = 271,
     COMADD = 272,
     COMSUB = 273,
     COMSTAR = 274,
     COMDIV = 275,
     COMMOD = 276,
     PLUS = 277,
     MINUS = 278,
     STAR = 279,
     DIV = 280,
     MOD = 281,
     ASSIGNOP = 282,
     AND = 283,
     OR = 284,
     NOT = 285,
     IF = 286,
     ELSE = 287,
     WHILE = 288,
     RETURN = 289,
     FOR = 290,
     SWITCH = 291,
     CASE = 292,
     COLON = 293,
     DEFAULT = 294,
     AUTOADD = 295,
     AUTOSUB = 296,
     BREAK = 297,
     CONTINUE = 298,
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
     ARRAY_DEC = 328,
     FOR_DEC = 329,
     CONTINUE_NODE = 330,
     BREAK_NODE = 331,
     BLANK = 332,
     ARRAY_DF = 333,
     FOR_EXP1 = 334,
     FOR_EXP2 = 335,
     FOR_EXP3 = 336,
     FOR_NODE = 337,
     ARRAY_CALL = 338,
     DPLUS = 339,
     UMINUS = 340,
     LOWER_THEN_ELSE = 341
   };
#endif
/* Tokens.  */
#define INT 258
#define ID 259
#define RELOP 260
#define TYPE 261
#define CHAR 262
#define FLOAT 263
#define LP 264
#define RP 265
#define LB 266
#define RB 267
#define LC 268
#define RC 269
#define SEMI 270
#define COMMA 271
#define COMADD 272
#define COMSUB 273
#define COMSTAR 274
#define COMDIV 275
#define COMMOD 276
#define PLUS 277
#define MINUS 278
#define STAR 279
#define DIV 280
#define MOD 281
#define ASSIGNOP 282
#define AND 283
#define OR 284
#define NOT 285
#define IF 286
#define ELSE 287
#define WHILE 288
#define RETURN 289
#define FOR 290
#define SWITCH 291
#define CASE 292
#define COLON 293
#define DEFAULT 294
#define AUTOADD 295
#define AUTOSUB 296
#define BREAK 297
#define CONTINUE 298
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
#define ARRAY_DEC 328
#define FOR_DEC 329
#define CONTINUE_NODE 330
#define BREAK_NODE 331
#define BLANK 332
#define ARRAY_DF 333
#define FOR_EXP1 334
#define FOR_EXP2 335
#define FOR_EXP3 336
#define FOR_NODE 337
#define ARRAY_CALL 338
#define DPLUS 339
#define UMINUS 340
#define LOWER_THEN_ELSE 341




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 19 "parser.y"
{
	int    type_int;
	float  type_float;
	char   type_char[3];
	char   type_id[32];
	struct ASTNode *ptr;
}
/* Line 1529 of yacc.c.  */
#line 229 "parser.tab.h"
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
