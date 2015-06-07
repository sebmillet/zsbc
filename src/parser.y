/* parser.y

Expression parser.
Inspired from
   http://www-h.eng.cam.ac.uk/help/tpl/languages/flexbison/

Sébastien Millet 2015 */

%{

#include "common.h"

#include <stdio.h>
#include <gmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();

	/* OL stands for Out Level (no link with Olympic Lyonnais) */
typedef enum {OL_QUIET = 0, OL_NORMAL = 1, OL_VERBOSE = 2, OL_VERYVERBOSE = 3} out_level_t;
out_level_t opt_ol = OL_NORMAL;

int out(const char *fmt, ...);
int out_err(const char *fmt, ...);

struct vars_t {
	char *name;
	mpz_t value;
};
typedef struct vars_t vars_t;
vars_t *vars;
int vars_nb;
int vars_ar;

void vars_init();
void vars_terminate();
mpz_t *vars_get_value(const char *var);
void vars_set_value(const char *name, mpz_t* const new_value);
void vars_display_all();

int opt_output_base = 10;
void display_base();
void display_int(mpz_t* const mp);

void expr_error(const char *fmt, ...);

#define MPZ_CREATE(a) \
	a = (mpz_t *)malloc(sizeof(mpz_t)); \
	COUNT_MPZ_INC; \
	mpz_init(*a)

#define MPZ_CREATE_SET(a, b) \
	a = (mpz_t *)malloc(sizeof(mpz_t)); \
	COUNT_MPZ_INC; \
	mpz_init_set(*a, b)

#define MPZ_DISCARD1(a) \
	mpz_clear(*a); \
	COUNT_MPZ_DEC; \
	free(a)

#define MPZ_DISCARD2(a, b) \
	mpz_clear(*a); \
	mpz_clear(*b); \
	COUNT_MPZ_DEC; \
	free(a); \
	COUNT_MPZ_DEC; \
	free(b)

#ifdef BISON_DEBUG
#define YYDEBUG 1
#endif

%}

%defines
%locations

%union {
	mpz_t *mp;
	char *id;
};

%token <mp> INTEGER
%type <mp> expression expr_assignment
%token <id> IDENTIFIER

%token QUIT OUTPUT VARS

%token NEWLINE

%right '='
%left '-' '+'
%left '*' '/' '%'
%precedence NEG
%right '^'

%destructor { mpz_clear(*$$); free($$); COUNT_MPZ_DEC; } <mp>
%destructor { free($$); } <id>

%start input

%%

input:
	%empty
	| instruction input
;

instruction:
	NEWLINE { loc_reset(); }
	| bare_assignment NEWLINE
	| expression NEWLINE {
		display_int($1);
		printf("\n");
		MPZ_DISCARD1($1);
		loc_reset();
	}
	| statement NEWLINE
	| error NEWLINE { yyclearin; yyerrok; }
;

bare_assignment:
	IDENTIFIER '=' expression {
		vars_set_value($1, $3);
/*        MPZ_CREATE_SET($$, *$3);*/
		free($1);
		MPZ_DISCARD1($3);
	}
;

expr_assignment:
	IDENTIFIER '=' expression {
		vars_set_value($1, $3);
		MPZ_CREATE_SET($$, *$3);
		free($1);
		MPZ_DISCARD1($3);
	}
;

