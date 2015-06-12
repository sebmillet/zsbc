/* parser.y

Expression parser.
Inspired from
   http://www-h.eng.cam.ac.uk/help/tpl/languages/flexbison/

Sébastien Millet 2015 */

%{

#include <stdio.h>
#include <gmp.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "expr.h"

extern int yylex();

void loc_reset();

	/* OL stands for Out Level (no link with Olympic Lyonnais) */
typedef enum {OL_QUIET = 0, OL_NORMAL = 1, OL_VERBOSE = 2} out_level_t;
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
void vars_display_all();

int opt_output_base = 10;
void display_base();
void display_int(mpz_t* const mp);

void out_error(const char *fmt, ...);
void print_error_code(int e);

const char *table_errors[] = {
	"No error",			/* ERR_NONE */
	"Division by 0"		/* ERR_DIV0 */
};

#ifdef BISON_DEBUG
#define YYDEBUG 1
#endif

%}

%code requires {
mpz_t *mpz_const_from_str(const char *str, int base);
void my_mpz_init_set_str(mpz_t *mp, const char *str, int base);
void my_mpz_init(mpz_t *mp);
void my_mpz_clear(mpz_t *mp);
void mpz_destruct(mpz_t *a);
}

%defines
%locations

%union {
	mpz_t *mp;
	expr_t *enode;
	char *id;
};

%token <mp> INTEGER
%type <enode> expression expr_assignment
%token <id> IDENTIFIER

%token QUIT OUTPUT VARS

%token NEWLINE

%right '='
%left '-' '+'
%left '*' '/' '%'
%precedence NEG
%right '^'

/*%destructor { mpz_clear(*$$); free($$); COUNT_MPZ_DEC; } <mp>*/
/*%destructor { free($$); } <id>*/

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
		mpz_t mp;
		my_mpz_init(&mp);
		int r = expr_eval($1, &mp);
		if (r != 0)
			print_error_code(r);
		else
			display_int(&mp);
		my_mpz_clear(&mp);
		expr_destruct($1);
		loc_reset();
	}
	| statement NEWLINE
	| error NEWLINE { yyclearin; yyerrok; }
;

bare_assignment:
	IDENTIFIER '=' expression {
		expr_t *enode = expr_const_setvar($1, $3);
		mpz_t mp;
		my_mpz_init(&mp);
		int r = expr_eval(enode, &mp);
		if (r != 0)
			print_error_code(r);
		my_mpz_clear(&mp);
		expr_destruct(enode);
	}
;

expr_assignment:
	IDENTIFIER '=' expression {
		$$ = expr_const_setvar($1, $3);
	}
;

expression:
    INTEGER { $$ = expr_const_number($1); }
	| IDENTIFIER { $$ = expr_const_getvar($1); }
	| expr_assignment
	| expression '+' expression { $$ = expr_const_op2(FN_ADD, $1, $3); }
	| expression '-' expression { $$ = expr_const_op2(FN_SUB, $1, $3); }
	| expression '*' expression { $$ = expr_const_op2(FN_MUL, $1, $3); }
	| expression '/' expression { $$ = expr_const_op2(FN_DIV, $1, $3); }
	| expression '^' expression { $$ = expr_const_op2(FN_POW, $1, $3); }
	| expression '%' expression { $$ = expr_const_op2(FN_MOD, $1, $3); }
	| '-' expression %prec NEG { $$ = expr_const_op1(FN_NEG, $2); }
	| '(' expression ')' { $$ = $2; }
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
			out_error("Unknown base name: %s", $2);
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
			out_error("Base value must be in the range [2, 62]");
			mpz_destruct($2);
			YYERROR;
		} else {
			opt_output_base = exp;
			display_base();
			mpz_destruct($2);
		}
	}
	| VARS {
		vars_display_all();
	}
;

%%

void my_mpz_pow(mpz_t r, const mpz_t a, const mpz_t b)
{
	unsigned long int exp = mpz_get_ui(b);
	mpz_pow_ui(r, a, exp);
}

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
#if defined(DEBUG) || defined(BISON_DEBUG) || defined(FLEX_DEBUG)
	out(PACKAGE_STRING "d\n");
#else
	out(PACKAGE_STRING "\n");
#endif
	out("Copyright 2015 Sébastien Millet\n");
}

int mpz_count_ref = 0;
int mpz_init_ref = 0;

mpz_t *mpz_const_from_str(const char *str, int base)
{
	out_dbg("Constructing one mpz_t from str\n");
	mpz_t *mp = (mpz_t *)malloc(sizeof(mpz_t));
	++mpz_count_ref;
	my_mpz_init_set_str(mp, str, base);
	return mp;
}

void my_mpz_init_set_str(mpz_t *mp, const char *str, int base)
{
	out_dbg("Initializing one mpz_t from str\n");
	mpz_init_set_str(*mp, str, base);
	++mpz_init_ref;
}

void my_mpz_init(mpz_t *mp)
{
	out_dbg("Initializing one mpz_t\n");
	mpz_init(*mp);
	++mpz_init_ref;
}

void my_mpz_clear(mpz_t *mp)
{
	out_dbg("Clearing one mpz_t\n");
	mpz_clear(*mp);
	--mpz_init_ref;
}

void mpz_destruct(mpz_t *mp)
{
	out_dbg("Destucting one mpz_t\n");
	my_mpz_clear(mp);
	free(mp);
	--mpz_count_ref;
}

int get_mpz_count_ref() { return mpz_count_ref; }

int get_mpz_init_ref() { return mpz_init_ref; }

void out_error(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	vfprintf(stderr, fmt, ap);
	fprintf(stderr, "\n");
}

void print_error_code(int e)
{
	if (e < 0 || e >= (sizeof(table_errors) / sizeof(*table_errors))) {
		out_error("Error code %d", e);
	} else {
		out_error("%s", table_errors[e]);
	}
}

char *s_strncpy(char *dest, const char *src, size_t n)
{
	char *r = strncpy(dest, src, n);
	dest[n - 1] = '\0';
	return r;
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

void vars_set_value(const char *name, const mpz_t* new_value)
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
		s_strncpy(vars[vars_nb - 1].name, name, l);
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
	}
}

void display_base()
{
	printf("Output base: %i\n", opt_output_base);
}

void display_int(mpz_t* const mp)
{
/*    if (opt_output_base == 2)*/
/*        printf("0b");*/
/*    else if (opt_output_base == 8)*/
/*        printf("0o");*/
/*    else if (opt_output_base == 16)*/
/*        printf("0x");*/
	mpz_out_str(NULL, opt_output_base, *mp);
	printf("\n");
/*    if (opt_output_base != 2 && opt_output_base != 8 && opt_output_base != 16 && opt_output_base != 10)*/
/*        printf("_%i", opt_output_base);*/
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

void output_count_ref_report(const char *name, int count_ref)
{
	if (opt_ol >= OL_VERBOSE || count_ref != 0) {
		fprintf(stderr, "%s count (should be null): %i\n", name, count_ref);
		fprintf(stderr, "%s\n", count_ref != 0 ? "****  ERROR  ****" : "OK");
	}
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

	out_dbg("DEBUG mode activated\n");

	vars_init();

	yyparse();

	vars_terminate();

	int m = get_mpz_count_ref();
	output_count_ref_report("mpz_t *", m);
	int I = get_mpz_init_ref();
	output_count_ref_report("mpz_t init/clear", I);
	int e = expr_get_count_ref();
	output_count_ref_report("expr_t *", e);

	return (m == 0 && e == 0 ? 0 : abs(e) + abs(m));
}

