/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         ppparse
#define yylex           pplex
#define yyerror         pperror
#define yydebug         ppdebug
#define yynerrs         ppnerrs

#define yylval          pplval
#define yychar          ppchar

/* First part of user prologue.  */
#line 34 "ppparse.y" /* yacc.c:337  */

#include <config.h>

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define	COB_IN_PPPARSE	1
#include "cobc.h"
#include "tree.h"

#ifndef	_STDLIB_H
#define	_STDLIB_H 1
#endif

#define pperror(x)	cb_error_always ("%s", x)

#define COND_EQ		0
#define COND_LT		1U
#define COND_GT		2U
#define COND_LE		3U
#define COND_GE		4U
#define COND_NE		5U

/* Global variables */

int				current_call_convention;

/* Local variables */

static struct cb_define_struct	*ppp_setvar_list = NULL;
static unsigned int		current_cmd = 0;

/* Local functions */

static char *
fix_filename (char *name)
{
	/* remove quotation from alphanumeric literals */
	if (name[0] == '\'' || name[0] == '\"') {
		name++;
		name[strlen (name) - 1] = 0;
	}
	return name;
}

static char *
fold_lower (char *name)
{
	unsigned char	*p;

	for (p = (unsigned char *)name; *p; p++) {
		if (isupper (*p)) {
			*p = (cob_u8_t)tolower (*p);
		}
	}
	return name;
}

static char *
fold_upper (char *name)
{
	unsigned char	*p;

	for (p = (unsigned char *)name; *p; p++) {
		if (islower (*p)) {
			*p = (cob_u8_t)toupper (*p);
		}
	}
	return name;
}

static struct cb_replace_list *
ppp_replace_list_add (struct cb_replace_list *list,
		     const struct cb_text_list *old_text,
		     const struct cb_text_list *new_text,
		     const unsigned int lead_or_trail)
{
	struct cb_replace_list *p;

	p = cobc_plex_malloc (sizeof (struct cb_replace_list));
	p->line_num = cb_source_line;
	p->old_text = old_text;
	p->new_text = new_text;
	p->lead_trail = lead_or_trail;
	if (!list) {
		p->last = p;
		return p;
	}
	list->last->next = p;
	list->last = p;
	return list;
}

static unsigned int
ppp_set_value (struct cb_define_struct *p, const char *value)
{
	const char	*s;
	size_t		size;
	unsigned int	dotseen;
	int		sign;
	int		int_part;
	int		dec_part;

	if (!value) {
		p->deftype = PLEX_DEF_NONE;
		p->value = NULL;
		p->sign = 0;
		p->int_part = 0;
		p->dec_part = 0;
		return 0;
	}

	if (*value == '"' || *value == '\'') {
		sign = *value;
		p->value = cobc_plex_strdup (value + 1);
		size = strlen (p->value) - 1;
		if (sign != p->value[size]) {
			p->value = NULL;
			p->deftype = PLEX_DEF_NONE;
			return 1;
		}
		p->value[size] = 0;
		p->deftype = PLEX_DEF_LIT;
		p->sign = 0;
		p->int_part = 0;
		p->dec_part = 0;
		return 0;
	}

	p->value = cobc_plex_strdup (value);
	p->deftype = PLEX_DEF_NUM;
	p->sign = 0;
	p->int_part = 0;
	p->dec_part = 0;

	sign = 0;
	if (*value == '+') {
		value++;
	} else if (*value == '-') {
		value++;
		sign = 1;
	}
	int_part = 0;
	dec_part = 0;
	size = 0;
	dotseen = 0;
	s = value;
	for ( ; *s; ++s, ++size) {
		if (*s == '.') {
			if (dotseen) {
				p->deftype = PLEX_DEF_NONE;
				return 1;
			}
			dotseen = 1;
			continue;
		}
		if (*s > '9' || *s < '0') {
			p->deftype = PLEX_DEF_NONE;
			return 1;
		}
		if (!dotseen) {
			int_part = (int_part * 10) + (*s - '0');
		} else {
			dec_part = (dec_part * 10) + (*s - '0');
		}
	}

	if (!int_part && !dec_part) {
		sign = 0;
	}
	p->sign = sign;
	p->int_part = int_part;
	p->dec_part = dec_part;
	return 0;
}

static unsigned int
ppp_compare_vals (const struct cb_define_struct *p1,
		 const struct cb_define_struct *p2,
		 const unsigned int cond)
{
	int	result;

	if (!p1 || !p2) {
		return 0;
	}
	if (p1->deftype != PLEX_DEF_LIT && p1->deftype != PLEX_DEF_NUM) {
		return 0;
	}
	if (p2->deftype != PLEX_DEF_LIT && p2->deftype != PLEX_DEF_NUM) {
		return 0;
	}
	if (p1->deftype != p2->deftype) {
		cb_warning (COBC_WARN_FILLER, _("directive comparison on different types"));
		return 0;
	}
	if (p1->deftype == PLEX_DEF_LIT) {
		result = strcmp (p1->value, p2->value);
	} else {
		if (p1->sign && !p2->sign) {
			result = -1;
		} else if (!p1->sign && p2->sign) {
			result = 1;
		} else if (p1->int_part < p2->int_part) {
			if (p1->sign) {
				result = 1;
			} else {
				result = -1;
			}
		} else if (p1->int_part > p2->int_part) {
			if (p1->sign) {
				result = -1;
			} else {
				result = 1;
			}
		} else if (p1->dec_part < p2->dec_part) {
			if (p1->sign) {
				result = 1;
			} else {
				result = -1;
			}
		} else if (p1->dec_part > p2->dec_part) {
			if (p1->sign) {
				result = -1;
			} else {
				result = 1;
			}
		} else {
			result = 0;
		}
	}
	switch (cond) {
	case COND_EQ:
		return (result == 0);
	case COND_LT:
		return (result < 0);
	case COND_GT:
		return (result > 0);
	case COND_LE:
		return (result <= 0);
	case COND_GE:
		return (result >= 0);
	case COND_NE:
		return (result != 0);
	default:
		break;
	}
	return 0;
}

static struct cb_define_struct *
ppp_define_add (struct cb_define_struct *list, const char *name,
		const char *text, const unsigned int override)
{
	struct cb_define_struct	*p;
	struct cb_define_struct	*l;

	/* Check duplicate */
	for (l = list; l; l = l->next) {
		if (!strcasecmp (name, l->name)) {
			if (!override && l->deftype != PLEX_DEF_DEL) {
				cb_error (_("duplicate DEFINE directive '%s'"), name);
				return NULL;
			}
			if (l->value) {
				l->value = NULL;
			}
			if (ppp_set_value (l, text)) {
				cb_error (_("invalid constant in DEFINE directive"));
				return NULL;
			}
			return list;
		}
	}

	p = cobc_plex_malloc (sizeof (struct cb_define_struct));
	p->name = cobc_plex_strdup (name);
	if (ppp_set_value (p, text)) {
		cb_error (_("invalid constant in DEFINE directive"));
		return NULL;
	}

	if (!list) {
		p->last = p;
		return p;
	}
	list->last->next = p;
	list->last = p;
	return list;
}

static void
ppp_define_del (const char *name)
{
	struct cb_define_struct	*l;

	for (l = ppp_setvar_list; l; l = l->next) {
		if (!strcmp (name, l->name)) {
			l->deftype = PLEX_DEF_DEL;
			if (l->value) {
				l->value = NULL;
			}
			l->sign = 0;
			l->int_part = 0;
			l->dec_part = 0;
			break;
		}
	}
}

void
ppp_clear_lists (void)
{
	ppp_setvar_list = NULL;
}

struct cb_define_struct *
ppp_search_lists (const char *name)
{
	struct cb_define_struct	*p;

	for (p = ppp_setvar_list; p; p = p->next) {
		if (p->name == NULL) {
			continue;
		}
		if (!strcasecmp (name, p->name)) {
			if (p->deftype != PLEX_DEF_DEL) {
				return p;
			}
			break;
		}
	}
	return NULL;
}

static struct cb_text_list *
ppp_list_add (struct cb_text_list *list, const char *text)
{
	struct cb_text_list	*p;

	p = cobc_plex_malloc (sizeof (struct cb_text_list));
	p->text = cobc_plex_strdup (text);
	if (!list) {
		p->last = p;
		return p;
	}
	list->last->next = p;
	list->last = p;
	return list;
}

