/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

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

/* Copy the first part of user declarations.  */
#line 34 "ppparse.y" /* yacc.c:339  */

#include "config.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#ifdef	HAVE_STRINGS_H
#include <strings.h>
#endif
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
static enum cb_directive_action		current_cmd = PLEX_ACT_IF;

/* Local functions */

/* Strips the given string from its quotation characters, if any.  Returns its
   argument as is otherwise. */
static char *
unquote (char *name)
{
	size_t size;
	if ((name[0] == '\'' || name[0] == '"') && (size = strlen (name)) > 1 &&
	    (name[0] == name[size - 1])) {
		name[size - 1] = '\0';
		name++;
	}
	return name;
}
#define fix_filename(filename) unquote (filename)

static int
literal_is_space_keyword (char *lit)
{
	return (strcmp ("SPACE",  lit) == 0
		 || strcmp ("SPACES", lit) == 0);
}

static char *
literal_token (char *t, int allow_spaces)
{
	if (t[0] == '\'' || t[0] == '"') {
		if (cb_partial_replace_when_literal_src != CB_SKIP)
			(void) ppparse_verify (cb_partial_replace_when_literal_src,
					       _("partial replacing with literal"));
	} else if (allow_spaces && literal_is_space_keyword (t)) {
		if (cb_partial_replace_when_literal_src != CB_SKIP)
			(void) ppparse_verify (cb_partial_replace_when_literal_src,
					       _("partial replacing with literal"));
		t[0] = '\0';
	} else {
		ppparse_error (_("unexpected COBOL word in partial replacement "
				 "phrase"));
	}
	return unquote (t);
}

static char *
fold_lower (char *name)
{
	unsigned char	*p;

	for (p = (unsigned char *)name; *p; p++) {
		*p = (cob_u8_t)tolower (*p);
	}
	return name;
}

static char *
fold_upper (char *name)
{
	unsigned char	*p;

	for (p = (unsigned char *)name; *p; p++) {
		*p = (cob_u8_t)toupper (*p);
	}
	return name;
}

static struct cb_replace_src *
ppp_replace_src (const struct cb_text_list * const text_list,
		 const unsigned int literal_src)
{
	const unsigned int allow_empty_replacement =
		!literal_src || cb_partial_replace_when_literal_src != CB_SKIP;
	struct cb_replace_src *s = cobc_plex_malloc (sizeof (struct cb_replace_src));
	/* Note the two next fields are re-assessed in ppp_replace_list_add below */
	s->lead_trail = CB_REPLACE_ALL;
	s->strict = allow_empty_replacement ? 0 : 1;
	s->text_list = text_list;
	return s;
}

