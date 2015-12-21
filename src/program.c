/*
 * =====================================================================================
 *
 *       Filename:  program.c
 *
 *    Description:  Manages instructions with program_t structure and provides
 *    				functions to *execute* it.
 *
 *        Version:  1.0
 *        Created:  27/06/2015 08:25:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet (smt), milletseb@laposte.net
 *
 * =====================================================================================
 */


#include "program.h"
#include "vars.h"

int instr_count_ref = 0;

extern defargs_t *defarg_t_badarg;

typedef enum {
	TINSTR_EXPR_EXPR,
	TINSTR_EXPR_ASSIGN_EXPR,
	TINSTR_EXPR_RETURN,
	TINSTR_STR,
	TINSTR_LOOP,
	TINSTR_BREAK,
	TINSTR_CONTINUE,
	TINSTR_IFSEQ,
	TINSTR_AUTOLIST
} instr_t;

struct program_t {
	instr_t type;
	code_location_t loc;
	int is_part_of_print;		/* for TINSTR_EXPR* and TINSTR_STR */

	union {
		expr_t *expr;			/* TINSTR_EXPR* */
		char *str;				/* TINSTR_STR */
		program_loop_t loop;	/* TINSTR_LOOP */
		program_ifseq_t ifseq;	/* TINSTR_IFSEQ */
		defargs_t *autolist;	/* TINSTR_DEFARGS */
	} prg;

	program_t *next;
		/*
		 * The variable below is not necessary, it aims to avoid
		 * walk-through in the whole chain everytime an element
		 * is added. It removes a O(n^2) condition that'd make it
		 * impossible to deal with programs of thousands of lines.
		 * */
	program_t *tail;
};

static program_t *program_construct(instr_t type, const code_location_t *ploc)
{
	program_t *p = (program_t *)malloc(sizeof(program_t));
	p->type = type;

	p->loc = *ploc;

	p->is_part_of_print = FALSE;
	p->next = NULL;
	p->tail = NULL;
	return p;
}

program_t *program_construct_expr(expr_t *e, int is_assignment, const code_location_t loc)
{
	program_t *p = program_construct(is_assignment ? TINSTR_EXPR_ASSIGN_EXPR : TINSTR_EXPR_EXPR, &loc);
	p->prg.expr = e;
	out_dbg("Construct of one program of type %s, address = %lu\n", is_assignment ? "TINSTR_ASSIGN_EXPR" : "TINSTR_EXPR", p);
	return p;
}

	/*
	 * *NOTE*
	 *
	 *   e can be NULL, in the case of a simple statement
	 *     return
	 *   without argument.
	 */
program_t *program_construct_return(expr_t *e, const code_location_t loc)
{
	program_t *p = program_construct(TINSTR_EXPR_RETURN, &loc);
	p->prg.expr = e;
	out_dbg("Construct of one program of type return, expression: %lu, address = %lu\n", e, p);
	return p;
}

program_t *program_construct_str(const char *s, const code_location_t loc)
{
	program_t *p = program_construct(TINSTR_STR, &loc);
	p->prg.str = (char *)s;
	out_dbg("Construct one program of type string, string value: '%s', address = %lu\n", s, p);
	return p;
}

program_t *program_construct_loop(program_loop_t *loop, const code_location_t loc)
{
	program_t *p = program_construct(TINSTR_LOOP, &loc);
	p->prg.loop = *loop;
	out_dbg("Construct one program of type loop, address = %lu\n", p);
	return p;
}

program_t *program_construct_break(const code_location_t loc)
{
	program_t *p = program_construct(TINSTR_BREAK, &loc);
	out_dbg("Construct of one program of type break, address = %lu\n", p);
	return p;
}

program_t *program_construct_continue(const code_location_t loc)
{
	program_t *p = program_construct(TINSTR_CONTINUE, &loc);
	out_dbg("Construct of one program of type continue, address = %lu\n", p);
	return p;
}

