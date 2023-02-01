/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_PP_PPPARSE_H_INCLUDED
# define YY_PP_PPPARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int ppdebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOKEN_EOF = 0,
    ALSO = 258,
    BY = 259,
    COPY = 260,
    EQEQ = 261,
    IN = 262,
    LAST = 263,
    LEADING = 264,
    OF = 265,
    OFF = 266,
    PRINTING = 267,
    REPLACE = 268,
    REPLACING = 269,
    SUPPRESS = 270,
    TRAILING = 271,
    DOT = 272,
    GARBAGE = 273,
    LISTING_DIRECTIVE = 274,
    LISTING_STATEMENT = 275,
    TITLE_STATEMENT = 276,
    CONTROL_STATEMENT = 277,
    SOURCE = 278,
    NOSOURCE = 279,
    LIST = 280,
    NOLIST = 281,
    MAP = 282,
    NOMAP = 283,
    LEAP_SECOND_DIRECTIVE = 284,
    SOURCE_DIRECTIVE = 285,
    FORMAT = 286,
    IS = 287,
    FIXED = 288,
    FREE = 289,
    VARIABLE = 290,
    CALL_DIRECTIVE = 291,
    COBOL = 292,
    TOK_EXTERN = 293,
    STDCALL = 294,
    STATIC = 295,
    DEFINE_DIRECTIVE = 296,
    AS = 297,
    PARAMETER = 298,
    OVERRIDE = 299,
    REFMOD_DIRECTIVE = 300,
    SET_DIRECTIVE = 301,
    ADDRSV = 302,
    ADDSYN = 303,
    ASSIGN = 304,
    BOUND = 305,
    CALLFH = 306,
    CHECKNUM = 307,
    COMP1 = 308,
    CONSTANT = 309,
    DPC_IN_DATA = 310,
    FOLDCOPYNAME = 311,
    MAKESYN = 312,
    NOBOUND = 313,
    NOCHECKNUM = 314,
    NODPC_IN_DATA = 315,
    NOFOLDCOPYNAME = 316,
    NOSPZERO = 317,
    NOSSRANGE = 318,
    REMOVE = 319,
    SOURCEFORMAT = 320,
    SPZERO = 321,
    SSRANGE = 322,
    IF_DIRECTIVE = 323,
    ELSE_DIRECTIVE = 324,
    ENDIF_DIRECTIVE = 325,
    ELIF_DIRECTIVE = 326,
    GE = 327,
    LE = 328,
    LT = 329,
    GT = 330,
    EQ = 331,
    NE = 332,
    NOT = 333,
    THAN = 334,
    TO = 335,
    OR = 336,
    EQUAL = 337,
    GREATER = 338,
    LESS = 339,
    SET = 340,
    DEFINED = 341,
    TURN_DIRECTIVE = 342,
    ON = 343,
    CHECKING = 344,
    WITH = 345,
    LOCATION = 346,
    TERMINATOR = 347,
    TOKEN = 348,
    TEXT_NAME = 349,
    VARIABLE_NAME = 350,
    LITERAL = 351
  };
#endif
/* Tokens.  */
#define TOKEN_EOF 0
#define ALSO 258
#define BY 259
#define COPY 260
#define EQEQ 261
#define IN 262
#define LAST 263
#define LEADING 264
#define OF 265
#define OFF 266
#define PRINTING 267
#define REPLACE 268
#define REPLACING 269
#define SUPPRESS 270
#define TRAILING 271
#define DOT 272
#define GARBAGE 273
#define LISTING_DIRECTIVE 274
#define LISTING_STATEMENT 275
#define TITLE_STATEMENT 276
#define CONTROL_STATEMENT 277
#define SOURCE 278
#define NOSOURCE 279
#define LIST 280
#define NOLIST 281
#define MAP 282
#define NOMAP 283
#define LEAP_SECOND_DIRECTIVE 284
#define SOURCE_DIRECTIVE 285
#define FORMAT 286
#define IS 287
#define FIXED 288
#define FREE 289
#define VARIABLE 290
#define CALL_DIRECTIVE 291
#define COBOL 292
#define TOK_EXTERN 293
#define STDCALL 294
#define STATIC 295
#define DEFINE_DIRECTIVE 296
#define AS 297
#define PARAMETER 298
#define OVERRIDE 299
#define REFMOD_DIRECTIVE 300
#define SET_DIRECTIVE 301
#define ADDRSV 302
#define ADDSYN 303
#define ASSIGN 304
#define BOUND 305
#define CALLFH 306
#define CHECKNUM 307
#define COMP1 308
#define CONSTANT 309
#define DPC_IN_DATA 310
#define FOLDCOPYNAME 311
#define MAKESYN 312
#define NOBOUND 313
#define NOCHECKNUM 314
#define NODPC_IN_DATA 315
#define NOFOLDCOPYNAME 316
#define NOSPZERO 317
#define NOSSRANGE 318
#define REMOVE 319
#define SOURCEFORMAT 320
#define SPZERO 321
#define SSRANGE 322
#define IF_DIRECTIVE 323
#define ELSE_DIRECTIVE 324
#define ENDIF_DIRECTIVE 325
#define ELIF_DIRECTIVE 326
#define GE 327
#define LE 328
#define LT 329
#define GT 330
#define EQ 331
#define NE 332
#define NOT 333
#define THAN 334
#define TO 335
#define OR 336
#define EQUAL 337
#define GREATER 338
#define LESS 339
#define SET 340
#define DEFINED 341
#define TURN_DIRECTIVE 342
#define ON 343
#define CHECKING 344
#define WITH 345
#define LOCATION 346
#define TERMINATOR 347
#define TOKEN 348
#define TEXT_NAME 349
#define VARIABLE_NAME 350
#define LITERAL 351

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 558 "ppparse.y" /* yacc.c:1921  */

	char			*s;
	struct cb_text_list	*l;
	struct cb_replace_list	*r;
	struct cb_define_struct	*ds;
	unsigned int		ui;
	int			si;

#line 261 "ppparse.h" /* yacc.c:1921  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE pplval;

int ppparse (void);

#endif /* !YY_PP_PPPARSE_H_INCLUDED  */