static struct cb_replace_list *
ppp_replace_list_add (struct cb_replace_list *list,
		      struct cb_replace_src *src,
		      const struct cb_text_list *new_text,
		      const unsigned int lead_or_trail)
{
	struct cb_replace_list *p;

	p = cobc_plex_malloc (sizeof (struct cb_replace_list));
	p->line_num = cb_source_line;
	src->lead_trail = lead_or_trail;
	if (!lead_or_trail) {
		/* Strictness flag is irrelevant for non-LEADING nor TRAILING
		   replacements */
		src->strict = 0;
	} else {
		/* Use replacement text to decide strictness of partial match */
		const unsigned char *c;
		int has_space = new_text->next != NULL;
		for (c = (unsigned char *) new_text->text; !has_space && *c; c++) {
			has_space = isspace(*c);
		}
		if (has_space) {
			/* Note: as it appears, multi-word or spaces in
			   replacing is forbidden on GCOS. */
			ppparse_error (_("invalid partial replacing operand"));
			return NULL;
		}
		src->strict = src->strict && *new_text->text == '\0';
	}
	p->src = src;
	p->new_text = new_text;
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

	p->value = NULL;
	p->sign = 0;
	p->int_part = 0;
	p->dec_part = 0;

	if (!value) {
		p->deftype = PLEX_DEF_NONE;
		return 0;
	}

	if (*value == '"' || *value == '\'') {
		s = value + 1;
		size = strlen (s) - 1;
		if (s[size] != *value) {
			p->deftype = PLEX_DEF_NONE;
			return 1;
		}
		p->deftype = PLEX_DEF_LIT;
		p->value = cobc_plex_strdup (s);
		p->value[size] = 0;
		return 0;
	}

	if (*value == '(') {
		/* actual MicroFocus Format for numeric values: (numlit) */
		s = value + 1;
		size = strlen (s) - 1;
		if (s[size] != ')') {
			p->deftype = PLEX_DEF_NONE;
			return 1;
		}
		p->deftype = PLEX_DEF_NUM;
		p->value = cobc_plex_strdup (s);
		p->value[size] = 0;
	} else {
		/* compatibility because this was supported since OpenCOBOL 2.0 */
		p->deftype = PLEX_DEF_NUM;
		p->value = cobc_plex_strdup (value);
	}

	p->sign = 0;
	s = p->value;
	if (*s == '+') {
		s++;
	} else if (*s == '-') {
		s++;
		p->sign = 1;
	}
	dotseen = 0;
	for ( ; *s; ++s) {
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
			p->int_part = (p->int_part * 10) + (*s - '0');
		} else {
			p->dec_part = (p->dec_part * 10) + (*s - '0');
		}
	}

	if (!p->int_part && !p->dec_part) {
		p->sign = 0;	/* zero is unsigned */
	}
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
				cb_error (_("invalid constant %s in DEFINE directive"), text);
				return NULL;
			}
			return list;
		}
	}

	p = cobc_plex_malloc (sizeof (struct cb_define_struct));
	p->name = cobc_plex_strdup (name);
	if (ppp_set_value (p, text)) {
		cb_error (_ ("invalid constant %s in DEFINE directive"), text);
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
#define	CB_PARSE_DEF(x,z)	if (!cb_strcasecmp (name, x)) return (z);
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


#line 659 "ppparse.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
#line 619 "ppparse.y" /* yacc.c:355  */

	char			*s;
	struct cb_text_list	*l;
	struct cb_replace_src	*p;
	struct cb_replace_list	*r;
	struct cb_define_struct	*ds;
	unsigned int		ui;
	int			si;

#line 815 "ppparse.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE pplval;

int ppparse (void);

#endif /* !YY_PP_PPPARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 832 "ppparse.c" /* yacc.c:358  */

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
# elif ! defined YYSIZE_T
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

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   318

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  107
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  77
/* YYNRULES -- Number of rules.  */
#define YYNRULES  220
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  316

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   359

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     105,   106,     2,     2,     2,     2,     2,     2,     2,     2,
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
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   788,   788,   789,   797,   798,   799,   800,   804,   809,
     812,   813,   816,   817,   821,   822,   826,   827,   828,   829,
     833,   834,   835,   836,   837,   838,   839,   840,   842,   841,
     847,   846,   851,   855,   860,   859,   872,   873,   881,   882,
     890,   891,   895,   911,   912,   919,   926,   932,   944,   949,
     953,   957,   962,   974,   988,  1000,  1004,  1010,  1015,  1020,
    1024,  1028,  1032,  1037,  1045,  1049,  1056,  1063,  1074,  1079,
    1084,  1125,  1129,  1136,  1137,  1144,  1152,  1153,  1160,  1168,
    1169,  1176,  1185,  1188,  1195,  1200,  1208,  1217,  1225,  1226,
    1230,  1239,  1272,  1276,  1292,  1299,  1307,  1314,  1322,  1332,
    1335,  1336,  1340,  1341,  1345,  1346,  1350,  1351,  1352,  1353,
    1354,  1355,  1358,  1359,  1362,  1364,  1368,  1372,  1379,  1383,
    1390,  1394,  1398,  1405,  1406,  1410,  1411,  1415,  1416,  1420,
    1425,  1430,  1435,  1442,  1449,  1456,  1466,  1481,  1489,  1490,
    1491,  1495,  1496,  1500,  1513,  1527,  1531,  1535,  1539,  1543,
    1547,  1551,  1555,  1559,  1563,  1567,  1574,  1579,  1586,  1595,
    1608,  1611,  1618,  1619,  1622,  1624,  1629,  1632,  1639,  1640,
    1647,  1651,  1658,  1662,  1666,  1670,  1677,  1681,  1706,  1710,
    1714,  1718,  1725,  1735,  1739,  1747,  1751,  1755,  1762,  1766,
    1773,  1777,  1784,  1791,  1806,  1810,  1818,  1822,  1829,  1849,
    1852,  1860,  1863,  1871,  1874,  1882,  1885,  1891,  1891,  1892,
    1892,  1893,  1893,  1894,  1894,  1895,  1895,  1896,  1896,  1897,
    1897
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
  "COBOL_WORDS_DIRECTIVE", "EQUATE", "UNDEFINE", "SUBSTITUTE", "RESERVE",
  "CONTROL_STATEMENT", "SOURCE", "NOSOURCE", "LIST", "NOLIST", "MAP",
  "NOMAP", "LEAP_SECOND_DIRECTIVE", "\"CONTROL DIVISION\"",
  "\"SUBSTITUTION SECTION\"", "SOURCE_DIRECTIVE", "FORMAT", "IS",
  "CALL_DIRECTIVE", "COBOL", "\"EXTERN\"", "STDCALL", "STATIC",
  "DEFINE_DIRECTIVE", "AS", "PARAMETER", "OVERRIDE", "REFMOD_DIRECTIVE",
  "SET_DIRECTIVE", "ADDRSV", "ADDSYN", "AREACHECK", "NOAREACHECK",
  "ASSIGN", "BOUND", "CALLFH", "CHECKNUM", "COMP1", "CONSTANT",
  "\"DPC-IN-DATA\"", "FOLDCOPYNAME", "MAKESYN", "NOBOUND", "NOCHECKNUM",
  "\"NODPC-IN-DATA\"", "NOFOLDCOPYNAME", "NOODOSLIDE", "NOSPZERO",
  "NOSSRANGE", "ODOSLIDE", "REMOVE", "SOURCEFORMAT", "SPZERO", "SSRANGE",
  "IF_DIRECTIVE", "ELSE_DIRECTIVE", "ENDIF_DIRECTIVE", "ELIF_DIRECTIVE",
  "\">=\"", "\"<=\"", "\"<\"", "\">\"", "\"=\"", "\"<>\"", "NOT", "THAN",
  "TO", "OR", "EQUAL", "GREATER", "LESS", "SET", "DEFINED",
  "TURN_DIRECTIVE", "ON", "CHECKING", "WITH", "LOCATION",
  "\"end of line\"", "\"Word or Literal\"", "\"Text-Name\"",
  "\"Variable\"", "\"Literal\"", "'('", "')'", "$accept",
  "program_structure", "program_with_control_division",
  "control_division_no_replace", "control_division_with_replace",
  "statement_list", "statement_no_replace_list", "statement",
  "statement_no_replace", "directive", "$@1", "$@2", "$@3",
  "if_directive_if", "if_directive_elif", "set_directive", "set_choice",
  "alnum_list", "alnum_equality_list", "alnum_equality", "alnum_with_list",
  "alnum_with", "alnum_by_list", "alnum_by", "set_options",
  "refmod_directive", "source_directive", "_literal", "define_directive",
  "cobol_words_directive", "listing_directive", "listing_statement",
  "control_options", "control_option", "_dot", "leap_second_directive",
  "turn_directive", "ec_list", "on_or_off", "on_with_loc", "with_loc",
  "call_directive", "call_choice", "if_directive", "garbage",
  "variable_or_literal", "object_id", "condition_clause", "copy_statement",
  "copy_source", "_copy_in", "in_or_of", "_copy_suppress",
  "_copy_replacing", "replace_statement_with_dot", "replace_statement",
  "replacing_list", "text_src", "text_dst", "text_partial_src",
  "text_partial_dst", "token_list", "identifier", "subscripts",
  "lead_trail", "unquoted_literal", "_override", "_not", "_also", "_last",
  "_as", "_format", "_is", "_printing", "_on", "_than", "_to", YY_NULLPTR
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
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,    40,    41
};
# endif

#define YYPACT_NINF -198

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-198)))

