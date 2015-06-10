/* expr.c */

/* Sébastien Millet 2015 */

#include "common.h"
#include "expr.h"
#include <gmp.h>
#include <string.h>

int expr_count_ref = 0;

static void destruct_number(expr_t *e)
{
	mpz_clear(*e->mp);

	free(e->mp);
	e->mp = NULL;
}

static void destruct_variable(expr_t *e) { }

static void destruct_builtin_function(expr_t *e) { }

static void (*table_destruct[])(expr_t *e) = {
	destruct_number,			/* TNODE_NUMBER */
	destruct_variable,			/* TNODE_VARIABLE */
	destruct_builtin_function	/* TNODE_BUILTIN_FUNCTION */
};

void expr_destruct(expr_t *e)
{
	int i;
	for (i = 0; i < e->nb_args; ++i)
		expr_destruct(e->args[i]);

	(table_destruct[e->type])(e);

	free(e);
	e = NULL;

	--expr_count_ref;
}

static expr_t *expr_construct(expr_node_t type, int nb_args)
{
	expr_t *e = (expr_t *)malloc(sizeof(expr_t));
	e->type = type;
	e->nb_args = nb_args;
	int i;
	for (i = 0; i < nb_args; ++i)
		e->args[i] = NULL;
	++expr_count_ref;
	return e;
}

expr_t *expr_const_number(mpz_t *mp)
{
	expr_t *e = expr_construct(TNODE_NUMBER, 0);
	e->mp = mp;
	return e;
}

expr_t *expr_const_getvar(char *varname)
{
	expr_t *e =  expr_construct(TNODE_GETVAR, 0);
	e->varname = varname;
	return e;
}

expr_t *expr_const_setvar(char *varname, expr_t *e1)
{
	expr_t *e = expr_construct(TNODE_SETVAR, 1);
	e->varname = varname;
	e->args[0] = e1;
	return e;
}

expr_t *expr_const_op1(function_t fn, expr_t *e1)
{
	expr_t *e = expr_construct(TNODE_BUILTIN_OP, 1);
	e->fn = fn;
	e->args[0] = e1;
	return e;
}

expr_t *expr_const_op2(function_t fn, expr_t *e1, expr_t *e2)
{
	expr_t *e = expr_construct(TNODE_BUILTIN_OP, 2);
	e->fn = fn;
	e->args[0] = e1;
	e->args[1] = e2;
	return e;
}

expr_t *expr_const_op2_and_setvar(char *varname, function_t fn, expr_t *e)
{
	expr_t *evar = expr_const_getvar(varname);
	expr_t *etop = expr_const_op2(fn, evar, e);
	return expr_const_setvar(varname, etop);
}

