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

#include <string.h>


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
	ENODE_MIN = 0,
	ENODE_NUMBER = 0,
	ENODE_GETVAR = 1,
	ENODE_SETVAR = 2,
	ENODE_SETVAR_POSTFIX = 3,
	ENODE_BUILTIN_OP = 4,
	ENODE_MAX = 4
} enode_t;

const char *ENODE_TYPES[] = {
	"ENODE_NUMBER",
	"ENODE_GETVAR",
	"ENODE_SETVAR",
	"ENODE_SETVAR_POSTFIX",
	"ENODE_BUILTIN_OP"
};

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

static void copy_number(expr_t *dst, const expr_t *src);
static void copy_getvar(expr_t *dst, const expr_t *src);
static void copy_setvar(expr_t *dst, const expr_t *src);
static void copy_builtin_op(expr_t *dst, const expr_t *src);

static int eval_number(const expr_t *self, const numptr *value_args, numptr *pval);
static int eval_getvar(const expr_t *self, const numptr *value_args, numptr *pval);
static int eval_setvar(const expr_t *self, const numptr *value_args, numptr *pval);
static int eval_builtin_op(const expr_t *self, const numptr *value_args, numptr *pval);

static void (*table_destruct[])(expr_t *self) = {
	destruct_number,		/* ENODE_NUMBER */
	destruct_getvar,		/* ENODE_GETVAR */
	destruct_setvar,		/* ENODE_SETVAR */
	destruct_setvar,		/* ENODE_SETVAR_POSTFIX */
	destruct_builtin_op		/* ENODE_BUILTIN_OP */
};

static void (*table_copy[])(expr_t *dst, const expr_t *src) = {
	copy_number,			/* ENODE_NUMBER */
	copy_getvar,			/* ENODE_GETVAR */
	copy_setvar,			/* ENODE_SETVAR */
	copy_setvar,			/* ENODE_SETVAR_POSTFIX */
	copy_builtin_op			/* ENODE_BUILTIN_OP */
};

static int (*table_eval[])(const expr_t *self, const numptr *value_args, numptr *pval) = {
	eval_number,			/* ENODE_NUMBER */
	eval_getvar,			/* ENODE_GETVAR */
	eval_setvar,			/* ENODE_SETVAR */
	eval_setvar,			/* ENODE_SETVAR_POSTFIX */
	eval_builtin_op			/* ENODE_BUILTIN_OP */
};

static void destruct_number(expr_t *self)
{
	num_destruct(&self->num);
}

static void destruct_getvar(expr_t *self)
{
	free(self->varname);
}

static void destruct_setvar(expr_t *self)
{
	free(self->varname);
}

static void destruct_builtin_op(expr_t *self) { }

void expr_destruct(expr_t *self)
{
	if (self == NULL)
		return;

	assert(self->type >= ENODE_MIN && self->type <= ENODE_MAX);

	out_dbg("expr_t destruct,  address: %lu, type: %s, #args: %d\n", self, ENODE_TYPES[self->type], self->nb_args);
	int i;
	for (i = 0; i < self->nb_args; ++i) {
		out_dbg("\t%lu -> call args[%d] destruct, address: %lu\n", self, i, self->args[i]);
		expr_destruct(self->args[i]);
	}

	(table_destruct[self->type])(self);

	free(self);
	self = NULL;

	--expr_count_ref;
}

static expr_t *expr_construct(enode_t type, int nb_args)
{
	expr_t *self = (expr_t *)malloc(sizeof(expr_t));
	self->type = type;
	self->nb_args = nb_args;
	int i;
	for (i = 0; i < nb_args; ++i)
		self->args[i] = NULL;
	++expr_count_ref;
	out_dbg("expr_t construct, address: %lu, type: %s, #args: %d\n", self, ENODE_TYPES[type], nb_args);
	return self;
}

static expr_t *expr_copy(const expr_t *src)
{
	if (src == NULL)
		return NULL;

	expr_t *copy = expr_construct(src->type, src->nb_args);

	(table_copy[copy->type])(copy, src);

	int i;
	for (i = 0; i < copy->nb_args; ++i)
		copy->args[i] = expr_copy(src->args[i]);
	return copy;
}

static void copy_number(expr_t *dst, const expr_t *src)
{
	dst->num = num_construct_from_num(src->num);
}

static void copy_getvar(expr_t *dst, const expr_t *src)
{
	s_alloc_and_copy(&dst->varname, src->varname);
}

static void copy_setvar(expr_t *dst, const expr_t *src)
{
	s_alloc_and_copy(&dst->varname, src->varname);
}

