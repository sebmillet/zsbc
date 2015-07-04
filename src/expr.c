/*
 * =====================================================================================
 *
 *       Filename:  expr.c
 *
 *    Description:  Manages expressions with expr_t structure and provides
 *    				functions to *evaluate* it.
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

	/*
	 *  	***********
	 *  	* WARNING *
	 *  	***********
	 *
	 *  The constants below are used, with these values, to address
	 *  the elements of the following arrays:
	 *  	table_destruct
	 *  	table_eval
	 *
	*/

typedef enum {
	ENODE_NUMBER = 0,
	ENODE_GETVAR = 1,
	ENODE_SETVAR = 2,
	ENODE_BUILTIN_OP = 3
} enode_t;

struct expr_t {
	enode_t type;
	union {
		char *varname;
		numptr num;
		builtin_id builtin;
	};
	int nb_args;
	expr_t *args[2];
};

static int expr_count_ref = 0;

static void destruct_number(expr_t *self);
static void destruct_getvar(expr_t *self);
static void destruct_setvar(expr_t *self);
static void destruct_builtin_op(expr_t *self);

static int eval_number(const expr_t *self, const numptr *value_args, numptr *pval);
static int eval_getvar(const expr_t *self, const numptr *value_args, numptr *pval);
static int eval_setvar(const expr_t *self, const numptr *value_args, numptr *pval);
static int eval_builtin_op(const expr_t *self, const numptr *value_args, numptr *pval);

static void (*table_destruct[])(expr_t *self) = {
	destruct_number,		/* ENODE_NUMBER */
	destruct_getvar,		/* ENODE_GETVAR */
	destruct_setvar,		/* ENODE_SETVAR */
	destruct_builtin_op		/* ENODE_BUILTIN_OP */
};

static int (*table_eval[])(const expr_t *self, const numptr *value_args, numptr *pval) = {
	eval_number,			/* ENODE_NUMBER */
	eval_getvar,			/* ENODE_GETVAR */
	eval_setvar,			/* ENODE_SETVAR */
	eval_builtin_op			/* ENODE_BUILTIN_OP */
};

static void destruct_number(expr_t *self)
{
	num_destruct(&self->num);
}

static void destruct_getvar(expr_t *self) { }

static void destruct_setvar(expr_t *self) { }

static void destruct_builtin_op(expr_t *self) { }

void expr_destruct(expr_t *self)
{
	if (self == NULL)
		return;

	out_dbg("Destructing expression, type: %d, #args: %d\n", self->type, self->nb_args);
	int i;
	for (i = 0; i < self->nb_args; ++i)
		expr_destruct(self->args[i]);

	(table_destruct[self->type])(self);

	free(self);
	self = NULL;

	--expr_count_ref;
}

static expr_t *expr_construct(enode_t type, int nb_args)
{
	out_dbg("Constructing one expression, type: %d, #args: %d\n", type, nb_args);
	expr_t *self = (expr_t *)malloc(sizeof(expr_t));
	self->type = type;
	self->nb_args = nb_args;
	int i;
	for (i = 0; i < nb_args; ++i)
		self->args[i] = NULL;
	++expr_count_ref;
	return self;
}

expr_t *expr_construct_number(numptr num)
{
	expr_t *self = expr_construct(ENODE_NUMBER, 0);
	self->num = num;
	return self;
}

expr_t *expr_construct_getvar(const char *varname, expr_t *index)
{
	expr_t *self =  expr_construct(ENODE_GETVAR, 1);
	self->varname = (char *)varname;
	self->args[0] = index;
	return self;
}

expr_t *expr_construct_setvar(const char *varname, expr_t *index, expr_t *e1)
{
	expr_t *self = expr_construct(ENODE_SETVAR, 2);
	self->varname = (char *)varname;
	self->args[0] = index;
	self->args[1] = e1;
	return self;
}

expr_t *expr_construct_op1(builtin_id builtin, expr_t *e1)
{
	expr_t *self = expr_construct(ENODE_BUILTIN_OP, 1);
	self->builtin = builtin;
	self->args[0] = e1;
	return self;
}

expr_t *expr_construct_op2(builtin_id builtin, expr_t *e1, expr_t *e2)
{
	expr_t *self = expr_construct(ENODE_BUILTIN_OP, 2);
	self->builtin = builtin;
	self->args[0] = e1;
	self->args[1] = e2;
	return self;
}