#define YYTABLE_NINF -208

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -13,     9,    47,   123,    32,  -198,    19,    43,    37,  -198,
     -29,    61,   208,    38,    56,  -198,   -45,    41,   215,  -198,
    -198,  -198,  -198,   -15,  -198,  -198,   -30,  -198,  -198,  -198,
      24,    79,  -198,   170,    83,   123,    88,  -198,  -198,    67,
    -198,  -198,    22,   115,  -198,  -198,  -198,   124,    51,    52,
      55,    52,  -198,  -198,  -198,  -198,  -198,  -198,  -198,    50,
    -198,  -198,  -198,  -198,  -198,  -198,   114,    49,    58,   -28,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,    62,    52,    62,
    -198,  -198,    63,  -198,    63,  -198,    63,    59,    63,   108,
      62,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,    52,
     108,  -198,    65,   -33,   215,  -198,     8,    15,  -198,  -198,
     -47,  -198,   148,  -198,   157,  -198,  -198,  -198,  -198,  -198,
     156,   -62,    73,  -198,  -198,  -198,    22,   178,    17,     2,
    -198,  -198,    84,    85,    51,  -198,  -198,    81,   189,    55,
    -198,    81,  -198,    94,  -198,   -43,  -198,  -198,  -198,  -198,
      49,  -198,   108,  -198,    -5,   111,    62,  -198,    81,  -198,
    -198,  -198,  -198,  -198,    92,  -198,    63,  -198,    81,    10,
    -198,  -198,  -198,    99,  -198,  -198,     4,     6,  -198,  -198,
      13,  -198,  -198,  -198,  -198,    -1,  -198,  -198,  -198,   123,
     170,   186,   191,  -198,  -198,    26,   202,     2,    23,   107,
     110,   112,   113,  -198,   205,  -198,   125,  -198,  -198,   126,
    -198,  -198,  -198,  -198,  -198,   138,  -198,   164,   164,   139,
    -198,  -198,  -198,  -198,  -198,  -198,   130,   130,  -198,  -198,
    -198,  -198,     3,   118,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,    22,   210,  -198,  -198,    23,   224,    28,  -198,  -198,
    -198,    17,  -198,  -198,  -198,   -37,   238,    29,  -198,  -198,
     164,  -198,  -198,  -198,  -198,  -198,   141,    96,  -198,  -198,
      22,  -198,  -198,    29,  -198,    30,  -198,  -198,  -198,    31,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,   162,
     158,   158,  -198,  -198,    36,    36,  -198,  -198,  -198,   245,
    -198,  -198,  -198,   163,   165,  -198,  -198,  -198,  -198,  -198,
     166,   167,   162,   162,  -198,  -198
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      10,     0,     0,     3,    10,     1,     0,   203,    99,   102,
       0,     0,     0,   114,   209,    34,     0,   215,     0,    28,
      32,    33,    30,     0,    11,    14,     0,    18,    16,    15,
       0,     0,     2,     6,     0,     4,     0,   158,   159,   160,
     204,   206,     0,     0,   101,   100,    26,   112,     0,     0,
       0,     0,    22,   106,   107,   108,   109,   110,   111,   112,
     104,   116,   115,    27,   210,    20,   211,     0,     0,   207,
     142,    21,    94,    85,   216,    24,    84,     0,     0,     0,
      46,    56,     0,    48,    50,    51,     0,     0,     0,   207,
       0,    57,    58,    59,    60,    61,    62,    63,    64,     0,
     207,    69,    88,    82,    23,    40,     0,     0,   118,    25,
       0,    17,     0,   168,     8,    10,    12,   157,   162,   163,
     164,     0,     0,   196,   197,   190,   170,     0,   177,     0,
     171,   113,     0,     0,    95,    76,    71,    96,     0,    97,
      79,    98,   105,     0,   212,     0,   129,   130,   131,   132,
      35,   127,   207,   208,     0,     0,    65,    73,    44,    45,
     198,    47,    49,    52,     0,    53,     0,    55,    66,     0,
      89,    70,    43,     0,    41,    37,   211,   211,    29,    36,
       0,   138,    39,    31,    38,     0,   119,   169,     9,     5,
       7,   213,   166,   161,   188,     0,     0,     0,     0,     0,
       0,     0,     0,   184,     0,   103,     0,    77,    72,     0,
      80,    19,    86,    87,   128,     0,    92,   199,   199,     0,
      74,    42,    54,    68,    67,    83,   201,   201,   140,   141,
     139,   122,   121,     0,   126,   117,   120,   124,    13,   214,
     165,     0,     0,   176,   189,     0,     0,     0,   181,   182,
     172,   180,   191,   192,   194,     0,     0,     0,    78,    81,
     199,   200,    91,    90,    75,   202,     0,     0,   123,   125,
     167,   156,   174,     0,   178,     0,   195,   193,   183,     0,
     187,   173,    93,   150,   152,   153,   151,   154,   155,   219,
     217,   217,   134,   133,     0,     0,   175,   179,   185,     0,
     220,   149,   218,   146,   148,   144,   143,   135,   136,   186,
       0,     0,   219,   219,   145,   147
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -198,  -198,  -198,  -198,  -198,     0,  -198,  -198,   -32,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,   149,   -34,  -198,   -67,
    -198,   121,  -198,   119,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,   200,   201,  -198,  -198,  -198,  -198,  -198,
      60,  -198,   143,   154,  -198,   -16,    -4,    -3,  -198,   173,
    -198,  -198,  -198,  -198,  -198,   181,    21,  -124,    53,   100,
      27,    54,  -179,  -198,  -123,   -31,  -197,    69,  -198,  -198,
     -27,  -198,   -25,  -198,  -198,    11,  -164
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,    32,    33,    34,     3,   190,    24,    25,    26,
     106,   107,    67,   178,   183,   104,   105,   137,   156,   157,
     134,   135,   139,   140,   172,    75,    65,   171,    71,    52,
      46,    27,    59,    60,   132,    63,   109,   110,   235,   236,
     237,   150,   151,   179,   180,   181,   307,   294,    28,    39,
     120,   121,   192,   242,    29,    30,   126,   127,   250,   204,
     281,   195,   128,   255,   129,   161,   262,   266,    42,    43,
     154,    66,   145,   240,    76,   303,   301
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      72,   115,   196,   197,    35,  -141,   216,  -142,   202,   175,
     231,   223,   159,   153,   228,    68,   182,   141,   153,   251,
      36,   263,     1,   167,   199,   112,     4,   200,   122,   247,
     248,   123,   243,   249,   274,   279,   297,   298,   124,    37,
      38,   113,   217,   144,   158,   144,    40,     5,    44,    61,
     185,    41,    73,   162,  -205,   163,   186,   165,    69,    70,
     212,   213,   166,   282,   276,   168,   251,   131,    31,   277,
     111,  -207,  -141,   169,   118,    47,   173,   119,    53,    54,
      55,    56,    57,    58,    48,    49,    50,    51,   108,   220,
     146,   147,   148,   149,    64,   232,   114,   233,   234,   218,
     116,   233,   234,   203,  -141,   117,  -142,  -141,  -141,  -142,
    -142,   176,   177,  -137,   160,   189,   229,    70,   176,   177,
      37,    38,   201,   125,   125,   215,   130,   244,     6,   194,
     280,   244,   299,    45,    62,   222,     7,    74,   224,   305,
     306,   131,     8,     9,    10,    11,   196,   197,   314,   315,
      12,   226,   227,   144,   153,   133,   136,    13,   238,   138,
      14,   152,   164,    15,   230,   187,   155,   160,    16,   170,
       7,   191,    17,    18,   194,     6,   283,   284,   285,   286,
     287,   288,   198,   206,   205,   208,   289,   290,   291,     8,
       9,    10,    11,   209,   211,   219,   221,    12,   239,    19,
      20,    21,    22,   225,    13,   241,   245,    14,   252,   257,
      15,   253,   261,   254,   256,    16,   265,   269,    23,    17,
      18,   283,   284,   285,   286,   287,   288,   271,   273,   258,
     259,   289,   290,   291,   292,   293,    53,    54,    55,    56,
      57,    58,   260,   264,   278,   302,    19,    20,    21,    22,
     300,   309,   310,   174,   311,   207,   312,   313,   210,   142,
     143,   184,   270,    77,   295,    23,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   308,   268,   214,   193,   188,   267,   246,   272,     0,
     296,   275,   304,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   103
};