static void copy_builtin_op(expr_t *dst, const expr_t *src)
{
	dst->builtin = src->builtin;
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

	/*
	 * is_postfix option is used to cause the old value of var to be returned,
	 * useful to calculate var++ and var--
	 */
static expr_t *construct_setvar(const char *varname, int is_postfix, expr_t *index, expr_t *e1)
{
	expr_t *self = expr_construct(is_postfix ? ENODE_SETVAR_POSTFIX : ENODE_SETVAR, 2);
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

expr_t *expr_construct_op2(const char *op, expr_t *e1, expr_t *e2)
{
	builtin_id id = FN_UNDEF;
	if (!strcmp(op, "+"))
		id = FN_ADD;
	else if (!strcmp(op, "-"))
		id = FN_SUB;
	else if (!strcmp(op, "*"))
		id = FN_MUL;
	else if (!strcmp(op, "/"))
		id = FN_DIV;
	else if (!strcmp(op, "^"))
		id = FN_POW;
	else if (!strcmp(op, "%"))
		id = FN_MOD;
	else if (!strcmp(op, "&&"))
		id = FN_AND;
	else if (!strcmp(op, "||"))
		id = FN_OR;
	else if (!strcmp(op, "<"))
		id = FN_CMPLT;
	else if (!strcmp(op, "<="))
		id = FN_CMPLE;
	else if (!strcmp(op, ">"))
		id = FN_CMPGT;
	else if (!strcmp(op, ">="))
		id = FN_CMPGE;
	else if (!strcmp(op, "=="))
		id = FN_CMPEQ;
	else if (!strcmp(op, "!="))
		id = FN_CMPNE;
	else
		FATAL_ERROR("Unknown operator: '%s'", op);

	expr_t *self = expr_construct(ENODE_BUILTIN_OP, 2);
	self->builtin = id;
	self->args[0] = e1;
	self->args[1] = e2;
	return self;
}

expr_t *expr_construct_setvar(const char *varname, expr_t *index, const char *op, expr_t *e1)
{
	if (!strcmp(op, "=")) {
		return construct_setvar(varname, FALSE, index, e1);
	} else {
		expr_t *evar = expr_construct_getvar(varname, index);

		char rewritten_op[10];
		s_strncpy(rewritten_op, op, sizeof(rewritten_op));
		if (rewritten_op[strlen(rewritten_op) - 1] == '=')
			rewritten_op[strlen(rewritten_op) - 1] = '\0';

		expr_t *etop = expr_construct_op2(rewritten_op, evar, e1);
		return construct_setvar(s_alloc_and_copy(NULL, varname), FALSE, expr_copy(index), etop);
	}
}

expr_t *expr_construct_incdecvar(const char *varname, expr_t *index, const char *op, int is_postfix)
{
	int delta = 0;
	if (!strcmp(op, "++"))
		delta = 1;
	else if (!strcmp(op, "--"))
		delta = -1;
	else
		FATAL_ERROR("Unknown operator: '%s'", op);

	expr_t *evar = expr_construct_getvar(varname, index);
	expr_t *eone = expr_construct_number(num_construct_from_int(1));
	expr_t *calc = expr_construct_op2(delta < 0 ? "-" : "+", evar, eone);
	return construct_setvar(s_alloc_and_copy(NULL, varname), is_postfix, expr_copy(index), calc);
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

static void getvar(const char *varname, const numptr *numindex, numptr *pval)
{
	const numptr *pnum;
	if (numindex != NULL) {
		long int index = num_getlongint(*numindex);
		pnum = vars_array_get_value(varname, index);
	} else {
		pnum = vars_get_value(varname);
	}

	if (pnum == NULL)
		*pval = num_construct();
	else
		*pval = num_construct_from_num(*pnum);
}

static int eval_getvar(const expr_t *self, const numptr *value_args, numptr *pval)
{
	assert(self->type == ENODE_GETVAR && self->nb_args == 1 && value_args != NULL);
	assert(num_is_not_initialized(*pval));

	getvar(self->varname, self->args[0] == NULL ? NULL : &value_args[0], pval);

	return ERROR_NONE;
}

static int eval_setvar(const expr_t *self, const numptr *value_args, numptr *pval)
{
	int is_postfix = (self->type == ENODE_SETVAR_POSTFIX);
	assert((self->type == ENODE_SETVAR || self->type == ENODE_SETVAR_POSTFIX) && self->nb_args == 2 && value_args != NULL);
	assert(num_is_not_initialized(*pval));

	numptr oldvalue = num_undefvalue();
	if (is_postfix)
		getvar(self->varname, self->args[0] == NULL ? NULL : &value_args[0], &oldvalue);

	if (self->args[0] != NULL) {
		long int index = num_getlongint(value_args[0]);
		vars_array_set_value(self->varname, index, value_args[1]);
	} else {
		vars_set_value(self->varname, value_args[1]);
	}

	*pval = num_construct_from_num(is_postfix ? oldvalue : value_args[1]);

	if (is_postfix)
		num_destruct(&oldvalue);

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