expr_t *expr_construct_op2_and_setvar(const char *varname, builtin_id builtin, expr_t *index, expr_t *e1)
{
	expr_t *evar = expr_construct_getvar(varname, index);
	expr_t *etop = expr_construct_op2(builtin, evar, e1);
	return expr_construct_setvar(varname, index, etop);
}

int expr_eval(const expr_t *self, numptr *pval)
{
	if (self == NULL) {
		*pval = num_undefvalue();
		return ERROR_NONE;
	}
	out_dbg("Evaluating expression, type: %d, #args: %d\n", self->type, self->nb_args);
	numptr *value_args = NULL;
	if (self->nb_args >= 1)
		value_args = malloc(sizeof(numptr) * (unsigned)self->nb_args);
	int i;
	int r = ERROR_NONE;
	for (i = 0; i < self->nb_args; ++i)
		value_args[i] = num_undefvalue();
	for (i = 0; i < self->nb_args; ++i) {
		if ((r = expr_eval(self->args[i], &value_args[i])) != ERROR_NONE)
			break;
	}
	if (r == ERROR_NONE) {
		r = (table_eval[self->type])(self, (const numptr *)value_args, pval);
	}
	for (i = 0; i < self->nb_args; ++i)
		num_destruct(&value_args[i]);
	if (value_args != NULL)
		free(value_args);
	return r;
}

static int eval_number(const expr_t *self, const numptr *value_args, numptr *pval)
{
	assert(self->type == ENODE_NUMBER && self->nb_args == 0 && value_args == NULL);
	assert(num_is_not_initialized(*pval));
	*pval = num_construct_from_num(self->num);
	return ERROR_NONE;
}

static int eval_getvar(const expr_t *self, const numptr *value_args, numptr *pval)
{
	assert(self->type == ENODE_GETVAR && self->nb_args == 1 && value_args != NULL);
	assert(num_is_not_initialized(*pval));

	const numptr *pnum;
	if (self->args[0] != NULL) {
		long int index = num_getlongint(value_args[0]);
		pnum = vars_array_get_value(self->varname, index);
	} else {
		pnum = vars_get_value(self->varname);
	}

	if (pnum == NULL)
		*pval = num_construct();
	else
		*pval = num_construct_from_num(*pnum);
	return ERROR_NONE;
}

static int eval_setvar(const expr_t *self, const numptr *value_args, numptr *pval)
{
	assert(self->type == ENODE_SETVAR && self->nb_args == 2 && value_args != NULL);
	assert(num_is_not_initialized(*pval));

	if (self->args[0] != NULL) {
		long int index = num_getlongint(value_args[0]);
		vars_array_set_value(self->varname, index, value_args[1]);
	} else {
		vars_set_value(self->varname, value_args[1]);
	}
	*pval = num_construct_from_num(value_args[1]);
	return ERROR_NONE;
}

static int eval_builtin_op(const expr_t *self, const numptr *value_args, numptr *pval)
{
	assert(self->type == ENODE_BUILTIN_OP);
	switch (self->builtin) {
		case FN_ADD:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_add(pval, value_args[0], value_args[1]);
		case FN_SUB:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_sub(pval, value_args[0], value_args[1]);
		case FN_MUL:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_mul(pval, value_args[0], value_args[1]);
		case FN_DIV:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_div(pval, value_args[0], value_args[1]);
		case FN_POW:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_pow(pval, value_args[0], value_args[1]);
		case FN_MOD:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_mod(pval, value_args[0], value_args[1]);
		case FN_NEG:
			assert(self->nb_args == 1 && value_args != NULL);
			return num_neg(pval, value_args[0]);

		case FN_CMPLT:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_cmplt(pval, value_args[0], value_args[1]);
		case FN_CMPLE:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_cmple(pval, value_args[0], value_args[1]);
		case FN_CMPGT:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_cmpgt(pval, value_args[0], value_args[1]);
		case FN_CMPGE:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_cmpge(pval, value_args[0], value_args[1]);
		case FN_CMPEQ:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_cmpeq(pval, value_args[0], value_args[1]);
		case FN_CMPNE:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_cmpne(pval, value_args[0], value_args[1]);
		case FN_AND:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_and(pval, value_args[0], value_args[1]);
		case FN_OR:
			assert(self->nb_args == 2 && value_args != NULL);
			return num_or(pval, value_args[0], value_args[1]);
		case FN_NOT:
			assert(self->nb_args == 1 && value_args != NULL);
			return num_not(pval, value_args[0]);

		default:
			assert(0);
	}
}

int expr_get_count_ref() { return expr_count_ref; }