program_t *program_construct_ifseq(program_ifseq_t *ifseq, const code_location_t loc)
{
	program_t *p = program_construct(TINSTR_IFSEQ, &loc);
	p->prg.ifseq = *ifseq;
	out_dbg("Construct of one program of type if, expression: %lu, program_if: %lu, program_else: %lu, address = %lu\n",
		ifseq->expr, ifseq->pif, ifseq->pelse, p);
	return p;
}

program_t *program_construct_autolist(defargs_t *autolist, const code_location_t loc)
{
	program_t *p = program_construct(TINSTR_AUTOLIST, &loc);
	p->prg.autolist = (autolist == defarg_t_badarg ? NULL : autolist);
	out_dbg("Construct of one program of type autolist, autolist: %lu, address = %lu\n", autolist, p);
	return p;
}

void program_gather_defargs(defargs_t **pautolist, program_t **base)
{
	*pautolist = NULL;
	program_t *p = *base;
	program_t *prec = NULL;
	while (p != NULL) {
		program_t *pnext = p->next;
		if (p->type == TINSTR_AUTOLIST) {

				/* 1- Detach the list from the program and attach it to the given autolist */

			if (p->prg.autolist) {
				if (!*pautolist) {
					*pautolist = p->prg.autolist;
				} else {
					defargs_chain(*pautolist, p->prg.autolist);
				}
				p->prg.autolist = NULL;
			}

				/* 2- Destruct the program and update pointers chain accordingly */

			if (!prec)
				*base = pnext;
			else {
				prec->next = pnext;
			}
								/*
								 * Important to cancel the chain here, if not done */
			p->next = NULL;		/* the program_destruct() call below would also
								 * destruct the whole chain.
								 * */
			program_destruct(p);

		} else {
			prec = p;
		}

			/* 3- Go to next program */

		p = pnext;

	}
}

void program_destruct(program_t *p)
{
	out_dbg("Entering program_destruct for %lu\n", p);
	program_t *pnext;
	while (p != NULL) {
		out_dbg("Starting to destruct one program instruction, address = %lu\n", p);
		switch (p->type) {
			case TINSTR_EXPR_EXPR:
			case TINSTR_EXPR_ASSIGN_EXPR:
			case TINSTR_EXPR_RETURN:
				expr_destruct(p->prg.expr);
				break;
			case TINSTR_STR:
				free(p->prg.str);
				break;
			case TINSTR_LOOP:
				expr_destruct(p->prg.loop.exprbefore);
				expr_destruct(p->prg.loop.testbefore);
				program_destruct(p->prg.loop.core);
				expr_destruct(p->prg.loop.testafter);
				expr_destruct(p->prg.loop.exprafter);
				break;
			case TINSTR_BREAK:
			case TINSTR_CONTINUE:
				break;
			case TINSTR_IFSEQ:
				expr_destruct(p->prg.ifseq.expr);
				program_destruct(p->prg.ifseq.pif);
				program_destruct(p->prg.ifseq.pelse);
				break;
			case TINSTR_AUTOLIST:
				defargs_destruct(p->prg.autolist);
				break;
			default:
				FATAL_ERROR("Unknown program type: %d, program address: %lu", p->type, p);
		}
		out_dbg("Done destructing one program instruction, going to next instruction\n");
		pnext = p->next;
		free(p);
		p = pnext;
	}
}

	/*
	 * This function manages the output as follows:
	 *
	 *   - Outputs something (using num_print() and outstring() functions) when there is no error
	 *
	 *   - DOES NOT OUTPUT ANYTHING if an error occurs. It is then up to the caller to manage
	 *     displaying an error.
	 *
	 * */