static struct cb_text_list *
ppp_list_append (struct cb_text_list *list_1, struct cb_text_list *list_2)
{
	struct cb_text_list	*list_1_end;

	if (!list_1) {
		return list_2;
	}

	for (list_1_end = list_1;
	     list_1_end->next;
	     list_1_end = list_1_end->next);
	list_1_end->next = list_2;
	list_2->last = list_1_end;

	return list_1;
}

static unsigned int
ppp_search_comp_vars (const char *name)
{
#undef	CB_PARSE_DEF
#define	CB_PARSE_DEF(x,z)	if (!strcasecmp (name, x)) return (z);
#include "ppparse.def"
#undef	CB_PARSE_DEF
	cb_warning (COBC_WARN_FILLER, _("compiler flag '%s' unknown"), name);
	return 0;
}

static unsigned int
ppp_check_needs_quote (const char *envval)
{
	const char	*s;
	size_t		size;
	unsigned int	dot_seen;
	unsigned int	sign_seen;

	/* Non-quoted value - Check if possible numeric */
	dot_seen = 0;
	sign_seen = 0;
	size = 0;
	s = envval;
	if (*s == '+' || *s == '-') {
		sign_seen = 1;
		size++;
		s++;
	}
	for (; *s; ++s) {
		if (*s == '.') {
			if (dot_seen) {
				break;
			}
			dot_seen = 1;
			size++;
			continue;
		}
		if (*s > '9' || *s < '0') {
			break;
		}
		size++;
	}

	if (*s || size <= ((size_t)dot_seen + sign_seen)) {
		return 1;
	}
	return 0;
}

static void
ppp_error_invalid_option (const char *directive, const char *option)
{
	if (option) {
		cb_error (_("invalid %s directive option '%s'"), directive, option);
	} else {
		cb_error (_("invalid %s directive option"), directive);
	}
}

static void
append_to_turn_list (struct cb_text_list *ec_names, int enable, int with_location)
{
	struct cb_turn_list	*l;
	struct cb_turn_list	*turn_list_end;

	/* Add turn directive data to end of cb_turn_list */
	l = cobc_plex_malloc (sizeof (struct cb_turn_list));
	l->ec_names = ec_names;
	l->enable = enable;
	l->with_location = with_location;
	l->next = NULL;
	/* The line number is set properly in the scanner */
	l->line = -1;
	
	if (cb_turn_list) {
		for (turn_list_end = cb_turn_list;
		     turn_list_end->next;
		     turn_list_end = turn_list_end->next);
		turn_list_end->next = l;
	} else {
		cb_turn_list = l;
	}

	/*
	  Output #TURN so we can assign a line number to this data later in the
	  scanner.
	*/
	fprintf (ppout, "#TURN\n");
}

/* Global functions */

void
ppparse_clear_vars (const struct cb_define_struct *p)
{
	const struct cb_define_struct	*q;

	ppp_setvar_list = NULL;
	/* Set standard DEFINE's */
	if (cb_perform_osvs) {
		ppp_setvar_list = ppp_define_add (ppp_setvar_list,
						  "PERFORM-TYPE",
						  "'OSVS'", 0);
	} else {
		ppp_setvar_list = ppp_define_add (ppp_setvar_list,
						  "PERFORM-TYPE",
						  "'MF'", 0);
	}
	if (cb_ebcdic_sign) {
		ppp_setvar_list = ppp_define_add (ppp_setvar_list,
						  "SIGN",
						  "'EBCDIC'", 0);
	} else {
		ppp_setvar_list = ppp_define_add (ppp_setvar_list,
						  "SIGN",
						  "'ASCII'", 0);
	}
#ifdef	WORDS_BIGENDIAN
	ppp_setvar_list = ppp_define_add (ppp_setvar_list,
					  "ENDIAN",
					  "'BIG'", 0);
#else
	ppp_setvar_list = ppp_define_add (ppp_setvar_list,
					  "ENDIAN",
					  "'LITTLE'", 0);
#endif
#if	' ' == 0x20
	ppp_setvar_list = ppp_define_add (ppp_setvar_list,
					  "CHARSET",
					  "'ASCII'", 0);
#elif	' ' == 0x40
	ppp_setvar_list = ppp_define_add (ppp_setvar_list,
					  "CHARSET",
					  "'EBCDIC'", 0);
#else
	ppp_setvar_list = ppp_define_add (ppp_setvar_list,
					  "CHARSET",
					  "'UNKNOWN'", 0);
#endif
	/* Set DEFINE's from '-D' option(s) */
	for (q = p; q; q = q->next) {
		ppp_setvar_list = ppp_define_add (ppp_setvar_list,
						  q->name,
						  q->value, 0);
	}
	/* reset CALL CONVENTION */
	current_call_convention = CB_CONV_COBOL;
}


#line 602 "ppparse.c" /* yacc.c:337  */
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
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
#line 558 "ppparse.y" /* yacc.c:352  */

	char			*s;
	struct cb_text_list	*l;
	struct cb_replace_list	*r;
	struct cb_define_struct	*ds;
	unsigned int		ui;
	int			si;

#line 848 "ppparse.c" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE pplval;

int ppparse (void);

#endif /* !YY_PP_PPPARSE_H_INCLUDED  */



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
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   247

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  99
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  189
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  269

#define YYUNDEFTOK  2
#define YYMAXUTOK   351

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      97,    98,     2,     2,     2,     2,     2,     2,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   710,   710,   711,   715,   716,   717,   718,   719,   726,
     727,   728,   729,   730,   731,   732,   734,   733,   739,   738,
     743,   747,   752,   751,   764,   765,   773,   774,   782,   783,
     787,   798,   799,   807,   815,   833,   838,   848,   852,   857,
     875,   895,   913,   917,   922,   927,   931,   935,   940,   948,
     956,   964,   990,   995,  1000,  1041,  1045,  1052,  1053,  1060,
    1069,  1072,  1079,  1084,  1092,  1101,  1106,  1110,  1115,  1123,
    1124,  1128,  1137,  1170,  1174,  1190,  1197,  1200,  1201,  1205,
    1206,  1210,  1211,  1215,  1216,  1217,  1218,  1219,  1220,  1223,
    1224,  1227,  1229,  1233,  1237,  1244,  1248,  1255,  1259,  1263,
    1270,  1271,  1275,  1276,  1280,  1281,  1285,  1290,  1295,  1300,
    1307,  1314,  1321,  1331,  1346,  1354,  1355,  1356,  1360,  1361,
    1365,  1378,  1392,  1396,  1400,  1404,  1408,  1412,  1416,  1420,
    1424,  1428,  1432,  1439,  1447,  1456,  1469,  1472,  1479,  1480,
    1483,  1484,  1489,  1492,  1499,  1503,  1510,  1514,  1518,  1522,
    1529,  1533,  1540,  1544,  1548,  1555,  1562,  1566,  1573,  1577,
    1584,  1588,  1595,  1602,  1617,  1621,  1629,  1633,  1643,  1646,
    1654,  1657,  1665,  1668,  1676,  1679,  1685,  1685,  1686,  1686,
    1687,  1687,  1688,  1688,  1689,  1689,  1690,  1690,  1691,  1691
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "ALSO", "BY", "COPY",
  "\"==\"", "IN", "LAST", "LEADING", "OF", "OFF", "PRINTING", "REPLACE",
  "REPLACING", "SUPPRESS", "TRAILING", "\".\"", "\"word\"",
  "LISTING_DIRECTIVE", "LISTING_STATEMENT", "TITLE_STATEMENT",
  "CONTROL_STATEMENT", "SOURCE", "NOSOURCE", "LIST", "NOLIST", "MAP",
  "NOMAP", "LEAP_SECOND_DIRECTIVE", "SOURCE_DIRECTIVE", "FORMAT", "IS",
  "FIXED", "FREE", "VARIABLE", "CALL_DIRECTIVE", "COBOL", "\"EXTERN\"",
  "STDCALL", "STATIC", "DEFINE_DIRECTIVE", "AS", "PARAMETER", "OVERRIDE",
  "REFMOD_DIRECTIVE", "SET_DIRECTIVE", "ADDRSV", "ADDSYN", "ASSIGN",
  "BOUND", "CALLFH", "CHECKNUM", "COMP1", "CONSTANT", "\"DPC-IN-DATA\"",
  "FOLDCOPYNAME", "MAKESYN", "NOBOUND", "NOCHECKNUM", "\"NODPC-IN-DATA\"",
  "NOFOLDCOPYNAME", "NOSPZERO", "NOSSRANGE", "REMOVE", "SOURCEFORMAT",
  "SPZERO", "SSRANGE", "IF_DIRECTIVE", "ELSE_DIRECTIVE", "ENDIF_DIRECTIVE",
  "ELIF_DIRECTIVE", "\">=\"", "\"<=\"", "\"<\"", "\">\"", "\"=\"",
  "\"<>\"", "NOT", "THAN", "TO", "OR", "EQUAL", "GREATER", "LESS", "SET",
  "DEFINED", "TURN_DIRECTIVE", "ON", "CHECKING", "WITH", "LOCATION",
  "\"end of line\"", "\"Identifier or Literal\"", "\"Text-Name\"",
  "\"Variable\"", "\"Literal\"", "'('", "')'", "$accept", "statement_list",
  "statement", "directive", "$@1", "$@2", "$@3", "if_directive_if",
  "if_directive_elif", "set_directive", "set_choice", "alnum_list",
  "alnum_equality_list", "alnum_equality", "set_options",
  "refmod_directive", "source_directive", "format_type", "_literal",
  "define_directive", "listing_directive", "listing_statement",
  "control_options", "control_option", "_dot", "leap_second_directive",
  "turn_directive", "ec_list", "on_or_off", "on_with_loc", "with_loc",
  "call_directive", "call_choice", "if_directive", "garbage",
  "variable_or_literal", "object_id", "condition_clause", "copy_statement",
  "copy_source", "copy_in", "in_or_of", "copy_suppress", "copy_replacing",
  "replace_statement", "replacing_list", "text_src", "text_dst",
  "text_partial_src", "text_partial_dst", "token_list", "identifier",
  "subscripts", "lead_trail", "_override", "_not", "_also", "_last", "_as",
  "_format", "_is", "_printing", "_on", "_than", "_to", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
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
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,    40,    41
};
# endif

