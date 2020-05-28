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




/* Copy the first part of user declarations.  */
#line 4 "parser.y"

#include "stdio.h"
#include "math.h"
#include "string.h"
#include "def.h"
extern int yylineno;
extern char *yytext;
extern FILE *yyin;
int yylex();
void yyerror(const char* fmt, ...);
void display(struct ASTNode *,int);


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
typedef union YYSTYPE
#line 19 "parser.y"
{
	int    type_int;
	float  type_float;
	char   type_char[3];
	char   type_id[32];
	struct ASTNode *ptr;
}
/* Line 193 of yacc.c.  */
#line 289 "parser.tab.c"
	YYSTYPE;
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
#line 314 "parser.tab.c"

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
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   587

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  87
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNRULES -- Number of states.  */
#define YYNSTATES  165

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   341

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    13,    17,    20,    22,
      24,    28,    30,    33,    37,    42,    45,    47,    52,    56,
      59,    61,    65,    68,    73,    74,    77,    80,    82,    86,
      92,   100,   106,   112,   115,   118,   120,   126,   131,   136,
     140,   145,   149,   153,   156,   158,   161,   165,   167,   171,
     173,   174,   177,   180,   184,   186,   190,   192,   196,   200,
     204,   208,   212,   216,   220,   224,   228,   232,   236,   240,
     244,   248,   252,   256,   259,   262,   265,   268,   271,   274,
     278,   283,   287,   292,   294,   296,   298,   300,   304
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      88,     0,    -1,    89,    -1,    -1,    90,    89,    -1,    91,
      92,    15,    -1,    91,    96,    99,    -1,     1,    15,    -1,
       6,    -1,    93,    -1,    93,    16,    92,    -1,     4,    -1,
       4,    94,    -1,    11,    95,    12,    -1,    11,    95,    12,
      94,    -1,     1,    12,    -1,     3,    -1,     4,     9,    97,
      10,    -1,     4,     9,    10,    -1,     1,    10,    -1,    98,
      -1,    98,    16,    97,    -1,    91,    93,    -1,    13,   106,
     100,    14,    -1,    -1,   101,   100,    -1,   110,    15,    -1,
      99,    -1,    34,   110,    15,    -1,    31,     9,   110,    10,
     101,    -1,    31,     9,   110,    10,   101,    32,   101,    -1,
      33,     9,   110,    10,   101,    -1,    35,     9,   102,    10,
     101,    -1,    42,    15,    -1,    43,    15,    -1,    15,    -1,
     103,    15,   104,    15,   105,    -1,   103,    15,    15,   105,
      -1,   103,    15,   104,    15,    -1,   103,    15,    15,    -1,
      15,   104,    15,   105,    -1,    15,   104,    15,    -1,    15,
      15,   105,    -1,    15,    15,    -1,   108,    -1,    91,   108,
      -1,   110,    16,   104,    -1,   110,    -1,   110,    16,   105,
      -1,   110,    -1,    -1,   107,   106,    -1,     1,    15,    -1,
      91,   108,    15,    -1,   109,    -1,   109,    16,   108,    -1,
      93,    -1,    93,    27,   110,    -1,   110,    27,   110,    -1,
     110,    28,   110,    -1,   110,    29,   110,    -1,   110,     5,
     110,    -1,   110,    22,   110,    -1,   110,    23,   110,    -1,
     110,    24,   110,    -1,   110,    25,   110,    -1,   110,    26,
     110,    -1,   110,    17,   110,    -1,   110,    18,   110,    -1,
     110,    19,   110,    -1,   110,    20,   110,    -1,   110,    21,
     110,    -1,     9,   110,    10,    -1,    23,   110,    -1,    30,
     110,    -1,    40,   110,    -1,   110,    40,    -1,    41,   110,
      -1,   110,    41,    -1,    11,   111,    12,    -1,     4,     9,
     111,    10,    -1,     4,     9,    10,    -1,   110,    11,   110,
      12,    -1,     4,    -1,     3,    -1,     8,    -1,     7,    -1,
     110,    16,   111,    -1,   110,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    67,    67,    70,    71,    74,    75,    76,    80,    84,
      85,    89,    90,    94,    95,    96,    99,   103,   104,   105,
     109,   110,   114,   118,   123,   124,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   141,   142,   143,   144,
     145,   146,   147,   148,   151,   152,   154,   155,   157,   158,
     163,   164,   165,   169,   172,   173,   175,   176,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,   200,   201,
     204,   205,   206,   207,   208,   209,   210,   212,   213
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "ID", "RELOP", "TYPE", "CHAR",
  "FLOAT", "LP", "RP", "LB", "RB", "LC", "RC", "SEMI", "COMMA", "COMADD",
  "COMSUB", "COMSTAR", "COMDIV", "COMMOD", "PLUS", "MINUS", "STAR", "DIV",
  "MOD", "ASSIGNOP", "AND", "OR", "NOT", "IF", "ELSE", "WHILE", "RETURN",
  "FOR", "SWITCH", "CASE", "COLON", "DEFAULT", "AUTOADD", "AUTOSUB",
  "BREAK", "CONTINUE", "EXT_DEF_LIST", "EXT_VAR_DEF", "FUNC_DEF",
  "FUNC_DEC", "EXT_DEC_LIST", "PARAM_LIST", "PARAM_DEC", "VAR_DEF",
  "DEC_LIST", "DEF_LIST", "COMP_STM", "STM_LIST", "EXP_STMT", "IF_THEN",
  "IF_THEN_ELSE", "FUNC_CALL", "ARGS", "FUNCTION", "PARAM", "ARG", "CALL",
  "LABEL", "GOTO", "JLT", "JLE", "JGT", "JGE", "EQ", "NEQ", "ARRAY_DEC",
  "FOR_DEC", "CONTINUE_NODE", "BREAK_NODE", "BLANK", "ARRAY_DF",
  "FOR_EXP1", "FOR_EXP2", "FOR_EXP3", "FOR_NODE", "ARRAY_CALL", "DPLUS",
  "UMINUS", "LOWER_THEN_ELSE", "$accept", "program", "ExtDefList",
  "ExtDef", "Specifier", "ExtDecList", "VarDec", "ArrayDec", "INDEX",
  "FuncDec", "VarList", "ParamDec", "CompSt", "StmList", "Stmt", "FORDEC",
  "FOREXP1", "FOREXP2", "FOREXP3", "DefList", "Def", "DecList", "Dec",
  "Exp", "Args", 0
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
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    87,    88,    89,    89,    90,    90,    90,    91,    92,
      92,    93,    93,    94,    94,    94,    95,    96,    96,    96,
      97,    97,    98,    99,   100,   100,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   102,   102,   102,   102,
     102,   102,   102,   102,   103,   103,   104,   104,   105,   105,
     106,   106,   106,   107,   108,   108,   109,   109,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   111,   111
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     3,     3,     2,     1,     1,
       3,     1,     2,     3,     4,     2,     1,     4,     3,     2,
       1,     3,     2,     4,     0,     2,     2,     1,     3,     5,
       7,     5,     5,     2,     2,     1,     5,     4,     4,     3,
       4,     3,     3,     2,     1,     2,     3,     1,     3,     1,
       0,     2,     2,     3,     1,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     2,     2,     3,
       4,     3,     4,     1,     1,     1,     1,     3,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     8,     0,     2,     0,     0,     7,     1,     4,
       0,     0,     0,     9,     0,    19,     0,     0,     0,    12,
       5,     0,     0,     6,    15,    18,     0,     0,    20,    16,
       0,     0,    10,     0,     0,    24,     0,    22,    17,     0,
       0,    52,    56,     0,    54,    84,    83,    86,    85,     0,
       0,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,     0,    24,     0,    51,    21,    14,     0,
      53,     0,     0,     0,    88,     0,    73,    74,     0,     0,
       0,     0,    75,    77,    33,    34,    23,    25,     0,     0,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    76,    78,    57,    55,    81,     0,
      72,     0,    79,     0,     0,    28,     0,     0,     0,     0,
      44,    61,     0,    67,    68,    69,    70,    71,    62,    63,
      64,    65,    66,    58,    59,    60,    80,    87,     0,     0,
      43,     0,    47,    45,     0,     0,    82,    29,    31,    42,
      49,    41,     0,    32,    39,     0,     0,     0,    40,    46,
      37,    38,    30,    48,    36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    12,    42,    19,    30,    14,
      27,    28,    62,    63,    64,   118,   119,   141,   149,    35,
      36,    43,    44,    65,    75
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -132
static const yytype_int16 yypact[] =
{
      26,    -7,  -132,    17,  -132,    26,    71,  -132,  -132,  -132,
       8,   571,     4,    22,    42,  -132,    44,    27,    54,  -132,
    -132,    59,    86,  -132,  -132,  -132,    59,    55,    48,  -132,
      65,    58,  -132,    56,    59,   127,    86,  -132,  -132,    74,
     136,  -132,    57,    66,    67,  -132,    79,  -132,  -132,   221,
     221,  -132,   221,   221,    89,    95,   221,    97,   221,   221,
      92,    96,  -132,    99,   127,   249,  -132,  -132,  -132,   221,
    -132,    59,   168,   274,   300,    98,   103,   103,   221,   221,
     327,     9,   103,   103,  -132,  -132,  -132,  -132,   221,   221,
    -132,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,  -132,  -132,   479,  -132,  -132,   105,
    -132,   221,  -132,   352,   377,  -132,   177,    59,   108,   107,
    -132,   171,   402,   504,   504,   504,   504,   504,   215,   215,
      -6,    -6,    -6,   512,   544,   537,  -132,  -132,   127,   127,
     221,   109,   428,  -132,   127,   212,  -132,    91,  -132,  -132,
     454,   221,   221,  -132,   221,   110,   127,   221,  -132,  -132,
    -132,   221,  -132,  -132,  -132
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,   128,  -132,   -11,   111,    10,   101,  -132,  -132,
     100,  -132,   129,    80,   -78,  -132,  -132,  -131,   -75,   112,
    -132,   -59,  -132,   -49,   -70
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -51
static const yytype_int16 yytable[] =
{
      73,    74,   109,    76,    77,    89,    26,    80,     7,    82,
      83,    34,   107,    31,   155,     2,    13,     8,    15,    20,
     106,   159,   120,    74,   116,    34,    -3,     1,    26,   113,
     114,    13,     2,     2,   104,   105,    37,    25,    21,   121,
     122,   137,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,    22,    24,    29,   143,    16,
     147,   148,    74,    31,    39,    38,   153,   142,   -11,    18,
     117,    41,    10,   -11,   -11,    11,   158,    40,   162,   160,
       2,    70,   163,    71,    69,   -11,   164,    33,    72,   -50,
     -50,   150,     2,   -50,   -50,   -50,   142,   -50,    78,   -50,
     -50,   -50,   150,   142,    79,   150,    81,    84,   150,   -50,
     112,    85,   150,    86,    89,   136,   -50,   -50,   144,   -50,
     -50,   -50,   145,   156,   151,   161,   -50,   -50,   -50,   -50,
      45,    46,    32,     9,    47,    48,    49,    16,    50,    67,
      22,    68,    51,    23,    87,     0,   -13,    18,    66,     0,
      52,   -13,   -13,     0,     0,     0,     0,    53,    54,     0,
      55,    56,    57,   -13,     0,     0,     0,    58,    59,    60,
      61,    45,    46,     0,     0,    47,    48,    49,   108,    50,
      45,    46,    89,     0,    47,    48,    49,     0,    50,     0,
       0,    52,   140,    96,    97,    98,    99,   100,    53,     0,
      52,     0,     0,     0,     0,     0,     0,    53,    58,    59,
       0,   104,   105,     0,     0,    45,    46,    58,    59,    47,
      48,    49,     0,    50,    45,    46,    89,   154,    47,    48,
      49,     0,    50,     0,     0,    52,     0,     0,     0,    98,
      99,   100,    53,     0,    52,     0,     0,     0,     0,     0,
       0,    53,    58,    59,    88,   104,   105,     0,     0,     0,
      89,    58,    59,     0,    90,     0,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    88,
       0,     0,     0,     0,   110,    89,     0,     0,     0,   104,
     105,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,     0,    88,     0,     0,     0,     0,
       0,    89,     0,     0,   104,   105,   111,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
       0,     0,    88,     0,     0,     0,     0,     0,    89,     0,
     104,   105,   115,     0,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,    88,     0,     0,
       0,     0,   138,    89,     0,     0,     0,   104,   105,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,    88,     0,     0,     0,     0,   139,    89,     0,
       0,     0,   104,   105,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,    88,     0,     0,
       0,     0,     0,    89,   146,     0,     0,   104,   105,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,     0,    88,     0,     0,     0,     0,     0,    89,
       0,     0,   104,   105,   152,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,     0,    88,
       0,     0,     0,     0,     0,    89,     0,     0,   104,   105,
     157,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    88,     0,     0,     0,     0,     0,
      89,     0,     0,     0,   104,   105,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    88,
       0,     0,     0,     0,     0,    89,     0,    88,     0,   104,
     105,     0,     0,    89,     0,     0,    96,    97,    98,    99,
     100,   101,   102,   103,    96,    97,    98,    99,   100,     0,
     102,   103,    88,     0,   104,   105,     0,     0,    89,    88,
       0,     0,   104,   105,     0,    89,     0,     0,     0,    96,
      97,    98,    99,   100,     0,   102,    96,    97,    98,    99,
     100,     0,    16,     0,     0,     0,     0,   104,   105,     0,
      17,     0,    18,     0,   104,   105,   -11,   -11
};

static const yytype_int16 yycheck[] =
{
      49,    50,    72,    52,    53,    11,    17,    56,    15,    58,
      59,    22,    71,     4,   145,     6,     6,     0,    10,    15,
      69,   152,    81,    72,    15,    36,     0,     1,    39,    78,
      79,    21,     6,     6,    40,    41,    26,    10,    16,    88,
      89,   111,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,    13,    12,     3,   117,     1,
     138,   139,   111,     4,    16,    10,   144,   116,    10,    11,
      81,    15,     1,    15,    16,     4,   151,    12,   156,   154,
       6,    15,   157,    16,    27,    27,   161,     1,     9,     3,
       4,   140,     6,     7,     8,     9,   145,    11,     9,    13,
      14,    15,   151,   152,     9,   154,     9,    15,   157,    23,
      12,    15,   161,    14,    11,    10,    30,    31,    10,    33,
      34,    35,    15,    32,    15,    15,    40,    41,    42,    43,
       3,     4,    21,     5,     7,     8,     9,     1,    11,    39,
      13,    40,    15,    14,    64,    -1,    10,    11,    36,    -1,
      23,    15,    16,    -1,    -1,    -1,    -1,    30,    31,    -1,
      33,    34,    35,    27,    -1,    -1,    -1,    40,    41,    42,
      43,     3,     4,    -1,    -1,     7,     8,     9,    10,    11,
       3,     4,    11,    -1,     7,     8,     9,    -1,    11,    -1,
      -1,    23,    15,    22,    23,    24,    25,    26,    30,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    40,    41,
      -1,    40,    41,    -1,    -1,     3,     4,    40,    41,     7,
       8,     9,    -1,    11,     3,     4,    11,    15,     7,     8,
       9,    -1,    11,    -1,    -1,    23,    -1,    -1,    -1,    24,
      25,    26,    30,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    40,    41,     5,    40,    41,    -1,    -1,    -1,
      11,    40,    41,    -1,    15,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,     5,
      -1,    -1,    -1,    -1,    10,    11,    -1,    -1,    -1,    40,
      41,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    -1,     5,    -1,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    40,    41,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,     5,    -1,    -1,    -1,    -1,    -1,    11,    -1,
      40,    41,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,     5,    -1,    -1,
      -1,    -1,    10,    11,    -1,    -1,    -1,    40,    41,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,     5,    -1,    -1,    -1,    -1,    10,    11,    -1,
      -1,    -1,    40,    41,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,     5,    -1,    -1,
      -1,    -1,    -1,    11,    12,    -1,    -1,    40,    41,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    -1,     5,    -1,    -1,    -1,    -1,    -1,    11,
      -1,    -1,    40,    41,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    -1,     5,
      -1,    -1,    -1,    -1,    -1,    11,    -1,    -1,    40,    41,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,     5,    -1,    -1,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    40,    41,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,     5,
      -1,    -1,    -1,    -1,    -1,    11,    -1,     5,    -1,    40,
      41,    -1,    -1,    11,    -1,    -1,    22,    23,    24,    25,
      26,    27,    28,    29,    22,    23,    24,    25,    26,    -1,
      28,    29,     5,    -1,    40,    41,    -1,    -1,    11,     5,
      -1,    -1,    40,    41,    -1,    11,    -1,    -1,    -1,    22,
      23,    24,    25,    26,    -1,    28,    22,    23,    24,    25,
      26,    -1,     1,    -1,    -1,    -1,    -1,    40,    41,    -1,
       9,    -1,    11,    -1,    40,    41,    15,    16
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    88,    89,    90,    91,    15,     0,    89,
       1,     4,    92,    93,    96,    10,     1,     9,    11,    94,
      15,    16,    13,    99,    12,    10,    91,    97,    98,     3,
      95,     4,    92,     1,    91,   106,   107,    93,    10,    16,
      12,    15,    93,   108,   109,     3,     4,     7,     8,     9,
      11,    15,    23,    30,    31,    33,    34,    35,    40,    41,
      42,    43,    99,   100,   101,   110,   106,    97,    94,    27,
      15,    16,     9,   110,   110,   111,   110,   110,     9,     9,
     110,     9,   110,   110,    15,    15,    14,   100,     5,    11,
      15,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    40,    41,   110,   108,    10,   111,
      10,    16,    12,   110,   110,    15,    15,    91,   102,   103,
     108,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,    10,   111,    10,    10,
      15,   104,   110,   108,    10,    15,    12,   101,   101,   105,
     110,    15,    16,   101,    15,   104,    32,    16,   105,   104,
     105,    15,   101,   105,   105
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
        case 2:
#line 67 "parser.y"
    { display((yyvsp[(1) - (1)].ptr),0); semantic_Analysis0((yyvsp[(1) - (1)].ptr));;}
    break;

  case 3:
#line 70 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 4:
#line 71 "parser.y"
    {(yyval.ptr)=mknode(2,EXT_DEF_LIST,yylineno,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr));;}
    break;

  case 5:
#line 74 "parser.y"
    {(yyval.ptr)=mknode(2,EXT_VAR_DEF,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr));;}
    break;

  case 6:
#line 75 "parser.y"
    {(yyval.ptr)=mknode(3,FUNC_DEF,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 7:
#line 76 "parser.y"
    {(yyval.ptr)=NULL;printf("\t missing SEMI \t\n");;}
    break;

  case 8:
#line 80 "parser.y"
    {(yyval.ptr)=mknode(0,TYPE,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));(yyval.ptr)->type=!strcmp((yyvsp[(1) - (1)].type_id),"int")?INT:(!strcmp((yyvsp[(1) - (1)].type_id),"float")?FLOAT:CHAR);;}
    break;

  case 9:
#line 84 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 10:
#line 85 "parser.y"
    {(yyval.ptr)=mknode(2,EXT_DEC_LIST,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 11:
#line 89 "parser.y"
    {(yyval.ptr)=mknode(0,ID,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));;}
    break;

  case 12:
#line 90 "parser.y"
    {(yyval.ptr)=mknode(1,ARRAY_DF,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (2)].type_id));;}
    break;

  case 13:
#line 94 "parser.y"
    {(yyval.ptr)=mknode(1,ARRAY_DEC,yylineno,(yyvsp[(2) - (3)].ptr));strcpy((yyval.ptr)->type_id,"ARRAY_DEC");;}
    break;

  case 14:
#line 95 "parser.y"
    {(yyval.ptr)=mknode(2,ARRAY_DEC,yylineno,(yyvsp[(2) - (4)].ptr),(yyvsp[(4) - (4)].ptr));strcpy((yyval.ptr)->type_id,"ARRAY_DEC");;}
    break;

  case 15:
#line 96 "parser.y"
    {(yyval.ptr)=NULL;printf("\t define array error \t\n");;}
    break;

  case 16:
#line 99 "parser.y"
    {(yyval.ptr)=mknode(0,INT,yylineno);(yyval.ptr)->type_int=(yyvsp[(1) - (1)].type_int);(yyval.ptr)->type=INT;;}
    break;

  case 17:
#line 103 "parser.y"
    {(yyval.ptr)=mknode(1,FUNC_DEC,yylineno,(yyvsp[(3) - (4)].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (4)].type_id));;}
    break;

  case 18:
#line 104 "parser.y"
    {(yyval.ptr)=mknode(0,FUNC_DEC,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (3)].type_id));(yyval.ptr)->ptr[0]=NULL;;}
    break;

  case 19:
#line 105 "parser.y"
    {(yyval.ptr)=NULL; printf("\t define function error\n");;}
    break;

  case 20:
#line 109 "parser.y"
    {(yyval.ptr)=mknode(1,PARAM_LIST,yylineno,(yyvsp[(1) - (1)].ptr));;}
    break;

  case 21:
#line 110 "parser.y"
    {(yyval.ptr)=mknode(2,PARAM_LIST,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 22:
#line 114 "parser.y"
    {(yyval.ptr)=mknode(2,PARAM_DEC,yylineno,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr));;}
    break;

  case 23:
#line 118 "parser.y"
    {(yyval.ptr)=mknode(2,COMP_STM,yylineno,(yyvsp[(2) - (4)].ptr),(yyvsp[(3) - (4)].ptr));;}
    break;

  case 24:
#line 123 "parser.y"
    {(yyval.ptr)=NULL; ;}
    break;

  case 25:
#line 124 "parser.y"
    {(yyval.ptr)=mknode(2,STM_LIST,yylineno,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr));;}
    break;

  case 26:
