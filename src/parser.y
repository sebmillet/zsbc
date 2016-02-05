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
 * For the arithmetic operators precedence and associativity definitions,
 * it is just a rewording of bc source.
 *
 * The LOWER_THAN_ELSE solution was found here:
 *   http://stackoverflow.com/questions/1737460/how-to-find-shift-reduce-conflict-in-this-yacc-file
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

typedef struct YYLTYPE YYLTYPE;
const code_location_t code_loc(const YYLTYPE yl);

const char *input_get_name();

extern defargs_t *defarg_t_badarg;
extern int flag_quitting;

#ifdef BISON_DEBUG
#define YYDEBUG 1
#endif

%}

%code provides {
void activate_bison_debug();
void hackbc_enter();
void hackbc_terminate();
void hackbc_inc_nested();
void hackbc_dec_nested();

#ifndef YY_TYPEDEF_YY_BUFFER_STATE
#define YY_TYPEDEF_YY_BUFFER_STATE
typedef struct yy_buffer_state *YY_BUFFER_STATE;
#endif
YY_BUFFER_STATE yy_scan_buffer(char *bytes, size_t len);
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
%type <prog> instruction_block instruction_inside_block instruction_list instruction
%type <prog> my_instruction_non_empty instruction_non_empty instruction_expr_assignment
%type <prog> loop_while loop_for ifseq instruction_string instruction_expr_no_assignment print_elem print_list
%type <defargs> defargs_list_or_empty defargs_list defarg defargsbyval_list defargbyval
%type <callargs> callarg callargs_list callargs_list_or_empty

%token QUIT SYMBOLS LIBSWITCH LIBLIST
%token WHILE FOR BREAK CONTINUE IF ELSE
%token DEFINE MYVOID RETURN AUTOLIST PRINT

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
%precedence LOWER_THAN_ELSE
%precedence ELSE

%destructor { num_destruct(&$$); out_dbg("parser.y: freed one num\n"); } <num>
%destructor { expr_destruct($$); out_dbg("parser.y: freed one enode\n"); } <enode>
%destructor { free($$); out_dbg("parser.y: freed one str\n"); } <str>
%destructor { program_destruct($$); out_dbg("parser.y: freed one program\n"); } <prog>
%destructor { defargs_destruct($$); out_dbg("parser.y: freed one DEF argument chain\n"); } <defargs>
%destructor { callargs_chain_destruct($$); out_dbg("parser.y: freed one CALL argument chain\n"); } <callargs>

%start input

%%

input:
	%empty { outstring_reset(); loc_reset(); }
	| { outstring_reset(); } program NEWLINE input
	| { outstring_reset(); } statement NEWLINE input
	| error NEWLINE input {
		out_dbg("Error encountered, ran yyclearin and yyerrok\n");
		yyclearin; yyerrok;
		outstring_reset();
	}
;

program:
	instruction_list {
		exec_ctx_t *pexec_ctx = construct_exec_ctx_t();
		int r = program_execute($1, NULL, pexec_ctx);
		if (r != ERROR_NONE) {
			outln_exec_error(r, pexec_ctx, FALSE);
		}
		program_destruct($1);
		destruct_exec_ctx_t(pexec_ctx, FALSE);
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
	| my_instruction_non_empty
;

instruction_non_empty:
	{ hackbc_inc_nested(); } my_instruction_non_empty { hackbc_dec_nested(); $$ = $2; }
;

my_instruction_non_empty:
	instruction_expr_assignment
	| instruction_expr_no_assignment
	| instruction_string
	| loop_while
	| loop_for
	| ifseq
	| RETURN { $$ = program_construct_return(NULL, code_loc(@$)); }
	| RETURN expression { $$ = program_construct_return($2, code_loc(@$)); }
	| BREAK { $$ = program_construct_break(code_loc(@$)); }
	| CONTINUE { $$ = program_construct_continue(code_loc(@$)); }
	| PRINT print_list { $$ = $2; }
	| AUTOLIST defargsbyval_list { $$ = program_construct_autolist($2, code_loc(@$)); }
	| instruction_block { $$ = $1; }
;

instruction_expr_assignment:
	IDENTIFIER OP_AND_ASSIGN expression {
		expr_t *enode = expr_construct_setvar($1, NULL, $2, FALSE, $3);
		$$ = program_construct_expr(enode, TRUE, code_loc(@$));
		free($2);
	}
	| IDENTIFIER '[' expression ']' OP_AND_ASSIGN expression {
		expr_t *enode = expr_construct_setvar($1, $3, $5, FALSE, $6);
		$$ = program_construct_expr(enode, TRUE, code_loc(@$));
		free($5);
	}
;

instruction_expr_no_assignment:
	expression_no_assignment { $$ = program_construct_expr($1, FALSE, code_loc(@$)); }
;

instruction_string:
	STRING { $$ = program_construct_str($1, code_loc(@$)); }
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

print_elem:
	instruction_expr_assignment { program_notify_is_part_of_print($1); $$ = $1; }
	| instruction_expr_no_assignment { program_notify_is_part_of_print($1); $$ = $1; }
	| instruction_string { program_notify_is_part_of_print($1); $$ = $1; }
;

print_list:
	print_elem
	| print_list ',' print_elem { $$ = program_chain($1, $3); }
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
		$$ = program_construct_loop(&loop, code_loc(@$));
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
		$$ = program_construct_loop(&loop, code_loc(@$));
	}
;

ifseq:
	IF '(' expression ')' newlines_or_empty instruction_non_empty %prec LOWER_THAN_ELSE {
		program_ifseq_t ifseq;
		ifseq.expr = $3;
		ifseq.pif = $6;
		ifseq.pelse = NULL;
		$$ = program_construct_ifseq(&ifseq, code_loc(@$));
	}
	| IF '(' expression ')' newlines_or_empty instruction_non_empty ELSE newlines_or_empty instruction_non_empty {
		program_ifseq_t ifseq;
		ifseq.expr = $3;
		ifseq.pif = $6;
		ifseq.pelse = $9;
		$$ = program_construct_ifseq(&ifseq, code_loc(@$));
	}
;

defargbyval:
	IDENTIFIER { $$ = defargs_construct(DARG_VALUE, $1); }
	| IDENTIFIER '[' ']' { $$ = defargs_construct(DARG_ARRAYVALUE, $1); }
;

defarg:
	defargbyval
	| '*' IDENTIFIER { $$ = defargs_construct(DARG_REF, $2); }
	| '*' IDENTIFIER '[' ']' { $$ = defargs_construct(DARG_ARRAYREF, $2); }
;

defargsbyval_list:
	defargbyval
	| defargsbyval_list ',' defargbyval {
		$$ = defargs_chain($1, $3);
		if ($$ == defarg_t_badarg && $1 != defarg_t_badarg && $3 != defarg_t_badarg) {
			yyerror("duplicate names in autolist (autolist will be ignored)");
		}
		if ($$ == defarg_t_badarg) {
			if ($1 != defarg_t_badarg)
				free($1);
			if ($3 != defarg_t_badarg)
				free($3);
		}
	}
;

defargs_list:
	defarg
	| defargs_list ',' defarg {
		$$ = defargs_chain($1, $3);
		if ($$ == defarg_t_badarg && $1 != defarg_t_badarg && $3 != defarg_t_badarg) {
			yyerror("duplicate parameter names");
		}
		if ($$ == defarg_t_badarg) {
			if ($1 != defarg_t_badarg)
				free($1);
			if ($3 != defarg_t_badarg)
				free($3);
		}
	}
;

defargs_list_or_empty:
	%empty { $$ = NULL; }
	| defargs_list
;

hackbc_enter:
	%empty { hackbc_enter(); }
;

hackbc_terminate:
	%empty { hackbc_terminate(); }
;

function_definition:
	hackbc_enter DEFINE IDENTIFIER '(' defargs_list_or_empty ')' newlines_or_empty instruction_non_empty hackbc_terminate {
		vars_user_function_construct($3, $5, $8, FALSE, code_loc(@$));
	}
	| hackbc_enter DEFINE MYVOID IDENTIFIER '(' defargs_list_or_empty ')' newlines_or_empty instruction_non_empty hackbc_terminate {
		vars_user_function_construct($4, $6, $9, TRUE, code_loc(@$));
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
	| QUIT { flag_quitting = TRUE; YYABORT; }
	| SYMBOLS {
		vars_display_all();
	}
	| LIBSWITCH STRING {
		if (num_libswitch($2) == 0) {
			outln_error("%s", "Unknown library");
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

#define VARIBASE "ibase"
static int hackbc_has_entered = FALSE;
static int hackbc_nested_level;
static int save_ibase_is_set;
static int save_ibase;

void hackbc_enter()
{
	const numptr *pnum = vars_get_value(VARIBASE);
	if (pnum == NULL) {
		out_dbg("Entering function definition - no ibase variable set\n");
		save_ibase_is_set = FALSE;
	} else {

			/*
			 * FIXME???
			 * Check int versus long int storage capacity?
			 * It'd be a bit strange to have ibase greater than INT_MAX...
			 * So I just ignore it.
			 *
			*/
		save_ibase = (int)num_getlongint(*pnum);

		out_dbg("Entering function definition - ibase set, value: %d\n", save_ibase);
		save_ibase_is_set = TRUE;
	}
	hackbc_has_entered = TRUE;
	hackbc_nested_level = 0;
}

void hackbc_terminate()
{
	if (!hackbc_has_entered)
		return;

	if (save_ibase_is_set) {
		out_dbg("Terminating function definition - ibase set back to %d\n", save_ibase);
		const numptr *pvar;
		vars_set_value(VARIBASE, num_construct_from_int(save_ibase), &pvar);
	} else {
		out_dbg("Terminating function definition - ibase is deleted\n");
		var_delete(VARIBASE);
	}
	hackbc_has_entered = FALSE;
}

void hackbc_inc_nested()
{
	++hackbc_nested_level;
	out_dbg("hack_inc_nested(): nested = %d\n", hackbc_nested_level);
}

void hackbc_dec_nested()
{
	--hackbc_nested_level;
	out_dbg("hack_dec_nested(): nested = %d\n", hackbc_nested_level);
}

void hackbc_check(const char *name, expr_t *e)
{
	if (!hackbc_has_entered || varname_cmp(name, VARIBASE))
		return;

	if (hackbc_nested_level != 1) {
		out_dbg("hackbc_check(): eligible assignment but not at correct nested level\n");
		return;
	}

	numptr num = num_undefvalue();
	exec_ctx_t *pexec_ctx = construct_exec_ctx_t();
	int r = expr_eval(e, &num, pexec_ctx);
		/*
		 * We just ignore cases when an error occurs (ex. with an
		 * instruction like "ibase = 1 / 0", and also cases where
		 * there is no return value.
		*/
	if (r == ERROR_NONE && !num_is_not_initialized(num)) {
		out_dbg("hackbc_check(): caught variable assignment successfully: assigning new value\n");
		const numptr *pvar;
		vars_set_value(VARIBASE, num, &pvar);
	} else {
		out_dbg("hackbc_check(): CAUGHT VARIABLE ASSIGNMENT BUT COULD NOT CALCULATE CONSTANT EXPRESSION VALUE!\n");
	}
	destruct_exec_ctx_t(pexec_ctx, FALSE);
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

