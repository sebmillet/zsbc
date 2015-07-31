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
	defargs_t *defargs;
	callargs_t *callargs;
};

%token <num> INTEGER
%type <enode> expression expression_no_assignment expression_assignment expression_or_empty function_call
%token <str> IDENTIFIER STRING COMPARISON OP_AND_ASSIGN PLUSPLUS_MINMIN
%type <prog> instruction_block instruction_inside_block instruction_list instruction instruction_non_empty instruction_assignment
%type <prog> loop_while loop_for ifseq else_or_empty
%type <defargs> defargs_list_or_empty defargs_list defarg
%type <callargs> callarg callargs_list callargs_list_or_empty

%token QUIT VARS LIBSWITCH LIBLIST
%token WHILE FOR BREAK CONTINUE IF ELSE
%token DEFINE VOID RETURN

%token NEWLINE

%left LOGIC_OR
%left LOGIC_AND
%nonassoc LOGIC_NOT
%left COMPARISON
%right OP_AND_ASSIGN
%left '+' '-'
%left '*' '/' '%'
%right '^'
%nonassoc NEG
%nonassoc PLUSPLUS_MINMIN

%destructor { num_destruct(&$$); out_dbg("parser.y: freed one num\n"); } <num>
%destructor { expr_destruct($$); out_dbg("parser.y: freed one enode\n"); } <enode>
%destructor { free($$); out_dbg("parser.y: freed one str\n"); } <str>
%destructor { program_destruct($$); out_dbg("parser.y: freed one program\n"); } <prog>
%destructor { defargs_destruct($$); out_dbg("parser.y: freed one DEF argument chain\n"); } <defargs>
%destructor { callargs_destruct($$); out_dbg("parser.y: freed one CALL argument chain\n"); } <callargs>

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
		program_execute($1, NULL);
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
	| STRING { $$ = program_construct_str($1); }
	| loop_while
	| loop_for
	| ifseq
	| RETURN expression { $$ = program_construct_return($2); }
	| BREAK { $$ = program_construct_break(); }
	| CONTINUE { $$ = program_construct_continue(); }
	| instruction_block { $$ = $1; }
;

instruction_assignment:
	IDENTIFIER OP_AND_ASSIGN expression {
		expr_t *enode = expr_construct_setvar($1, NULL, $2, FALSE, $3);
		$$ = program_construct_expr(enode, TRUE);
		free($2);
	}
	| IDENTIFIER '[' expression ']' OP_AND_ASSIGN expression {
		expr_t *enode = expr_construct_setvar($1, $3, $5, FALSE, $6);
		$$ = program_construct_expr(enode, TRUE);
		free($5);
	}
;

expression:
	expression_no_assignment
	| expression_assignment
;

expression_assignment:
	IDENTIFIER OP_AND_ASSIGN expression { $$ = expr_construct_setvar($1, NULL, $2, FALSE, $3); free($2); }
	| IDENTIFIER '[' expression ']' OP_AND_ASSIGN expression { $$ = expr_construct_setvar($1, $3, $5, FALSE, $6); free($5); }
;

expression_no_assignment:
    INTEGER { $$ = expr_construct_number($1); }
	| IDENTIFIER { $$ = expr_construct_getvar($1, NULL); }
	| IDENTIFIER '[' expression ']' { $$ = expr_construct_getvar($1, $3); }
	| PLUSPLUS_MINMIN IDENTIFIER { $$ = expr_construct_setvar($2, NULL, $1, FALSE, NULL); free($1); }
	| IDENTIFIER PLUSPLUS_MINMIN { $$ = expr_construct_setvar($1, NULL, $2, TRUE, NULL); free($2); }
	| PLUSPLUS_MINMIN IDENTIFIER '[' expression ']' { $$ = expr_construct_setvar($2, $4, $1, FALSE, NULL); free($1); }
	| IDENTIFIER '[' expression ']' PLUSPLUS_MINMIN { $$ = expr_construct_setvar($1, $3, $5, TRUE, NULL); free($5); }
	| function_call
	| expression '+' expression { $$ = expr_construct_op2_str("+", $1, $3); }
	| expression '-' expression { $$ = expr_construct_op2_str("-", $1, $3); }
	| expression '*' expression { $$ = expr_construct_op2_str("*", $1, $3); }
	| expression '/' expression { $$ = expr_construct_op2_str("/", $1, $3); }
	| expression '^' expression { $$ = expr_construct_op2_str("^", $1, $3); }
	| expression '%' expression { $$ = expr_construct_op2_str("%", $1, $3); }
	| '-' expression %prec NEG { $$ = expr_construct_op1_str("-", $2); }
	| expression COMPARISON expression { $$ = expr_construct_op2_str($2, $1, $3); free($2); }
	| expression LOGIC_AND expression { $$ = expr_construct_op2_str("&&", $1, $3); }
	| expression LOGIC_OR expression { $$ = expr_construct_op2_str("||", $1, $3); }
	| LOGIC_NOT expression { $$ = expr_construct_op1_str("!", $2); }
	| '(' expression ')' { $$ = $2; }
