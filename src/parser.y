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
 *
 * And for the arithmetic operators precedence and associativity definitions,
 * it is just a rewording of bc source.
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

#ifdef BISON_DEBUG
#define YYDEBUG 1
#endif

builtin_id get_comparison_code(const char *s);

%}

%defines
%locations

%union {
	numptr num;
	expr_t *enode;
	char *str;
};

%token <num> INTEGER
%type <enode> expression expr_assignment
%token <str> IDENTIFIER STRING COMPARISON

%token QUIT VARS LIBSWITCH LIBLIST

%token NEWLINE

%left LOGIC_OR
%left LOGIC_AND
%nonassoc LOGIC_NOT
%left COMPARISON
%right '='
%left '+' '-'
%left '*' '/' '%'
%right '^'
%nonassoc NEG

%destructor { num_destruct(&$$); out_dbg("parser.y: freed one num\n"); } <num>
%destructor { expr_destruct($$); out_dbg("parser.y: freed one enode\n"); } <enode>
%destructor { free($$); out_dbg("parser.y: freed one str\n"); } <str>

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
		numptr num = num_undefvalue();
		int r = expr_eval($1, &num);
		if (r != 0) {
			outln_error_code(r);
		} else {
			num_print(num, 10);
			printf("\n");
		}
		num_destruct(&num);
		expr_destruct($1);
		loc_reset();
	}
	| statement NEWLINE
	| error NEWLINE { yyclearin; yyerrok; }
;

bare_assignment:
	IDENTIFIER '=' expression {
		expr_t *enode = expr_const_setvar($1, $3);
		numptr num = num_undefvalue();
		int r = expr_eval(enode, &num);
		if (r != 0)
			outln_error_code(r);
		num_destruct(&num);
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
	| expression COMPARISON expression { $$ = expr_const_op2(get_comparison_code($2), $1, $3); free($2); }
	| expression LOGIC_AND expression { $$ = expr_const_op2(FN_AND, $1, $3); }
	| expression LOGIC_OR expression { $$ = expr_const_op2(FN_OR, $1, $3); }
	| LOGIC_NOT expression { $$ = expr_const_op1(FN_NOT, $2); }
	| '(' expression ')' { $$ = $2; }
;

statement:
	QUIT NEWLINE { YYABORT; }
	| VARS {
		vars_display_all();
	}
	| LIBSWITCH STRING {
		if (num_libswitch($2) == 0) {
			outln_error("Unknown library");
		}
		free($2);
	}
	| LIBSWITCH {
		outln(L_ENFORCE, "%s", num_identify_yourself());
	}
	| LIBLIST {
		char *w = NULL;
		const char *id;
		const char *description;
		const char *libname;
		const char *version;
		outln(L_ENFORCE, "%-20s %-30s %-12s %-12s", "ID", "DESCRIPTION", "LIBNAME", "VERSION");
		outln(L_ENFORCE, "%-20s %-30s %-12s %-12s", "--------------------", "------------------------------",
				"------------", "------------");
		do {
			num_lib_enumerate(&w, &id, &description, &libname, &version);
			outln(L_ENFORCE, "%-20s %-30s %-12s %-12s", id, description, libname, version);
		} while (w != NULL);
	}
;

%%

builtin_id get_comparison_code(const char *s)
{
	if (!strcmp(s, "<"))
		return FN_CMPLT;
	else if (!strcmp(s, "<="))
		return FN_CMPLE;
	else if (!strcmp(s, ">"))
		return FN_CMPGT;
	else if (!strcmp(s, ">="))
		return FN_CMPGE;
	else if (!strcmp(s, "=="))
		return FN_CMPEQ;
	else if (!strcmp(s, "!="))
		return FN_CMPNE;
	assert(0);
}

