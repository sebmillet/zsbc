/*
 * =====================================================================================
 *
 *       Filename:  expr.c
 *
 *    Description:  Manage expressions with expr_t structure.
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


#include "expr.h"
#include "vars.h"

/*#include <string.h>*/

int expr_count_ref = 0;

static void destruct_number(expr_t *self);
static void destruct_getvar(expr_t *self);
static void destruct_setvar(expr_t *self);
static void destruct_builtin_op(expr_t *self);

static int eval_number(const expr_t *self, const numptr *value_args, numptr value);
static int eval_getvar(const expr_t *self, const numptr *value_args, numptr value);
static int eval_setvar(const expr_t *self, const numptr *value_args, numptr value);
static int eval_builtin_op(const expr_t *self, const numptr *value_args, numptr value);

static void (*table_destruct[])(expr_t *self) = {
	destruct_number,	/* TNODE_NUMBER */
	destruct_getvar,	/* TNODE_GETVAR */
	destruct_setvar,	/* TNODE_SETVAR */
	destruct_builtin_op	/* TNODE_BUILTIN_OP */
};

static int (*table_eval[])(const expr_t *self, const numptr *value_args, numptr value) = {
	eval_number,		/* TNODE_NUMBER */
	eval_getvar,		/* TNODE_GETVAR */
	eval_setvar,		/* TNODE_SETVAR */
	eval_builtin_op		/* TNODE_BUILTIN_OP */
};

static void destruct_number(expr_t *self)
{
	num_destruct(self->num);
}

static void destruct_getvar(expr_t *self) { }

static void destruct_setvar(expr_t *self) { }

static void destruct_builtin_op(expr_t *self) { }

void expr_destruct(expr_t *self)
{
	out_dbg("Destructing expression, type: %d, #args: %d\n", self->type, self->nb_args);
	int i;
	for (i = 0; i < self->nb_args; ++i)
		expr_destruct(self->args[i]);

	(table_destruct[self->type])(self);

	free(self);
	self = NULL;

	--expr_count_ref;
}

static expr_t *expr_construct(expr_node_t type, int nb_args)
{
	out_dbg("Constructing expression, type: %d, #args: %d\n", type, nb_args);
	expr_t *self = (expr_t *)malloc(sizeof(expr_t));
	self->type = type;
	self->nb_args = nb_args;
	int i;
	for (i = 0; i < nb_args; ++i)
		self->args[i] = NULL;
	++expr_count_ref;
	return self;
}

expr_t *expr_const_number(numptr num)
{
	expr_t *self = expr_construct(TNODE_NUMBER, 0);
	self->num = num;
	return self;
}

expr_t *expr_const_getvar(char *varname)
{
	expr_t *self =  expr_construct(TNODE_GETVAR, 0);
	self->varname = varname;
	return self;
}

expr_t *expr_const_setvar(char *varname, expr_t *e1)
{
	expr_t *self = expr_construct(TNODE_SETVAR, 1);
	self->varname = varname;
	self->args[0] = e1;
	return self;
}

expr_t *expr_const_op1(builtin_id builtin, expr_t *e1)
{
	expr_t *self = expr_construct(TNODE_BUILTIN_OP, 1);
	self->builtin = builtin;
	self->args[0] = e1;
	return self;
}

expr_t *expr_const_op2(builtin_id builtin, expr_t *e1, expr_t *e2)
{
	expr_t *self = expr_construct(TNODE_BUILTIN_OP, 2);
	self->builtin = builtin;
	self->args[0] = e1;
	self->args[1] = e2;
	return self;
}

expr_t *expr_const_op2_and_setvar(char *varname, builtin_id builtin, expr_t *e1)
{
	expr_t *evar = expr_const_getvar(varname);
	expr_t *etop = expr_const_op2(builtin, evar, e1);
	return expr_const_setvar(varname, etop);
}

int expr_eval(const expr_t *self, numptr value)
{
	out_dbg("Evaluating expression, type: %d, #args: %d\n", self->type, self->nb_args);
	numptr *value_args = NULL;
	if (self->nb_args >= 1)
		value_args = malloc(sizeof(numptr) * (unsigned)self->nb_args);
	int i;
	int r;
	for (i = 0; i < self->nb_args; ++i)
		value_args[i] = num_construct();
	for (i = 0; i < self->nb_args; ++i) {
		if ((r = expr_eval(self->args[i], value_args[i])) != ERR_NONE)
			break;
	}
	if (r == ERR_NONE) {
		r = (table_eval[self->type])(self, (const numptr *)value_args, value);
	}
	for (i = 0; i < self->nb_args; ++i)
		num_destruct(value_args[i]);
	if (value_args != NULL)
		free(value_args);
	return r;
}

static int eval_number(const expr_t *self, const numptr *value_args, numptr value)
{
	assert(self->type == TNODE_NUMBER);
	assert(self->nb_args == 0);
	assert(value_args == NULL);
	num_copy(value, self->num);
	return 0;
}

static int eval_getvar(const expr_t *self, const numptr *value_args, numptr value)
{
	assert(self->type == TNODE_GETVAR);
	assert(self->nb_args == 0);
	assert(value_args == NULL);
	numptr *pnum = vars_get_value(self->varname);
	if (pnum == NULL)
		num_reset(value);
	else
		num_copy(value, *pnum);
	return 0;
}

static int eval_setvar(const expr_t *self, const numptr *value_args, numptr value)
{
	assert(self->type == TNODE_SETVAR);
	assert(self->nb_args == 1);
	assert(value_args != NULL);
	vars_set_value(self->varname, value_args[0]);
	num_copy(value, value_args[0]);
	return 0;
}

static int eval_builtin_op(const expr_t *self, const numptr *value_args, numptr value)
{
	assert(self->type == TNODE_BUILTIN_OP);
	switch (self->builtin) {
		case FN_ADD:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_add(value, value_args[0], value_args[1]);
		case FN_SUB:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_sub(value, value_args[0], value_args[1]);
		case FN_MUL:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_mul(value, value_args[0], value_args[1]);
		case FN_DIV:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_div(value, value_args[0], value_args[1]);
		case FN_POW:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_pow(value, value_args[0], value_args[1]);
		case FN_MOD:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_mod(value, value_args[0], value_args[1]);
		case FN_NEG:
			assert(self->nb_args == 1 && value_args != NULL);
			return num_neg(value, value_args[0]);
		default:
			assert(0);
	}
}

int expr_get_count_ref() { return expr_count_ref; }