int program_execute(program_t *p, numptr *pval, exec_ctx_t *pexec_ctx)
{
	out_dbg("Entering program_execute for %lu\n", p);
	int r = ERROR_NONE;
	while (p != NULL && r == ERROR_NONE) {
		out_dbg("Executing one instruction, type: %d, address: %lu\n", p->type, p);
		pexec_ctx->ploc = &p->loc;
		numptr num;
		program_loop_t *loop;
		program_ifseq_t *ifseq;
		program_t *pnext = p->next;
		int b;
		int print_result;
		char *t;
		switch (p->type) {
			case TINSTR_EXPR_EXPR:
			case TINSTR_EXPR_ASSIGN_EXPR:
			case TINSTR_EXPR_RETURN:
				print_result = (p->type == TINSTR_EXPR_EXPR || (p->is_part_of_print && p->type == TINSTR_EXPR_ASSIGN_EXPR));
				num = num_undefvalue();
				if ((r = expr_eval(p->prg.expr, &num, pexec_ctx)) != ERROR_NONE) {
					out_dbg("Expression produced return value %d\n", r);
					break;
				} else if (print_result && !num_is_not_initialized(num)) {
					num_print(num);
					if (!p->is_part_of_print)
						outstring("", TRUE);
				}
				if (p->type == TINSTR_EXPR_RETURN) {
					r = ERROR_RETURN;
					if (pval == NULL) {
						num_destruct(&num);
					} else {
						*pval = num;
					}
					pnext = NULL;
				} else {
					if (r == ERROR_NONE) {
						const numptr *ppvarnum;
						vars_set_value(VAR_LAST, num, &ppvarnum);
					}
				}
				break;
			case TINSTR_STR:
				t = interpret_escape_sequences_alloc(p->prg.str);
				outstring(t, FALSE);
				free(t);
				break;
			case TINSTR_LOOP:
				loop = &p->prg.loop;

					/* First term of 3-term for() */
				num = num_undefvalue();
				if ((r = expr_eval(loop->exprbefore, &num, pexec_ctx)) != ERROR_NONE)
					break;
				num_destruct(&num);

				while (TRUE) {

						/* Second term of a 3-term for() or test part of a while() */
					if (loop->testbefore != NULL) {
						num = num_undefvalue();
						if ((r = expr_eval(loop->testbefore, &num, pexec_ctx)) != ERROR_NONE)
							break;
						b = num_is_zero(num);
						num_destruct(&num);
						if (b)
							break;
					}

						/* The content of the loop being executed, for every loops realms */
					r = program_execute(loop->core, pval, pexec_ctx);
					if (r == ERROR_BREAK) {
						r = ERROR_NONE;
						break;
					}
					if (r == ERROR_CONTINUE) {
						r = ERROR_NONE;
						continue;
					}
					if (r != ERROR_NONE)
						break;

						/* Test part of a do ... while() */
					if (loop->testafter != NULL) {
						num = num_undefvalue();
						if ((r = expr_eval(loop->testafter, &num, pexec_ctx)) != ERROR_NONE)
							break;
						b = num_is_zero(num);
						num_destruct(&num);
						if (b)
							break;
					}

						/* Third term of a 3-term for() */
					num = num_undefvalue();
					if ((r = expr_eval(loop->exprafter, &num, pexec_ctx)) != ERROR_NONE)
						break;
					num_destruct(&num);

				}
				break;
			case TINSTR_BREAK:
				pnext = NULL;
				r = ERROR_BREAK;
				break;
			case TINSTR_CONTINUE:
				pnext = NULL;
				r = ERROR_CONTINUE;
				break;
			case TINSTR_IFSEQ:
				ifseq = &p->prg.ifseq;

					/* PART 1 - TEST */

				num = num_undefvalue();
				if ((r = expr_eval(ifseq->expr, &num, pexec_ctx)) != ERROR_NONE)
					break;
				b = num_is_zero(num);
				num_destruct(&num);

					/* PART 2 - IF or ELSE execution*/
				if (!b)
					r = program_execute(ifseq->pif, pval, pexec_ctx);
				else
					r = program_execute(ifseq->pelse, pval, pexec_ctx);

				break;
			default:
				FATAL_ERROR("Unknown program type: %d, program address: %lu", p->type, p);
		}
		out_dbg("Execution done, going to next instruction\n");
		p = pnext;
	}
	return r;
}

program_t *program_chain(program_t *base, program_t *append)
{
	out_dbg("Chaining one program, base: %lu, append: %lu\n", base, append);
	if (append == NULL)
		return base;
	if (base == NULL) {
		return append;
	} else {
		if (base->tail == NULL) {
			base->next = append;
		} else {
			base->tail->next = append;
		}
		base->tail = (append->tail == NULL ? append : append->tail);
	}
	return base;
}