#define YYPACT_NINF -161

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-161)))

#define YYTABLE_NINF -177

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -161,    22,  -161,   -75,    37,    -2,  -161,   -68,   170,     0,
     -10,  -161,   -21,    27,    88,  -161,  -161,  -161,  -161,   -49,
    -161,   -16,  -161,    40,    53,  -161,  -161,    43,  -161,  -161,
      23,    69,  -161,  -161,  -161,    65,  -161,  -161,  -161,  -161,
    -161,  -161,   164,  -161,  -161,  -161,  -161,  -161,  -161,    55,
      90,    -6,   -28,  -161,  -161,  -161,  -161,  -161,  -161,  -161,
     -11,    35,   -11,    68,  -161,    75,  -161,    76,    38,    77,
      72,   -11,  -161,  -161,  -161,  -161,  -161,  -161,    35,    72,
    -161,    86,   -35,    88,  -161,     7,    11,  -161,  -161,   -24,
    -161,  -161,  -161,  -161,  -161,   104,   -75,    87,  -161,  -161,
    -161,    23,   161,    13,   193,  -161,  -161,   108,  -161,   109,
    -161,    44,  -161,  -161,  -161,  -161,    90,  -161,    72,  -161,
      26,   126,   -11,  -161,  -161,   107,  -161,  -161,  -161,  -161,
     110,  -161,   111,  -161,   107,    12,  -161,  -161,  -161,   112,
    -161,  -161,     2,     4,  -161,  -161,     9,  -161,  -161,  -161,
    -161,    -7,  -161,   192,   191,  -161,  -161,    18,   205,   193,
      19,   117,   118,   119,   120,   210,  -161,  -161,  -161,  -161,
    -161,  -161,  -161,  -161,   121,  -161,   171,   171,   122,  -161,
    -161,  -161,  -161,  -161,  -161,  -161,   138,   138,  -161,  -161,
    -161,  -161,   -18,   128,  -161,  -161,  -161,  -161,  -161,  -161,
      23,  -161,  -161,  -161,    19,   216,    20,  -161,    13,  -161,
    -161,  -161,   -44,   215,   217,   171,  -161,  -161,  -161,  -161,
    -161,    84,   102,  -161,  -161,    23,  -161,   217,  -161,    24,
    -161,  -161,  -161,    25,  -161,  -161,  -161,  -161,  -161,  -161,
    -161,  -161,   142,   145,   145,  -161,  -161,    28,    28,  -161,
    -161,  -161,   219,  -161,  -161,  -161,   146,   147,  -161,  -161,
    -161,  -161,  -161,   144,   148,   142,   142,  -161,  -161
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,   172,    76,    79,     0,     0,    91,
     178,    22,     0,   184,     0,    16,    20,    21,    18,     0,
       3,     0,     7,     0,     0,   134,   135,   136,   173,   175,
       0,     0,    78,    77,    14,    89,    83,    84,    85,    86,
      87,    88,    89,    81,    93,    92,    15,   179,     9,   180,
       0,     0,   176,   119,    10,    75,    63,   185,    12,    62,
       0,     0,     0,     0,    35,    37,    38,     0,     0,     0,
     176,     0,    43,    44,    45,    46,    47,    48,     0,   176,
      53,    69,    60,    11,    28,     0,     0,    95,    13,     0,
       6,     4,     5,   138,   139,   140,     0,     0,   166,   167,
     160,   144,     0,   151,     0,   145,    90,     0,    82,     0,
     181,     0,   106,   107,   108,   109,    23,   104,   176,   177,
       0,     0,    49,    57,    55,    32,    33,    34,    36,    39,
       0,    40,     0,    42,    50,     0,    70,    54,    31,     0,
      29,    25,   180,   180,    17,    24,     0,   115,    27,    19,
      26,     0,    96,   182,   142,   137,   158,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    80,     8,    68,    65,
      66,    67,    64,   105,     0,    73,   168,   168,     0,    58,
      56,    30,    41,    52,    51,    61,   170,   170,   117,   118,
     116,    99,    98,     0,   103,    94,    97,   101,   183,   141,
       0,   133,   150,   159,     0,     0,     0,   146,   154,   161,
     162,   164,     0,     0,     0,   168,   169,    72,    71,    59,
     171,     0,     0,   100,   102,   143,   148,     0,   152,     0,
     165,   163,   155,     0,   147,    74,   127,   129,   130,   128,
     131,   132,   188,   186,   186,   111,   110,     0,     0,   149,
     153,   156,     0,   189,   126,   187,   123,   125,   121,   120,
     112,   113,   157,     0,     0,   188,   188,   122,   124
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -161,  -161,  -161,  -161,  -161,  -161,  -161,  -161,  -161,  -161,
     149,   151,  -161,   -56,  -161,  -161,  -161,  -161,  -161,  -161,
    -161,  -161,  -161,   189,   194,  -161,  -161,  -161,  -161,  -161,
      41,  -161,   123,   152,  -161,   -12,   -14,    15,  -161,   139,
    -161,  -161,  -161,  -161,  -161,    42,  -100,    36,    82,    16,
      39,  -144,  -161,   -99,  -160,    57,  -161,  -161,   -23,  -161,
     -22,  -161,  -161,     3,  -103
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    20,    21,    85,    86,    50,   144,   149,    83,
      84,   125,   122,   123,   138,    58,    48,   172,   137,    54,
      34,    22,    42,    43,   107,    46,    88,    89,   195,   196,
     197,   116,   117,   145,   146,   147,   260,   247,    23,    27,
      95,    96,   154,   201,    24,   101,   102,   207,   165,   234,
     157,   103,   212,   104,   217,   221,    30,    31,   120,    49,
     111,   199,    59,   256,   254
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      55,   158,   159,  -118,   191,  -119,   126,   119,   141,    32,
     188,    44,   148,   183,   119,   133,   208,   218,    25,    26,
     161,    47,     2,   162,   202,   206,   228,     3,    35,    97,
     250,   251,    98,    51,   110,     4,   110,   175,    56,    99,
      28,     5,     6,     7,     8,    29,    87,   132,  -174,   230,
      93,     9,    10,    94,   231,   235,   135,    91,    11,   139,
     208,  -176,   168,    12,  -118,   151,   179,    13,    14,   176,
      92,   152,   193,   194,    52,    53,    90,   169,   170,   171,
     105,   192,   106,   193,   194,   121,    33,   110,    45,   118,
      15,    16,    17,    18,  -118,   174,  -119,  -118,  -118,  -119,
    -119,  -114,   142,   143,   189,    53,   142,   143,   184,    19,
     163,   203,   100,   156,   119,    57,   100,   203,   252,   153,
     186,   187,   177,   258,   259,   158,   159,   112,   113,   114,
     115,   124,    60,   130,   190,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,   236,   237,   238,   239,
     240,   241,   267,   268,   127,   160,   242,   243,   244,   245,
     246,   128,   129,   131,   236,   237,   238,   239,   240,   241,
     156,   106,   136,    82,   242,   243,   244,    36,    37,    38,
      39,    40,    41,    36,    37,    38,    39,    40,    41,   164,
     166,   167,   178,   180,   198,   200,   181,   182,   185,   204,
     209,   210,   211,   213,   214,   216,   220,   215,   219,   224,
     227,   232,   253,   233,   255,   262,   265,   263,   264,   134,
     266,   108,   140,   223,   261,   155,   109,   248,   150,   173,
     226,   205,   225,   249,   222,   229,     0,   257
};

