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

struct expr_t;
typedef struct expr_t expr_t;

typedef enum {CARG_EXPR, CARG_ARRAY} callarg_type_t;
struct callargs_t;
typedef struct callargs_t callargs_t;

struct token_keeper_t;
typedef struct token_keeper_t token_keeper_t;

void expr_destruct(expr_t *self);

expr_t *expr_construct_number(numptr num);
expr_t *expr_construct_getvar(const char *varname, expr_t *index);
expr_t *expr_construct_setvar(const char *varname, expr_t *index, const char *op, int is_postfix, expr_t *e1);
expr_t *expr_construct_op1_str(const char *op, expr_t *e1);
expr_t *expr_construct_op2_str(const char *op, expr_t *e1, expr_t *e2);

callargs_t *callargs_construct(callarg_type_t type, expr_t *e, const char *array_name);
callargs_t *callargs_chain(callargs_t *base, callargs_t *append);
void callargs_chain_destruct(callargs_t *cargs);

expr_t *expr_construct_function_call(const char *fcnt_name, callargs_t *callargs);

int expr_is_constant(const expr_t *e);
int expr_eval(const expr_t *self, numptr *pval);
int expr_get_count_ref();

#endif	/* EXPR_H */