void program_notify_is_part_of_print(program_t *program)
{
	program->is_part_of_print = TRUE;
}

	/*
	 * Detect inconsistencies like:
	 *   - continue or break out of a loop
	 *   - void functions returning a value (return statement with a return value)
	 *   - non-void functions non returning a value (return without statement or no return statement)
	 *   - check function calls ->
	 *       function existence
	 *       number and type of arguments
	 *
	 * *IMPORTANT*
	 *   No program is executed here.
	 *   However an exec_ctx_t *pexec_ctx is passed to hold error information if need be.
	 *
	 * *NOTE*
	 *   No return code because the goal is first to display warning messages not error messages.
	 *
	 * FIXME
	 *   Also will have to manage the notion of "want a return value" = a void function
	 *   should not be called in any expression.
	 */
void program_check(program_t *p, exec_ctx_t *pexec_ctx, check_t *check)
{

	out_dbg("Entering check_program_recursive()\n");

	while (p != NULL) {

		out_dbg("Now checking program %lu\n", p);

		pexec_ctx->ploc = &p->loc;

		check_t save_check = *check;

		switch (p->type) {

			case TINSTR_EXPR_EXPR:
			case TINSTR_EXPR_ASSIGN_EXPR:
				check->i_want_a_value = p->is_part_of_print;
				expr_check(p->prg.expr, pexec_ctx, check);
				break;

			case TINSTR_STR:
			case TINSTR_AUTOLIST:
				break;

			case TINSTR_IFSEQ:
				check->i_want_a_value = TRUE;
				expr_check(p->prg.ifseq.expr, pexec_ctx, check);
				check->i_want_a_value = FALSE;
				program_check(p->prg.ifseq.pif, pexec_ctx, check);
				if (p->prg.ifseq.pelse != NULL) {
					check->i_want_a_value = FALSE;
					program_check(p->prg.ifseq.pelse, pexec_ctx, check);
				}
				break;

			case TINSTR_EXPR_RETURN:
				if (p->prg.expr == NULL && !check->is_void) {
					set_exec_error_message(pexec_ctx, "Void return in non void function");
					outln_exec_error(ERROR_CUSTOM, pexec_ctx, TRUE);
				} else if (p->prg.expr != NULL && check->is_void) {
					set_exec_error_message(pexec_ctx, "Non void return in void function");
					outln_exec_error(ERROR_CUSTOM, pexec_ctx, TRUE);
				}
				check->i_want_a_value = TRUE;
				expr_check(p->prg.expr, pexec_ctx, check);
				break;

			case TINSTR_LOOP:
				check->is_inside_loop = TRUE;
				check->i_want_a_value = FALSE;
				expr_check(p->prg.loop.exprbefore, pexec_ctx, check);
				check->i_want_a_value = TRUE;
				expr_check(p->prg.loop.testbefore, pexec_ctx, check);
				check->i_want_a_value = FALSE;
				program_check(p->prg.loop.core, pexec_ctx, check);
				check->i_want_a_value = TRUE;
				expr_check(p->prg.loop.testafter, pexec_ctx, check);
				check->i_want_a_value = FALSE;
				expr_check(p->prg.loop.exprafter, pexec_ctx, check);
				break;

			case TINSTR_BREAK:
				if (!check->is_inside_loop) {
					set_exec_error_message(pexec_ctx, "Illegal break statement outside of a loop");
					outln_exec_error(ERROR_CUSTOM, pexec_ctx, FALSE);
				}
				break;

			case TINSTR_CONTINUE:
				if (!check->is_inside_loop) {
					set_exec_error_message(pexec_ctx, "Illegal continue statement outside of a loop");
					outln_exec_error(ERROR_CUSTOM, pexec_ctx, FALSE);
				}
				break;

			default:
				FATAL_ERROR("Unknown program type: %d, program address: %lu", p->type, p);
		}
		*check = save_check;
		p = p->next;
	}
}

