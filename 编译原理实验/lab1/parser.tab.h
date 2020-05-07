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
     STRUCT = 265,
     RETURN = 266,
     FOR = 267,
     SWITCH = 268,
     CASE = 269,
     COLON = 270,
     DEFAULT = 271,
     STRUCT_VISIT = 272,
     STRUCT_NEW = 273,
     STRUCT_DEC = 274,
     EXT_STRUCT_DEC = 275,
     CASE_STMT = 276,
     CASE_STMT_LIST = 277,
     DEFAULT_STMT = 278,
     FOR_DEC = 279,
     FOR_EXP1 = 280,
     FOR_EXP2 = 281,
     FOR_EXP3 = 282,
     DPLUS = 283,
     LP = 284,
     RP = 285,
     LC = 286,
     RC = 287,
     LB = 288,
     RB = 289,
     SEMI = 290,
     COMMA = 291,
     DOT = 292,
     PLUS = 293,
     MINUS = 294,
     STAR = 295,
     DIV = 296,
     MOD = 297,
     ASSIGNOP = 298,
     PLUSASSIGNOP = 299,
     MINUSASSIGNOP = 300,
     STARASSIGNOP = 301,
     DIVASSIGNOP = 302,
     MODASSIGNOP = 303,
     AND = 304,
     OR = 305,
     NOT = 306,
     AUTOPLUS = 307,
     AUTOMINUS = 308,
     IF = 309,
     ELSE = 310,
     WHILE = 311,
     BREAK = 312,
     CONTINUE = 313,
     EXT_DEF_LIST = 314,
     EXT_VAR_DEF = 315,
     FUNC_DEF = 316,
     FUNC_DEC = 317,
     EXT_DEC_LIST = 318,
     PARAM_LIST = 319,
     PARAM_DEC = 320,
     VAR_DEF = 321,
     DEC_LIST = 322,
     DEF_LIST = 323,
     COMP_STM = 324,
     STM_LIST = 325,
     EXP_STMT = 326,
     IF_THEN = 327,
     IF_THEN_ELSE = 328,
     FUNC_CALL = 329,
     ARGS = 330,
     FUNCTION = 331,
     PARAM = 332,
     ARG = 333,
     CALL = 334,
     LABEL = 335,
     GOTO = 336,
     JLT = 337,
     JLE = 338,
     JGT = 339,
     JGE = 340,
     EQ = 341,
     NEQ = 342,
     ARRAY_LIST = 343,
     DMINUS = 344,
     UMINUS = 345,
     LOWER_THEN_ELSE = 346
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
#define STRUCT 265
#define RETURN 266
#define FOR 267
#define SWITCH 268
#define CASE 269
#define COLON 270
#define DEFAULT 271
#define STRUCT_VISIT 272
#define STRUCT_NEW 273
#define STRUCT_DEC 274
#define EXT_STRUCT_DEC 275
#define CASE_STMT 276
#define CASE_STMT_LIST 277
#define DEFAULT_STMT 278
#define FOR_DEC 279
#define FOR_EXP1 280
#define FOR_EXP2 281
#define FOR_EXP3 282
#define DPLUS 283
#define LP 284
#define RP 285
#define LC 286
#define RC 287
#define LB 288
#define RB 289
#define SEMI 290
#define COMMA 291
#define DOT 292
#define PLUS 293
#define MINUS 294
#define STAR 295
#define DIV 296
#define MOD 297
#define ASSIGNOP 298
#define PLUSASSIGNOP 299
#define MINUSASSIGNOP 300
#define STARASSIGNOP 301
#define DIVASSIGNOP 302
#define MODASSIGNOP 303
#define AND 304
#define OR 305
#define NOT 306
#define AUTOPLUS 307
#define AUTOMINUS 308
#define IF 309
#define ELSE 310
#define WHILE 311
#define BREAK 312
#define CONTINUE 313
#define EXT_DEF_LIST 314
#define EXT_VAR_DEF 315
#define FUNC_DEF 316
#define FUNC_DEC 317
#define EXT_DEC_LIST 318
#define PARAM_LIST 319
#define PARAM_DEC 320
#define VAR_DEF 321
#define DEC_LIST 322
#define DEF_LIST 323
#define COMP_STM 324
#define STM_LIST 325
#define EXP_STMT 326
#define IF_THEN 327
#define IF_THEN_ELSE 328
#define FUNC_CALL 329
#define ARGS 330
#define FUNCTION 331
#define PARAM 332
#define ARG 333
#define CALL 334
#define LABEL 335
#define GOTO 336
#define JLT 337
#define JLE 338
#define JGT 339
#define JGE 340
#define EQ 341
#define NEQ 342
#define ARRAY_LIST 343
#define DMINUS 344
#define UMINUS 345
#define LOWER_THEN_ELSE 346




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
#line 239 "parser.tab.h"
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