;

newlines_or_empty:
	%empty
	| NEWLINE newlines_or_empty
;

loop_while:
	WHILE '(' expression ')' newlines_or_empty instruction_non_empty {
		program_loop_t loop;
		loop.exprbefore = NULL;
		loop.testbefore = $3;
		loop.core = $6;
		loop.testafter = NULL;
		loop.exprafter = NULL;
		$$ = program_construct_loop(&loop);
	}
;

expression_or_empty:
	%empty { $$ = NULL; }
	| expression
;

loop_for:
	FOR '(' expression_or_empty ';' expression_or_empty ';' expression_or_empty ')' newlines_or_empty instruction_non_empty {
		program_loop_t loop;
		loop.exprbefore = $3;
		loop.testbefore = $5;
		loop.core = $10;
		loop.testafter = NULL;
		loop.exprafter = $7;
		$$ = program_construct_loop(&loop);
	}
;

ifseq:
	IF '(' expression ')' newlines_or_empty instruction_non_empty else_or_empty {
		program_ifseq_t ifseq;
		ifseq.expr = $3;
		ifseq.pif = $6;
		ifseq.pelse = $7;
		$$ = program_construct_ifseq(&ifseq);
	}
;

else_or_empty:
	%empty { $$ = NULL; }
	| newlines_or_empty ELSE newlines_or_empty instruction_non_empty { $$ = $4; }
;

defarg:
	IDENTIFIER { $$ = defargs_construct(DARG_VALUE, $1); }
	| IDENTIFIER '[' ']' { $$ = defargs_construct(DARG_ARRAYVALUE, $1); }
	| '*' IDENTIFIER { $$ = defargs_construct(DARG_REF, $2); }
	| '*' IDENTIFIER '[' ']' { $$ = defargs_construct(DARG_ARRAYREF, $2); }
;

defargs_list:
	defarg
	| defargs_list ',' defarg { $$ = defargs_chain($1, $3); }
;

defargs_list_or_empty:
	%empty { $$ = NULL; }
	| defargs_list
;

function_definition:
	DEFINE IDENTIFIER '(' defargs_list_or_empty ')' newlines_or_empty instruction_non_empty {
		int r;
		if ((r = vars_function_construct($2, $4, $7, FALSE)) != ERROR_NONE)
			outln_error_code(r);
	}
	| DEFINE VOID IDENTIFIER '(' defargs_list_or_empty ')' newlines_or_empty instruction_non_empty {
		int r;
		if ((r = vars_function_construct($3, $5, $8, TRUE)) != ERROR_NONE)
			outln_error_code(r);
	}
;

callarg:
	expression { $$ = callargs_construct(CARG_EXPR, $1, NULL); }
	| IDENTIFIER '[' ']' { $$ = callargs_construct(CARG_ARRAY, NULL, $1); }
;

callargs_list:
	callarg
	| callargs_list ',' callarg { $$ = callargs_chain($1, $3); }
;

callargs_list_or_empty:
	%empty { $$ = NULL; }
	| callargs_list
;

function_call:
	IDENTIFIER '(' callargs_list_or_empty ')' { $$ = expr_construct_function_call($1, $3); }
;

statement:
	function_definition
	| QUIT { YYABORT; }
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
		lib_list();
	}
;

%%

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

