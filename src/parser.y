/*
 * =====================================================================================
 *
 *       Filename:  parser.y
 *
 *    Description:  Manage zsbc input (grammar level).
 *
 *        Version:  1.0
 *        Created:  03/06/2015 23:22:00
 *       Revision:  none
 *       Compiler:  bison
 *
 *         Author:  Sébastien Millet (smt), milletseb@laposte.net
 *
 * =====================================================================================
 */

/* Inspired from
 *   http://www-h.eng.cam.ac.uk/help/tpl/languages/flexbison/
 */


%{

#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "expr.h"
#include "number.h"

extern int yylex();

void yyerror(char *s, ...);

void loc_reset();

int opt_output_base = 10;
void display_base();

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

%destructor { mpz_destruct($$); } <mp>
%destructor { expr_destruct($$); } <enode>
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

