/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "src/try4.y"

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "try1.h"
#include "etype.h"
#include "y.tab.h"

FILE *wfile;
FILE *wfile1;
FILE *ftemp;
char fch;
#include "codegn.h"

int yylex(void);
void yyerror(char *);


//To store different tac lists for different scopes
struct tac* tac_list[50];
sym_tab *func_list[50];
int fnum=0;
int j;

//For handling Switch Case
char* scases[20];
int saddr[20];
int k = 0;
int it;
int temp_quad;

				//stack for pointers of symbol tables 
sym_tab *t;					//pointer for symbol table	
char* u;					//int_to_real 
char ch[50];					//to store a line of the three address code
int p;						//for lookups						
int i;

int counter = 0;				//to count elements of arrays
char *s;						//for arrays
int array_elem[20];


char *try;
char* cnew;
int pcounter;					//for parameters

//For the stack 'tblptr', needed for symbol table
int stack_ctr = 0;
sym_tab *tblptr[50];

int search(sym_tab* t)					//to find the list in which the tac code should be appended
{
	int l;
	for (l = 0; l<50; l++)
	{
		if (func_list[l] == t)
		return l;
	} 
}
int check = 0;
void fadd(sym_tab *t)
{
	func_list[fnum]=t;
	fnum++;
}					
void push(sym_tab *t)					
{
	tblptr[stack_ctr] = t;
	stack_ctr++;
}
void pop()
{
	stack_ctr--;
}
sym_tab *stack_top()
{
	return tblptr[stack_ctr-1];
	
}

char* removeSubstring(char *s)
{
  char *new = (char*) malloc(sizeof(char)*8);
  int i = strlen(s) - 6;
  int j;
  for (j = 0; j<i; j++)
  {
  	new[j] = s[j];
  	
  }
  new[j] = '\0';
  return new;
}

char* extract_id(char* s)
{
	char *new = (char*) malloc(sizeof(char)*8);
	int i;
	for (i=0; s[i]!= '['; i++)
	{
		new[i] = s[i];
	}
	new[i] = '\0';
	return new;
}

