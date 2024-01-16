/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
    COBOL_WORDS_DIRECTIVE = 277,
    EQUATE = 278,
    UNDEFINE = 279,
    SUBSTITUTE = 280,
    RESERVE = 281,
    CONTROL_STATEMENT = 282,
    SOURCE = 283,
    NOSOURCE = 284,
    LIST = 285,
    NOLIST = 286,
    MAP = 287,
    NOMAP = 288,
    LEAP_SECOND_DIRECTIVE = 289,
    CONTROL_DIVISION = 290,
    SUBSTITUTION_SECTION = 291,
    SOURCE_DIRECTIVE = 292,
    FORMAT = 293,
    IS = 294,
    CALL_DIRECTIVE = 295,
    COBOL = 296,
    TOK_EXTERN = 297,
    STDCALL = 298,
    STATIC = 299,
    DEFINE_DIRECTIVE = 300,
    AS = 301,
    PARAMETER = 302,
    OVERRIDE = 303,
    REFMOD_DIRECTIVE = 304,
    SET_DIRECTIVE = 305,
    ADDRSV = 306,
    ADDSYN = 307,
    AREACHECK = 308,
    NOAREACHECK = 309,
    ASSIGN = 310,
    BOUND = 311,
    CALLFH = 312,
    CHECKNUM = 313,
    COMP1 = 314,
    CONSTANT = 315,
    DPC_IN_DATA = 316,
    FOLDCOPYNAME = 317,
    MAKESYN = 318,
    NOBOUND = 319,
    NOCHECKNUM = 320,
    NODPC_IN_DATA = 321,
    NOFOLDCOPYNAME = 322,
    NOODOSLIDE = 323,
    NOSPZERO = 324,
    NOSSRANGE = 325,
    ODOSLIDE = 326,
    REMOVE = 327,
    SOURCEFORMAT = 328,
    SPZERO = 329,
    SSRANGE = 330,
    IF_DIRECTIVE = 331,
    ELSE_DIRECTIVE = 332,
    ENDIF_DIRECTIVE = 333,
    ELIF_DIRECTIVE = 334,
    GE = 335,
    LE = 336,
    LT = 337,
    GT = 338,
    EQ = 339,
    NE = 340,
    NOT = 341,
    THAN = 342,
    TO = 343,
    OR = 344,
    EQUAL = 345,
    GREATER = 346,
    LESS = 347,
    SET = 348,
    DEFINED = 349,
    TURN_DIRECTIVE = 350,
    ON = 351,
    CHECKING = 352,
    WITH = 353,
    LOCATION = 354,
    TERMINATOR = 355,
    TOKEN = 356,
    TEXT_NAME = 357,
    VARIABLE_NAME = 358,
    LITERAL = 359
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 619 "ppparse.y" /* yacc.c:1909  */

	char			*s;
	struct cb_text_list	*l;
	struct cb_replace_src	*p;
	struct cb_replace_list	*r;
	struct cb_define_struct	*ds;
	unsigned int		ui;
	int			si;

#line 170 "ppparse.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE pplval;

int ppparse (void);

#endif /* !YY_PP_PPPARSE_H_INCLUDED  */
