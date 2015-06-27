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

typedef enum {TINSTR_EXPR, TINSTR_ASSIGN_EXPR, TINSTR_STRING, TINSTR_LOOP} instr_t;

struct program_t {
	instr_t type;

	union {
		expr_t *expr;			/* TINSTR_EXPR */
		char *str;				/* TINSTR_STRING */
		program_loop_t loop;	/* TINSTR_LOOP */
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
	program_t *p = program_construct(is_assignment ? TINSTR_ASSIGN_EXPR : TINSTR_EXPR);
	p->expr = e;
	out_dbg("Construct of one program of type %s, address = %lu\n", is_assignment ? "TINSTR_ASSIGN_EXPR" : "TINSTR_EXPR", p);
	return p;
}

program_t *program_construct_string(const char *s)
{
	program_t *p = program_construct(TINSTR_STRING);
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

void program_destruct(program_t *p)
{
	out_dbg("Entering program_destruct for %lu\n", p);
	program_t *pnext;
	while (p != NULL) {
		out_dbg("Starting to destruct one program instruction, address = %lu\n", p);
		switch (p->type) {
			case TINSTR_EXPR:
			case TINSTR_ASSIGN_EXPR:
				expr_destruct(p->expr);
				break;
			case TINSTR_STRING:
				free(p->str);
				break;
			case TINSTR_LOOP:
				program_destruct(p->loop.prgbefore);
				if (p->loop.expbefore != NULL)
					expr_destruct(p->loop.expbefore);
				program_destruct(p->loop.core);
				if (p->loop.expafter != NULL)
					expr_destruct(p->loop.expafter);
				program_destruct(p->loop.prgafter);
				break;
			default:
				assert(0);
		}
		out_dbg("Done destructing one program instruction, going to next instruction\n");
		pnext = p->next;
		free(p);
		p = pnext;
	}
}

int program_execute(program_t *p)
{
	out_dbg("Entering program_execute for %lu\n", p);
	int r = ERROR_NONE;
	while (p != NULL && r == ERROR_NONE) {
		out_dbg("Executing one instruction, type: %d, address: %lu\n", p->type, p);
		numptr num;
		program_loop_t *loop;
		int b;
		switch (p->type) {
			case TINSTR_EXPR:
			case TINSTR_ASSIGN_EXPR:
				num = num_undefvalue();
				r = expr_eval(p->expr, &num);
				if (r != 0) {
					outln_error_code(r);
				} else if (p->type == TINSTR_EXPR) {
					num_print(num, 10);
					outln(L_ENFORCE, "");
				}
				num_destruct(&num);
				break;
			case TINSTR_STRING:
				out(L_ENFORCE, "%s", p->str);
				break;
			case TINSTR_LOOP:
				loop = &p->loop;

					/* First term of 3-term for() */
				if ((r = program_execute(loop->prgbefore)) != ERROR_NONE)
					break;

				while (TRUE) {

						/* Second term of a 3-term for() or test part of a while() */
					if (loop->expbefore != NULL) {
						num = num_undefvalue();
						if ((r = expr_eval(loop->expbefore, &num)) != ERROR_NONE)
							break;
						b = num_is_zero(num);
						num_destruct(&num);
						if (b)
							break;
					}

						/* The content of the loop being executed, for every loops realms */
					if ((r = program_execute(loop->core)) != ERROR_NONE)
						break;

						/* Test part of a do ... while() */
					if (loop->expafter != NULL) {
						num = num_undefvalue();
						if ((r = expr_eval(loop->expafter, &num)) != ERROR_NONE)
							break;
						b = num_is_zero(num);
						num_destruct(&num);
						if (b)
							break;
					}

						/* Third term of a 3-term for() */
					if ((r = program_execute(loop->prgafter)) != ERROR_NONE)
						break;

				}
				break;
			default:
				assert(0);
		}
		out_dbg("Execution done, going to next instruction\n");
		p = p->next;
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