static const yytype_int16 yycheck[] =
{
      12,   101,   101,     1,    11,     1,    62,    42,     1,    11,
       1,    11,     1,     1,    42,    71,   160,   177,    93,    94,
       7,    31,     0,    10,     6,     6,     6,     5,    96,     6,
       6,     6,     9,    54,    32,    13,    32,    11,    11,    16,
       3,    19,    20,    21,    22,     8,    95,    70,    11,    93,
       7,    29,    30,    10,    98,   215,    79,    17,    36,    82,
     204,    96,    18,    41,    92,    89,   122,    45,    46,    43,
      17,    95,    90,    91,    95,    96,    92,    33,    34,    35,
      11,    88,    17,    90,    91,    96,    88,    32,    88,    95,
      68,    69,    70,    71,    92,   118,    92,    95,    96,    95,
      96,    92,    95,    96,    95,    96,    95,    96,    96,    87,
      97,    93,    93,    93,    42,    88,    93,    93,    93,    15,
     142,   143,    96,    95,    96,   225,   225,    37,    38,    39,
      40,    96,    44,    95,   146,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    72,    73,    74,    75,
      76,    77,   265,   266,    96,     4,    82,    83,    84,    85,
      86,    96,    96,    96,    72,    73,    74,    75,    76,    77,
      93,    17,    96,    95,    82,    83,    84,    23,    24,    25,
      26,    27,    28,    23,    24,    25,    26,    27,    28,     6,
      92,    92,    76,    96,    12,    14,    96,    96,    96,     4,
      93,    93,    93,    93,     4,    44,    78,    96,    96,    91,
       4,     6,    80,     6,    79,     6,    82,    81,    81,    78,
      82,    42,    83,   192,   248,    96,    42,   222,    86,   116,
     204,   159,   200,   227,   187,   206,    -1,   244
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   100,     0,     5,    13,    19,    20,    21,    22,    29,
      30,    36,    41,    45,    46,    68,    69,    70,    71,    87,
     101,   102,   120,   137,   143,    93,    94,   138,     3,     8,
     155,   156,    11,    88,   119,    96,    23,    24,    25,    26,
      27,    28,   121,   122,    11,    88,   124,    31,   115,   158,
     105,    54,    95,    96,   118,   134,    11,    88,   114,   161,
      44,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    95,   108,   109,   103,   104,    95,   125,   126,
      92,    17,    17,     7,    10,   139,   140,     6,     9,    16,
      93,   144,   145,   150,   152,    11,    17,   123,   122,   123,
      32,   159,    37,    38,    39,    40,   130,   131,    95,    42,
     157,    96,   111,   112,    96,   110,   112,    96,    96,    96,
      95,    96,   157,   112,   110,   157,    96,   117,   113,   157,
     109,     1,    95,    96,   106,   132,   133,   134,     1,   107,
     132,    89,    95,    15,   141,   138,    93,   149,   145,   152,
       4,     7,    10,    97,     6,   147,    92,    92,    18,    33,
      34,    35,   116,   131,   157,    11,    43,    96,    76,   112,
      96,    96,    96,     1,    96,    96,   159,   159,     1,    95,
     134,    11,    88,    90,    91,   127,   128,   129,    12,   160,
      14,   142,     6,    93,     4,   147,     6,   146,   150,    93,
      93,    93,   151,    93,     4,    96,    44,   153,   153,    96,
      78,   154,   154,   129,    91,   144,   146,     4,     6,   149,
      93,    98,     6,     6,   148,   153,    72,    73,    74,    75,
      76,    77,    82,    83,    84,    85,    86,   136,   136,   148,
       6,     6,    93,    80,   163,    79,   162,   162,    95,    96,
     135,   135,     6,    81,    81,    82,    82,   163,   163
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    99,   100,   100,   101,   101,   101,   101,   101,   102,
     102,   102,   102,   102,   102,   102,   103,   102,   104,   102,
     102,   102,   105,   102,   106,   106,   107,   107,   108,   108,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   110,   110,   111,   111,   112,
     113,   113,   114,   114,   115,   116,   116,   116,   116,   117,
     117,   118,   118,   118,   118,   118,   119,   119,   119,   120,
     120,   121,   121,   122,   122,   122,   122,   122,   122,   123,
     123,   124,   124,   124,   125,   126,   126,   127,   127,   127,
     128,   128,   129,   129,   130,   130,   131,   131,   131,   131,
     132,   132,   132,   132,   132,   133,   133,   133,   134,   134,
     135,   135,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   137,   138,   138,   139,   139,   140,   140,
     141,   141,   142,   142,   143,   143,   144,   144,   144,   144,
     145,   145,   146,   146,   146,   147,   148,   148,   149,   149,
     150,   150,   150,   150,   151,   151,   152,   152,   153,   153,
     154,   154,   155,   155,   156,   156,   157,   157,   158,   158,
     159,   159,   160,   160,   161,   161,   162,   162,   163,   163
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     1,     4,     2,
       2,     2,     2,     2,     2,     2,     0,     3,     0,     3,
       1,     1,     0,     3,     1,     1,     1,     1,     1,     2,
       3,     2,     2,     2,     2,     1,     2,     1,     1,     2,
       2,     3,     2,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     3,     1,     2,     1,     2,     1,     2,     3,
       0,     2,     1,     1,     3,     1,     1,     1,     1,     0,
       1,     4,     4,     3,     5,     1,     0,     1,     1,     1,
       4,     1,     2,     1,     1,     1,     1,     1,     1,     0,
       1,     0,     1,     1,     3,     1,     2,     1,     1,     1,
       2,     1,     2,     1,     1,     2,     1,     1,     1,     1,
       4,     4,     5,     5,     1,     1,     2,     2,     1,     1,
       1,     1,     5,     2,     5,     2,     2,     1,     1,     1,
       1,     1,     1,     5,     1,     1,     0,     2,     1,     1,
       0,     2,     0,     2,     3,     3,     3,     4,     4,     5,
       3,     1,     2,     3,     1,     3,     2,     3,     1,     2,
       1,     3,     3,     4,     1,     2,     1,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex ();
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 8:
#line 720 "ppparse.y" /* yacc.c:1652  */
    {
	CB_PENDING (_("*CONTROL statement"));
  }
#line 2171 "ppparse.c" /* yacc.c:1652  */
    break;

  case 16:
#line 734 "ppparse.y" /* yacc.c:1652  */
    {
	current_cmd = PLEX_ACT_IF;
  }
#line 2179 "ppparse.c" /* yacc.c:1652  */
    break;

  case 18:
#line 739 "ppparse.y" /* yacc.c:1652  */
    {
	current_cmd = PLEX_ACT_ELIF;
  }
#line 2187 "ppparse.c" /* yacc.c:1652  */
    break;

  case 20:
#line 744 "ppparse.y" /* yacc.c:1652  */
    {
	plex_action_directive (PLEX_ACT_ELSE, 0);
  }
#line 2195 "ppparse.c" /* yacc.c:1652  */
    break;

  case 21:
#line 748 "ppparse.y" /* yacc.c:1652  */
    {
	plex_action_directive (PLEX_ACT_END, 0);
  }
#line 2203 "ppparse.c" /* yacc.c:1652  */
    break;

  case 22:
#line 752 "ppparse.y" /* yacc.c:1652  */
    {
	current_call_convention = 0;
  }
#line 2211 "ppparse.c" /* yacc.c:1652  */
    break;

  case 23:
#line 756 "ppparse.y" /* yacc.c:1652  */
    {
	if (current_call_convention == CB_CONV_STATIC_LINK) {
		current_call_convention |= CB_CONV_COBOL;
	};
  }
#line 2221 "ppparse.c" /* yacc.c:1652  */
    break;

  case 25:
#line 766 "ppparse.y" /* yacc.c:1652  */
    {
	cb_error (_("invalid %s directive"), "IF");
	yyerrok;
  }
#line 2230 "ppparse.c" /* yacc.c:1652  */
    break;

  case 27:
#line 775 "ppparse.y" /* yacc.c:1652  */
    {
	cb_error (_("invalid %s directive"), "ELIF");
	yyerrok;
  }
#line 2239 "ppparse.c" /* yacc.c:1652  */
    break;

  case 30:
#line 788 "ppparse.y" /* yacc.c:1652  */
    {
	/* note: the old version was _as LITERAL but MF doesn't support this */
	struct cb_define_struct	*p;

	p = ppp_define_add (ppp_setvar_list, (yyvsp[-1].s), (yyvsp[0].s), 1);
	if (p) {
		ppp_setvar_list = p;
		fprintf (ppout, "#DEFLIT %s %s\n", (yyvsp[-1].s), (yyvsp[0].s));
	}
  }
#line 2254 "ppparse.c" /* yacc.c:1652  */
    break;

  case 32:
#line 800 "ppparse.y" /* yacc.c:1652  */
    {
	struct cb_text_list	*l;

	for (l = (yyvsp[0].l); l; l = l->next) {
		fprintf (ppout, "#ADDRSV %s\n", l->text);
	}
  }
#line 2266 "ppparse.c" /* yacc.c:1652  */
    break;

  case 33:
#line 808 "ppparse.y" /* yacc.c:1652  */
    {
	struct cb_text_list	*l;
	
	for (l = (yyvsp[0].l); l; l = l->next->next) {
		fprintf (ppout, "#ADDSYN %s %s\n", l->text, l->next->text);
	}
  }
#line 2278 "ppparse.c" /* yacc.c:1652  */
    break;

  case 34:
#line 816 "ppparse.y" /* yacc.c:1652  */
    {
	char	*p = (yyvsp[0].s);
	size_t	size;

	/* Remove surrounding quotes/brackets */
	++p;
	size = strlen (p) - 1;
	p[size] = '\0';

	if (!strcasecmp (p, "EXTERNAL")) {
		fprintf (ppout, "#ASSIGN %d\n", (int)CB_ASSIGN_EXT_FILE_NAME_REQUIRED);
	} else if (!strcasecmp (p, "DYNAMIC")) {
		fprintf (ppout, "#ASSIGN %d\n", (int)CB_ASSIGN_VARIABLE_DEFAULT);
	} else {
		ppp_error_invalid_option ("ASSIGN", p);
	}	
  }
#line 2300 "ppparse.c" /* yacc.c:1652  */
    break;

  case 35:
#line 834 "ppparse.y" /* yacc.c:1652  */
    {
	/* Enable EC-BOUND-SUBSCRIPT checking */
	append_to_turn_list (ppp_list_add (NULL, "EC-BOUND-SUBSCRIPT"), 1, 0);
  }
#line 2309 "ppparse.c" /* yacc.c:1652  */
    break;

  case 36:
#line 839 "ppparse.y" /* yacc.c:1652  */
    {
	char	*p = (yyvsp[0].s);
	/* Remove surrounding quotes/brackets */
	size_t	size;
	++p;
	size = strlen (p) - 1;
	p[size] = '\0';
	fprintf (ppout, "#CALLFH \"%s\"\n", p);
  }
#line 2323 "ppparse.c" /* yacc.c:1652  */
    break;

  case 37:
#line 849 "ppparse.y" /* yacc.c:1652  */
    {
	fprintf (ppout, "#CALLFH \"EXTFH\"\n");
  }
#line 2331 "ppparse.c" /* yacc.c:1652  */
    break;

  case 38:
#line 853 "ppparse.y" /* yacc.c:1652  */
    {
	/* Enable EC-DATA-INCOMPATIBLE checking */
	append_to_turn_list (ppp_list_add (NULL, "EC-DATA-INCOMPATIBLE"), 1, 0);
  }
#line 2340 "ppparse.c" /* yacc.c:1652  */
    break;

  case 39:
#line 858 "ppparse.y" /* yacc.c:1652  */
    {
	char	*p = (yyvsp[0].s);
	size_t	size;

	/* Remove surrounding quotes/brackets */
	++p;
	size = strlen (p) - 1;
	p[size] = '\0';

	if (!strcasecmp (p, "BINARY")) {
		cb_binary_comp_1 = 1;
	} else if (!strcasecmp (p, "FLOAT")) {
		cb_binary_comp_1 = 0;
	} else {
		ppp_error_invalid_option ("COMP1", p);
	}
  }
#line 2362 "ppparse.c" /* yacc.c:1652  */
    break;

  case 40:
#line 876 "ppparse.y" /* yacc.c:1652  */
    {
	char	*p = (yyvsp[0].s);
	size_t	size;

	/* Remove surrounding quotes/brackets */
	++p;
	size = strlen (p) - 1;
	p[size] = '\0';

	if (!strcasecmp (p, "XML")) {
		cb_dpc_in_data = CB_DPC_IN_XML;
	} else if (!strcasecmp (p, "JSON")) {
		cb_dpc_in_data = CB_DPC_IN_JSON;
	} else if (!strcasecmp (p, "ALL")) {
		cb_dpc_in_data = CB_DPC_IN_ALL;
	} else {
		ppp_error_invalid_option ("DPC-IN-DATA", p);
	}
  }
#line 2386 "ppparse.c" /* yacc.c:1652  */
    break;

  case 41:
#line 896 "ppparse.y" /* yacc.c:1652  */
    {
	char	*p = (yyvsp[0].s);
	size_t	size;

	/* Remove surrounding quotes/brackets */
	++p;
	size = strlen (p) - 1;
	p[size] = '\0';

	if (!strcasecmp (p, "UPPER")) {
		cb_fold_copy = COB_FOLD_UPPER;
	} else if (!strcasecmp (p, "LOWER")) {
		cb_fold_copy = COB_FOLD_LOWER;
	} else {
		ppp_error_invalid_option ("FOLD-COPY-NAME", p);
	}
  }
#line 2408 "ppparse.c" /* yacc.c:1652  */
    break;

  case 42:
#line 914 "ppparse.y" /* yacc.c:1652  */
    {
	fprintf (ppout, "#MAKESYN %s %s\n", (yyvsp[0].l)->text, (yyvsp[0].l)->next->text);
  }
#line 2416 "ppparse.c" /* yacc.c:1652  */
    break;

  case 43:
#line 918 "ppparse.y" /* yacc.c:1652  */
    {
	/* Disable EC-BOUND-SUBSCRIPT checking */
	append_to_turn_list (ppp_list_add (NULL, "EC-BOUND-SUBSCRIPT"), 0, 0);
  }
#line 2425 "ppparse.c" /* yacc.c:1652  */
    break;

  case 44:
#line 923 "ppparse.y" /* yacc.c:1652  */
    {
	/* Disable EC-DATA-INCOMPATIBLE checking */
	append_to_turn_list (ppp_list_add (NULL, "EC-DATA-INCOMPATIBLE"), 0, 0);
  }
#line 2434 "ppparse.c" /* yacc.c:1652  */
    break;

  case 45:
#line 928 "ppparse.y" /* yacc.c:1652  */
    {
	cb_dpc_in_data = CB_DPC_IN_NONE;
  }
#line 2442 "ppparse.c" /* yacc.c:1652  */
    break;

  case 46:
#line 932 "ppparse.y" /* yacc.c:1652  */
    {
	cb_fold_copy = 0;
  }
#line 2450 "ppparse.c" /* yacc.c:1652  */
    break;

  case 47:
#line 936 "ppparse.y" /* yacc.c:1652  */
    {
	CB_PENDING ("SPZERO");
	/* TODO: cb_space_is_zero = 0; */
  }
#line 2459 "ppparse.c" /* yacc.c:1652  */
    break;

  case 48:
#line 941 "ppparse.y" /* yacc.c:1652  */
    {
	/* Disable EC-BOUND-SUBSCRIPT and -REF-MOD checking */
	struct cb_text_list	*txt = ppp_list_add (NULL, "EC-BOUND-SUBSCRIPT");
	txt = ppp_list_add (txt, "EC-BOUND-REF-MOD");
	
	append_to_turn_list (txt, 0, 0);
  }
#line 2471 "ppparse.c" /* yacc.c:1652  */
    break;

  case 49:
#line 949 "ppparse.y" /* yacc.c:1652  */
    {
      struct cb_text_list	*l;

      for (l = (yyvsp[0].l); l; l = l->next->next) {
	      fprintf (ppout, "#OVERRIDE %s %s\n", l->text, l->next->text);
      }
  }
#line 2483 "ppparse.c" /* yacc.c:1652  */
    break;

  case 50:
#line 957 "ppparse.y" /* yacc.c:1652  */
    {
	struct cb_text_list	*l;

	for (l = (yyvsp[0].l); l; l = l->next) {
		fprintf (ppout, "#REMOVE %s\n", l->text);
	}
  }
#line 2495 "ppparse.c" /* yacc.c:1652  */
    break;

  case 51:
#line 965 "ppparse.y" /* yacc.c:1652  */
    {
	char	*p = (yyvsp[0].s);
	size_t	size;

	/* Remove surrounding quotes/brackets */
	++p;
	size = strlen (p) - 1;
	p[size] = '\0';

	if (!strcasecmp (p, "FIXED")) {
		cb_source_format = CB_FORMAT_FIXED;
		cb_text_column = cb_config_text_column;
	} else if (!strcasecmp (p, "FREE")) {
		cb_source_format = CB_FORMAT_FREE;
	} else if (!strcasecmp (p, "VARIABLE")) {
		cb_source_format = CB_FORMAT_FIXED;
		/* This value matches most MF Visual COBOL 4.0 version. */
		cb_text_column = 250;
	} else {
		ppp_error_invalid_option ("SOURCEFORMAT", p);
	}
	if (cb_src_list_file) {
		cb_current_file->source_format = cb_source_format;
	}
  }
#line 2525 "ppparse.c" /* yacc.c:1652  */
    break;

  case 52:
#line 991 "ppparse.y" /* yacc.c:1652  */
    {
	/* FIXME: we should consume until end of line here! */
	ppp_error_invalid_option ("SOURCEFORMAT", NULL);
  }
#line 2534 "ppparse.c" /* yacc.c:1652  */
    break;

  case 53:
#line 996 "ppparse.y" /* yacc.c:1652  */
    {
	CB_PENDING ("SPZERO");
	/* TODO: cb_space_is_zero = 1; */
  }
#line 2543 "ppparse.c" /* yacc.c:1652  */
    break;

  case 54:
#line 1001 "ppparse.y" /* yacc.c:1652  */
    {
	char	*p = (yyvsp[0].s);
	char	ep = 0;
	
	/* Remove surrounding quotes/brackets */
	if (p) {
		size_t	size;
		++p;
		size = strlen (p) - 1;
		p[size] = '\0';
		if (size == 1 && *p >= '1' && *p <= '3') {
			ep = *p;
		}
	} else {
		ep = '2';
	}

	/* Enable EC-BOUND-SUBSCRIPT and -REF-MOD checking */
	if (ep) {
		struct cb_text_list	*txt;
		if (ep == '3') {
			/* SSRANGE"3": REF-MOD, with zero length allowed (at runtime) */
			fprintf (ppout, "#REFMOD_ZERO 1\n");
		} else if (ep == '2') {
			/* SSRANGE"2": REF-MOD, zero length not allowed */
			fprintf (ppout, "#REFMOD_ZERO 0\n");
		} else /* if (ep == '1') */ {
			/* SSRANGE"1": REF-MOD minimal - check only for zero/negative */
			fprintf (ppout, "#REFMOD_ZERO 2\n");
		}
		txt = ppp_list_add (NULL, "EC-BOUND-SUBSCRIPT");
		txt = ppp_list_add (txt, "EC-BOUND-REF-MOD");
		append_to_turn_list (txt, 1, 0);
	} else {
		ppp_error_invalid_option ("SSRANGE", p);
	}
  }
#line 2585 "ppparse.c" /* yacc.c:1652  */
    break;

  case 55:
#line 1042 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[0].s));
  }