expression:
    INTEGER { MPZ_CREATE_SET($$, *$1); MPZ_DISCARD1($1); }
	| IDENTIFIER {
		mpz_t *v = vars_get_value($1);
		if (v == NULL) {
			MPZ_CREATE($$);
		} else {
			MPZ_CREATE_SET($$, *v);
		}
		free($1);
	}
	| expr_assignment
	| expression '+' expression { MPZ_CREATE($$); mpz_add(*$$, *$1, *$3); MPZ_DISCARD2($1, $3); }
	| expression '-' expression { MPZ_CREATE($$); mpz_sub(*$$, *$1, *$3); MPZ_DISCARD2($1, $3); }
	| expression '*' expression { MPZ_CREATE($$); mpz_mul(*$$, *$1, *$3); MPZ_DISCARD2($1, $3); }
	| expression '/' expression {
		if (!mpz_cmp_ui(*$3, 0)) {
			expr_error("Division by 0");
			MPZ_DISCARD2($1, $3);
			YYERROR;
		} else {
			MPZ_CREATE($$);
			mpz_tdiv_q(*$$, *$1, *$3);
			MPZ_DISCARD2($1, $3);
		}
	}
	| expression '^' expression {
		unsigned long int exp = mpz_get_ui(*$3);
		MPZ_CREATE($$);
		mpz_pow_ui(*$$, *$1, exp);
		MPZ_DISCARD2($1, $3);
	}
	| expression '%' expression {
		if (!mpz_cmp_ui(*$3, 0)) {
			expr_error("Division by 0");
			MPZ_DISCARD2($1, $3);
			YYERROR;
		} else {
			MPZ_CREATE($$);
			mpz_mod(*$$, *$1, *$3);
			MPZ_DISCARD2($1, $3);
		}
	}
	| '-' expression %prec NEG { MPZ_CREATE($$); mpz_neg(*$$, *$2); MPZ_DISCARD1($2); }
	| '(' expression ')' { MPZ_CREATE_SET($$, *$2); MPZ_DISCARD1($2); }
;

statement:
	QUIT NEWLINE { YYABORT; }
	| OUTPUT {
		display_base();
	}
	| OUTPUT IDENTIFIER {
		int n = 0;
		if (!strcmp($2, "bin") || !strcmp($2, "binary")) {
			n = 2;
		} else if (!strcmp($2, "oct") || !strcmp($2, "octal")) {
			n = 8;
		} else if (!strcmp($2, "dec") || !strcmp($2, "decimal")) {
			n = 10;
		} else if (!strcmp($2, "hex") || !strcmp($2, "hexadecimal")) {
			n = 16;
		}
		if (n == 0) {
			expr_error("Unknown base name: %s", $2);
			free($2);
			YYERROR;
		} else {
			free($2);
			opt_output_base = n;
			display_base();
		}
	}
	| OUTPUT INTEGER {
		unsigned long int exp = mpz_get_ui(*$2);
		if (exp < 2 || exp > 62) {
			expr_error("Base value must be in the range [2, 62]");
			MPZ_DISCARD1($2);
			YYERROR;
		} else {
			opt_output_base = exp;
			display_base();
			MPZ_DISCARD1($2);
		}
	}
	| VARS {
		vars_display_all();
	}
;

%%

int out(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int r = vprintf(fmt, args);
	va_end(args);
	return r;
}

int out_err(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int r = vfprintf(stderr, fmt, args);
	va_end(args);
	return r;
}

void usage()
{
	out_err("Usage: %s [options] [file ...]\n", PACKAGE_NAME);
	out_err("  -h  -help     print this usage and exit\n");
	out_err("  -V  -verbose  verbose output\n");
	out_err("  -q  -quiet    don't print initial banner\n");
	out_err("  -v  -version  print version information and exit\n");
	out_err("  --            end of parameters, next options are file names\n");
	exit(-1);
}

void version()
{
	out(PACKAGE_STRING "\n");
	out("Copyright 2015 Sébastien Millet\n");
}

#ifdef COUNT_MPZ
long int count_mpz = 0;

void count_mpz_add(const long int delta)
{
	count_mpz += delta;
}

long int count_mpz_get()
{
	return count_mpz;
}

void count_mpz_output_report()
{
	if (opt_ol >= OL_VERBOSE || count_mpz_get() != 0) {
		fprintf(stderr, "MPZ COUNT (SHOULD BE NULL): %li\n", count_mpz_get());
		fprintf(stderr, "%s\n", count_mpz_get() ? "****  ERROR  ****" : "OK");
	}
}
#else /* COUNT_MPZ */

#define count_mpz_output_report()

#endif /* COUNT_MPZ */

