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

program_t *program_construct_expr(expr_t *e, int is_assignment);
program_t *program_construct_string(const char *s);
program_t *program_construct_loop(program_loop_t *loop);
void program_destruct(program_t *p);

int program_execute(program_t *p);
program_t *program_chain(program_t *base, program_t *append);

#endif	/* PROGRAM_H */

