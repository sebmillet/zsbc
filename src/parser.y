/*
 * =====================================================================================
 *
 *       Filename:  parser.y
 *
 *    Description:  Manages zsbc input (grammar level).
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

/*
 * Inspired from
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
#include "program.h"

extern int yylex();

void yyerror(char *s, ...);

void loc_reset();

#ifdef BISON_DEBUG
#define YYDEBUG 1
#endif

builtin_id get_comparison_code(const char *s);

%}

%code provides {
void activate_bison_debug();
}

%defines
%locations

%union {
	numptr num;
	expr_t *enode;
	char *str;
	program_t *prog;
};

%token <num> INTEGER
%type <enode> expression expression_no_assignment expression_assignment
%token <str> IDENTIFIER STRING COMPARISON
%type <prog> instruction_block instruction_inside_block instruction_list instruction instruction_non_empty instruction_assignment
%type <prog> loop_while

%token QUIT VARS LIBSWITCH LIBLIST
%token WHILE

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
%destructor { program_destruct($$); out_dbg("parser.y: freed one program\n"); } <prog>

%start input

%%

input:
	%empty { loc_reset(); }
	| program NEWLINE input
	| statement NEWLINE input
	| error NEWLINE input { out_dbg("Error encountered, ran yyclearin and yyerrok\n"); yyclearin; yyerrok; }
;

program:
	instruction_list {
		program_execute($1);
		program_destruct($1);
	}
;

instruction_block:
	'{' instruction_inside_block '}' { $$ = $2; }
;

instruction_inside_block:
	instruction_list { $$ = $1; }
	| instruction_inside_block NEWLINE instruction_list { $$ = program_chain($1, $3); }
;

instruction_list:
	instruction
	| instruction_list ';' instruction { $$ = program_chain($1, $3); }
;

instruction:
	%empty { $$ = NULL; }
	| instruction_non_empty
;

instruction_non_empty:
	instruction_assignment
	| expression_no_assignment { $$ = program_construct_expr($1, FALSE); }
	| STRING { $$ = program_construct_string($1); }
	| loop_while
	| instruction_block { $$ = $1; }
;

instruction_assignment:
	IDENTIFIER '=' expression {
		expr_t *enode = expr_construct_setvar($1, $3);
		$$ = program_construct_expr(enode, TRUE);
	}
;

expression:
	expression_no_assignment
	| expression_assignment
;

expression_assignment:
	IDENTIFIER '=' expression { $$ = expr_construct_setvar($1, $3); }
;

expression_no_assignment:
    INTEGER { $$ = expr_construct_number($1); }
	| IDENTIFIER { $$ = expr_construct_getvar($1); }
	| expression '+' expression { $$ = expr_construct_op2(FN_ADD, $1, $3); }
	| expression '-' expression { $$ = expr_construct_op2(FN_SUB, $1, $3); }
	| expression '*' expression { $$ = expr_construct_op2(FN_MUL, $1, $3); }
	| expression '/' expression { $$ = expr_construct_op2(FN_DIV, $1, $3); }
	| expression '^' expression { $$ = expr_construct_op2(FN_POW, $1, $3); }
	| expression '%' expression { $$ = expr_construct_op2(FN_MOD, $1, $3); }
	| '-' expression %prec NEG { $$ = expr_construct_op1(FN_NEG, $2); }
	| expression COMPARISON expression { $$ = expr_construct_op2(get_comparison_code($2), $1, $3); free($2); }
	| expression LOGIC_AND expression { $$ = expr_construct_op2(FN_AND, $1, $3); }
	| expression LOGIC_OR expression { $$ = expr_construct_op2(FN_OR, $1, $3); }
	| LOGIC_NOT expression { $$ = expr_construct_op1(FN_NOT, $2); }
	| '(' expression ')' { $$ = $2; }
;

loop_while:
	WHILE '(' expression ')' instruction_non_empty {
		program_loop_t loop;
		loop.prgbefore = NULL;
		loop.expbefore = $3;
		loop.core = $5;
		loop.expafter = NULL;
		loop.prgafter = NULL;
		$$ = program_construct_loop(&loop);
	}
;

statement:
	QUIT { YYABORT; }
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
		libinfo_t li;
		outln(L_ENFORCE, "%-12s %-30s %-10s %-10s %-10s", "ID", "DESCRIPTION", "LIBNAME", "VERSION", "NUMSET");
		outln(L_ENFORCE, "%-12s %-30s %-10s %-10s %-10s", "------------", "------------------------------",
				"----------", "----------", "----------");
		do {
			num_lib_enumerate(&w, &li);
			outln(L_ENFORCE, "%-12s %-30s %-10s %-10s %-10s", li.id, li.description, li.libname, li.version, li.number_set);
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

void activate_bison_debug()
{
	/*
	* Double test with caller (in main.c) as main.c also checks for BISON_DEBUG,
	* but I find it clearer. This way, main.c highlights it is only when debug
	* is activated. Below, the test is mandatory (yydebug undefined if no BISON_DEBUG)
	*/
#ifdef BISON_DEBUG
	yydebug = 1;
#endif
}