static const yytype_int16 yycheck[] =
{
      16,    33,   126,   126,     4,     1,    11,     1,     6,     1,
      11,     1,    79,    46,     1,    60,     1,    51,    46,   198,
       1,   218,    35,    90,     7,     1,    17,    10,     6,     6,
       7,     9,     6,    10,     6,     6,     6,     6,    16,   101,
     102,    17,    47,    39,    78,    39,     3,     0,    11,    11,
      97,     8,    11,    84,    11,    86,   103,    88,   103,   104,
     103,   104,    89,   260,   101,    99,   245,    17,    36,   106,
     100,   104,   100,   100,     7,   104,   103,    10,    28,    29,
      30,    31,    32,    33,    23,    24,    25,    26,   103,   156,
      41,    42,    43,    44,    38,    96,    17,    98,    99,   104,
      17,    98,    99,   101,   100,    17,   100,   103,   104,   103,
     104,   103,   104,   100,   104,   115,   103,   104,   103,   104,
     101,   102,   105,   101,   101,   152,    11,   101,     5,   101,
     101,   101,   101,    96,    96,   166,    13,    96,   169,   103,
     104,    17,    19,    20,    21,    22,   270,   270,   312,   313,
      27,   176,   177,    39,    46,   104,   104,    34,   190,   104,
      37,   103,   103,    40,   180,    17,   104,   104,    45,   104,
      13,    15,    49,    50,   101,     5,    80,    81,    82,    83,
      84,    85,     4,    98,   100,   104,    90,    91,    92,    19,
      20,    21,    22,     4,   100,    84,   104,    27,    12,    76,
      77,    78,    79,   104,    34,    14,     4,    37,   101,     4,
      40,   101,    48,   101,   101,    45,    86,    99,    95,    49,
      50,    80,    81,    82,    83,    84,    85,    17,     4,   104,
     104,    90,    91,    92,    93,    94,    28,    29,    30,    31,
      32,    33,   104,   104,     6,    87,    76,    77,    78,    79,
      88,     6,    89,   104,    89,   134,    90,    90,   139,    59,
      59,   107,   241,    48,   267,    95,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,   295,   232,   150,   121,   114,   227,   197,   245,    -1,
     273,   247,   291,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   103
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    35,   108,   112,    17,     0,     5,    13,    19,    20,
      21,    22,    27,    34,    37,    40,    45,    49,    50,    76,
      77,    78,    79,    95,   114,   115,   116,   138,   155,   161,
     162,    36,   109,   110,   111,   112,     1,   101,   102,   156,
       3,     8,   175,   176,    11,    96,   137,   104,    23,    24,
      25,    26,   136,    28,    29,    30,    31,    32,    33,   139,
     140,    11,    96,   142,    38,   133,   178,   119,    60,   103,
     104,   135,   152,    11,    96,   132,   181,    48,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,   103,   122,   123,   117,   118,   103,   143,
     144,   100,     1,    17,    17,   115,    17,    17,     7,    10,
     157,   158,     6,     9,    16,   101,   163,   164,   169,   171,
      11,    17,   141,   104,   127,   128,   104,   124,   104,   129,
     130,   124,   140,   141,    39,   179,    41,    42,    43,    44,
     148,   149,   103,    46,   177,   104,   125,   126,   124,   126,
     104,   172,   172,   172,   103,   172,   177,   126,   124,   177,
     104,   134,   131,   177,   123,     1,   103,   104,   120,   150,
     151,   152,     1,   121,   150,    97,   103,    17,   162,   112,
     113,    15,   159,   156,   101,   168,   164,   171,     4,     7,
      10,   105,     6,   101,   166,   100,    98,   128,   104,     4,
     130,   100,   103,   104,   149,   177,    11,    47,   104,    84,
     126,   104,   172,     1,   172,   104,   179,   179,     1,   103,
     152,    11,    96,    98,    99,   145,   146,   147,   115,    12,
     180,    14,   160,     6,   101,     4,   166,     6,     7,    10,
     165,   169,   101,   101,   101,   170,   101,     4,   104,   104,
     104,    48,   173,   173,   104,    86,   174,   174,   147,    99,
     163,    17,   165,     4,     6,   168,   101,   106,     6,     6,
     101,   167,   173,    80,    81,    82,    83,    84,    85,    90,
      91,    92,    93,    94,   154,   154,   167,     6,     6,   101,
      88,   183,    87,   182,   182,   103,   104,   153,   153,     6,
      89,    89,    90,    90,   183,   183
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   107,   108,   108,   109,   109,   109,   109,   110,   111,
     112,   112,   113,   113,   114,   114,   115,   115,   115,   115,
     116,   116,   116,   116,   116,   116,   116,   116,   117,   116,
     118,   116,   116,   116,   119,   116,   120,   120,   121,   121,
     122,   122,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   124,   124,   125,   125,   126,   127,   127,   128,   129,
     129,   130,   131,   131,   132,   132,   133,   133,   134,   134,
     135,   135,   135,   135,   135,   136,   136,   136,   136,   137,
     137,   137,   138,   138,   139,   139,   140,   140,   140,   140,
     140,   140,   141,   141,   142,   142,   142,   143,   144,   144,
     145,   145,   145,   146,   146,   147,   147,   148,   148,   149,
     149,   149,   149,   150,   150,   150,   150,   150,   151,   151,
     151,   152,   152,   153,   153,   154,   154,   154,   154,   154,
     154,   154,   154,   154,   154,   154,   155,   155,   156,   156,
     157,   157,   158,   158,   159,   159,   160,   160,   161,   161,
     162,   162,   163,   163,   163,   163,   164,   164,   165,   165,
     165,   165,   165,   166,   166,   167,   167,   167,   168,   168,
     169,   169,   169,   169,   170,   170,   171,   171,   172,   173,
     173,   174,   174,   175,   175,   176,   176,   177,   177,   178,
     178,   179,   179,   180,   180,   181,   181,   182,   182,   183,
     183
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     1,     1,     3,     1,     3,     2,     3,
       0,     2,     0,     2,     1,     1,     1,     2,     1,     4,
       2,     2,     2,     2,     2,     2,     2,     2,     0,     3,
       0,     3,     1,     1,     0,     3,     1,     1,     1,     1,
       1,     2,     3,     2,     2,     2,     1,     2,     1,     2,
       1,     1,     2,     2,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     3,     3,     1,
       2,     1,     2,     1,     2,     3,     1,     2,     3,     1,
       2,     3,     0,     2,     1,     1,     3,     3,     0,     1,
       4,     4,     3,     5,     1,     2,     2,     2,     2,     0,
       1,     1,     1,     4,     1,     2,     1,     1,     1,     1,
       1,     1,     0,     1,     0,     1,     1,     3,     1,     2,
       1,     1,     1,     2,     1,     2,     1,     1,     2,     1,
       1,     1,     1,     4,     4,     5,     5,     1,     1,     2,
       2,     1,     1,     1,     1,     5,     2,     5,     2,     2,
       1,     1,     1,     1,     1,     1,     6,     3,     1,     1,
       0,     2,     1,     1,     0,     2,     0,     2,     2,     3,
       3,     3,     3,     4,     4,     5,     3,     1,     2,     3,
       1,     1,     1,     3,     1,     2,     3,     1,     1,     2,
       1,     3,     3,     4,     1,     2,     1,     1,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
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
  unsigned long int yylno = yyrline[yyrule];
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
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
| yyreduce -- Do a reduction.  |
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
        case 28:
#line 842 "ppparse.y" /* yacc.c:1646  */
    {
	current_cmd = PLEX_ACT_IF;
  }
#line 2192 "ppparse.c" /* yacc.c:1646  */
    break;

  case 30:
#line 847 "ppparse.y" /* yacc.c:1646  */
    {
	current_cmd = PLEX_ACT_ELIF;
  }
#line 2200 "ppparse.c" /* yacc.c:1646  */
    break;

  case 32:
#line 852 "ppparse.y" /* yacc.c:1646  */
    {
	plex_action_directive (PLEX_ACT_ELSE, 0);
  }
#line 2208 "ppparse.c" /* yacc.c:1646  */
    break;

  case 33:
#line 856 "ppparse.y" /* yacc.c:1646  */
    {
	plex_action_directive (PLEX_ACT_END, 0);
  }
#line 2216 "ppparse.c" /* yacc.c:1646  */
    break;

  case 34:
#line 860 "ppparse.y" /* yacc.c:1646  */
    {
	current_call_convention = 0;
  }
#line 2224 "ppparse.c" /* yacc.c:1646  */
    break;

  case 35:
#line 864 "ppparse.y" /* yacc.c:1646  */
    {
	if (current_call_convention == CB_CONV_STATIC_LINK) {
		current_call_convention |= CB_CONV_COBOL;
	};
  }
#line 2234 "ppparse.c" /* yacc.c:1646  */
    break;

  case 37:
#line 874 "ppparse.y" /* yacc.c:1646  */
    {
	cb_error (_("invalid %s directive"), "IF");
	yyerrok;
  }
#line 2243 "ppparse.c" /* yacc.c:1646  */
    break;

  case 39:
#line 883 "ppparse.y" /* yacc.c:1646  */
    {
	cb_error (_("invalid %s directive"), "ELIF");
	yyerrok;
  }
#line 2252 "ppparse.c" /* yacc.c:1646  */
    break;

  case 42:
#line 896 "ppparse.y" /* yacc.c:1646  */
    {
	/* note: the old version was _as LITERAL but MF doesn't support this */
	struct cb_define_struct	*p;

	p = ppp_define_add (ppp_setvar_list, (yyvsp[-1].s), (yyvsp[0].s), 1);
	if (p) {
		ppp_setvar_list = p;
		p = p->last;
		if (p->deftype == PLEX_DEF_NUM) {
			fprintf (ppout, "#DEFLIT %s %s\n", (yyvsp[-1].s), p->value);
		} else {
			fprintf (ppout, "#DEFLIT %s \"%s\"\n", (yyvsp[-1].s), p->value);
		}
	}
  }
#line 2272 "ppparse.c" /* yacc.c:1646  */
    break;

  case 44:
#line 913 "ppparse.y" /* yacc.c:1646  */
    {
	struct cb_text_list	*l;
	for (l = (yyvsp[0].l); l; l = l->next) {
		fprintf (ppout, "#ADDRSV %s\n", l->text);
	}
  }
#line 2283 "ppparse.c" /* yacc.c:1646  */
    break;

  case 45:
#line 920 "ppparse.y" /* yacc.c:1646  */
    {
	struct cb_text_list	*l;
	for (l = (yyvsp[0].l); l; l = l->next->next) {
		fprintf (ppout, "#ADDSYN %s %s\n", l->text, l->next->text);
	}
  }
#line 2294 "ppparse.c" /* yacc.c:1646  */
    break;

  case 46:
#line 927 "ppparse.y" /* yacc.c:1646  */
    {
	if (cobc_has_areacheck_directive ("AREACHECK")) {
		fprintf (ppout, "#AREACHECK\n");
	}
  }
#line 2304 "ppparse.c" /* yacc.c:1646  */
    break;

  case 47:
#line 933 "ppparse.y" /* yacc.c:1646  */
    {
	char	*p = (yyvsp[0].s);

	if (!cb_strcasecmp (p, "EXTERNAL")) {
		fprintf (ppout, "#ASSIGN %d\n", (int)CB_ASSIGN_EXT_FILE_NAME_REQUIRED);
	} else if (!cb_strcasecmp (p, "DYNAMIC")) {
		fprintf (ppout, "#ASSIGN %d\n", (int)CB_ASSIGN_VARIABLE_DEFAULT);
	} else {
		ppp_error_invalid_option ("ASSIGN", p);
	}
  }
#line 2320 "ppparse.c" /* yacc.c:1646  */
    break;

  case 48:
#line 945 "ppparse.y" /* yacc.c:1646  */
    {
	/* Enable EC-BOUND-SUBSCRIPT checking */
	append_to_turn_list (ppp_list_add (NULL, "EC-BOUND-SUBSCRIPT"), 1, 0);
  }
#line 2329 "ppparse.c" /* yacc.c:1646  */
    break;

  case 49:
#line 950 "ppparse.y" /* yacc.c:1646  */
    {
	fprintf (ppout, "#CALLFH \"%s\"\n", (yyvsp[0].s));
  }
#line 2337 "ppparse.c" /* yacc.c:1646  */
    break;

  case 50:
#line 954 "ppparse.y" /* yacc.c:1646  */
    {
	fprintf (ppout, "#CALLFH \"EXTFH\"\n");
  }
#line 2345 "ppparse.c" /* yacc.c:1646  */
    break;

  case 51:
#line 958 "ppparse.y" /* yacc.c:1646  */
    {
	/* Enable EC-DATA-INCOMPATIBLE checking */
	append_to_turn_list (ppp_list_add (NULL, "EC-DATA-INCOMPATIBLE"), 1, 0);
  }
#line 2354 "ppparse.c" /* yacc.c:1646  */
    break;

  case 52:
#line 963 "ppparse.y" /* yacc.c:1646  */
    {
	char	*p = (yyvsp[0].s);

	if (!cb_strcasecmp (p, "BINARY")) {
		cb_binary_comp_1 = 1;
	} else if (!cb_strcasecmp (p, "FLOAT")) {
		cb_binary_comp_1 = 0;
	} else {
		ppp_error_invalid_option ("COMP1", p);
	}
  }
#line 2370 "ppparse.c" /* yacc.c:1646  */
    break;

  case 53:
#line 975 "ppparse.y" /* yacc.c:1646  */
    {
	char	*p = (yyvsp[0].s);

	if (!cb_strcasecmp (p, "XML")) {
		cb_dpc_in_data = CB_DPC_IN_XML;
	} else if (!cb_strcasecmp (p, "JSON")) {
		cb_dpc_in_data = CB_DPC_IN_JSON;
	} else if (!cb_strcasecmp (p, "ALL")) {
		cb_dpc_in_data = CB_DPC_IN_ALL;
	} else {
		ppp_error_invalid_option ("DPC-IN-DATA", p);
	}
  }
#line 2388 "ppparse.c" /* yacc.c:1646  */
    break;

  case 54:
#line 989 "ppparse.y" /* yacc.c:1646  */
    {
	char	*p = (yyvsp[0].s);

	if (!cb_strcasecmp (p, "UPPER")) {
		cb_fold_copy = COB_FOLD_UPPER;
	} else if (!cb_strcasecmp (p, "LOWER")) {
		cb_fold_copy = COB_FOLD_LOWER;
	} else {
		ppp_error_invalid_option ("FOLD-COPY-NAME", p);
	}
  }
#line 2404 "ppparse.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1001 "ppparse.y" /* yacc.c:1646  */
    {
	fprintf (ppout, "#MAKESYN %s %s\n", (yyvsp[0].l)->text, (yyvsp[0].l)->next->text);
  }
#line 2412 "ppparse.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1005 "ppparse.y" /* yacc.c:1646  */
    {
	if (cobc_has_areacheck_directive ("NOAREACHECK")) {
		fprintf (ppout, "#NOAREACHECK\n");
	}
  }
#line 2422 "ppparse.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1011 "ppparse.y" /* yacc.c:1646  */
    {
	/* Disable EC-BOUND-SUBSCRIPT checking */
	append_to_turn_list (ppp_list_add (NULL, "EC-BOUND-SUBSCRIPT"), 0, 0);
  }
#line 2431 "ppparse.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1016 "ppparse.y" /* yacc.c:1646  */
    {
	/* Disable EC-DATA-INCOMPATIBLE checking */
	append_to_turn_list (ppp_list_add (NULL, "EC-DATA-INCOMPATIBLE"), 0, 0);
  }
#line 2440 "ppparse.c" /* yacc.c:1646  */
    break;

  case 59:
#line 1021 "ppparse.y" /* yacc.c:1646  */
    {
	cb_dpc_in_data = CB_DPC_IN_NONE;
  }
#line 2448 "ppparse.c" /* yacc.c:1646  */
    break;

  case 60:
#line 1025 "ppparse.y" /* yacc.c:1646  */
    {
	cb_fold_copy = 0;
  }
#line 2456 "ppparse.c" /* yacc.c:1646  */
    break;

  case 61:
#line 1029 "ppparse.y" /* yacc.c:1646  */
    {
	fprintf (ppout, "#ODOSLIDE 0\n");
  }
#line 2464 "ppparse.c" /* yacc.c:1646  */
    break;

  case 62:
#line 1033 "ppparse.y" /* yacc.c:1646  */
    {
	CB_PENDING ("SPZERO");
	/* TODO: cb_space_is_zero = 0; */
  }
#line 2473 "ppparse.c" /* yacc.c:1646  */
    break;

  case 63:
#line 1038 "ppparse.y" /* yacc.c:1646  */
    {
	/* Disable EC-BOUND-SUBSCRIPT and -REF-MOD checking */
	struct cb_text_list	*txt = ppp_list_add (NULL, "EC-BOUND-SUBSCRIPT");
	txt = ppp_list_add (txt, "EC-BOUND-REF-MOD");

	append_to_turn_list (txt, 0, 0);
  }
#line 2485 "ppparse.c" /* yacc.c:1646  */
    break;

  case 64:
#line 1046 "ppparse.y" /* yacc.c:1646  */
    {
	fprintf (ppout, "#ODOSLIDE 1\n");
  }
#line 2493 "ppparse.c" /* yacc.c:1646  */
    break;

  case 65:
#line 1050 "ppparse.y" /* yacc.c:1646  */
    {
	struct cb_text_list	*l;
	for (l = (yyvsp[0].l); l; l = l->next->next) {
		fprintf (ppout, "#OVERRIDE %s %s\n", l->text, l->next->text);
	}
  }
#line 2504 "ppparse.c" /* yacc.c:1646  */
    break;

  case 66:
#line 1057 "ppparse.y" /* yacc.c:1646  */
    {
	struct cb_text_list	*l;
	for (l = (yyvsp[0].l); l; l = l->next) {
		fprintf (ppout, "#REMOVE %s\n", l->text);
	}
  }
#line 2515 "ppparse.c" /* yacc.c:1646  */
    break;

  case 67:
#line 1064 "ppparse.y" /* yacc.c:1646  */
    {
	char	*p = (yyvsp[0].s);

	if (cobc_deciph_source_format (p) != 0) {
		ppp_error_invalid_option ("SOURCEFORMAT", p);
	}
	if (cb_src_list_file) {
		cb_current_file->source_format = cobc_get_source_format ();
	}
  }
#line 2530 "ppparse.c" /* yacc.c:1646  */
    break;

  case 68:
#line 1075 "ppparse.y" /* yacc.c:1646  */
    {
	/* FIXME: we should consume until end of line here! */
	ppp_error_invalid_option ("SOURCEFORMAT", NULL);
  }
#line 2539 "ppparse.c" /* yacc.c:1646  */
    break;

  case 69:
#line 1080 "ppparse.y" /* yacc.c:1646  */
    {
	CB_PENDING ("SPZERO");
	/* TODO: cb_space_is_zero = 1; */
  }
#line 2548 "ppparse.c" /* yacc.c:1646  */
    break;

  case 70:
#line 1085 "ppparse.y" /* yacc.c:1646  */
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
#line 2590 "ppparse.c" /* yacc.c:1646  */
    break;

  case 71:
#line 1126 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[0].s));
  }