#line 2593 "ppparse.c" /* yacc.c:1652  */
    break;

  case 56:
#line 1046 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add ((yyvsp[-1].l), (yyvsp[0].s));
  }
#line 2601 "ppparse.c" /* yacc.c:1652  */
    break;

  case 58:
#line 1054 "ppparse.y" /* yacc.c:1652  */
    {
	  (yyval.l) = ppp_list_append ((yyvsp[-1].l), (yyvsp[0].l));
  }
#line 2609 "ppparse.c" /* yacc.c:1652  */
    break;

  case 59:
#line 1061 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[-2].s));
	(yyval.l) = ppp_list_add ((yyval.l), (yyvsp[0].s));
  }
#line 2618 "ppparse.c" /* yacc.c:1652  */
    break;

  case 60:
#line 1069 "ppparse.y" /* yacc.c:1652  */
    {
	fprintf (ppout, "#OPTION %s\n", (yyvsp[0].s));
  }
#line 2626 "ppparse.c" /* yacc.c:1652  */
    break;

  case 61:
#line 1073 "ppparse.y" /* yacc.c:1652  */
    {
	fprintf (ppout, "#OPTION %s %s\n", (yyvsp[-2].s), (yyvsp[0].s));
  }
#line 2634 "ppparse.c" /* yacc.c:1652  */
    break;

  case 62:
#line 1080 "ppparse.y" /* yacc.c:1652  */
    {
	cb_ref_mod_zero_length = 1;
	fprintf (ppout, "#OPTION REFMOD_ZERO 1\n");
  }
#line 2643 "ppparse.c" /* yacc.c:1652  */
    break;

  case 63:
#line 1085 "ppparse.y" /* yacc.c:1652  */
    {
	cb_ref_mod_zero_length = 0;
	fprintf (ppout, "#OPTION REFMOD_ZERO 0\n");
  }
#line 2652 "ppparse.c" /* yacc.c:1652  */
    break;

  case 64:
#line 1093 "ppparse.y" /* yacc.c:1652  */
    {
	  if (cb_src_list_file) {
		  cb_current_file->source_format = cb_source_format;
	  }
  }
#line 2662 "ppparse.c" /* yacc.c:1652  */
    break;

  case 65:
#line 1102 "ppparse.y" /* yacc.c:1652  */
    {
	cb_source_format = CB_FORMAT_FIXED;
	cb_text_column = cb_config_text_column;
  }
#line 2671 "ppparse.c" /* yacc.c:1652  */
    break;

  case 66:
#line 1107 "ppparse.y" /* yacc.c:1652  */
    {
	cb_source_format = CB_FORMAT_FREE;
  }
#line 2679 "ppparse.c" /* yacc.c:1652  */
    break;

  case 67:
#line 1111 "ppparse.y" /* yacc.c:1652  */
    {
	cb_source_format = CB_FORMAT_FIXED;
	cb_text_column = 500;
  }
#line 2688 "ppparse.c" /* yacc.c:1652  */
    break;

  case 68:
#line 1116 "ppparse.y" /* yacc.c:1652  */
    {
	cb_error (_("invalid %s directive"), "SOURCE");
	YYERROR;
  }
#line 2697 "ppparse.c" /* yacc.c:1652  */
    break;

  case 69:
#line 1123 "ppparse.y" /* yacc.c:1652  */
    { (yyval.s) = NULL; }
#line 2703 "ppparse.c" /* yacc.c:1652  */
    break;

  case 71:
#line 1129 "ppparse.y" /* yacc.c:1652  */
    {
	struct cb_define_struct	*p;

	p = ppp_define_add (ppp_setvar_list, (yyvsp[-3].s), (yyvsp[-1].s), (yyvsp[0].ui));
	if (p) {
		ppp_setvar_list = p;
	}
  }
#line 2716 "ppparse.c" /* yacc.c:1652  */
    break;

  case 72:
#line 1138 "ppparse.y" /* yacc.c:1652  */
    {
	char			*s;
	char			*q;
	struct cb_define_struct	*p;

	s = getenv ((yyvsp[-3].s));
	q = NULL;
	if (s && *s && *s != ' ') {
		if (*s == '"' || *s == '\'') {
			const size_t	size = strlen (s) - 1U;
			/* Ignore if improperly quoted */
			if (s[0] == s[size]) {
				q = s;
			}
		} else {
			if (ppp_check_needs_quote (s)) {
				/* Alphanumeric literal */
				q = cobc_plex_malloc (strlen (s) + 4U);
				sprintf (q, "'%s'", s);
			} else {
				/* Numeric literal */
				q = s;
			}
		}
	}
	if (q) {
		p = ppp_define_add (ppp_setvar_list, (yyvsp[-3].s), q, (yyvsp[0].ui));
		if (p) {
			ppp_setvar_list = p;
		}
	}
  }
