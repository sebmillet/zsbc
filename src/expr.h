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

typedef enum {FN_ADD, FN_SUB, FN_MUL, FN_DIV, FN_POW, FN_MOD, FN_NEG,
	FN_CMPLT, FN_CMPLE, FN_CMPGT, FN_CMPGE, FN_CMPEQ, FN_CMPNE, FN_OR, FN_AND, FN_NOT} builtin_id;

struct expr_t;
typedef struct expr_t expr_t;

void expr_destruct(expr_t *self);

expr_t *expr_construct_number(numptr num);
expr_t *expr_construct_getvar(char *varname);
expr_t *expr_construct_setvar(char *varname, expr_t *e1);
expr_t *expr_construct_op1(builtin_id builtin, expr_t *e1);
expr_t *expr_construct_op2(builtin_id builtin, expr_t *e1, expr_t *e2);
expr_t *expr_construct_op2_and_setvar(char *varname, builtin_id builtin, expr_t *e1);

int expr_eval(const expr_t *self, numptr *pval);
int expr_get_count_ref();

#endif	/* EXPR_H */