#line 128 "parser.y"
    {(yyval.ptr)=mknode(1,EXP_STMT,yylineno,(yyvsp[(1) - (2)].ptr));;}
    break;

  case 27:
#line 129 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 28:
#line 130 "parser.y"
    {(yyval.ptr)=mknode(1,RETURN,yylineno,(yyvsp[(2) - (3)].ptr));;}
    break;

  case 29:
#line 131 "parser.y"
    {(yyval.ptr)=mknode(2,IF_THEN,yylineno,(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr));;}
    break;

  case 30:
#line 132 "parser.y"
    {(yyval.ptr)=mknode(3,IF_THEN_ELSE,yylineno,(yyvsp[(3) - (7)].ptr),(yyvsp[(5) - (7)].ptr),(yyvsp[(7) - (7)].ptr));;}
    break;

  case 31:
#line 133 "parser.y"
    {(yyval.ptr)=mknode(2,WHILE,yylineno,(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr));;}
    break;

  case 32:
#line 134 "parser.y"
    {(yyval.ptr)=mknode(2,FOR_NODE,yylineno,(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr));;}
    break;

  case 33:
#line 135 "parser.y"
    {(yyval.ptr)=mknode(0,BREAK_NODE,yylineno);strcpy((yyval.ptr)->type_id,"BREAK");;}
    break;

  case 34:
#line 136 "parser.y"
    {(yyval.ptr)=mknode(0,CONTINUE_NODE,yylineno);strcpy((yyval.ptr)->type_id,"CONTINUE");;}
    break;

  case 35:
#line 137 "parser.y"
    {(yyval.ptr) = mknode(0,BLANK,yylineno);strcpy((yyval.ptr)->type_id,"BLANK");;}
    break;

  case 36:
#line 141 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DEC,yylineno,(yyvsp[(1) - (5)].ptr),(yyvsp[(3) - (5)].ptr),(yyvsp[(5) - (5)].ptr));;}
    break;

  case 37:
#line 142 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DEC,yylineno,(yyvsp[(1) - (4)].ptr),NULL,(yyvsp[(4) - (4)].ptr));;}
    break;

  case 38:
#line 143 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DEC,yylineno,(yyvsp[(1) - (4)].ptr),(yyvsp[(3) - (4)].ptr),NULL);;}
    break;

  case 39:
#line 144 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DEC,yylineno,(yyvsp[(1) - (3)].ptr),NULL,NULL);;}
    break;

  case 40:
#line 145 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DEC,yylineno,NULL,(yyvsp[(2) - (4)].ptr),(yyvsp[(4) - (4)].ptr));;}
    break;

  case 41:
#line 146 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DEC,yylineno,NULL,(yyvsp[(2) - (3)].ptr),NULL);;}
    break;

  case 42:
#line 147 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DEC,yylineno,NULL,NULL,(yyvsp[(3) - (3)].ptr));;}
    break;

  case 43:
#line 148 "parser.y"
    {(yyval.ptr)=mknode(3, FOR_DEC, yylineno, NULL, NULL, NULL);;}
    break;

  case 44:
#line 151 "parser.y"
    {(yyval.ptr)=mknode(1, FOR_EXP1, yylineno, (yyvsp[(1) - (1)].ptr));;}
    break;

  case 45:
#line 152 "parser.y"
    {(yyval.ptr)=mknode(2, FOR_EXP1, yylineno, (yyvsp[(1) - (2)].ptr), (yyvsp[(2) - (2)].ptr));;}
    break;

  case 46:
#line 154 "parser.y"
    {(yyval.ptr)=mknode(2, FOR_EXP2, yylineno, (yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 47:
#line 155 "parser.y"
    {(yyval.ptr)=mknode(1, FOR_EXP2, yylineno, (yyvsp[(1) - (1)].ptr));;}
    break;

  case 48:
#line 157 "parser.y"
    {(yyval.ptr)=mknode(2, FOR_EXP3, yylineno, (yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 49:
#line 158 "parser.y"
    {(yyval.ptr)=mknode(2, FOR_EXP3, yylineno, (yyvsp[(1) - (1)].ptr), NULL);;}
    break;

  case 50:
#line 163 "parser.y"
    {(yyval.ptr)=NULL; ;}
    break;

  case 51:
#line 164 "parser.y"
    {(yyval.ptr)=mknode(2,DEF_LIST,yylineno,(yyvsp[(1) - (2)].ptr),(yyvsp[(2) - (2)].ptr));;}
    break;

  case 52:
#line 165 "parser.y"
    {(yyval.ptr)=NULL;;}
    break;

  case 53:
#line 169 "parser.y"
    {(yyval.ptr)=mknode(2,VAR_DEF,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(2) - (3)].ptr));;}
    break;

  case 54:
#line 172 "parser.y"
    {(yyval.ptr)=mknode(1,DEC_LIST,yylineno,(yyvsp[(1) - (1)].ptr));;}
    break;

  case 55:
#line 173 "parser.y"
    {(yyval.ptr)=mknode(2,DEC_LIST,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 56:
#line 175 "parser.y"
    {(yyval.ptr)=(yyvsp[(1) - (1)].ptr);;}
    break;

  case 57:
#line 176 "parser.y"
    {(yyval.ptr)=mknode(2,ASSIGNOP,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"ASSIGNOP");;}
    break;

  case 58:
#line 180 "parser.y"
    {(yyval.ptr)=mknode(2,ASSIGNOP,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"ASSIGNOP");;}
    break;

  case 59:
#line 181 "parser.y"
    {(yyval.ptr)=mknode(2,AND,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"AND");;}
    break;

  case 60:
#line 182 "parser.y"
    {(yyval.ptr)=mknode(2,OR,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"OR");;}
    break;

  case 61:
#line 183 "parser.y"
    {(yyval.ptr)=mknode(2,RELOP,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[(2) - (3)].type_id));;}
    break;

  case 62:
#line 184 "parser.y"
    {(yyval.ptr)=mknode(2,PLUS,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"PLUS");;}
    break;

  case 63:
#line 185 "parser.y"
    {(yyval.ptr)=mknode(2,MINUS,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"MINUS");;}
    break;

  case 64:
#line 186 "parser.y"
    {(yyval.ptr)=mknode(2,STAR,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"STAR");;}
    break;

  case 65:
#line 187 "parser.y"
    {(yyval.ptr)=mknode(2,DIV,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"DIV");;}
    break;

  case 66:
#line 188 "parser.y"
    {(yyval.ptr)=mknode(2,MOD,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"MOD");;}
    break;

  case 67:
#line 189 "parser.y"
    {(yyval.ptr)=mknode(2,COMADD,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"COMADD");;}
    break;

  case 68:
#line 190 "parser.y"
    {(yyval.ptr)=mknode(2,COMSUB,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"COMSUB");;}
    break;

  case 69:
#line 191 "parser.y"
    {(yyval.ptr)=mknode(2,COMSTAR,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"COMSTAR");;}
    break;

  case 70:
#line 192 "parser.y"
    {(yyval.ptr)=mknode(2,COMDIV,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"COMDIV");;}
    break;

  case 71:
#line 193 "parser.y"
    {(yyval.ptr)=mknode(2,COMMOD,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));strcpy((yyval.ptr)->type_id,"COMMOD");;}
    break;

  case 72:
#line 194 "parser.y"
    {(yyval.ptr)=(yyvsp[(2) - (3)].ptr);;}
    break;

  case 73:
#line 195 "parser.y"
    {(yyval.ptr)=mknode(1,UMINUS,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,"UMINUS");;}
    break;

  case 74:
#line 196 "parser.y"
    {(yyval.ptr)=mknode(1,NOT,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,"NOT");;}
    break;

  case 75:
#line 197 "parser.y"
    {(yyval.ptr)=mknode(1,AUTOADD,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,"AUTOADD");;}
    break;

  case 76:
#line 198 "parser.y"
    {(yyval.ptr)=mknode(1,AUTOADD,yylineno,(yyvsp[(1) - (2)].ptr));strcpy((yyval.ptr)->type_id,"AUTOADD");;}
    break;

  case 77:
#line 199 "parser.y"
    {(yyval.ptr)=mknode(1,AUTOSUB,yylineno,(yyvsp[(2) - (2)].ptr));strcpy((yyval.ptr)->type_id,"AUTOSUB");;}
    break;

  case 78:
#line 200 "parser.y"
    {(yyval.ptr)=mknode(1,AUTOSUB,yylineno,(yyvsp[(1) - (2)].ptr));strcpy((yyval.ptr)->type_id,"AUTOSUB");;}
    break;

  case 79:
#line 201 "parser.y"
    {(yyval.ptr)=(yyvsp[(2) - (3)].ptr);;}
    break;

  case 80:
#line 204 "parser.y"
    {(yyval.ptr)=mknode(1,FUNC_CALL,yylineno,(yyvsp[(3) - (4)].ptr));strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (4)].type_id));;}
    break;

  case 81:
#line 205 "parser.y"
    {(yyval.ptr)=mknode(0,FUNC_CALL,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (3)].type_id));;}
    break;

  case 82:
#line 206 "parser.y"
    {(yyval.ptr)=mknode(2,ARRAY_CALL,yylineno,(yyvsp[(1) - (4)].ptr),(yyvsp[(3) - (4)].ptr));;}
    break;

  case 83:
#line 207 "parser.y"
    {(yyval.ptr)=mknode(0,ID,yylineno);strcpy((yyval.ptr)->type_id,(yyvsp[(1) - (1)].type_id));;}
    break;

  case 84:
#line 208 "parser.y"
    {(yyval.ptr)=mknode(0,INT,yylineno);(yyval.ptr)->type_int=(yyvsp[(1) - (1)].type_int);(yyval.ptr)->type=INT;;}
    break;

  case 85:
#line 209 "parser.y"
    {(yyval.ptr)=mknode(0,FLOAT,yylineno);(yyval.ptr)->type_float=(yyvsp[(1) - (1)].type_float);(yyval.ptr)->type=FLOAT;;}
    break;

  case 86:
#line 210 "parser.y"
    {(yyval.ptr)=mknode(0,CHAR,yylineno); strcpy((yyval.ptr)->type_char,(yyvsp[(1) - (1)].type_char));(yyval.ptr)->type=CHAR;;}
    break;

  case 87:
#line 212 "parser.y"
    {(yyval.ptr)=mknode(2,ARGS,yylineno,(yyvsp[(1) - (3)].ptr),(yyvsp[(3) - (3)].ptr));;}
    break;

  case 88:
#line 213 "parser.y"
    {(yyval.ptr)=mknode(1,ARGS,yylineno,(yyvsp[(1) - (1)].ptr));;}
    break;


/* Line 1267 of yacc.c.  */
#line 2214 "parser.tab.c"
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


#line 216 "parser.y"


int main(int argc, char *argv[]){
	yyin=fopen(argv[1],"r");
	if (!yyin) return -1;
	yylineno=1;
	yyparse();
	return 0;
	}

#include<stdarg.h>
void yyerror(const char* fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "Grammar Error at Line %d Column %d: ", yylloc.first_line,yylloc.first_column);
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, ".\n");
}
 