#line 2598 "ppparse.c" /* yacc.c:1646  */
    break;

  case 72:
#line 1130 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add ((yyvsp[-1].l), (yyvsp[0].s));
  }
#line 2606 "ppparse.c" /* yacc.c:1646  */
    break;

  case 74:
#line 1138 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_append ((yyvsp[-1].l), (yyvsp[0].l));
  }
#line 2614 "ppparse.c" /* yacc.c:1646  */
    break;

  case 75:
#line 1145 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[-2].s));
	(yyval.l) = ppp_list_add ((yyval.l), (yyvsp[0].s));
  }
#line 2623 "ppparse.c" /* yacc.c:1646  */
    break;

  case 77:
#line 1154 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_append ((yyvsp[-1].l), (yyvsp[0].l));
  }
#line 2631 "ppparse.c" /* yacc.c:1646  */
    break;

  case 78:
#line 1161 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[-2].s));
	(yyval.l) = ppp_list_add ((yyval.l), (yyvsp[0].s));
  }
#line 2640 "ppparse.c" /* yacc.c:1646  */
    break;

  case 80:
#line 1170 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_append ((yyvsp[-1].l), (yyvsp[0].l));
  }
#line 2648 "ppparse.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1177 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[-2].s));
	(yyval.l) = ppp_list_add ((yyval.l), (yyvsp[0].s));
  }