#line 2753 "ppparse.c" /* yacc.c:1652  */
    break;

  case 73:
#line 1171 "ppparse.y" /* yacc.c:1652  */
    {
	ppp_define_del ((yyvsp[-2].s));
  }
#line 2761 "ppparse.c" /* yacc.c:1652  */
    break;

  case 74:
#line 1175 "ppparse.y" /* yacc.c:1652  */
    {
  /* OpenCOBOL/GnuCOBOL 2.0 extension: MF $SET CONSTANT in 2002+ style as
     >> DEFINE CONSTANT var [AS] literal  archaic extension:
     use plain  >> DEFINE var [AS] literal  for conditional compilation and
     use        01 CONSTANT with/without FROM clause  for constant definitions */
	struct cb_define_struct	*p;

	if (cb_verify (cb_define_constant_directive, ">> DEFINE CONSTANT var")) {
		p = ppp_define_add (ppp_setvar_list, (yyvsp[-3].s), (yyvsp[-1].s), (yyvsp[0].ui));
		if (p) {
			ppp_setvar_list = p;
			fprintf (ppout, "#DEFLIT %s %s%s\n", (yyvsp[-3].s), (yyvsp[-1].s), (yyvsp[0].ui) ? " OVERRIDE" : "");
		}
	}
  }
#line 2781 "ppparse.c" /* yacc.c:1652  */
    break;

  case 75:
#line 1191 "ppparse.y" /* yacc.c:1652  */
    {
	cb_error (_("invalid %s directive"), "DEFINE/SET");
  }
#line 2789 "ppparse.c" /* yacc.c:1652  */
    break;

  case 92:
#line 1230 "ppparse.y" /* yacc.c:1652  */
    {
	CB_PENDING (_("LEAP-SECOND ON directive"));
  }
#line 2797 "ppparse.c" /* yacc.c:1652  */
    break;

  case 94:
#line 1238 "ppparse.y" /* yacc.c:1652  */
    {
	append_to_turn_list ((yyvsp[-2].l), !!(yyvsp[0].ui), (yyvsp[0].ui) == 2U);
  }
#line 2805 "ppparse.c" /* yacc.c:1652  */
    break;

  case 95:
#line 1245 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[0].s));
  }
#line 2813 "ppparse.c" /* yacc.c:1652  */
    break;

  case 96:
#line 1249 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add ((yyvsp[-1].l), (yyvsp[0].s));
  }
#line 2821 "ppparse.c" /* yacc.c:1652  */
    break;

  case 97:
#line 1256 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = 2U;
  }
#line 2829 "ppparse.c" /* yacc.c:1652  */
    break;

  case 98:
#line 1260 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = 1U;
  }
#line 2837 "ppparse.c" /* yacc.c:1652  */
    break;

  case 99:
#line 1264 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = 0;
  }
#line 2845 "ppparse.c" /* yacc.c:1652  */
    break;

  case 106:
#line 1286 "ppparse.y" /* yacc.c:1652  */
    {
	current_call_convention |= CB_CONV_COBOL;
	current_call_convention &= ~CB_CONV_STDCALL;
  }
#line 2854 "ppparse.c" /* yacc.c:1652  */
    break;

  case 107:
#line 1291 "ppparse.y" /* yacc.c:1652  */
    {
	current_call_convention &= ~CB_CONV_STDCALL;
	current_call_convention &= ~CB_CONV_COBOL;
  }
#line 2863 "ppparse.c" /* yacc.c:1652  */
    break;

  case 108:
#line 1296 "ppparse.y" /* yacc.c:1652  */
    {
	current_call_convention |= CB_CONV_STDCALL;
	current_call_convention &= ~CB_CONV_COBOL;
  }
#line 2872 "ppparse.c" /* yacc.c:1652  */
    break;

  case 109:
#line 1301 "ppparse.y" /* yacc.c:1652  */
    {
	current_call_convention |= CB_CONV_STATIC_LINK;
  }
#line 2880 "ppparse.c" /* yacc.c:1652  */
    break;

  case 110:
#line 1308 "ppparse.y" /* yacc.c:1652  */
    {
	unsigned int		found;

	found = (ppp_search_lists ((yyvsp[-3].s)) != NULL);
	plex_action_directive (current_cmd, found ^ (yyvsp[-1].ui));
  }
#line 2891 "ppparse.c" /* yacc.c:1652  */
    break;

  case 111:
#line 1315 "ppparse.y" /* yacc.c:1652  */
    {
	unsigned int		found;

	found = ppp_search_comp_vars ((yyvsp[-3].s));
	plex_action_directive (current_cmd, found ^ (yyvsp[-1].ui));
  }
#line 2902 "ppparse.c" /* yacc.c:1652  */
    break;

  case 112:
#line 1322 "ppparse.y" /* yacc.c:1652  */
    {
	struct cb_define_struct	*p;
	unsigned int		found;

	found = 0;
	p = ppp_search_lists ((yyvsp[-4].s));
	found = ppp_compare_vals (p, (yyvsp[0].ds), (yyvsp[-1].ui));
	plex_action_directive (current_cmd, found ^ (yyvsp[-2].ui));
  }
#line 2916 "ppparse.c" /* yacc.c:1652  */
    break;

  case 113:
#line 1332 "ppparse.y" /* yacc.c:1652  */
    {
	struct cb_define_struct	*p;
	unsigned int		found;

	found = 0;
	p = cobc_plex_malloc (sizeof (struct cb_define_struct));
	p->next = NULL;
	if (ppp_set_value (p, (yyvsp[-4].s))) {
		cb_error (_("invalid constant"));
	} else {
		found = ppp_compare_vals (p, (yyvsp[0].ds), (yyvsp[-1].ui));
	}
	plex_action_directive (current_cmd, found ^ (yyvsp[-2].ui));
  }
#line 2935 "ppparse.c" /* yacc.c:1652  */
    break;

  case 114:
#line 1347 "ppparse.y" /* yacc.c:1652  */
    {
	plex_action_directive (current_cmd, 0);
	YYERROR;
  }
#line 2944 "ppparse.c" /* yacc.c:1652  */
    break;

  case 120:
#line 1366 "ppparse.y" /* yacc.c:1652  */
    {
	struct cb_define_struct	*p;

	p = cobc_plex_malloc (sizeof (struct cb_define_struct));
	p->next = NULL;
	if (ppp_set_value (p, (yyvsp[0].s))) {
		cb_error (_("invalid constant"));
		(yyval.ds) = NULL;
	} else {
		(yyval.ds) = p;
	}
  }
#line 2961 "ppparse.c" /* yacc.c:1652  */
    break;

  case 121:
#line 1379 "ppparse.y" /* yacc.c:1652  */
    {
	struct cb_define_struct	*p;

	p = ppp_search_lists ((yyvsp[0].s));
	if (p != NULL && p->deftype != PLEX_DEF_NONE) {
		(yyval.ds) = p;
	} else {
		(yyval.ds) = NULL;
	}
  }
#line 2976 "ppparse.c" /* yacc.c:1652  */
    break;

  case 122:
#line 1393 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = COND_GE;
  }
#line 2984 "ppparse.c" /* yacc.c:1652  */
    break;

  case 123:
#line 1397 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = COND_GT;
  }
#line 2992 "ppparse.c" /* yacc.c:1652  */
    break;

  case 124:
#line 1401 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = COND_LE;
  }
#line 3000 "ppparse.c" /* yacc.c:1652  */
    break;

  case 125:
#line 1405 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = COND_LT;
  }
#line 3008 "ppparse.c" /* yacc.c:1652  */
    break;

  case 126:
#line 1409 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = COND_EQ;
  }
#line 3016 "ppparse.c" /* yacc.c:1652  */
    break;

  case 127:
#line 1413 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = COND_GE;
  }
#line 3024 "ppparse.c" /* yacc.c:1652  */
    break;

  case 128:
#line 1417 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = COND_GT;
  }
#line 3032 "ppparse.c" /* yacc.c:1652  */
    break;

  case 129:
#line 1421 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = COND_LE;
  }
#line 3040 "ppparse.c" /* yacc.c:1652  */
    break;

  case 130:
#line 1425 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = COND_LT;
  }
