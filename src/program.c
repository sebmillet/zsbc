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
 *   Organization:  
 *
 * =====================================================================================
 */


#include "program.h"
#include "vars.h"

int instr_count_ref = 0;

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

	union {
		expr_t *expr;			/* TINSTR_EXPR* */
		char *str;				/* TINSTR_STR */
		program_loop_t loop;	/* TINSTR_LOOP */
		program_ifseq_t ifseq;	/* TINSTR_IFSEQ */
		defargs_t *autolist;		/* TINSTR_DEFARGS */
	};

	program_t *next;
};

static program_t *program_construct(instr_t type)
{
	program_t *p = (program_t *)malloc(sizeof(program_t));
	p->type = type;
	p->next = NULL;
	return p;
}

program_t *program_construct_expr(expr_t *e, int is_assignment)
{
	program_t *p = program_construct(is_assignment ? TINSTR_EXPR_ASSIGN_EXPR : TINSTR_EXPR_EXPR);
	p->expr = e;
	out_dbg("Construct of one program of type %s, address = %lu\n", is_assignment ? "TINSTR_ASSIGN_EXPR" : "TINSTR_EXPR", p);
	return p;
}

program_t *program_construct_return(expr_t *e)
{
	program_t *p = program_construct(TINSTR_EXPR_RETURN);
	p->expr = e;
	out_dbg("Construct of one program of type return, expression: %lu, address = %lu\n", e, p);
	return p;
}

program_t *program_construct_str(const char *s)
{
	program_t *p = program_construct(TINSTR_STR);
	p->str = (char *)s;
	out_dbg("Construct one program of type string, string value: '%s', address = %lu\n", s, p);
	return p;
}

program_t *program_construct_loop(program_loop_t *loop)
{
	program_t *p = program_construct(TINSTR_LOOP);
	p->loop = *loop;
	out_dbg("Construct one program of type loop, address = %lu\n", p);
	return p;
}

program_t *program_construct_break()
{
	program_t *p = program_construct(TINSTR_BREAK);
	out_dbg("Construct of one program of type break, address = %lu\n", p);
	return p;
}

program_t *program_construct_continue()
{
	program_t *p = program_construct(TINSTR_CONTINUE);
	out_dbg("Construct of one program of type continue, address = %lu\n", p);
	return p;
}

program_t *program_construct_ifseq(program_ifseq_t *ifseq)
{
	program_t *p = program_construct(TINSTR_IFSEQ);
	p->ifseq = *ifseq;
	out_dbg("Construct of one program of type if, expression: %lu, program_if: %lu, program_else: %lu, address = %lu\n",
		ifseq->expr, ifseq->pif, ifseq->pelse, p);
	return p;
}

program_t *program_construct_autolist(defargs_t *autolist)
{
	program_t *p = program_construct(TINSTR_AUTOLIST);
	p->autolist = autolist;
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

			if (p->autolist) {
				if (!*pautolist) {
					*pautolist = p->autolist;
				} else {
					defargs_chain(*pautolist, p->autolist);
				}
				p->autolist = NULL;
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
				expr_destruct(p->expr);
				break;
			case TINSTR_STR:
				free(p->str);
				break;
			case TINSTR_LOOP:
				expr_destruct(p->loop.exprbefore);
				expr_destruct(p->loop.testbefore);
				program_destruct(p->loop.core);
				expr_destruct(p->loop.testafter);
				expr_destruct(p->loop.exprafter);
				break;
			case TINSTR_BREAK:
			case TINSTR_CONTINUE:
				break;
			case TINSTR_IFSEQ:
				expr_destruct(p->ifseq.expr);
				program_destruct(p->ifseq.pif);
				program_destruct(p->ifseq.pelse);
				break;
			case TINSTR_AUTOLIST:
				defargs_destruct(p->autolist);
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

int program_execute(program_t *p, numptr *pval)
{
	out_dbg("Entering program_execute for %lu\n", p);
	int r = ERROR_NONE;
	while (p != NULL && r == ERROR_NONE) {
		out_dbg("Executing one instruction, type: %d, address: %lu\n", p->type, p);
		numptr num;
		program_loop_t *loop;
		program_ifseq_t *ifseq;
		program_t *pnext = p->next;
		int b;
		int print_result;
		switch (p->type) {
			case TINSTR_EXPR_EXPR:
			case TINSTR_EXPR_ASSIGN_EXPR:
			case TINSTR_EXPR_RETURN:
				print_result = (p->type == TINSTR_EXPR_EXPR);
				num = num_undefvalue();
				if ((r = expr_eval(p->expr, &num)) != ERROR_NONE) {
					outln_error_code(r);
				} else if (print_result && !num_is_not_initialized(num)) {
					num_print(num, 10);
					outln(L_ENFORCE, "");
				}
				if (p->type == TINSTR_EXPR_RETURN) {
					r = ERROR_RETURN;
					if (pval == NULL) {
						outln_error_code(r);
						num_destruct(&num);
					} else {
						*pval = num;
					}
					pnext = NULL;
				} else
					num_destruct(&num);
				break;
			case TINSTR_STR:
				out(L_ENFORCE, "%s", p->str);
				break;
			case TINSTR_LOOP:
				loop = &p->loop;

					/* First term of 3-term for() */
				num = num_undefvalue();
				if ((r = expr_eval(loop->exprbefore, &num)) != ERROR_NONE)
					break;
				num_destruct(&num);

				while (TRUE) {

						/* Second term of a 3-term for() or test part of a while() */
					if (loop->testbefore != NULL) {
						num = num_undefvalue();
						if ((r = expr_eval(loop->testbefore, &num)) != ERROR_NONE)
							break;
						b = num_is_zero(num);
						num_destruct(&num);
						if (b)
							break;
					}

						/* The content of the loop being executed, for every loops realms */
					r = program_execute(loop->core, pval);
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
						if ((r = expr_eval(loop->testafter, &num)) != ERROR_NONE)
							break;
						b = num_is_zero(num);
						num_destruct(&num);
						if (b)
							break;
					}

						/* Third term of a 3-term for() */
					num = num_undefvalue();
					if ((r = expr_eval(loop->exprafter, &num)) != ERROR_NONE)
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
				ifseq = &p->ifseq;

					/* PART 1 - TEST */

				num = num_undefvalue();
				if ((r = expr_eval(ifseq->expr, &num)) != ERROR_NONE)
					break;
				b = num_is_zero(num);
				num_destruct(&num);

					/* PART 2 - IF or ELSE execution*/
				if (!b)
					r = program_execute(ifseq->pif, pval);
				else
					r = program_execute(ifseq->pelse, pval);

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
	/*
	 * TODO - FIXME
	 * Will have to store list' tail in the head, to avoid systematical walk
	 * through to append one instruction. Could seem as a "nice to have" optimization
	 * but NOT doing it will make the creation of programs O(n^2) instead of
	 * O(n), becoming a bug in case of very big size entry.
	 */
	out_dbg("Chaining one program, base: %lu, append: %lu\n", base, append);
	if (append == NULL)
		return base;
	if (base == NULL) {
		return append;
	} else {
		program_t *p = base;
		while (p->next != NULL)
			p = p->next;
		p->next = append;
	}
	return base;
}