#line 2657 "ppparse.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1185 "ppparse.y" /* yacc.c:1646  */
    {
	fprintf (ppout, "#OPTION %s\n", (yyvsp[0].s));
  }
#line 2665 "ppparse.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1189 "ppparse.y" /* yacc.c:1646  */
    {
	fprintf (ppout, "#OPTION %s %s\n", (yyvsp[-2].s), (yyvsp[0].s));
  }
#line 2673 "ppparse.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1196 "ppparse.y" /* yacc.c:1646  */
    {
	cb_ref_mod_zero_length = 1;
	fprintf (ppout, "#OPTION REFMOD_ZERO 1\n");
  }
#line 2682 "ppparse.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1201 "ppparse.y" /* yacc.c:1646  */
    {
	cb_ref_mod_zero_length = 0;
	fprintf (ppout, "#OPTION REFMOD_ZERO 0\n");
  }
#line 2691 "ppparse.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1209 "ppparse.y" /* yacc.c:1646  */
    {
	  if (cobc_deciph_source_format ((yyvsp[0].s)) != 0) {
		  ppp_error_invalid_option ("SOURCE", (yyvsp[0].s));
	  }
	  if (cb_src_list_file) {
		  cb_current_file->source_format = cobc_get_source_format ();
	  }
  }
#line 2704 "ppparse.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1218 "ppparse.y" /* yacc.c:1646  */
    {
	ppp_error_invalid_option ("SOURCE", (yyvsp[0].s));
	YYERROR;
  }
#line 2713 "ppparse.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1225 "ppparse.y" /* yacc.c:1646  */
    { (yyval.s) = NULL; }