#line 3048 "ppparse.c" /* yacc.c:1652  */
    break;

  case 131:
#line 1429 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = COND_EQ;
  }
#line 3056 "ppparse.c" /* yacc.c:1652  */
    break;

  case 132:
#line 1433 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = COND_NE;
  }
#line 3064 "ppparse.c" /* yacc.c:1652  */
    break;

  case 133:
#line 1440 "ppparse.y" /* yacc.c:1652  */
    {
	fputc ('\n', ppout);
	ppcopy ((yyvsp[-3].s), (yyvsp[-2].s), (yyvsp[0].r));
  }
#line 3073 "ppparse.c" /* yacc.c:1652  */
    break;

  case 134:
#line 1448 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.s) = fix_filename ((yyvsp[0].s));
	if (cb_fold_copy == COB_FOLD_LOWER) {
		(yyval.s) = fold_lower ((yyval.s));
	} else if (cb_fold_copy == COB_FOLD_UPPER) {
		(yyval.s) = fold_upper ((yyval.s));
	}
  }
#line 3086 "ppparse.c" /* yacc.c:1652  */
    break;

  case 135:
#line 1457 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.s) = (yyvsp[0].s);
	if (cb_fold_copy == COB_FOLD_LOWER) {
		(yyval.s) = fold_lower ((yyval.s));
	} else {
		(yyval.s) = fold_upper ((yyval.s));
	}
  }
#line 3099 "ppparse.c" /* yacc.c:1652  */
    break;

  case 136:
#line 1469 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.s) = NULL;
  }
#line 3107 "ppparse.c" /* yacc.c:1652  */
    break;

  case 137:
#line 1473 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.s) = (yyvsp[0].s);
  }
#line 3115 "ppparse.c" /* yacc.c:1652  */
    break;

  case 142:
#line 1489 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.r) = NULL;
  }
#line 3123 "ppparse.c" /* yacc.c:1652  */
    break;

  case 143:
#line 1493 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.r) = (yyvsp[0].r);
  }
#line 3131 "ppparse.c" /* yacc.c:1652  */
    break;

  case 144:
#line 1500 "ppparse.y" /* yacc.c:1652  */
    {
	pp_set_replace_list ((yyvsp[0].r), (yyvsp[-1].ui));
  }
#line 3139 "ppparse.c" /* yacc.c:1652  */
    break;

  case 145:
#line 1504 "ppparse.y" /* yacc.c:1652  */
    {
	pp_set_replace_list (NULL, (yyvsp[-1].ui));
  }
#line 3147 "ppparse.c" /* yacc.c:1652  */
    break;

  case 146:
#line 1511 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.r) = ppp_replace_list_add (NULL, (yyvsp[-2].l), (yyvsp[0].l), 0);
  }
#line 3155 "ppparse.c" /* yacc.c:1652  */
    break;

  case 147:
#line 1515 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.r) = ppp_replace_list_add (NULL, (yyvsp[-2].l), (yyvsp[0].l), (yyvsp[-3].ui));
  }
#line 3163 "ppparse.c" /* yacc.c:1652  */
    break;

  case 148:
#line 1519 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.r) = ppp_replace_list_add ((yyvsp[-3].r), (yyvsp[-2].l), (yyvsp[0].l), 0);
  }
#line 3171 "ppparse.c" /* yacc.c:1652  */
    break;

  case 149:
#line 1523 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.r) = ppp_replace_list_add ((yyvsp[-4].r), (yyvsp[-2].l), (yyvsp[0].l), (yyvsp[-3].ui));
  }
#line 3179 "ppparse.c" /* yacc.c:1652  */
    break;

  case 150:
#line 1530 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = (yyvsp[-1].l);
  }
#line 3187 "ppparse.c" /* yacc.c:1652  */
    break;

  case 151:
#line 1534 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = (yyvsp[0].l);
  }
#line 3195 "ppparse.c" /* yacc.c:1652  */
    break;

  case 152:
#line 1541 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = NULL;
  }
#line 3203 "ppparse.c" /* yacc.c:1652  */
    break;

  case 153:
#line 1545 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = (yyvsp[-1].l);
  }
#line 3211 "ppparse.c" /* yacc.c:1652  */
    break;

  case 154:
#line 1549 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = (yyvsp[0].l);
  }
#line 3219 "ppparse.c" /* yacc.c:1652  */
    break;

  case 155:
#line 1556 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[-1].s));
  }
#line 3227 "ppparse.c" /* yacc.c:1652  */
    break;

  case 156:
#line 1563 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = NULL;
  }
#line 3235 "ppparse.c" /* yacc.c:1652  */
    break;

  case 157:
#line 1567 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[-1].s));
  }
#line 3243 "ppparse.c" /* yacc.c:1652  */
    break;

  case 158:
#line 1574 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[0].s));
  }
#line 3251 "ppparse.c" /* yacc.c:1652  */
    break;

  case 159:
#line 1578 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add ((yyvsp[-1].l), (yyvsp[0].s));
  }
#line 3259 "ppparse.c" /* yacc.c:1652  */
    break;

  case 160:
#line 1585 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[0].s));
  }
#line 3267 "ppparse.c" /* yacc.c:1652  */
    break;

  case 161:
#line 1589 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add ((yyvsp[-2].l), " ");
	(yyval.l) = ppp_list_add ((yyval.l), "IN");
	(yyval.l) = ppp_list_add ((yyval.l), " ");
	(yyval.l) = ppp_list_add ((yyval.l), (yyvsp[0].s));
  }
#line 3278 "ppparse.c" /* yacc.c:1652  */
    break;

  case 162:
#line 1596 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add ((yyvsp[-2].l), " ");
	(yyval.l) = ppp_list_add ((yyval.l), "OF");
	(yyval.l) = ppp_list_add ((yyval.l), " ");
	(yyval.l) = ppp_list_add ((yyval.l), (yyvsp[0].s));
  }
#line 3289 "ppparse.c" /* yacc.c:1652  */
    break;

  case 163:
#line 1603 "ppparse.y" /* yacc.c:1652  */
    {
	struct cb_text_list *l;

	(yyval.l) = ppp_list_add ((yyvsp[-3].l), " ");
	(yyval.l) = ppp_list_add ((yyval.l), "(");
	(yyvsp[-1].l) = ppp_list_add ((yyvsp[-1].l), ")");
	for (l = (yyval.l); l->next; l = l->next) {
		;
	}
	l->next = (yyvsp[-1].l);
  }
#line 3305 "ppparse.c" /* yacc.c:1652  */
    break;

  case 164:
#line 1618 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[0].s));
  }
#line 3313 "ppparse.c" /* yacc.c:1652  */
    break;

  case 165:
#line 1622 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.l) = ppp_list_add ((yyvsp[-1].l), " ");
	(yyval.l) = ppp_list_add ((yyval.l), (yyvsp[0].s));
  }
#line 3322 "ppparse.c" /* yacc.c:1652  */
    break;

  case 166:
#line 1630 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = CB_REPLACE_LEADING;
  }
#line 3330 "ppparse.c" /* yacc.c:1652  */
    break;

  case 167:
#line 1634 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = CB_REPLACE_TRAILING;
  }
#line 3338 "ppparse.c" /* yacc.c:1652  */
    break;

  case 168:
#line 1643 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = 0;
  }
#line 3346 "ppparse.c" /* yacc.c:1652  */
    break;

  case 169:
#line 1647 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = 1U;
  }
#line 3354 "ppparse.c" /* yacc.c:1652  */
    break;

  case 170:
#line 1654 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = 0;
  }
#line 3362 "ppparse.c" /* yacc.c:1652  */
    break;

  case 171:
#line 1658 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = 1U;
  }
#line 3370 "ppparse.c" /* yacc.c:1652  */
    break;

  case 172:
#line 1665 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = 0;
  }
#line 3378 "ppparse.c" /* yacc.c:1652  */
    break;

  case 173:
#line 1669 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = 1U;
  }
#line 3386 "ppparse.c" /* yacc.c:1652  */
    break;

  case 174:
#line 1676 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = 0;
  }
#line 3394 "ppparse.c" /* yacc.c:1652  */
    break;

  case 175:
#line 1680 "ppparse.y" /* yacc.c:1652  */
    {
	(yyval.ui) = 1U;
  }
#line 3402 "ppparse.c" /* yacc.c:1652  */
    break;


#line 3406 "ppparse.c" /* yacc.c:1652  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 1693 "ppparse.y" /* yacc.c:1918  */

