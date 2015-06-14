/*
 * =====================================================================================
 *
 *       Filename:  expr.h
 *
 *    Description:  Header file of expr.c.
 *
 *        Version:  1.0
 *        Created:  07/06/2015 20:25:40
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet (smt), milletseb@laposte.net
 *
 * =====================================================================================
 */


#ifndef EXPR_H
#define EXPR_H

#include "common.h"
#include "numwrap.h"

typedef enum {TNODE_NUMBER = 0, TNODE_GETVAR, TNODE_SETVAR, TNODE_BUILTIN_OP, TNODE_LAST = TNODE_BUILTIN_OP} expr_node_t;

typedef enum {FN_ADD, FN_SUB, FN_MUL, FN_DIV, FN_POW, FN_MOD, FN_NEG} builtin_id;

struct expr_t {
	expr_node_t type;
	union {
		char *varname;
		numptr num;
		builtin_id builtin;
	};
	int nb_args;
	struct expr_t *args[2];
};
typedef struct expr_t expr_t;

void expr_destruct(expr_t *self);

expr_t *expr_const_number(numptr num);
expr_t *expr_const_getvar(char *varname);
expr_t *expr_const_setvar(char *varname, expr_t *e1);
expr_t *expr_const_op1(builtin_id builtin, expr_t *e1);
expr_t *expr_const_op2(builtin_id builtin, expr_t *e1, expr_t *e2);
expr_t *expr_const_op2_and_setvar(char *varname, builtin_id builtin, expr_t *e1);

int expr_eval(const expr_t *self, numptr value);
int expr_get_count_ref();

#endif	/* EXPR_H */