#line 2719 "ppparse.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1231 "ppparse.y" /* yacc.c:1646  */
    {
	struct cb_define_struct	*p;

	p = ppp_define_add (ppp_setvar_list, (yyvsp[-3].s), (yyvsp[-1].s), (yyvsp[0].ui));
	if (p) {
		ppp_setvar_list = p;
	}
  }
#line 2732 "ppparse.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1240 "ppparse.y" /* yacc.c:1646  */
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
#line 2769 "ppparse.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1273 "ppparse.y" /* yacc.c:1646  */
    {
	ppp_define_del ((yyvsp[-2].s));
  }
#line 2777 "ppparse.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1277 "ppparse.y" /* yacc.c:1646  */
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
#line 2797 "ppparse.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1293 "ppparse.y" /* yacc.c:1646  */
    {
	cb_error (_("invalid %s directive"), "DEFINE/SET");
  }
#line 2805 "ppparse.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1300 "ppparse.y" /* yacc.c:1646  */
    {
	struct cb_text_list* l;
	/* GC-Extension: standard has only one literal combination here */
	for (l = (yyvsp[0].l); l; l = l->next->next) {
		fprintf (ppout, "#ADDSYN-STD %s %s\n", l->text, l->next->text);
	}
  }
#line 2817 "ppparse.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1308 "ppparse.y" /* yacc.c:1646  */
    {
	struct cb_text_list	*l;
	for (l = (yyvsp[0].l); l; l = l->next) {
		fprintf (ppout, "#REMOVE-STD %s\n", l->text);
	}
  }
#line 2828 "ppparse.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1315 "ppparse.y" /* yacc.c:1646  */
    {
	struct cb_text_list* l;
	/* GC-Extension: standard has only one literal combination here */
	for (l = (yyvsp[0].l); l; l = l->next->next) {
		fprintf (ppout, "#OVERRIDE-STD %s %s\n", l->text, l->next->text);
	}
  }
#line 2840 "ppparse.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1323 "ppparse.y" /* yacc.c:1646  */
    {
	struct cb_text_list	*l;
	for (l = (yyvsp[0].l); l; l = l->next) {
		fprintf (ppout, "#ADDRSV %s\n", l->text);
	}
  }
#line 2851 "ppparse.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1365 "ppparse.y" /* yacc.c:1646  */
    {
	CB_PENDING (_("LEAP-SECOND ON directive"));
  }
#line 2859 "ppparse.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1373 "ppparse.y" /* yacc.c:1646  */
    {
	append_to_turn_list ((yyvsp[-2].l), !!(yyvsp[0].ui), (yyvsp[0].ui) == 2U);
  }
#line 2867 "ppparse.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1380 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[0].s));
  }
#line 2875 "ppparse.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1384 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add ((yyvsp[-1].l), (yyvsp[0].s));
  }
#line 2883 "ppparse.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1391 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = 2U;
  }
#line 2891 "ppparse.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1395 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = 1U;
  }
#line 2899 "ppparse.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1399 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = 0;
  }
#line 2907 "ppparse.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1421 "ppparse.y" /* yacc.c:1646  */
    {
	current_call_convention |= CB_CONV_COBOL;
	current_call_convention &= ~CB_CONV_STDCALL;
  }
#line 2916 "ppparse.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1426 "ppparse.y" /* yacc.c:1646  */
    {
	current_call_convention &= ~CB_CONV_STDCALL;
	current_call_convention &= ~CB_CONV_COBOL;
  }
#line 2925 "ppparse.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1431 "ppparse.y" /* yacc.c:1646  */
    {
	current_call_convention |= CB_CONV_STDCALL;
	current_call_convention &= ~CB_CONV_COBOL;
  }
#line 2934 "ppparse.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1436 "ppparse.y" /* yacc.c:1646  */
    {
	current_call_convention |= CB_CONV_STATIC_LINK;
  }
#line 2942 "ppparse.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1443 "ppparse.y" /* yacc.c:1646  */
    {
	unsigned int		found;

	found = (ppp_search_lists ((yyvsp[-3].s)) != NULL);
	plex_action_directive (current_cmd, found ^ (yyvsp[-1].ui));
  }
#line 2953 "ppparse.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1450 "ppparse.y" /* yacc.c:1646  */
    {
	unsigned int		found;

	found = ppp_search_comp_vars ((yyvsp[-3].s));
	plex_action_directive (current_cmd, found ^ (yyvsp[-1].ui));
  }
#line 2964 "ppparse.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1457 "ppparse.y" /* yacc.c:1646  */
    {
	struct cb_define_struct	*p;
	unsigned int		found;

	found = 0;
	p = ppp_search_lists ((yyvsp[-4].s));
	found = ppp_compare_vals (p, (yyvsp[0].ds), (yyvsp[-1].ui));
	plex_action_directive (current_cmd, found ^ (yyvsp[-2].ui));
  }
#line 2978 "ppparse.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1467 "ppparse.y" /* yacc.c:1646  */
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
#line 2997 "ppparse.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1482 "ppparse.y" /* yacc.c:1646  */
    {
	plex_action_directive (current_cmd, 0);
	YYERROR;
  }
#line 3006 "ppparse.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1501 "ppparse.y" /* yacc.c:1646  */
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
#line 3023 "ppparse.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1514 "ppparse.y" /* yacc.c:1646  */
    {
	struct cb_define_struct	*p;

	p = ppp_search_lists ((yyvsp[0].s));
	if (p != NULL && p->deftype != PLEX_DEF_NONE) {
		(yyval.ds) = p;
	} else {
		(yyval.ds) = NULL;
	}
  }
#line 3038 "ppparse.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1528 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = COND_GE;
  }
#line 3046 "ppparse.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1532 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = COND_GT;
  }
#line 3054 "ppparse.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1536 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = COND_LE;
  }
#line 3062 "ppparse.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1540 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = COND_LT;
  }
#line 3070 "ppparse.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1544 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = COND_EQ;
  }
#line 3078 "ppparse.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1548 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = COND_GE;
  }
#line 3086 "ppparse.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1552 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = COND_GT;
  }
#line 3094 "ppparse.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1556 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = COND_LE;
  }
#line 3102 "ppparse.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1560 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = COND_LT;
  }
#line 3110 "ppparse.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1564 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = COND_EQ;
  }
#line 3118 "ppparse.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1568 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = COND_NE;
  }
#line 3126 "ppparse.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1575 "ppparse.y" /* yacc.c:1646  */
    {
	fputc ('\n', ppout);
	ppcopy ((yyvsp[-4].s), (yyvsp[-3].s), (yyvsp[-1].r));
  }
#line 3135 "ppparse.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1580 "ppparse.y" /* yacc.c:1646  */
    {
	yyerrok;
  }
#line 3143 "ppparse.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1587 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.s) = fix_filename ((yyvsp[0].s));
	if (cb_fold_copy == COB_FOLD_LOWER) {
		(yyval.s) = fold_lower ((yyval.s));
	} else if (cb_fold_copy == COB_FOLD_UPPER) {
		(yyval.s) = fold_upper ((yyval.s));
	}
  }