int extract_loc(char* s)
{
	char *new = (char*) malloc(sizeof(char)*8);
	int i;
	int j=0;
	for (i=0; s[i]!= '['; i++)
	{
		
	}
	i++;
	while (s[i] != ']')
	{
		new[j] = s[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return atoi(new);
}



/* Line 268 of yacc.c  */
#line 201 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     STRING = 259,
     INT_CONST = 260,
     FLOAT = 261,
     KEYWORD_BREAK = 262,
     KEYWORD_CONTINUE = 263,
     KEYWORD_RETURN = 264,
     KEYWORD_VAR = 265,
     KEYWORD_FUNCTION = 266,
     KEYWORD_FLOAT = 267,
     KEYWORD_INT = 268,
     KEYWORD_CHAR = 269,
     KEYWORD_STRING = 270,
     KEYWORD_BOOL = 271,
     INT_ARRAY = 272,
     FLOAT_ARRAY = 273,
     CHAR_ARRAY = 274,
     STRING_ARRAY = 275,
     BOOL_ARRAY = 276,
     KEYWORD_IF = 277,
     KEYWORD_ELSE = 278,
     KEYWORD_SWITCH = 279,
     KEYWORD_CASE = 280,
     KEYWORD_DEFAULT = 281,
     KEYWORD_DO = 282,
     KEYWORD_WHILE = 283,
     KEYWORD_FOR = 284,
     KEYWORD_IN = 285,
     BLOCK_BEGIN = 286,
     BLOCK_END = 287,
     REAL = 288,
     OR_OPERATOR = 289,
     AND_OPERATOR = 290,
     NOT_OPERATOR = 291,
     BITWISE_OR = 292,
     BITWISE_AND = 293,
     BITWISE_XOR = 294,
     BITWISE_LSHIFT = 295,
     BITWISE_RSHIFT = 296,
     BITWISE_NOT = 297,
     INCREMENT_BY = 298,
     DECREMENT_BY = 299,
     MULTIPLY_BY = 300,
     DIVIDE_BY = 301,
     MODULO_BY = 302,
     AND_ASSIGN = 303,
     OR_ASSIGN = 304,
     XOR_ASSIGN = 305,
     LSHIFT_ASSIGN = 306,
     RSHIFT_ASSIGN = 307,
     EQUALS = 308,
     NOT_EQUALS = 309,
     LE = 310,
     GE = 311,
     INCREMENT = 312,
     DECREMENT = 313,
     KEYWORD_THIS = 314,
     KEYWORD_NEW = 315,
     KEYWORD_DELETE = 316,
     KEYWORD_PRINT = 317,
     KEYWORD_SCAN = 318,
     KEYWORD_TRUE = 319,
     KEYWORD_FALSE = 320,
     KEYWORD_NULL = 321,
     NO_ELSE = 322,
     UMINUS = 323
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define STRING 259
#define INT_CONST 260
#define FLOAT 261
#define KEYWORD_BREAK 262
#define KEYWORD_CONTINUE 263
#define KEYWORD_RETURN 264
#define KEYWORD_VAR 265
#define KEYWORD_FUNCTION 266
#define KEYWORD_FLOAT 267
#define KEYWORD_INT 268
#define KEYWORD_CHAR 269
#define KEYWORD_STRING 270
#define KEYWORD_BOOL 271
#define INT_ARRAY 272
#define FLOAT_ARRAY 273
#define CHAR_ARRAY 274
#define STRING_ARRAY 275
#define BOOL_ARRAY 276
#define KEYWORD_IF 277
#define KEYWORD_ELSE 278
#define KEYWORD_SWITCH 279
#define KEYWORD_CASE 280
#define KEYWORD_DEFAULT 281
#define KEYWORD_DO 282
#define KEYWORD_WHILE 283
#define KEYWORD_FOR 284
#define KEYWORD_IN 285
#define BLOCK_BEGIN 286
#define BLOCK_END 287
#define REAL 288
#define OR_OPERATOR 289
#define AND_OPERATOR 290
#define NOT_OPERATOR 291
#define BITWISE_OR 292
#define BITWISE_AND 293
#define BITWISE_XOR 294
#define BITWISE_LSHIFT 295
#define BITWISE_RSHIFT 296
#define BITWISE_NOT 297
#define INCREMENT_BY 298
#define DECREMENT_BY 299
#define MULTIPLY_BY 300
#define DIVIDE_BY 301
#define MODULO_BY 302
#define AND_ASSIGN 303
#define OR_ASSIGN 304
#define XOR_ASSIGN 305
#define LSHIFT_ASSIGN 306
#define RSHIFT_ASSIGN 307
#define EQUALS 308
#define NOT_EQUALS 309
#define LE 310
#define GE 311
#define INCREMENT 312
#define DECREMENT 313
#define KEYWORD_THIS 314
#define KEYWORD_NEW 315
#define KEYWORD_DELETE 316
#define KEYWORD_PRINT 317
#define KEYWORD_SCAN 318
#define KEYWORD_TRUE 319
#define KEYWORD_FALSE 320
#define KEYWORD_NULL 321
#define NO_ELSE 322
#define UMINUS 323




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 130 "src/try4.y"

        int num;
        char *str;
        double val;
        struct etype eval;



/* Line 293 of yacc.c  */
#line 382 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 394 "y.tab.c"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   683

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  99
/* YYNRULES -- Number of states.  */
#define YYNSTATES  219

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   323

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    76,     2,     2,
      78,    79,    74,    72,    81,    73,     2,    75,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    68,    82,
      70,    83,    71,    69,    80,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    84,     2,    85,     2,     2,     2,     2,     2,     2,
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
      65,    66,    67,    77
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     7,     8,    11,    12,    20,    22,
      23,    25,    30,    37,    39,    41,    43,    45,    47,    49,
      51,    53,    55,    59,    61,    63,    65,    68,    70,    72,
      74,    76,    78,    83,    91,    92,    99,   100,   103,   107,
     114,   121,   129,   132,   135,   138,   141,   144,   148,   153,
     154,   163,   164,   171,   172,   179,   180,   186,   187,   193,
     199,   207,   220,   233,   239,   248,   254,   263,   267,   271,
     275,   279,   283,   287,   291,   295,   299,   303,   307,   311,
     316,   321,   324,   327,   329,   331,   333,   335,   337,   339,
     343,   345,   347,   351,   352,   358,   359,   361,   363,   367
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      87,     0,    -1,    -1,    88,    89,    -1,    -1,    90,    89,
      -1,    -1,    11,     3,    91,    78,    92,    79,    97,    -1,
      96,    -1,    -1,    93,    -1,    10,     3,    80,    94,    -1,
      93,    81,    10,     3,    80,    94,    -1,    13,    -1,    14,
      -1,    12,    -1,    15,    -1,    16,    -1,    17,    -1,    19,
      -1,    18,    -1,    20,    -1,    96,   119,    95,    -1,    96,
      -1,    97,    -1,    98,    -1,   101,    82,    -1,   102,    -1,
     103,    -1,   110,    -1,   111,    -1,   112,    -1,    31,    95,
     119,    32,    -1,    10,    99,     3,    80,    94,   100,    82,
      -1,    -1,    99,     3,    80,    94,   100,    81,    -1,    -1,
      83,   113,    -1,     3,    83,   113,    -1,     3,    83,     3,
      84,   113,    85,    -1,     3,    84,   113,    85,    83,   113,
      -1,     3,    83,   113,    69,   113,    68,   113,    -1,     3,
      57,    -1,     3,    58,    -1,     8,    82,    -1,     7,    82,
      -1,     9,    82,    -1,     9,   113,    82,    -1,    22,   113,
     119,    96,    -1,    -1,    22,   113,   119,    96,    23,   104,
     119,    96,    -1,    -1,    24,   113,    31,   105,   106,    32,
      -1,    -1,   106,    25,   113,    68,   107,    95,    -1,    -1,
      25,   113,    68,   108,    95,    -1,    -1,   106,    26,    68,
     109,    95,    -1,    28,   119,   113,   119,    96,    -1,    27,
     119,    96,    28,   119,   113,    82,    -1,    29,    78,   101,
      82,   119,   113,    82,   119,     3,    57,    79,    96,    -1,
      29,    78,   101,    82,   119,   113,    82,   119,     3,    58,
      79,    96,    -1,    62,    78,   113,    79,    82,    -1,    62,
      78,     3,    84,   113,    85,    79,    82,    -1,    63,    78,
     113,    79,    82,    -1,    63,    78,     3,    84,   113,    85,
      79,    82,    -1,    78,   113,    79,    -1,   113,    72,   113,
      -1,   113,    74,   113,    -1,   113,    73,   113,    -1,   113,
      75,   113,    -1,   113,    76,   113,    -1,   113,    71,   113,
      -1,   113,    70,   113,    -1,   113,    55,   113,    -1,   113,
      56,   113,    -1,   113,    53,   113,    -1,   113,    54,   113,
      -1,   113,    35,   119,   113,    -1,   113,    34,   119,   113,
      -1,    36,   113,    -1,    73,   113,    -1,     3,    -1,     5,
      -1,     6,    -1,     4,    -1,    64,    -1,    65,    -1,    84,
     114,    85,    -1,   115,    -1,   113,    -1,   114,    81,   113,
      -1,    -1,     3,    78,   116,   117,    79,    -1,    -1,   118,
      -1,   113,    -1,   113,    81,   117,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   171,   171,   171,   182,   185,   190,   189,   203,   206,
     208,   212,   216,   222,   225,   228,   231,   234,   237,   240,
     243,   246,   251,   258,   266,   272,   278,   284,   290,   295,
     301,   307,   316,   324,   372,   375,   423,   430,   439,   467,
     511,   594,   627,   656,   687,   696,   705,   714,   725,   739,
     738,   761,   760,   787,   786,   795,   794,   803,   802,   812,
     829,   848,   863,   878,   887,   898,   907,   918,   929,   988,
    1047,  1106,  1165,  1224,  1240,  1256,  1272,  1288,  1306,  1322,
    1331,  1341,  1349,  1355,  1401,  1407,  1412,  1427,  1438,  1449,
    1470,  1477,  1484,  1497,  1496,  1522,  1524,  1528,  1533,  1541
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING", "INT_CONST",
  "FLOAT", "KEYWORD_BREAK", "KEYWORD_CONTINUE", "KEYWORD_RETURN",
  "KEYWORD_VAR", "KEYWORD_FUNCTION", "KEYWORD_FLOAT", "KEYWORD_INT",
  "KEYWORD_CHAR", "KEYWORD_STRING", "KEYWORD_BOOL", "INT_ARRAY",
  "FLOAT_ARRAY", "CHAR_ARRAY", "STRING_ARRAY", "BOOL_ARRAY", "KEYWORD_IF",
  "KEYWORD_ELSE", "KEYWORD_SWITCH", "KEYWORD_CASE", "KEYWORD_DEFAULT",
  "KEYWORD_DO", "KEYWORD_WHILE", "KEYWORD_FOR", "KEYWORD_IN",
  "BLOCK_BEGIN", "BLOCK_END", "REAL", "OR_OPERATOR", "AND_OPERATOR",
  "NOT_OPERATOR", "BITWISE_OR", "BITWISE_AND", "BITWISE_XOR",
  "BITWISE_LSHIFT", "BITWISE_RSHIFT", "BITWISE_NOT", "INCREMENT_BY",
  "DECREMENT_BY", "MULTIPLY_BY", "DIVIDE_BY", "MODULO_BY", "AND_ASSIGN",
  "OR_ASSIGN", "XOR_ASSIGN", "LSHIFT_ASSIGN", "RSHIFT_ASSIGN", "EQUALS",
  "NOT_EQUALS", "LE", "GE", "INCREMENT", "DECREMENT", "KEYWORD_THIS",
  "KEYWORD_NEW", "KEYWORD_DELETE", "KEYWORD_PRINT", "KEYWORD_SCAN",
  "KEYWORD_TRUE", "KEYWORD_FALSE", "KEYWORD_NULL", "NO_ELSE", "':'", "'?'",
  "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "UMINUS", "'('", "')'",
  "'@'", "','", "';'", "'='", "'['", "']'", "$accept", "Start", "$@1",
  "Program", "Element", "$@2", "ParametersOption", "Parameters", "Type",
  "Statements", "Statement", "CompoundStatement", "DeclarationStatement",
  "DecList", "Assign", "AssignmentStatement", "JumpStatement",
  "ConditionStatement", "$@3", "$@4", "Cases", "$@5", "$@6", "$@7",
  "LoopStatement", "PrintStatement", "ScanStatement", "Expression",
  "ArrayList", "FunctionCall", "$@8", "ArgList", "Arguments", "M", 0
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
     315,   316,   317,   318,   319,   320,   321,   322,    58,    63,
      60,    62,    43,    45,    42,    47,    37,   323,    40,    41,
      64,    44,    59,    61,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    88,    87,    89,    89,    91,    90,    90,    92,
      92,    93,    93,    94,    94,    94,    94,    94,    94,    94,
      94,    94,    95,    95,    96,    96,    96,    96,    96,    96,
      96,    96,    97,    98,    99,    99,   100,   100,   101,   101,
     101,   101,   101,   101,   102,   102,   102,   102,   103,   104,
     103,   105,   103,   107,   106,   108,   106,   109,   106,   110,
     110,   110,   110,   111,   111,   112,   112,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   114,   114,   116,   115,   117,   117,   118,   118,   119
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     0,     2,     0,     7,     1,     0,
       1,     4,     6,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     2,     1,     1,     1,
       1,     1,     4,     7,     0,     6,     0,     2,     3,     6,
       6,     7,     2,     2,     2,     2,     2,     3,     4,     0,
       8,     0,     6,     0,     6,     0,     5,     0,     5,     5,
       7,    12,    12,     5,     8,     5,     8,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       4,     2,     2,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     3,     0,     5,     0,     1,     1,     3,     0
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     4,     1,     0,     0,     0,     0,    34,     0,
       0,     0,    99,    99,     0,     0,     0,     0,     3,     4,
       8,    24,    25,     0,    27,    28,    29,    30,    31,    42,
      43,     0,     0,    45,    44,    83,    86,    84,    85,     0,
      87,    88,     0,     0,    46,     0,     0,    90,     0,     6,
      99,     0,     0,     0,     0,    99,    99,     0,     0,     5,
      26,    83,    38,     0,    93,    81,    82,     0,    91,     0,
      99,    99,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    47,     0,     0,     0,    51,     0,    99,
       0,     0,     0,    83,     0,    83,     0,     0,     0,     0,
      95,    67,     0,    89,     0,     0,    77,    78,    75,    76,
      74,    73,    68,    70,    69,    71,    72,     0,     9,    48,
       0,    99,     0,    99,    32,    22,     0,     0,     0,     0,
       0,     0,     0,    97,     0,    96,    92,    80,    79,    15,
      13,    14,    16,    17,    18,    20,    19,    21,    36,     0,
       0,    10,    49,     0,     0,     0,    59,     0,     0,    63,
       0,    65,    39,     0,    40,    95,    94,     0,     0,     0,
       0,     0,    99,     0,     0,     0,    52,     0,     0,     0,
       0,    41,    98,    37,    35,    33,     0,     7,     0,     0,
      55,     0,    57,    60,    99,     0,     0,    11,     0,    50,
       0,    53,     0,     0,    64,    66,     0,    56,     0,    58,
       0,    12,    54,     0,     0,     0,     0,    61,    62
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    18,    19,    85,   150,   151,   148,    55,
      56,    21,    22,    48,   168,    23,    24,    25,   172,   120,
     154,   208,   200,   202,    26,    27,    28,   133,    69,    47,
     100,   134,   135,    52
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -185
static const yytype_int16 yypact[] =
{
    -185,    27,   209,  -185,   -54,   -42,   -31,     3,  -185,    39,
      86,    86,  -185,  -185,   -24,   219,   -23,   -22,  -185,   209,
    -185,  -185,  -185,   -25,  -185,  -185,  -185,  -185,  -185,  -185,
    -185,   102,    86,  -185,  -185,   -17,  -185,  -185,  -185,    86,
    -185,  -185,    86,    86,  -185,    86,   316,  -185,    59,  -185,
     583,   418,   219,    86,    62,  -185,   -14,   125,   137,  -185,
    -185,   -68,   498,   220,  -185,  -185,  -185,   442,   583,   -40,
    -185,  -185,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,  -185,   -10,    -7,   219,  -185,    41,   583,
       0,    40,   219,   -65,   452,   -58,   485,    86,    86,    -8,
      86,  -185,    86,  -185,    86,    86,   189,   189,   -39,   -39,
     -39,   -39,   -51,   -51,  -185,  -185,  -185,   413,    63,    57,
      58,  -185,   219,  -185,  -185,  -185,    86,     4,    86,     6,
     244,   528,    86,   389,    25,  -185,   583,   607,   213,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,    29,   107,
      35,    36,  -185,    86,   -11,    86,  -185,    86,   268,  -185,
     292,  -185,  -185,    86,   583,    86,  -185,    86,   -35,    44,
      85,   117,  -185,   552,    86,    64,  -185,   340,   365,    54,
      55,   583,  -185,   583,  -185,  -185,   413,  -185,   132,   219,
    -185,   576,  -185,  -185,  -185,    66,    70,  -185,    56,  -185,
     219,  -185,   219,   134,  -185,  -185,   413,  -185,   219,  -185,
      -9,  -185,  -185,    60,    65,   219,   219,  -185,  -185
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -185,  -185,  -185,   126,  -185,  -185,  -185,  -185,  -184,   -87,
      -2,   -16,  -185,  -185,  -185,    92,  -185,  -185,  -185,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,  -185,    21,  -185,  -185,
    -185,    -3,  -185,   -12
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -24
static const yytype_int16 yytable[] =
{
      20,    53,   197,    29,    30,   125,    35,    36,    37,    38,
      64,   -23,   -23,    64,   174,   175,    97,    20,   -23,   126,
      64,   176,   211,    80,    81,    82,   128,     3,    46,    31,
      32,    50,    51,    78,    79,    80,    81,    82,    86,    39,
      33,   102,    49,    91,    92,   103,   184,   185,   213,   214,
      88,    34,    62,    63,    54,    57,    58,    60,   104,   105,
      65,    64,    84,    66,    67,     4,    68,    40,    41,   121,
     117,   118,   124,   149,    89,   132,    42,   122,    94,    96,
     152,    43,   123,   153,   119,    44,   159,    45,   161,    35,
      36,    37,    38,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   166,    61,    36,    37,    38,   155,
     169,   157,   167,   207,   170,   209,    15,   171,   130,   131,
     156,   212,    39,   136,   186,   137,   138,   188,    93,    36,
      37,    38,   192,   195,   196,   198,   206,   210,    39,   215,
      95,    36,    37,    38,   216,    59,    90,   158,   204,   160,
      40,    41,   205,   164,   187,     0,     0,     0,     0,    42,
     189,    39,   182,     0,    43,     0,    40,    41,     0,     0,
      45,     0,     0,    39,   173,    42,   177,     0,   178,     0,
      43,     0,   203,     0,   181,     0,    45,   199,   183,    40,
      41,     0,     0,     0,     0,   191,     0,     0,    42,     0,
       0,    40,    41,    43,     0,     0,     0,     0,     0,    45,
      42,     0,     4,   217,   218,    43,     5,     6,     7,     8,
       9,    45,     4,     0,     0,     0,     5,     6,     7,     8,
       0,    10,     0,    11,     0,     0,    12,    13,    14,     0,
      15,    10,     0,    11,    74,    75,    12,    13,    14,     0,
      15,     0,     0,     0,    70,    71,     0,     0,     0,    76,
      77,    78,    79,    80,    81,    82,    72,    73,    74,    75,
       0,    16,    17,    72,    73,    74,    75,     0,    70,    71,
       0,    16,    17,    76,    77,    78,    79,    80,    81,    82,
      76,    77,    78,    79,    80,    81,    82,    72,    73,    74,
      75,     0,    70,    71,     0,    99,     0,     0,     0,     0,
       0,     0,     0,     0,    76,    77,    78,    79,    80,    81,
      82,    72,    73,    74,    75,     0,    70,    71,     0,   162,
       0,     0,     0,     0,     0,     0,     0,     0,    76,    77,
      78,    79,    80,    81,    82,    72,    73,    74,    75,     0,
      70,    71,     0,   179,     0,     0,     0,     0,     0,     0,
       0,     0,    76,    77,    78,    79,    80,    81,    82,    72,
      73,    74,    75,     0,    70,    71,     0,   180,     0,     0,
       0,     0,     0,     0,     0,     0,    76,    77,    78,    79,
      80,    81,    82,    72,    73,    74,    75,     0,    83,    70,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      76,    77,    78,    79,    80,    81,    82,     0,    72,    73,
      74,    75,   193,    70,    71,   139,   140,   141,   142,   143,
     144,   145,   146,   147,     0,    76,    77,    78,    79,    80,
      81,    82,    72,    73,    74,    75,     0,   194,     0,    87,
       0,     0,    70,    71,     0,     0,     0,     0,     0,    76,
      77,    78,    79,    80,    81,    82,     0,     0,     0,     0,
     165,    72,    73,    74,    75,     0,    70,    71,     0,     0,
       0,     0,     0,     0,     0,     0,    70,    71,    76,    77,
      78,    79,    80,    81,    82,    72,    73,    74,    75,     0,
       0,     0,     0,     0,     0,    72,    73,    74,    75,     0,
       0,     0,    76,    77,    78,    79,    80,    81,    82,    70,
      71,   101,    76,    77,    78,    79,    80,    81,    82,     0,
       0,   127,    70,    71,     0,     0,     0,     0,    72,    73,
      74,    75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    70,    71,   129,     0,     0,    98,    76,    77,
      78,    79,    80,    81,    82,     0,     0,     0,     0,     0,
       0,    72,    73,    74,    75,     0,    70,    71,     0,     0,
       0,     0,     0,     0,     0,     0,   163,     0,    76,    77,
      78,    79,    80,    81,    82,    72,    73,    74,    75,     0,
      70,    71,     0,     0,     0,     0,     0,    70,    71,     0,
     190,     0,    76,    77,    78,    79,    80,    81,    82,    72,
      73,    74,    75,     0,     0,     0,    72,    73,    74,    75,
       0,     0,    71,     0,   201,     0,    76,    77,    78,    79,
      80,    81,    82,    76,    77,    78,    79,    80,    81,    82,
      72,    73,    74,    75,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    76,    77,    78,
      79,    80,    81,    82
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-185))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       2,    13,   186,    57,    58,    92,     3,     4,     5,     6,
      78,    25,    26,    78,    25,    26,    84,    19,    32,    84,
      78,    32,   206,    74,    75,    76,    84,     0,     7,    83,
      84,    10,    11,    72,    73,    74,    75,    76,    50,    36,
      82,    81,     3,    55,    56,    85,    81,    82,    57,    58,
      52,    82,    31,    32,    78,    78,    78,    82,    70,    71,
      39,    78,     3,    42,    43,     3,    45,    64,    65,    28,
      80,    78,    32,    10,    53,    83,    73,    89,    57,    58,
      23,    78,    82,    25,    86,    82,    82,    84,    82,     3,
       4,     5,     6,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    79,     3,     4,     5,     6,   121,
       3,   123,    83,   200,    79,   202,    31,    81,    97,    98,
     122,   208,    36,   102,    80,   104,   105,    10,     3,     4,
       5,     6,    68,    79,    79,     3,    80,     3,    36,    79,
       3,     4,     5,     6,    79,    19,    54,   126,    82,   128,
      64,    65,    82,   132,   170,    -1,    -1,    -1,    -1,    73,
     172,    36,   165,    -1,    78,    -1,    64,    65,    -1,    -1,
      84,    -1,    -1,    36,   153,    73,   155,    -1,   157,    -1,
      78,    -1,   194,    -1,   163,    -1,    84,   189,   167,    64,
      65,    -1,    -1,    -1,    -1,   174,    -1,    -1,    73,    -1,
      -1,    64,    65,    78,    -1,    -1,    -1,    -1,    -1,    84,
      73,    -1,     3,   215,   216,    78,     7,     8,     9,    10,
      11,    84,     3,    -1,    -1,    -1,     7,     8,     9,    10,
      -1,    22,    -1,    24,    -1,    -1,    27,    28,    29,    -1,
      31,    22,    -1,    24,    55,    56,    27,    28,    29,    -1,
      31,    -1,    -1,    -1,    34,    35,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    53,    54,    55,    56,
      -1,    62,    63,    53,    54,    55,    56,    -1,    34,    35,
      -1,    62,    63,    70,    71,    72,    73,    74,    75,    76,
      70,    71,    72,    73,    74,    75,    76,    53,    54,    55,
      56,    -1,    34,    35,    -1,    85,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    53,    54,    55,    56,    -1,    34,    35,    -1,    85,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    53,    54,    55,    56,    -1,
      34,    35,    -1,    85,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    53,
      54,    55,    56,    -1,    34,    35,    -1,    85,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    53,    54,    55,    56,    -1,    82,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    -1,    53,    54,
      55,    56,    82,    34,    35,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    -1,    70,    71,    72,    73,    74,
      75,    76,    53,    54,    55,    56,    -1,    82,    -1,    31,
      -1,    -1,    34,    35,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    -1,    -1,    -1,    -1,
      81,    53,    54,    55,    56,    -1,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    70,    71,
      72,    73,    74,    75,    76,    53,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    34,
      35,    79,    70,    71,    72,    73,    74,    75,    76,    -1,
      -1,    79,    34,    35,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    70,    71,    72,    73,    74,
      75,    76,    34,    35,    79,    -1,    -1,    69,    70,    71,
      72,    73,    74,    75,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    -1,    34,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    71,
      72,    73,    74,    75,    76,    53,    54,    55,    56,    -1,
      34,    35,    -1,    -1,    -1,    -1,    -1,    34,    35,    -1,
      68,    -1,    70,    71,    72,    73,    74,    75,    76,    53,
      54,    55,    56,    -1,    -1,    -1,    53,    54,    55,    56,
      -1,    -1,    35,    -1,    68,    -1,    70,    71,    72,    73,
      74,    75,    76,    70,    71,    72,    73,    74,    75,    76,
      53,    54,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    87,    88,     0,     3,     7,     8,     9,    10,    11,
      22,    24,    27,    28,    29,    31,    62,    63,    89,    90,
      96,    97,    98,   101,   102,   103,   110,   111,   112,    57,
      58,    83,    84,    82,    82,     3,     4,     5,     6,    36,
      64,    65,    73,    78,    82,    84,   113,   115,    99,     3,
     113,   113,   119,   119,    78,    95,    96,    78,    78,    89,
      82,     3,   113,   113,    78,   113,   113,   113,   113,   114,
      34,    35,    53,    54,    55,    56,    70,    71,    72,    73,
      74,    75,    76,    82,     3,    91,   119,    31,    96,   113,
     101,   119,   119,     3,   113,     3,   113,    84,    69,    85,
     116,    79,    81,    85,   119,   119,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,    80,    78,    96,
     105,    28,   119,    82,    32,    95,    84,    79,    84,    79,
     113,   113,    83,   113,   117,   118,   113,   113,   113,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    94,    10,
      92,    93,    23,    25,   106,   119,    96,   119,   113,    82,
     113,    82,    85,    68,   113,    81,    79,    83,   100,     3,
      79,    81,   104,   113,    25,    26,    32,   113,   113,    85,
      85,   113,   117,   113,    81,    82,    80,    97,    10,   119,
      68,   113,    68,    82,    82,    79,    79,    94,     3,    96,
     108,    68,   109,   119,    82,    82,    80,    95,   107,    95,
       3,    94,    95,    57,    58,    79,    79,    96,    96
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 171 "src/try4.y"
    {
	t = mktable(NULL,"_start");
	push(t);
	fadd(t);
	}
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 177 "src/try4.y"
    {t = stack_top(); 
	pop();
	}
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 190 "src/try4.y"
    {t = mktable(stack_top(),(yyvsp[(2) - (2)].str)); push(t);fadd(t);
	enterproc(t, (yyvsp[(2) - (2)].str), t);
	pcounter = 0;
	}
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 195 "src/try4.y"
    {t = stack_top(); //printf("\nHERE\n");
	
	t->paramCount = pcounter;
	//printf("\nPrameters-%d\n", t->paramCount);
	pop(); 
	enterproc(stack_top(), (yyvsp[(2) - (7)].str), t);
	}
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 213 "src/try4.y"
    {enter(stack_top(),(yyvsp[(2) - (4)].str),(yyvsp[(4) - (4)].eval).type,(yyvsp[(4) - (4)].eval).width,0);
	pcounter++;}
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 217 "src/try4.y"
    {enter(stack_top(),(yyvsp[(4) - (6)].str),(yyvsp[(6) - (6)].eval).type,(yyvsp[(6) - (6)].eval).width,0);
	pcounter++;}
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 223 "src/try4.y"
    {(yyval.eval).type = "int"; (yyval.eval).width = 4;}
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 226 "src/try4.y"
    {(yyval.eval).type = "char"; (yyval.eval).width = 1;}
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 229 "src/try4.y"
    {(yyval.eval).type = "float"; (yyval.eval).width = 8;}
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 232 "src/try4.y"
    {(yyval.eval).type = "string"; (yyval.eval).width = 100;}
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 235 "src/try4.y"
    {(yyval.eval).type = "bool"; (yyval.eval).width = 4;}
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 238 "src/try4.y"
    {(yyval.eval).type = "int_array"; (yyval.eval).width = 4;}
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 241 "src/try4.y"
    {(yyval.eval).type = "char_array"; (yyval.eval).width = 1;}
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 244 "src/try4.y"
    {(yyval.eval).type = "float_array"; (yyval.eval).width = 8;}
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 247 "src/try4.y"
    {(yyval.eval).type = "string_array"; (yyval.eval).width = 100;}
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 252 "src/try4.y"
    {backpatch((yyvsp[(1) - (3)].eval).nextlist, (yyvsp[(2) - (3)].eval).quad, tac_list[check]);
	(yyval.eval).nextlist = (yyvsp[(3) - (3)].eval).nextlist;
	(yyval.eval).breaklist = merge((yyvsp[(1) - (3)].eval).breaklist, (yyvsp[(3) - (3)].eval).breaklist);
	(yyval.eval).continuelist = merge((yyvsp[(1) - (3)].eval).continuelist,(yyvsp[(3) - (3)].eval).continuelist);
	}
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 259 "src/try4.y"
    {(yyval.eval).nextlist = (yyvsp[(1) - (1)].eval).nextlist;
	(yyval.eval).breaklist = (yyvsp[(1) - (1)].eval).breaklist;
	(yyval.eval).continuelist = (yyvsp[(1) - (1)].eval).continuelist;
	}
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 267 "src/try4.y"
    {(yyval.eval).nextlist = (yyvsp[(1) - (1)].eval).nextlist;
	(yyval.eval).breaklist = (yyvsp[(1) - (1)].eval).breaklist;
	(yyval.eval).continuelist = (yyvsp[(1) - (1)].eval).continuelist;
	}
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 273 "src/try4.y"
    {(yyval.eval).nextlist = (yyvsp[(1) - (1)].eval).nextlist;
	(yyval.eval).breaklist = (yyvsp[(1) - (1)].eval).breaklist;
	(yyval.eval).continuelist = (yyvsp[(1) - (1)].eval).continuelist;
	}
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 279 "src/try4.y"
    {(yyval.eval).nextlist = (yyvsp[(1) - (2)].eval).nextlist;
	(yyval.eval).breaklist = (yyvsp[(1) - (2)].eval).breaklist;
	(yyval.eval).continuelist = (yyvsp[(1) - (2)].eval).continuelist;
	}
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 285 "src/try4.y"
    {(yyval.eval).nextlist = (yyvsp[(1) - (1)].eval).nextlist;
	(yyval.eval).breaklist = (yyvsp[(1) - (1)].eval).breaklist;
	(yyval.eval).continuelist = (yyvsp[(1) - (1)].eval).continuelist;
	}
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 291 "src/try4.y"
    {backpatch((yyvsp[(1) - (1)].eval).nextlist,nextquad, tac_list[check]);
	(yyval.eval).breaklist = (yyvsp[(1) - (1)].eval).breaklist;
	}
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 296 "src/try4.y"
    {backpatch((yyvsp[(1) - (1)].eval).nextlist,nextquad, tac_list[check]);
	(yyval.eval).breaklist = (yyvsp[(1) - (1)].eval).breaklist;
	(yyval.eval).continuelist = (yyvsp[(1) - (1)].eval).continuelist;
	}
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 302 "src/try4.y"
    {(yyval.eval).nextlist = (yyvsp[(1) - (1)].eval).nextlist;
	(yyval.eval).breaklist = (yyvsp[(1) - (1)].eval).breaklist;
	(yyval.eval).continuelist = (yyvsp[(1) - (1)].eval).continuelist;
	}
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 308 "src/try4.y"
    {(yyval.eval).nextlist = (yyvsp[(1) - (1)].eval).nextlist;
	(yyval.eval).breaklist = (yyvsp[(1) - (1)].eval).breaklist;
	(yyval.eval).continuelist = (yyvsp[(1) - (1)].eval).continuelist;
	}
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 317 "src/try4.y"
    {(yyval.eval).nextlist = (yyvsp[(2) - (4)].eval).nextlist;
	(yyval.eval).breaklist = (yyvsp[(2) - (4)].eval).breaklist;
	(yyval.eval).continuelist = (yyvsp[(2) - (4)].eval).continuelist;
	}
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 325 "src/try4.y"
    {t = stack_top();
	p = lookup(stack_top(),(yyvsp[(3) - (7)].str));
	if (p!=-1) 
	{
		printf("\nVariable already exists.\n");
		return;	
	}
	else
	{
		if ((yyvsp[(6) - (7)].eval).checkFunc != 1)
		{
			if ((strcmp((yyvsp[(5) - (7)].eval).type,(yyvsp[(6) - (7)].eval).type) != 0) && (strcmp((yyvsp[(6) - (7)].eval).type,"NULL") != 0)) 
			{
				printf("\nType Error\n");
				return;
			}
		}
		enter(t,(yyvsp[(3) - (7)].str),(yyvsp[(5) - (7)].eval).type,(yyvsp[(5) - (7)].eval).width,0); 
		setValue(t,(yyvsp[(6) - (7)].eval).place,(yyvsp[(3) - (7)].str));
		
		if(strstr((yyvsp[(5) - (7)].eval).type, "_array") != NULL)
		{
			setElements(t, counter, (yyvsp[(3) - (7)].str));
			check = search(stack_top());
			for (i=0; i<counter; i++)
			{
				char* s = (char*) malloc(sizeof(char)*3);
				sprintf(s, "%d", array_elem[i]);
				append(ARRAY,(yyvsp[(3) - (7)].str),s,"","",i,nextquad,tac_list[check]);
				gen();
			}
			counter = 0;
		}
		
		if (strcmp((yyvsp[(6) - (7)].eval).place,"NULL") != 0)
		{	
			check = search(stack_top());
			append(ASSIGN,(yyvsp[(3) - (7)].str),(yyvsp[(6) - (7)].eval).place,"","",0,nextquad,tac_list[check]);
			gen();
		}
	}
	(yyval.eval).nextlist = makelist(0);
	(yyval.eval).breaklist = makelist(0);
	(yyval.eval).continuelist = makelist(0);
	}
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 376 "src/try4.y"
    {t = stack_top();
	p = lookup(stack_top(),(yyvsp[(2) - (6)].str));
	if (p!=-1) 
	{
		printf("\nVariable already exists.\n");
		return;	
	}
	else
	{
		if ((yyvsp[(5) - (6)].eval).checkFunc != 1)
		{
			if ((strcmp((yyvsp[(4) - (6)].eval).type,(yyvsp[(5) - (6)].eval).type) != 0) && (strcmp((yyvsp[(5) - (6)].eval).type,"NULL") != 0)) 
			{
				printf("\nType Error\n");
				return;
			}
		}

		enter(t,(yyvsp[(2) - (6)].str),(yyvsp[(4) - (6)].eval).type,(yyvsp[(4) - (6)].eval).width,0);
		setValue(t,(yyvsp[(5) - (6)].eval).place,(yyvsp[(2) - (6)].str));
		if(strstr((yyvsp[(4) - (6)].eval).type, "_array") != NULL)
		{
			
			setElements(t, counter, (yyvsp[(2) - (6)].str));
			check = search(stack_top());
			for (i=0; i<counter; i++)
			{
				char* s = (char*) malloc(sizeof(char)*3);
				sprintf(s, "%d", array_elem[i]);
				append(ARRAY,(yyvsp[(2) - (6)].str),s,"","",i,nextquad,tac_list[check]);
				gen();
			}
			counter = 0;
		}
		//print_st(t);
		if (strcmp((yyvsp[(5) - (6)].eval).place,"NULL") != 0)
		{	
			check = search(stack_top());
			append(ASSIGN, (yyvsp[(2) - (6)].str), (yyvsp[(5) - (6)].eval).place, "", "",0,nextquad,tac_list[check]);
			gen();
		}
	}
	}
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 423 "src/try4.y"
    {(yyval.eval).place = (char*)malloc(sizeof(char)*5);
	strcpy((yyval.eval).place, "NULL");
	(yyval.eval).type = "NULL";
	(yyval.eval).width = 0;
	(yyval.eval).checkFunc = 0;
	}
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 431 "src/try4.y"
    {(yyval.eval).place = (yyvsp[(2) - (2)].eval).place;
	(yyval.eval).type = (yyvsp[(2) - (2)].eval).type;
	(yyval.eval).width = (yyvsp[(2) - (2)].eval).width;
	(yyval.eval).checkFunc = (yyvsp[(2) - (2)].eval).checkFunc;
	}
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 440 "src/try4.y"
    {p = lookup(stack_top(),(yyvsp[(1) - (3)].str));
	if (p!=-1) 
	{	
		if ((strcmp(stack_top()->value[p].type, (yyvsp[(3) - (3)].eval).type) != 0) && ((yyvsp[(3) - (3)].eval).checkFunc != 1))
		{
			printf("\nType Error\n");
			return;
		}
		setValue(t,(yyvsp[(3) - (3)].eval).place, (yyvsp[(1) - (3)].str));//printf("\nHERE\n");
		check = search(stack_top());
		//int length = strlen($3.type);
		//if ($3.type[length-1] == ']')
		//	append(ARRAY1, $1, extract_id($3.place), "", "",extract_loc($3.place),nextquad,tac_list[check]);
		//else
			append(ASSIGN, (yyvsp[(1) - (3)].str), (yyvsp[(3) - (3)].eval).place, "", "",0,nextquad,tac_list[check]);
		gen();
		(yyval.eval).nextlist = makelist(0);
		(yyval.eval).breaklist = makelist(0);
		(yyval.eval).continuelist = makelist(0);
	}
	else
	{
		printf("\nVariable %s should be declared first.\n", (yyvsp[(1) - (3)].str));
		return;
	}
	}
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 468 "src/try4.y"
    {p = lookup(stack_top(),(yyvsp[(1) - (6)].str));
	if (p!=-1) 
	{
		int q = lookup(stack_top(),(yyvsp[(3) - (6)].str));
		int r = lookup(stack_top(),(yyvsp[(5) - (6)].eval).place);
		if (q != -1)
		{
			if(strstr(t->value[q].type, "_array") == NULL)
			{
				printf("\n%s is not an array.\n", (yyvsp[(3) - (6)].str));
				return;	
			}
			if (strcmp((yyvsp[(5) - (6)].eval).type,"int") != 0)
			{
				printf("\nCan't access %s[%s]\n", (yyvsp[(3) - (6)].str), (yyvsp[(5) - (6)].eval).place);
				return;	
			}
			check = search(stack_top());
			if (r == -1)
				append(ARRAY1, (yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), "", "",atoi((yyvsp[(5) - (6)].eval).place),nextquad,tac_list[check]);
			else
				append(ARRAY2, (yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].str), "", (yyvsp[(5) - (6)].eval).place,0,nextquad,tac_list[check]);
			gen();
		}
		else
		{
			printf("\nArray %s should be declared first.\n", (yyvsp[(3) - (6)].str));
			return;
		}
		(yyval.eval).nextlist = makelist(0);
		(yyval.eval).breaklist = makelist(0);
		(yyval.eval).continuelist = makelist(0);
			
		
	}
	else
	{
		printf("\nVariable %s should be declared first.\n", (yyvsp[(1) - (6)].str));
		return;
	}
		
	}
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 512 "src/try4.y"
    {t = stack_top();
	p = lookup(t,(yyvsp[(1) - (6)].str));
	if (p!=-1) 
	{
		if(strstr(t->value[p].type, "_array") == NULL)
		{
			printf("\n%s is not an array.\n", (yyvsp[(1) - (6)].str));
			return;	
		}
		if (strcmp((yyvsp[(3) - (6)].eval).type,"int") != 0)
		{
			printf("\nCan't access %s[%s]\n", (yyvsp[(1) - (6)].str), (yyvsp[(3) - (6)].eval).place);
			return;	
		}
		if((strstr(t->value[p].type, "_array") != NULL) && (strcmp((yyvsp[(3) - (6)].eval).type,"int") == 0))
		{
			if (atoi((yyvsp[(3) - (6)].eval).place) > ((t->value[p].no_elements)-1))
			{
				printf("\nArray bound exceeded.\n");
				return;
			}
			
			s = removeSubstring(t->value[p].type);
			if ((strcmp(s, (yyvsp[(6) - (6)].eval).type) != 0) && ((yyvsp[(6) - (6)].eval).checkFunc != 1))
			{
				printf("\nType Error\n");
				return;
			}
			
			check = search(stack_top());
			append(ARRAY, (yyvsp[(1) - (6)].str), (yyvsp[(6) - (6)].eval).place, "", "",atoi((yyvsp[(3) - (6)].eval).place),nextquad,tac_list[check]);
			gen();
			
			/*char* u1;
			char* u2;
			char* u3;
			char* u4;
			int base = t->value[p].offset;
			int i = atoi($3.place);	
			int constant = base * $6.width;
			cnew = (char*) malloc(sizeof(char)*10);
			sprintf(cnew, "%d", $6.width);
			u1 = newtmp();

			check = search(stack_top());
			append(ARRAY, u1, $3.place, "*", cnew,0, nextquad,tac_list[check]);
			gen();
			u2 = newtmp();
			sprintf(cnew, "%d", constant);
			
			check = search(stack_top());
			append(ARRAY, u2, $1, "-", cnew,0,nextquad,tac_list[check]);
			gen();
			u3 = newtmp();
			
			check = search(stack_top());
			append(ARRAY, u3, u1, "+", u2,0,nextquad,tac_list[check]);
			gen();
			u4 = newtmp();
			
			check = search(stack_top());
			append(ARRAY, u4, u3, "", "",0,nextquad,tac_list[check]);
			gen();
			
			check = search(stack_top());
			append(ARRAY, u4, $6.place, "", "",0,nextquad,tac_list[check]);
			gen();
			return;	*/
		}
		
		(yyval.eval).nextlist = makelist(0);
		(yyval.eval).breaklist = makelist(0);
		(yyval.eval).continuelist = makelist(0);
	}
	else
	{
		printf("\nVariable %s should be declared first.\n", (yyvsp[(1) - (6)].str));
		return;
	}
	
	}
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 595 "src/try4.y"
    {t = stack_top();
	p = lookup(t,(yyvsp[(1) - (7)].str));
	if (p!= -1)
	{
		backpatch((yyvsp[(3) - (7)].eval).truelist,nextquad, tac_list[check]);
		backpatch((yyvsp[(3) - (7)].eval).falselist,nextquad+1, tac_list[check]);
		(yyval.eval).place = newtmp();
		
		check = search(stack_top());
		append(ASSIGN, (yyvsp[(1) - (7)].str), (yyvsp[(5) - (7)].eval).place, "", "",0,nextquad,tac_list[check]);
		gen();
		check = search(stack_top());
		append(GOTO_L,"","","","",nextquad+3,nextquad,tac_list[check]);
		gen();
		check = search(stack_top());
		append(GOTO_L,"","","","",nextquad+1,nextquad,tac_list[check]);
		gen();
		check = search(stack_top());
		append(ASSIGN, (yyvsp[(1) - (7)].str), (yyvsp[(7) - (7)].eval).place, "", "",0,nextquad,tac_list[check]);
		gen();
		(yyval.eval).nextlist = makelist(0);
		(yyval.eval).breaklist = makelist(0);
		(yyval.eval).continuelist = makelist(0);
	
	}
	else
	{
		printf("\nVariable %s should be declared first.\n", (yyvsp[(1) - (7)].str));
		return;
	}
	}
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 628 "src/try4.y"
    {t = stack_top();
	p = lookup(t,(yyvsp[(1) - (2)].str));
	if (p!= -1)
	{
		/*$$.place = newtmp();
		check = search(stack_top());
		append(ASSIGN, $$.place, $1, "+", "1",0,nextquad,tac_list[check]);
		gen();
		check = search(stack_top());
		append(ASSIGN, $1, $$.place, "", "",0,nextquad,tac_list[check]);
		gen();
		enter(t,$$.place,"int",4,1);*/
		check = search(stack_top());
		append(INC, "", (yyvsp[(1) - (2)].str), "", "",0,nextquad,tac_list[check]);
		gen();
		
		(yyval.eval).nextlist = makelist(0);
		(yyval.eval).breaklist = makelist(0);
		(yyval.eval).continuelist = makelist(0);
		
	}
	else
	{
		printf("\nVariable %s should be declared first.\n", (yyvsp[(1) - (2)].str));
		return;
	}
	}
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 657 "src/try4.y"
    {t = stack_top();
	p = lookup(t,(yyvsp[(1) - (2)].str));
	if (p!= -1)
	{
		/*$$.place = newtmp();
		check = search(stack_top());
		append(ASSIGN, $$.place, $1, "-", "1",0,nextquad,tac_list[check]);
		gen();
		check = search(stack_top());
		append(ASSIGN, $1, $$.place, "", "",0,nextquad,tac_list[check]);
		gen();
		enter(t,$$.place,"int",4,1);*/
		check = search(stack_top());
		append(DEC, "", (yyvsp[(1) - (2)].str), "", "",0,nextquad,tac_list[check]);
		gen();
		
		(yyval.eval).nextlist = makelist(0);
		(yyval.eval).breaklist = makelist(0);
		(yyval.eval).continuelist = makelist(0);
		
	}
	else
	{
		printf("\nVariable %s should be declared first.\n", (yyvsp[(1) - (2)].str));
		return;
	}
	}
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 688 "src/try4.y"
    {(yyval.eval).nextlist = makelist(0);
	(yyval.eval).breaklist = makelist(0);
	(yyval.eval).continuelist = makelist(nextquad);
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 697 "src/try4.y"
    {(yyval.eval).nextlist = makelist(0);
	(yyval.eval).continuelist = makelist(0);
	(yyval.eval).breaklist = makelist(nextquad);
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 706 "src/try4.y"
    {check = search(stack_top());
	append(RETURN,"", "", "", "",0,nextquad,tac_list[check]);
	gen();
	(yyval.eval).nextlist = makelist(0);
	(yyval.eval).breaklist = makelist(0);
	(yyval.eval).continuelist = makelist(0);
	}
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 715 "src/try4.y"
    {check = search(stack_top());
	append(RETURN,"", (yyvsp[(2) - (3)].eval).place, "", "",0,nextquad,tac_list[check]);
	gen();
	(yyval.eval).nextlist = makelist(0);
	(yyval.eval).breaklist = makelist(0);
	(yyval.eval).continuelist = makelist(0);
	}
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 726 "src/try4.y"
    {
	if (strcmp((yyvsp[(2) - (4)].eval).type,"bool")!= 0)
	{
		printf("\nIf condition must be a boolean\n");
		return;
	}
	backpatch((yyvsp[(2) - (4)].eval).truelist, (yyvsp[(3) - (4)].eval).quad, tac_list[check]);
	(yyval.eval).nextlist = merge((yyvsp[(2) - (4)].eval).falselist, (yyvsp[(4) - (4)].eval).nextlist);
	(yyval.eval).breaklist = (yyvsp[(4) - (4)].eval).breaklist;
	(yyval.eval).continuelist = (yyvsp[(4) - (4)].eval).continuelist;
	}
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 739 "src/try4.y"
    {temp_quad = nextquad;
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	
	}
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 746 "src/try4.y"
    {if (strcmp((yyvsp[(2) - (8)].eval).type,"bool")!= 0)
	{
		printf("\nIf condition must be a boolean\n");
		return;
	}
	backpatch((yyvsp[(2) - (8)].eval).truelist,(yyvsp[(3) - (8)].eval).quad, tac_list[check]);
	backpatch((yyvsp[(2) - (8)].eval).falselist,(yyvsp[(7) - (8)].eval).quad, tac_list[check]);
	(yyval.eval).switchlist = makelist(temp_quad);
	(yyval.eval).nextlist = merge((yyvsp[(4) - (8)].eval).nextlist,(yyvsp[(8) - (8)].eval).nextlist);
	(yyval.eval).nextlist = merge((yyval.eval).nextlist, (yyval.eval).switchlist);
	(yyval.eval).breaklist = merge((yyvsp[(4) - (8)].eval).breaklist, (yyvsp[(8) - (8)].eval).breaklist);
	(yyval.eval).continuelist = merge((yyvsp[(4) - (8)].eval).continuelist, (yyvsp[(8) - (8)].eval).continuelist);
	}
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 761 "src/try4.y"
    {temp_quad = nextquad;
	check = search(stack_top());
	append(GOTO,"", "", "", "",0,nextquad,tac_list[check]);
	gen();
	}
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 767 "src/try4.y"
    {(yyval.eval).switchlist = makelist(temp_quad);
	backpatch((yyval.eval).switchlist,nextquad, tac_list[check]);
	for (it = 0; it<k-1; it++)
	{
		check = search(stack_top());
		append(IF_GOTOL,"", (yyvsp[(2) - (6)].eval).place, "==", scases[it],saddr[it],nextquad,tac_list[check]);
		gen();
	}
	check = search(stack_top());
	append(GOTO_L,"","", "", "",saddr[it],nextquad,tac_list[check]);
	gen();
	(yyval.eval).nextlist = makelist(0);
	(yyval.eval).breaklist = makelist(0);
	(yyval.eval).continuelist = makelist(0);
	backpatch((yyvsp[(5) - (6)].eval).breaklist,nextquad, tac_list[check]);
	}
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 787 "src/try4.y"
    {strcpy(scases[k], (yyvsp[(3) - (4)].eval).place);
	saddr[k] = nextquad;
	k++; 
	}
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 792 "src/try4.y"
    {(yyval.eval).breaklist = merge((yyvsp[(1) - (6)].eval).breaklist, (yyvsp[(6) - (6)].eval).breaklist);}
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 795 "src/try4.y"
    {strcpy(scases[k], (yyvsp[(2) - (3)].eval).place);
	saddr[k] = nextquad;
	k++; 
	}
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 800 "src/try4.y"
    {(yyval.eval).breaklist = (yyvsp[(5) - (5)].eval).breaklist;}
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 803 "src/try4.y"
    {strcpy(scases[k], "");
	saddr[k] = nextquad;
	k++;
	}
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 808 "src/try4.y"
    {(yyval.eval).breaklist = merge((yyvsp[(1) - (5)].eval).breaklist, (yyvsp[(5) - (5)].eval).breaklist);}
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 813 "src/try4.y"
    {if (strcmp((yyvsp[(3) - (5)].eval).type,"bool")!= 0)
	{
		printf("\nWhile condition must be a boolean\n");
		return;
	}
	backpatch((yyvsp[(5) - (5)].eval).nextlist, (yyvsp[(2) - (5)].eval).quad, tac_list[check]);
	backpatch((yyvsp[(3) - (5)].eval).truelist, (yyvsp[(4) - (5)].eval).quad, tac_list[check]);
	
	backpatch((yyvsp[(5) - (5)].eval).continuelist, (yyvsp[(4) - (5)].eval).quad, tac_list[check]);
	(yyval.eval).nextlist = (yyvsp[(3) - (5)].eval).falselist;
	check = search(stack_top());
	append(GOTO_L,"", "", "", "",(yyvsp[(2) - (5)].eval).quad,nextquad,tac_list[check]);
	gen();
	backpatch((yyvsp[(5) - (5)].eval).breaklist,nextquad, tac_list[check]);
	}
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 830 "src/try4.y"
    {backpatch((yyvsp[(6) - (7)].eval).truelist, (yyvsp[(2) - (7)].eval).quad, tac_list[check]);
	backpatch((yyvsp[(3) - (7)].eval).nextlist, (yyvsp[(5) - (7)].eval).quad, tac_list[check]);
	backpatch((yyvsp[(3) - (7)].eval).continuelist, (yyvsp[(2) - (7)].eval).quad, tac_list[check]);
	backpatch((yyvsp[(3) - (7)].eval).breaklist,nextquad, tac_list[check]);
	(yyval.eval).nextlist = (yyvsp[(6) - (7)].eval).falselist;
	}
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 849 "src/try4.y"
    {backpatch((yyvsp[(6) - (12)].eval).truelist, (yyvsp[(8) - (12)].eval).quad, tac_list[check]);
	(yyval.eval).nextlist = merge((yyvsp[(6) - (12)].eval).falselist,(yyvsp[(12) - (12)].eval).nextlist);
	//print_list($$.nextlist);
	backpatch((yyvsp[(12) - (12)].eval).continuelist, nextquad, tac_list[check]);
	check = search(stack_top());
	append(INC, "", (yyvsp[(9) - (12)].str), "", "",0,nextquad,tac_list[check]);
	gen();
	append(GOTO_L,"", "", "", "",(yyvsp[(5) - (12)].eval).quad,nextquad,tac_list[check]);
	gen();
	backpatch((yyvsp[(12) - (12)].eval).breaklist,nextquad, tac_list[check]);
	(yyval.eval).breaklist = makelist(0);
	(yyval.eval).continuelist = makelist(0);
	}
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 864 "src/try4.y"
    {backpatch((yyvsp[(6) - (12)].eval).truelist, (yyvsp[(8) - (12)].eval).quad, tac_list[check]);
	(yyval.eval).nextlist = merge((yyvsp[(6) - (12)].eval).falselist,(yyvsp[(12) - (12)].eval).nextlist);
	//print_list($$.nextlist);
	backpatch((yyvsp[(12) - (12)].eval).continuelist, (yyvsp[(8) - (12)].eval).quad, tac_list[check]);
	check = search(stack_top());
	append(DEC, "", (yyvsp[(9) - (12)].str), "", "",0,nextquad,tac_list[check]);
	gen();
	append(GOTO_L,"", "", "", "",(yyvsp[(5) - (12)].eval).quad,nextquad,tac_list[check]);
	gen();
	backpatch((yyvsp[(12) - (12)].eval).breaklist,nextquad, tac_list[check]);
	}
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 879 "src/try4.y"
    {check = search(stack_top());
	append(PRINT,"", (yyvsp[(3) - (5)].eval).place, "", "",0,nextquad,tac_list[check]);
	gen();
	(yyval.eval).nextlist = makelist(0);
	(yyval.eval).breaklist = makelist(0);
	(yyval.eval).continuelist = makelist(0);
	}
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 888 "src/try4.y"
    {check = search(stack_top());
	append(PRINT1,"", (yyvsp[(3) - (8)].str), "", (yyvsp[(5) - (8)].eval).place,0,nextquad,tac_list[check]);
	gen();
	(yyval.eval).nextlist = makelist(0);
	(yyval.eval).breaklist = makelist(0);
	(yyval.eval).continuelist = makelist(0);
	}
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 899 "src/try4.y"
    {check = search(stack_top());
	append(SCAN,"", (yyvsp[(3) - (5)].eval).place, "", "",0,nextquad,tac_list[check]);
	gen();
	(yyval.eval).nextlist = makelist(0);
	(yyval.eval).breaklist = makelist(0);
	(yyval.eval).continuelist = makelist(0);
	}
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 908 "src/try4.y"
    {check = search(stack_top());
	append(SCAN1,"", (yyvsp[(3) - (8)].str), "", (yyvsp[(5) - (8)].eval).place,0,nextquad,tac_list[check]);
	gen();
	(yyval.eval).nextlist = makelist(0);
	(yyval.eval).breaklist = makelist(0);
	(yyval.eval).continuelist = makelist(0);
	}
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 919 "src/try4.y"
    {
	(yyval.eval).type = (yyvsp[(2) - (3)].eval).type;
	(yyval.eval).place = (yyvsp[(2) - (3)].eval).place;
	if (strcmp((yyvsp[(2) - (3)].eval).type,"bool") == 0)
	{
		(yyval.eval).truelist = (yyvsp[(2) - (3)].eval).truelist;
		(yyval.eval).falselist = (yyvsp[(2) - (3)].eval).falselist;
	}
	}
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 930 "src/try4.y"
    { t = stack_top();
	if ((strcmp((yyvsp[(1) - (3)].eval).type,"int") == 0) && (strcmp((yyvsp[(3) - (3)].eval).type,"int") == 0))
	{
		(yyval.eval).place = newtmp();
		//sprintf(ch, "%s = %s int+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,(yyval.eval).place, (yyvsp[(1) - (3)].eval).place, "+", (yyvsp[(3) - (3)].eval).place,0,nextquad,tac_list[check]);
		gen();
		(yyval.eval).type = "int";
		enter(t,(yyval.eval).place,(yyval.eval).type,4,1);
	}
	/*else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"float") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s float+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real+", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"float") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $1.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$1.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, u, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place,u, "real+", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"int") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $3.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$3.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, $1.place, u);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real+", u,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}*/
	else
	{
		printf("\nType Error\n");
		return;
	}
	}
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 989 "src/try4.y"
    {t = stack_top();
	if ((strcmp((yyvsp[(1) - (3)].eval).type,"int") == 0) && (strcmp((yyvsp[(3) - (3)].eval).type,"int") == 0))
	{
		(yyval.eval).place = newtmp();
		//sprintf(ch, "%s = %s int+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,(yyval.eval).place, (yyvsp[(1) - (3)].eval).place, "*", (yyvsp[(3) - (3)].eval).place,0,nextquad,tac_list[check]);
		gen();
		(yyval.eval).type = "int";
		enter(t,(yyval.eval).place,(yyval.eval).type,4,1);
	}
	/*else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"float") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s float+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real*", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"float") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $1.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$1.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, u, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place,u, "real*", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"int") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $3.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$3.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, $1.place, u);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real*", u,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}*/
	else
	{
		printf("\nType Error\n");
		return;
	}
	}
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 1048 "src/try4.y"
    {t = stack_top();
	if ((strcmp((yyvsp[(1) - (3)].eval).type,"int") == 0) && (strcmp((yyvsp[(3) - (3)].eval).type,"int") == 0))
	{
		(yyval.eval).place = newtmp();
		//sprintf(ch, "%s = %s int+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,(yyval.eval).place, (yyvsp[(1) - (3)].eval).place, "-", (yyvsp[(3) - (3)].eval).place,0,nextquad,tac_list[check]);
		gen();
		(yyval.eval).type = "int";
		enter(t,(yyval.eval).place,(yyval.eval).type,4,1);
	}
	/*else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"float") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s float+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real-", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"float") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $1.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$1.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, u, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place,u, "real-", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"int") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $3.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$3.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, $1.place, u);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real-", u,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}*/
	else
	{
		printf("\nType Error\n");
		return;
	}
	}
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 1107 "src/try4.y"
    {t = stack_top();
	if ((strcmp((yyvsp[(1) - (3)].eval).type,"int") == 0) && (strcmp((yyvsp[(3) - (3)].eval).type,"int") == 0))
	{
		(yyval.eval).place = newtmp();
		//sprintf(ch, "%s = %s int+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,(yyval.eval).place, (yyvsp[(1) - (3)].eval).place, "/", (yyvsp[(3) - (3)].eval).place,0,nextquad,tac_list[check]);
		gen();
		(yyval.eval).type = "int";
		enter(t,(yyval.eval).place,(yyval.eval).type,4,1);
	}
	/*else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"float") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s float+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real/", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"float") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $1.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$1.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, u, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place,u, "real/", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"int") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $3.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$3.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, $1.place, u);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real/", u,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}*/
	else
	{
		printf("\nType Error\n");
		return;
	}
	}
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 1166 "src/try4.y"
    {t = stack_top();
	if ((strcmp((yyvsp[(1) - (3)].eval).type,"int") == 0) && (strcmp((yyvsp[(3) - (3)].eval).type,"int") == 0))
	{
		(yyval.eval).place = newtmp();
		//sprintf(ch, "%s = %s int+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,(yyval.eval).place, (yyvsp[(1) - (3)].eval).place, "%", (yyvsp[(3) - (3)].eval).place,0,nextquad,tac_list[check]);
		gen();
		(yyval.eval).type = "int";
		enter(t,(yyval.eval).place,(yyval.eval).type,4,1);
	}
	/*else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"float") == 0))
	{
		$$.place = newtmp();
		//sprintf(ch, "%s = %s float+ %s", $$.place, $1.place, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real%", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"int") == 0) && (strcmp($3.type,"float") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $1.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$1.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, u, $3.place);
		check = search(stack_top());
		append(ASSIGN,$$.place,u, "real%", $3.place,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}
	else if ((strcmp($1.type,"float") == 0) && (strcmp($3.type,"int") == 0))
	{
		u = newtmp();
		//sprintf(ch, "%s = int_to_real %s", u, $3.place);
		check = search(stack_top());
		append(CHANGE_TYPE,u,$3.place,"","",0,nextquad,tac_list[check]);
		gen();
		$$.place = newtmp();
		//sprintf(ch, "%s = %s real+ %s", $$.place, $1.place, u);
		check = search(stack_top());
		append(ASSIGN,$$.place, $1.place, "real%", u,0,nextquad,tac_list[check]);
		gen();
		$$.type = "float";
		enter(t,$$.place,$$.type,8);
	}*/
	else
	{
		printf("\nType Error\n");
		return;
	}
	}
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 1225 "src/try4.y"
    {(yyval.eval).type = "bool";
	(yyval.eval).truelist = makelist(nextquad);
	(yyval.eval).falselist = makelist(nextquad+1);
	(yyval.eval).place = (char*) malloc(sizeof(char)*5);
 	sprintf((yyval.eval).place, "%s > %s", (yyvsp[(1) - (3)].eval).place, (yyvsp[(3) - (3)].eval).place);
	//sprintf(ch, "if %s > %s goto ", $1.place, $3.place);
	check = search(stack_top());
	append(IF_GOTO,"",(yyvsp[(1) - (3)].eval).place,">",(yyvsp[(3) - (3)].eval).place,0,nextquad,tac_list[check]);
	gen();
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 1241 "src/try4.y"
    {(yyval.eval).type = "bool";
	(yyval.eval).truelist = makelist(nextquad);
	(yyval.eval).falselist = makelist(nextquad+1);
	(yyval.eval).place = (char*) malloc(sizeof(char)*5);
 	sprintf((yyval.eval).place, "%s < %s", (yyvsp[(1) - (3)].eval).place, (yyvsp[(3) - (3)].eval).place);
	//sprintf(ch, "if %s > %s goto ", $1.place, $3.place);
	check = search(stack_top());
	append(IF_GOTO,"",(yyvsp[(1) - (3)].eval).place,"<",(yyvsp[(3) - (3)].eval).place,0,nextquad,tac_list[check]);//printf("\nHere\n");
	gen();
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 1257 "src/try4.y"
    {(yyval.eval).type = "bool";
	(yyval.eval).truelist = makelist(nextquad);
	(yyval.eval).falselist = makelist(nextquad+1);
	(yyval.eval).place = (char*) malloc(sizeof(char)*5);
 	sprintf((yyval.eval).place, "%s <= %s", (yyvsp[(1) - (3)].eval).place, (yyvsp[(3) - (3)].eval).place);
	//sprintf(ch, "if %s <= %s goto ", $1.place, $3.place);
	check = search(stack_top());
	append(IF_GOTO,"",(yyvsp[(1) - (3)].eval).place,"<=",(yyvsp[(3) - (3)].eval).place,0,nextquad,tac_list[check]);
	gen();
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 1273 "src/try4.y"
    {(yyval.eval).type = "bool";
	(yyval.eval).truelist = makelist(nextquad);
	(yyval.eval).falselist = makelist(nextquad+1);
	(yyval.eval).place = (char*) malloc(sizeof(char)*5);
 	sprintf((yyval.eval).place, "%s >= %s", (yyvsp[(1) - (3)].eval).place, (yyvsp[(3) - (3)].eval).place);
	//sprintf(ch, "if %s >= %s goto ", $1.place, $3.place);
	check = search(stack_top());
	append(IF_GOTO,"",(yyvsp[(1) - (3)].eval).place,">=",(yyvsp[(3) - (3)].eval).place,0,nextquad,tac_list[check]);
	gen();
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 1289 "src/try4.y"
    {(yyval.eval).type = "bool";
	(yyval.eval).truelist = makelist(nextquad);
	
	(yyval.eval).falselist = makelist(nextquad+1);
	//print_list($$.falselist);
	(yyval.eval).place = (char*) malloc(sizeof(char)*5);
 	sprintf((yyval.eval).place, "%s == %s", (yyvsp[(1) - (3)].eval).place, (yyvsp[(3) - (3)].eval).place);
	//sprintf(ch, "if %s == %s goto ", $1.place, $3.place);
	check = search(stack_top());
	append(IF_GOTO,"",(yyvsp[(1) - (3)].eval).place,"==",(yyvsp[(3) - (3)].eval).place,0,nextquad,tac_list[check]);
	gen();
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 1307 "src/try4.y"
    {(yyval.eval).type = "bool";
	(yyval.eval).truelist = makelist(nextquad);
	(yyval.eval).falselist = makelist(nextquad+1);
	(yyval.eval).place = (char*) malloc(sizeof(char)*5);
 	sprintf((yyval.eval).place, "%s != %s", (yyvsp[(1) - (3)].eval).place, (yyvsp[(3) - (3)].eval).place);
	//sprintf(ch, "if %s != %s goto ", $1.place, $3.place);
	check = search(stack_top());
	append(IF_GOTO,"",(yyvsp[(1) - (3)].eval).place,"!=",(yyvsp[(3) - (3)].eval).place,0,nextquad,tac_list[check]);
	gen();
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 1323 "src/try4.y"
    {(yyval.eval).type = "bool";
	backpatch((yyvsp[(1) - (4)].eval).truelist,(yyvsp[(3) - (4)].eval).quad, tac_list[check]);
	(yyval.eval).truelist = (yyvsp[(4) - (4)].eval).truelist;
 	(yyval.eval).falselist = merge((yyvsp[(1) - (4)].eval).falselist,(yyvsp[(4) - (4)].eval).falselist);
 	(yyval.eval).place = (char*) malloc(sizeof(char)*5);
 	sprintf((yyval.eval).place, "%s and %s", (yyvsp[(1) - (4)].eval).place, (yyvsp[(4) - (4)].eval).place);
	}
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 1332 "src/try4.y"
    {(yyval.eval).type = "bool";//printf("\n%d\n",$3.quad);
	backpatch((yyvsp[(1) - (4)].eval).falselist, (yyvsp[(3) - (4)].eval).quad, tac_list[check]);
	(yyval.eval).truelist = merge((yyvsp[(1) - (4)].eval).truelist, (yyvsp[(4) - (4)].eval).truelist);
	//print_list($$.truelist);
	(yyval.eval).falselist = (yyvsp[(4) - (4)].eval).falselist;
	(yyval.eval).place = (char*) malloc(sizeof(char)*5);
	sprintf((yyval.eval).place, "%s or %s", (yyvsp[(1) - (4)].eval).place, (yyvsp[(4) - (4)].eval).place);
	}
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 1342 "src/try4.y"
    {(yyval.eval).type = "bool";
	(yyval.eval).truelist = (yyvsp[(2) - (2)].eval).falselist;
	(yyval.eval).falselist = (yyvsp[(2) - (2)].eval).truelist;
	(yyval.eval).place = (char*) malloc(sizeof(char)*5);
	sprintf((yyval.eval).place, "not %s", (yyvsp[(2) - (2)].eval).place);
	}
    break;

  case 82:

/* Line 1806 of yacc.c  */
#line 1350 "src/try4.y"
    {(yyval.eval).type = (yyvsp[(2) - (2)].eval).type;
	(yyval.eval).place = (char*) malloc(sizeof(char)*5);
	sprintf((yyval.eval).place,"-%s",(yyvsp[(2) - (2)].eval).place);
	}
    break;

  case 83:

/* Line 1806 of yacc.c  */
#line 1356 "src/try4.y"
    {
	p = lookup(stack_top(),(yyvsp[(1) - (1)].str));

	if (p!=-1)
	{
		(yyval.eval).place = (char*) malloc(sizeof(char)*5);
		strcpy((yyval.eval).place,(yyvsp[(1) - (1)].str));
		strcpy((yyval.eval).type,stack_top()->value[p].type);
	}
	else
	{
		printf("\nVariable not declared\n");
		return;
	}
	if (strcmp((yyval.eval).type,"bool") == 0)
	{
		(yyval.eval).truelist = makelist(0);
		(yyval.eval).falselist = makelist(0);
	}
	}
    break;

  case 84:

/* Line 1806 of yacc.c  */
#line 1402 "src/try4.y"
    {
	(yyval.eval).place = (yyvsp[(1) - (1)].str);(yyval.eval).type = "int";
	(yyval.eval).width = 4;
	}
    break;

  case 85:

/* Line 1806 of yacc.c  */
#line 1408 "src/try4.y"
    {
	(yyval.eval).place = (yyvsp[(1) - (1)].str);(yyval.eval).type = "float";
	(yyval.eval).width = 8;}
    break;

  case 86:

/* Line 1806 of yacc.c  */
#line 1413 "src/try4.y"
    {
	(yyval.eval).place = (yyvsp[(1) - (1)].str);
	if (strlen((yyvsp[(1) - (1)].str)) == 3)
	{
		(yyval.eval).type = "char";
		(yyval.eval).width = 1;
	}
	else
	{
		(yyval.eval).type = "string";
		(yyval.eval).width = 100;
	}
	}
    break;

  case 87:

/* Line 1806 of yacc.c  */
#line 1428 "src/try4.y"
    {(yyval.eval).place = "1";(yyval.eval).type = "bool";
	(yyval.eval).width = 4;
	(yyval.eval).truelist = makelist(nextquad);
	(yyval.eval).falselist = makelist(0);
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
    break;

  case 88:

/* Line 1806 of yacc.c  */
#line 1439 "src/try4.y"
    {(yyval.eval).place = "0";(yyval.eval).type = "bool";
	(yyval.eval).width = 4;
	(yyval.eval).truelist = makelist(0);
	(yyval.eval).falselist = makelist(nextquad);
	//sprintf(ch, "goto ");
	check = search(stack_top());
	append(GOTO,"","","","",0,nextquad,tac_list[check]);
	gen();
	}
    break;

  case 89:

/* Line 1806 of yacc.c  */
#line 1450 "src/try4.y"
    {if (strcmp((yyvsp[(2) - (3)].eval).type,"int") == 0)
	{
		(yyval.eval).type = "int_array";
	}
	else if (strcmp((yyvsp[(2) - (3)].eval).type,"char") == 0)
	{
		(yyval.eval).type = "char_array";
	}
	else if (strcmp((yyvsp[(2) - (3)].eval).type,"float") == 0)
	{
		(yyval.eval).type = "float_array";
	}
	else if (strcmp((yyvsp[(2) - (3)].eval).type,"string") == 0)
	{
		(yyval.eval).type = "string_array";
	}
	(yyval.eval).width = counter * (yyvsp[(2) - (3)].eval).width;
	(yyval.eval).place = "NULL";
	}
    break;

  case 90:

/* Line 1806 of yacc.c  */
#line 1471 "src/try4.y"
    {(yyval.eval).place = (yyvsp[(1) - (1)].eval).place;
	(yyval.eval).checkFunc = 1;
	}
    break;

  case 91:

/* Line 1806 of yacc.c  */
#line 1478 "src/try4.y"
    {array_elem[counter] = atoi((yyvsp[(1) - (1)].eval).place);
	counter++;
	(yyval.eval).width = (yyvsp[(1) - (1)].eval).width;
	(yyval.eval).type = (yyvsp[(1) - (1)].eval).type;
	}
    break;

  case 92:

/* Line 1806 of yacc.c  */
#line 1485 "src/try4.y"
    {array_elem[counter] = atoi((yyvsp[(3) - (3)].eval).place);
	counter++;
	if (strcmp((yyvsp[(1) - (3)].eval).type,(yyvsp[(3) - (3)].eval).type) != 0)
	{
		printf("\nArray elements should be of same type.\n");
		return;
	}
	}
    break;

  case 93:

/* Line 1806 of yacc.c  */
#line 1497 "src/try4.y"
    {p = lookup(stack_top(), (yyvsp[(1) - (2)].str));
	if (p == -1)
	{
		printf("\nFunction not defined\n");
		return;
	}
	array_cnt = 0;}
    break;

  case 94:

/* Line 1806 of yacc.c  */
#line 1505 "src/try4.y"
    {for (i=0; i<array_cnt; i++)
	{
		//printf("\nparam %s\n ", params[i]);
		check = search(stack_top());
		append(PARAM,"",params[i],"","",0,nextquad,tac_list[check]);
		gen();
	}
	(yyval.eval).place = newtmp();
	//sprintf(ch, "%s = call %s ",$$.place, $1);
	check = search(stack_top());
	append(FCALL,(yyval.eval).place,(yyvsp[(1) - (5)].str),"","",array_cnt,nextquad,tac_list[check]);
	gen();
	enter(stack_top(),(yyval.eval).place, "int", 4,1);
	//enter(stack_top(), $$.place);
	}
    break;

  case 97:

/* Line 1806 of yacc.c  */
#line 1529 "src/try4.y"
    {//printf("\nInserting %s\n", $1.place);
	insert_param((yyvsp[(1) - (1)].eval).place);
	}
    break;

  case 98:

/* Line 1806 of yacc.c  */
#line 1534 "src/try4.y"
    {//printf("\nInserting %s\n", $1.place);
	insert_param((yyvsp[(1) - (3)].eval).place);
	}
    break;

  case 99:

/* Line 1806 of yacc.c  */
#line 1541 "src/try4.y"
    {(yyval.eval).quad = nextquad;
	}
    break;



/* Line 1806 of yacc.c  */
#line 3560 "y.tab.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
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
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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



/* Line 2067 of yacc.c  */
#line 1546 "src/try4.y"

extern FILE* yyin;
//int yydebug = 1;

void yyerror(char *s) {
	fprintf(stderr, "%s\n", s);
}

void yyterminate() {
}


main(int argc, char **argv)

{           
	if (argc > 1)
	{
	    FILE *file;
	    file = fopen(argv[1], "r");
	    
	    if (!file)
	    {
	        fprintf(stderr, "Could not open %s\n", argv[1]);
	        //exit(1);
	    }
	    yyin = file;
	}
	
	wfile = fopen("code.s", "w");
	wfile1 = fopen("data.s", "w");
	for (j=0; j<20; j++)
	{
		tac_list[j] = (tac*)malloc(sizeof(tac));
		scases[j] = (char*)malloc(sizeof(char)*10);
	}
	
	
	yyparse();
	for (i =0; i<fnum; i++){
	printf("\n%s:\n",func_list[i]->name);
	print_tac(tac_list[i]);
	}
	
	fprintf(wfile, "\n.section .text\n");
	fprintf(wfile, "\n.globl _start\n");
	fprintf(wfile1, "\n.section .data\n");
	fprintf(wfile1, "\ngroup:\n.long 1\n");
	fprintf(wfile1, "\nnumb:\n.long 1\n");
	for (i =0; i<fnum; i++){
		//fprintf(wfile, "\n%s:",func_list[i]->name);
		code_gen(func_list[i], tac_list[i]);
	}
	//print_st(func_list[1]);
	print_x86();
	fclose(wfile);
	fclose(wfile1);
	
	wfile1 = fopen("data.s", "r");
	wfile = fopen("code.s", "r");
	
	ftemp = fopen("ans.s", "w");
	while ((fch = fgetc(wfile1)) != EOF)
		fputc(fch, ftemp);
	fprintf(ftemp, "\n");
	while ((fch = fgetc(wfile)) != EOF)
		fputc(fch, ftemp);
		
	fclose(wfile);
	fclose(wfile1);
	fclose(ftemp);
	
	
}

