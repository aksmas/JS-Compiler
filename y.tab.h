/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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

/* Line 2068 of yacc.c  */
#line 130 "src/try4.y"

        int num;
        char *str;
        double val;
        struct etype eval;



/* Line 2068 of yacc.c  */
#line 195 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


