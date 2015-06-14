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
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "numwrap.h"
#include "vars.h"
#include "expr.h"

extern int yylex();

void yyerror(char *s, ...);

void loc_reset();

int opt_output_base = 10;
void display_base();

#ifdef BISON_DEBUG
#define YYDEBUG 1
#endif

%}

/*%code requires {*/
/*}*/

%defines
%locations

%union {
	numptr num;
	expr_t *enode;
	char *id;
};

%token <num> INTEGER
%type <enode> expression expr_assignment
%token <id> IDENTIFIER

%token QUIT OUTPUT VARS

%token NEWLINE

%right '='
%left '-' '+'
%left '*' '/' '%'
%precedence NEG
%right '^'

%destructor { num_destruct($$); } <num>
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
		numptr num = num_construct();
		int r = expr_eval($1, num);
		if (r != 0)
			out_err_code(r);
		else
			num_print(num, 10);
		num_destruct(num);
		expr_destruct($1);
		loc_reset();
	}
	| statement NEWLINE
	| error NEWLINE { yyclearin; yyerrok; }
;

bare_assignment:
	IDENTIFIER '=' expression {
		expr_t *enode = expr_const_setvar($1, $3);
		numptr num = num_construct();
		int r = expr_eval(enode, num);
		if (r != 0)
			out_err_code(r);
		num_destruct(num);
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
			out_err("Unknown base name: %s", $2);
			free($2);
			YYERROR;
		} else {
			free($2);
			opt_output_base = n;
			display_base();
		}
	}
	| OUTPUT INTEGER {
		unsigned long int exp = num_getlongint($2);
		if (exp < 2 || exp > 62) {
			out_err("Base value must be in the range [2, 62]");
			num_destruct($2);
			YYERROR;
		} else {
			opt_output_base = exp;
			display_base();
			num_destruct($2);
		}
	}
	| VARS {
		vars_display_all();
	}
;

%%

void display_base()
{
	printf("Output base: %i\n", opt_output_base);
}

