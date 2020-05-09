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
     ERRORID = 261,
     STRING = 262,
     RELOP = 263,
     TYPE = 264,
     FLOAT = 265,
     STRUCT = 266,
     RETURN = 267,
     FOR = 268,
     SWITCH = 269,
     CASE = 270,
     COLON = 271,
     DEFAULT = 272,
     STRUCT_VISIT = 273,
     STRUCT_NEW = 274,
     STRUCT_DEC = 275,
     EXT_STRUCT_DEC = 276,
     CASE_STMT = 277,
     CASE_STMT_LIST = 278,
     DEFAULT_STMT = 279,
     FOR_DEC = 280,
     FOR_EXP1 = 281,
     FOR_EXP2 = 282,
     FOR_EXP3 = 283,
     DPLUS = 284,
     LP = 285,
     RP = 286,
     LC = 287,
     RC = 288,
     LB = 289,
     RB = 290,
     SEMI = 291,
     COMMA = 292,
     DOT = 293,
     PLUS = 294,
     MINUS = 295,
     STAR = 296,
     DIV = 297,
     MOD = 298,
     ASSIGNOP = 299,
     PLUSASSIGNOP = 300,
     MINUSASSIGNOP = 301,
     STARASSIGNOP = 302,
     DIVASSIGNOP = 303,
     MODASSIGNOP = 304,
     AND = 305,
     OR = 306,
     NOT = 307,
     AUTOPLUS = 308,
     AUTOMINUS = 309,
     IF = 310,
     ELSE = 311,
     WHILE = 312,
     BREAK = 313,
     CONTINUE = 314,
     EXT_DEF_LIST = 315,
     EXT_VAR_DEF = 316,
     FUNC_DEF = 317,
     FUNC_DEC = 318,
     EXT_DEC_LIST = 319,
     PARAM_LIST = 320,
     PARAM_DEC = 321,
     VAR_DEF = 322,
     DEC_LIST = 323,
     DEF_LIST = 324,
     COMP_STM = 325,
     STM_LIST = 326,
     EXP_STMT = 327,
     IF_THEN = 328,
     IF_THEN_ELSE = 329,
     FUNC_CALL = 330,
     ARGS = 331,
     FUNCTION = 332,
     PARAM = 333,
     ARG = 334,
     CALL = 335,
     LABEL = 336,
     GOTO = 337,
     JLT = 338,
     JLE = 339,
     JGT = 340,
     JGE = 341,
     EQ = 342,
     NEQ = 343,
     ARRAY_LIST = 344,
     DMINUS = 345,
     UMINUS = 346,
     LOWER_THEN_ELSE = 347
   };
#endif
/* Tokens.  */
#define CHAR 258
#define INT 259
#define ID 260
#define ERRORID 261
#define STRING 262
#define RELOP 263
#define TYPE 264
#define FLOAT 265
#define STRUCT 266
#define RETURN 267
#define FOR 268
#define SWITCH 269
#define CASE 270
#define COLON 271
#define DEFAULT 272
#define STRUCT_VISIT 273
#define STRUCT_NEW 274
#define STRUCT_DEC 275
#define EXT_STRUCT_DEC 276
#define CASE_STMT 277
#define CASE_STMT_LIST 278
#define DEFAULT_STMT 279
#define FOR_DEC 280
#define FOR_EXP1 281
#define FOR_EXP2 282
#define FOR_EXP3 283
#define DPLUS 284
#define LP 285
#define RP 286
#define LC 287
#define RC 288
#define LB 289
#define RB 290
#define SEMI 291
#define COMMA 292
#define DOT 293
#define PLUS 294
#define MINUS 295
#define STAR 296
#define DIV 297
#define MOD 298
#define ASSIGNOP 299
#define PLUSASSIGNOP 300
#define MINUSASSIGNOP 301
#define STARASSIGNOP 302
#define DIVASSIGNOP 303
#define MODASSIGNOP 304
#define AND 305
#define OR 306
#define NOT 307
#define AUTOPLUS 308
#define AUTOMINUS 309
#define IF 310
#define ELSE 311
#define WHILE 312
#define BREAK 313
#define CONTINUE 314
#define EXT_DEF_LIST 315
#define EXT_VAR_DEF 316
#define FUNC_DEF 317
#define FUNC_DEC 318
#define EXT_DEC_LIST 319
#define PARAM_LIST 320
#define PARAM_DEC 321
#define VAR_DEF 322
#define DEC_LIST 323
#define DEF_LIST 324
#define COMP_STM 325
#define STM_LIST 326
#define EXP_STMT 327
#define IF_THEN 328
#define IF_THEN_ELSE 329
#define FUNC_CALL 330
#define ARGS 331
#define FUNCTION 332
#define PARAM 333
#define ARG 334
#define CALL 335
#define LABEL 336
#define GOTO 337
#define JLT 338
#define JLE 339
#define JGT 340
#define JGE 341
#define EQ 342
#define NEQ 343
#define ARRAY_LIST 344
#define DMINUS 345
#define UMINUS 346
#define LOWER_THEN_ELSE 347




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 20 "parser.y"
{
	int    type_int;
        char   type_char;
	float  type_float;
	char   type_id[32];
	struct ASTNode *ptr;
}
/* Line 1529 of yacc.c.  */
#line 241 "parser.tab.h"
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