#line 3156 "ppparse.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1596 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.s) = (yyvsp[0].s);
	if (cb_fold_copy == COB_FOLD_LOWER) {
		(yyval.s) = fold_lower ((yyval.s));
	} else {
		(yyval.s) = fold_upper ((yyval.s));
	}
  }
#line 3169 "ppparse.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1608 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.s) = NULL;
  }
#line 3177 "ppparse.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1612 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.s) = (yyvsp[0].s);
  }
#line 3185 "ppparse.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1629 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.r) = NULL;
  }
#line 3193 "ppparse.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1633 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.r) = (yyvsp[0].r);
  }
#line 3201 "ppparse.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1641 "ppparse.y" /* yacc.c:1646  */
    {
	yyerrok;
  }
#line 3209 "ppparse.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1648 "ppparse.y" /* yacc.c:1646  */
    {
	cb_set_replace_list ((yyvsp[0].r), (yyvsp[-1].ui));
  }
#line 3217 "ppparse.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1652 "ppparse.y" /* yacc.c:1646  */
    {
	cb_set_replace_list (NULL, (yyvsp[-1].ui));
  }
#line 3225 "ppparse.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1659 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.r) = ppp_replace_list_add (NULL, (yyvsp[-2].p), (yyvsp[0].l), 0);
  }
#line 3233 "ppparse.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1663 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.r) = ppp_replace_list_add (NULL, (yyvsp[-2].p), (yyvsp[0].l), (yyvsp[-3].ui));
  }
#line 3241 "ppparse.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1667 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.r) = ppp_replace_list_add ((yyvsp[-3].r), (yyvsp[-2].p), (yyvsp[0].l), 0);
  }
#line 3249 "ppparse.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1671 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.r) = ppp_replace_list_add ((yyvsp[-4].r), (yyvsp[-2].p), (yyvsp[0].l), (yyvsp[-3].ui));
  }
#line 3257 "ppparse.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1678 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.p) = ppp_replace_src ((yyvsp[-1].l), 0);
  }
#line 3265 "ppparse.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1682 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.p) = ppp_replace_src ((yyvsp[0].l), 0);
/* CHECKME later (parser conflict)
  }
| IN
  {
	/ * as we need this word, which is valid as replacement,
	   also for qualification, we need to explicit make it
	   a word if given alone * /
	$$ = ppp_list_add (NULL, "IN");
	$$ = ppp_replace_src ($$, 0);
  }
| OF
  {
	/ * as we need this word, which is valid as replacement,
	   also for qualification, we need to explicit make it
	   a word if given alone * /
	$$ = ppp_list_add (NULL, "OF");
	$$ = ppp_replace_src ($$, 0);
*/
  }
#line 3291 "ppparse.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1707 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = NULL;
  }
#line 3299 "ppparse.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1711 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = (yyvsp[-1].l);
  }
#line 3307 "ppparse.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1715 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = (yyvsp[0].l);
  }
#line 3315 "ppparse.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1719 "ppparse.y" /* yacc.c:1646  */
    {
	/* as we need this word, which is valid as replacement,
	   also for qualification, we need to explicit make it
	   a word if given alone */
	(yyval.l) = ppp_list_add (NULL, "IN");
  }
#line 3326 "ppparse.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1726 "ppparse.y" /* yacc.c:1646  */
    {
	/* as we need this word, which is valid as replacement,
	   also for qualification, we need to explicit make it
	   a word if given alone */
	(yyval.l) = ppp_list_add (NULL, "OF");
  }
#line 3337 "ppparse.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1736 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.p) = ppp_replace_src (ppp_list_add (NULL, (yyvsp[-1].s)), 0);
  }
#line 3345 "ppparse.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1740 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.p) = ppp_replace_src (ppp_list_add (NULL, literal_token ((yyvsp[0].s), 0)),
			      ((yyvsp[0].s)[0] == '\'' || (yyvsp[0].s)[0] == '"'));
  }
#line 3354 "ppparse.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1748 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = NULL;
  }
#line 3362 "ppparse.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1752 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[-1].s));
  }
#line 3370 "ppparse.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1756 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add (NULL, literal_token ((yyvsp[0].s), 1));
  }
#line 3378 "ppparse.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1763 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[0].s));
  }
#line 3386 "ppparse.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1767 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add ((yyvsp[-1].l), (yyvsp[0].s));
  }
#line 3394 "ppparse.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1774 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[0].s));
  }
#line 3402 "ppparse.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1778 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add ((yyvsp[-2].l), " ");
	(yyval.l) = ppp_list_add ((yyval.l), "IN");
	(yyval.l) = ppp_list_add ((yyval.l), " ");
	(yyval.l) = ppp_list_add ((yyval.l), (yyvsp[0].s));
  }
#line 3413 "ppparse.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1785 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add ((yyvsp[-2].l), " ");
	(yyval.l) = ppp_list_add ((yyval.l), "OF");
	(yyval.l) = ppp_list_add ((yyval.l), " ");
	(yyval.l) = ppp_list_add ((yyval.l), (yyvsp[0].s));
  }
#line 3424 "ppparse.c" /* yacc.c:1646  */
    break;

  case 193:
#line 1792 "ppparse.y" /* yacc.c:1646  */
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
#line 3440 "ppparse.c" /* yacc.c:1646  */
    break;

  case 194:
#line 1807 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add (NULL, (yyvsp[0].s));
  }
#line 3448 "ppparse.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1811 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.l) = ppp_list_add ((yyvsp[-1].l), " ");
	(yyval.l) = ppp_list_add ((yyval.l), (yyvsp[0].s));
  }
#line 3457 "ppparse.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1819 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = CB_REPLACE_LEADING;
  }
#line 3465 "ppparse.c" /* yacc.c:1646  */
    break;

  case 197:
#line 1823 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = CB_REPLACE_TRAILING;
  }
#line 3473 "ppparse.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1830 "ppparse.y" /* yacc.c:1646  */
    {
	/* Do not reuse unquote as some literals here may be delimited with
	   parentheses */
	char	*p = (yyvsp[0].s);
	size_t	size;

	/* Remove surrounding quotes/brackets */
	++p;
	size = strlen (p) - 1;
	p[size] = '\0';

	(yyval.s) = p;
  }
#line 3491 "ppparse.c" /* yacc.c:1646  */
    break;

  case 199:
#line 1849 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = 0;
  }
#line 3499 "ppparse.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1853 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = 1U;
  }
#line 3507 "ppparse.c" /* yacc.c:1646  */
    break;

  case 201:
#line 1860 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = 0;
  }
#line 3515 "ppparse.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1864 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = 1U;
  }
#line 3523 "ppparse.c" /* yacc.c:1646  */
    break;

  case 203:
#line 1871 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = 0;
  }
#line 3531 "ppparse.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1875 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = 1U;
  }
#line 3539 "ppparse.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1882 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = 0;
  }
#line 3547 "ppparse.c" /* yacc.c:1646  */
    break;

  case 206:
#line 1886 "ppparse.y" /* yacc.c:1646  */
    {
	(yyval.ui) = 1U;
  }
#line 3555 "ppparse.c" /* yacc.c:1646  */
    break;


#line 3559 "ppparse.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
#line 1899 "ppparse.y" /* yacc.c:1906  */