void expr_error(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
}

void vars_init()
{
	vars = NULL;
	vars_ar = 0;
	vars_nb = 0;
}

void vars_terminate()
{
	int i;
	for (i = 0; i < vars_nb; ++i) {
		free(vars[i].name);
		mpz_clear(vars[i].value);
	}
	free(vars);
	vars = NULL;
	vars_ar = 0;
	vars_nb = 0;
}

mpz_t *vars_get_value(const char *name)
{
	int i;
	for (i = 0; i < vars_nb; ++i) {
		if (!strcmp(vars[i].name, name)) {
			return &(vars[i].value);
		}
	}
	return NULL;
}

void vars_set_value(const char *name, mpz_t* const new_value)
{
	mpz_t *value = vars_get_value(name);
	if (value == NULL) {
		if (++vars_nb >= vars_ar) {
			int new_vars_ar = vars_ar * 2;
			if (new_vars_ar <= 0)
				new_vars_ar = 1;
			vars = (vars_t *)realloc(vars, sizeof(vars_t) * new_vars_ar);
			vars_ar = new_vars_ar;
		}
		int l = strlen(name) + 1;
		vars[vars_nb - 1].name = (char *)malloc(l);
		strncpy(vars[vars_nb - 1].name, name, l);
		value = &(vars[vars_nb - 1].value);
	} else {
		mpz_clear(*value);
	}
	mpz_init_set(*value, *new_value);
}

void vars_display_all()
{
	int i;
	for (i = 0; i < vars_nb; ++i) {
		printf("%s=", vars[i].name);
		display_int(&(vars[i].value));
		printf("\n");
	}
}

void display_base()
{
	printf("Output base: %i\n", opt_output_base);
}

void display_int(mpz_t* const mp)
{
	if (opt_output_base == 2)
		printf("0b");
	else if (opt_output_base == 8)
		printf("0o");
	else if (opt_output_base == 16)
		printf("0x");
	mpz_out_str(NULL, opt_output_base, *mp);
	if (opt_output_base != 2 && opt_output_base != 8 && opt_output_base != 16 && opt_output_base != 10)
		printf("_%i", opt_output_base);
}

void opt_check(int n, const char *opt)
{
	static int defined_options[2] = {0, 0};

	if (defined_options[n]) {
		out_err("Option %s already set\n", opt);
		exit(-2);
	} else
		defined_options[n] = 1;
}

int main(int argc, char *argv[])
{

#ifdef BISON_DEBUG
	yydebug = 1;
#endif

	int optset_verbose = 0;
	int optset_quiet = 0;

	int a = 1;
	while (a >= 1 && a < argc) {
		if (!strcmp(argv[a], "-help") || !strcmp(argv[a], "-h")) {
			usage();
		} else if (!strcmp(argv[a], "-version") || !strcmp(argv[a], "-v")) {
			version();
			exit(0);
		} else if (!strcmp(argv[a], "-verbose") || !strcmp(argv[a], "-V")) {
			opt_check(0, argv[a]);
			optset_verbose = 1;
			opt_ol = OL_VERBOSE;
		} else if (!strcmp(argv[a], "-quiet") || !strcmp(argv[a], "-q")) {
			opt_check(1, argv[a]);
			optset_quiet = 1;
			opt_ol = OL_QUIET;
		} else if (argv[a][0] == '-') {
			if (strcmp(argv[a], "--")) {
				out_err("%s: invalid option -- '%s'\n", PACKAGE_NAME, argv[a]);
				a = -1;
				break;
			} else {
				++a;
				break;
			}
		} else {
			break;
		}
		if (a >= 1)
			++a;
	}

	if (optset_verbose && optset_quiet) {
		opt_ol = OL_NORMAL;
	}
	if (a < 0)
		usage();

	if (opt_ol >= OL_NORMAL) {
		version();
		out("GMP library version %s\n", gmp_version);
	}

	vars_init();

	yyparse();

	vars_terminate();

	count_mpz_output_report();

	return 0;
}

