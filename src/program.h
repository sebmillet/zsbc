/*
 * =====================================================================================
 *
 *       Filename:  program.h
 *
 *    Description:  Header file of program.c
 *
 *        Version:  1.0
 *        Created:  27/06/2015 08:25:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet (smt), milletseb@laposte.net
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef PROGRAM_H
#define PROGRAM_H

#include "common.h"
#include "numwrap.h"
#include "expr.h"

struct program_t;
typedef struct program_t program_t;

typedef struct program_loop_t {
	expr_t *exprbefore;
	expr_t *testbefore;
	program_t *core;
	expr_t *testafter;
	expr_t *exprafter;
} program_loop_t;

typedef struct program_ifseq_t {
	expr_t *expr;
	program_t *pif;
	program_t *pelse;
} program_ifseq_t;

program_t *program_construct_expr(expr_t *e, int is_assignment, const code_location_t loc);
program_t *program_construct_str(const char *s, const code_location_t loc);
program_t *program_construct_loop(program_loop_t *loop, const code_location_t loc);
program_t *program_construct_return(expr_t *e, const code_location_t loc);
program_t *program_construct_continue(const code_location_t loc);
program_t *program_construct_break(const code_location_t loc);
program_t *program_construct_ifseq(program_ifseq_t *ifseq, const code_location_t loc);
program_t *program_construct_autolist(defargs_t *defargs, const code_location_t loc);
void program_gather_defargs(defargs_t **pdefargs, program_t **pprogram);

void program_destruct(program_t *p);

int program_execute(program_t *p, numptr *pval, exec_ctx_t *pexec_ctx);
program_t *program_chain(program_t *base, program_t *append);

void program_notify_is_part_of_print(program_t *program);

void program_check(program_t *p, exec_ctx_t *pexec_ctx, check_t *check);

#endif	/* PROGRAM_H */

