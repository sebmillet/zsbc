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



/*-----------------------------------------------------------------------------
 *  expr_t management
 *-----------------------------------------------------------------------------*/



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
	ENODE_FUNCTION_CALL = 5,
	ENODE_MAX = 5
} enode_t;

const char *ENODE_TYPES[] = {
	"ENODE_NUMBER",
	"ENODE_GETVAR",
	"ENODE_SETVAR",
	"ENODE_SETVAR_POSTFIX",
	"ENODE_BUILTIN_OP",
	"ENODE_FUNCTION_CALL"
};

typedef enum {FN_UNDEF, FN_NOOP, FN_ADD, FN_SUB, FN_MUL, FN_DIV, FN_POW, FN_MOD, FN_NEG,
	FN_CMPLT, FN_CMPLE, FN_CMPGT, FN_CMPGE, FN_CMPEQ, FN_CMPNE, FN_OR, FN_AND, FN_NOT,
	FN_INC, FN_DEC} builtin_id;

typedef struct accessvar_t {
	char *name;
	expr_t *index;
	builtin_id builtin;
} accessvar_t;

typedef struct callargs_t {
	callarg_type_t type;
	union {
		expr_t *e;
		char *array_name;
	};
	struct callargs_t *next;
} callargs_t;

struct expr_t {
	enode_t type;
	union {
		accessvar_t var;
		numptr num;
		builtin_id builtin;
	};
	int nb_args;
	expr_t* *args;
};

static int expr_count_ref = 0;

static expr_t *expr_construct_op2_builtin_id(builtin_id id, expr_t *e1, expr_t *e2);
static expr_t *expr_construct_op1_builtin_id(builtin_id builtin, expr_t *e1);

static void destruct_number(expr_t *self);
static void destruct_getvar(expr_t *self);
static void destruct_setvar(expr_t *self);
static void destruct_builtin_op(expr_t *self);
static void destruct_function_call(expr_t *self);

static int eval_number(const expr_t *self, const numptr *value_args, numptr *pval);
static int eval_getvar(const expr_t *self, const numptr *value_args, numptr *pval);
static int eval_setvar(const expr_t *self, const numptr *value_args, numptr *pval);
static int eval_builtin_op(const expr_t *self, const numptr *value_args, numptr *pval);
static int eval_function_call(const expr_t *self, const numptr *value_args, numptr *pval);

static void (*table_destruct[])(expr_t *self) = {
	destruct_number,		/* ENODE_NUMBER */
	destruct_getvar,		/* ENODE_GETVAR */
	destruct_setvar,		/* ENODE_SETVAR */
	destruct_setvar,		/* ENODE_SETVAR_POSTFIX */
	destruct_builtin_op,	/* ENODE_BUILTIN_OP */
	destruct_function_call	/* ENODE_FUNCTION_CALL */
};

static int (*table_eval[])(const expr_t *self, const numptr *value_args, numptr *pval) = {
	eval_number,			/* ENODE_NUMBER */
	eval_getvar,			/* ENODE_GETVAR */
	eval_setvar,			/* ENODE_SETVAR */
	eval_setvar,			/* ENODE_SETVAR_POSTFIX */
	eval_builtin_op,		/* ENODE_BUILTIN_OP */
	eval_function_call		/* ENODE_FUNCTION_CALL */
};



/*-----------------------------------------------------------------------------
 *  Constructors and destructors part
 *-----------------------------------------------------------------------------*/



static void destruct_number(expr_t *self)
{
	num_destruct(&self->num);
}

static void destruct_getvar(expr_t *self)
{
	free(self->var.name);
	expr_destruct(self->var.index);
}

static void destruct_setvar(expr_t *self)
{
	free(self->var.name);
	expr_destruct(self->var.index);
}

static void destruct_builtin_op(expr_t *self) { }

static void destruct_function_call(expr_t *self) { }

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
	if (self->args != NULL) {
		free(self->args);
		self->args = NULL;
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
	if (nb_args >= 1)
		self->args = (expr_t **)malloc(sizeof(expr_t *) * nb_args);
	else
		self->args = NULL;
	int i;
	for (i = 0; i < nb_args; ++i)
		self->args[i] = NULL;
	++expr_count_ref;
	out_dbg("expr_t construct, address: %lu, type: %s, #args: %d\n", self, ENODE_TYPES[type], nb_args);
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
	expr_t *self =  expr_construct(ENODE_GETVAR, 0);
	self->var.name = (char *)varname;
	self->var.index = index;
		/* Good practice to have NOOP action for getvar (but not examined) */
	self->var.builtin = FN_NOOP;
	return self;
}

static expr_t *expr_construct_op1_builtin_id(builtin_id builtin, expr_t *e1)
{
	expr_t *self = expr_construct(ENODE_BUILTIN_OP, 1);
	self->builtin = builtin;
	self->args[0] = e1;
	return self;
}

expr_t *expr_construct_op1_str(const char *op, expr_t *e1)
{
	builtin_id id = FN_UNDEF;
	if (!strcmp(op, "-"))
		id = FN_NEG;
	else if (!strcmp(op, "!"))
		id = FN_NOT;
	else
		FATAL_ERROR("Unknown operator: '%s'", op);

	return expr_construct_op1_builtin_id(id, e1);
}

builtin_id str2builtin_id(const char *op)
{
	builtin_id id = FN_UNDEF;
	if (!strcmp(op, ""))
		id = FN_NOOP;
	else if (!strcmp(op, "+"))
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
	else if (!strcmp(op, "++"))
		id = FN_INC;
	else if (!strcmp(op, "--"))
		id = FN_DEC;
	return id;
}

static expr_t *expr_construct_op2_builtin_id(builtin_id id, expr_t *e1, expr_t *e2)
{
	expr_t *self = expr_construct(ENODE_BUILTIN_OP, 2);
	self->builtin = id;
	self->args[0] = e1;
	self->args[1] = e2;
	return self;
}

expr_t *expr_construct_op2_str(const char *op, expr_t *e1, expr_t *e2)
{
	builtin_id id = str2builtin_id(op);
	if (id == FN_UNDEF)
		FATAL_ERROR("Unknown operator: '%s'", op);

	return expr_construct_op2_builtin_id(id, e1, e2);
}

expr_t *expr_construct_setvar(const char *varname, expr_t *index, const char *op, int is_postfix, expr_t *e1)
{
	char rewritten_op[10];
	s_strncpy(rewritten_op, op, sizeof(rewritten_op));
	if (rewritten_op[strlen(rewritten_op) - 1] == '=')
		rewritten_op[strlen(rewritten_op) - 1] = '\0';

	builtin_id id = str2builtin_id(rewritten_op);
	if (id == FN_UNDEF)
		FATAL_ERROR("Unknown operator: '%s'", op);

	expr_t *self = expr_construct(is_postfix ? ENODE_SETVAR_POSTFIX : ENODE_SETVAR, 1);
	self->var.name = (char *)varname;
	self->var.index = index;
	self->var.builtin = id;
	self->args[0] = e1;
	return self;
}

callargs_t *callargs_construct(callarg_type_t type, expr_t *e, const char *array_name)
{
	callargs_t *callarg = (callargs_t *)malloc(sizeof(callargs_t));
	callarg->type = type;
	if (callarg->type == CARG_EXPR) {
		callarg->e = e;
	} else if (callarg->type == CARG_ARRAY) {
		callarg->array_name = (char *)array_name;
	} else
		FATAL_ERROR("Unknown call argument type: %d", callarg->type);
	return callarg;
}

callargs_t *callargs_chain(callargs_t *base, callargs_t *append)
{
	/*
	 * FIXME
	 * Should save the base in the list to avoid systematical walk through
	 * the entire list to append one element, that has O(n^2) execution time.
	 */
	assert(base != NULL && append != NULL);
	callargs_t *w = base;
	while (w->next != NULL)
		w = w->next;
	w->next = append;
	return base;
}

void callargs_destruct(callargs_t *callargs)
{
	callargs_t *w = callargs;
	callargs_t *wnext;
	while (w != NULL) {
		wnext = w->next;

		if (w->type == CARG_EXPR)
			expr_destruct(w->e);
		else if (w->type == CARG_ARRAY)
			FATAL_ERROR("%s", "Not done...");
		else
			FATAL_ERROR("Unknown call argument type, callargs_t: %lu, type: %d", w, w->type);

		free(w);
		w = wnext;
	}
}

expr_t *expr_construct_function_call(const char *fcnt_name, callargs_t *callargs)
{
	callargs_t *w = callargs;
	int n = 0;
	while (w != NULL) {
		++n;
		w = w->next;
	}
	expr_t *self = expr_construct(ENODE_FUNCTION_CALL, n);
	self->var.name = (char *)fcnt_name;
	int i;
	w = callargs;
	for (i = 0; i < n; ++i) {

		assert(w != NULL);

		self->args[i] = w->e; /*  FIXME - at the moment, ignores CARG_ARRAY case */
		w = w->next;
	}

	assert(w == NULL);

	return self;
}



/*-----------------------------------------------------------------------------
 *  Evaluation part
 *-----------------------------------------------------------------------------*/



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

			/*  Can happen with a void function, defined as is:
			 *    define void f(...)
			 *  */
		if (num_is_not_initialized(value_args[i]))
			value_args[i] = num_construct();

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

static int getindex(expr_t *index, long int *pidxval)
{
	int has_index = (index != NULL);
	if (has_index) {
		numptr num = num_undefvalue();
		int r = expr_eval(index, &num);
		if (r != ERROR_NONE)
			return r;
		*pidxval = num_getlongint(num);
		num_destruct(&num);
	}
	return ERROR_NONE;
}

static void getvar(const char *varname, int has_index, long int idxval, numptr *pval)
{
	const numptr *pnum;
	if (has_index) {
		pnum = vars_array_get_value(varname, idxval);
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
	assert(self->type == ENODE_GETVAR && self->nb_args == 0 && value_args == NULL);
	assert(num_is_not_initialized(*pval));

	int has_index = self->var.index != NULL;

	long int idxval;
	int r;
	if ((r = getindex(self->var.index, &idxval)) != ERROR_NONE)
		return r;
	getvar(self->var.name, has_index, idxval, pval);
	return ERROR_NONE;
}

static int eval_setvar(const expr_t *self, const numptr *value_args, numptr *pval)
{
	int is_postfix = (self->type == ENODE_SETVAR_POSTFIX);
	assert((self->type == ENODE_SETVAR || self->type == ENODE_SETVAR_POSTFIX) && self->nb_args == 1 && value_args != NULL);
	assert(num_is_not_initialized(*pval));

	int has_index = self->var.index != NULL;
	long int idxval;

	numptr val = num_undefvalue();
	int val_is_to_be_destructed = FALSE;
	numptr res = num_undefvalue();
	int res_is_to_be_destructed = FALSE;
	const numptr *presult = NULL;

	int r = getindex(self->var.index, &idxval);
	if (r != ERROR_NONE)
		return r;

	if (self->var.builtin == FN_NOOP)
		presult = &value_args[0];
	else {
		getvar(self->var.name, has_index, idxval, &val);
		val_is_to_be_destructed = TRUE;
		numptr valcopy = num_construct_from_num(val);
		expr_t *exprval = expr_construct_number(valcopy);
		expr_t *etmp;
		if (self->args[0] == NULL) {
			etmp = expr_construct_op1_builtin_id(self->var.builtin, exprval);
		} else {
			expr_t *earg0 = expr_construct_number(num_construct_from_num(value_args[0]));
			etmp = expr_construct_op2_builtin_id(self->var.builtin, exprval, earg0);
		}
		r = expr_eval(etmp, &res);
		res_is_to_be_destructed = TRUE;
		expr_destruct(etmp);
		presult = &res;
	}

	if (r == ERROR_NONE) {
		if (has_index) {
			vars_array_set_value(self->var.name, idxval, *presult);
		} else {
			vars_set_value(self->var.name, *presult);
		}
		*pval = num_construct_from_num(is_postfix ? val : *presult);
	}

	if (res_is_to_be_destructed)
		num_destruct(&res);
	if (val_is_to_be_destructed)
		num_destruct(&val);

	return r;
}

static int eval_builtin_op(const expr_t *self, const numptr *value_args, numptr *pval)
{
	assert(self->type == ENODE_BUILTIN_OP);
	assert(num_is_not_initialized(*pval));

	numptr numone;
	int r;
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
		case FN_INC:
			assert(self->nb_args == 1 && value_args != NULL);
			numone = num_construct_from_int(1);
			r = num_add(pval, value_args[0], numone);
			num_destruct(&numone);
			return r;
		case FN_DEC:
			assert(self->nb_args == 1 && value_args != NULL);
			numone = num_construct_from_int(1);
			r = num_sub(pval, value_args[0], numone);
			num_destruct(&numone);
			return r;
		default:
			assert(0);
	}
}

static int eval_function_call(const expr_t *self, const numptr *value_args, numptr *pval)
{
	assert(self->type == ENODE_FUNCTION_CALL);
	assert(num_is_not_initialized(*pval));

	function_t *f;
	if ((f = vars_get_function(self->var.name)) == NULL)
		return ERROR_FUNCTION_NOT_DEFINED;

	int n = 0;
	defargs_t *darg = f->defargs;
	while (darg != NULL) {
		darg = darg->next;
		++n;
	}
	if (self->nb_args != n)
		return ERROR_PARAMETER_NUMBER_MISMATCH;

	vars_keeper_t *keeper;
	if (n >= 1)
		keeper = (vars_keeper_t *)malloc(sizeof(vars_keeper_t) * n);
	else
		keeper = NULL;

	vars_value_t nv;
	darg = f->defargs;
	int i;
	for (i = 0; i < n; ++i) {

		assert(darg != NULL);

		if (darg->type == DARG_VALUE) {
			nv.type = TYPE_NUM;
			nv.num = num_construct_from_num(value_args[i]);
			vars_send_to_keeper(&keeper[i], darg->name, &nv);
		} else
			assert(0);	/* FIXME - to be implemented... */
		darg = darg->next;
	}

	assert(darg == NULL);

	int r = program_execute(f->program, pval);
	if (r == ERROR_NONE) {
		if (!num_is_not_initialized(*pval) && f->is_void) {
			num_destruct(pval);
			*pval = num_undefvalue();
		} else if (num_is_not_initialized(*pval) && !f->is_void) {
			*pval = num_construct();
		}
	}

	darg = f->defargs;
	for (i = 0; i < n; ++i) {

		assert(darg != NULL);

		if (darg->type == DARG_VALUE) {
			vars_recall_from_keeper(darg->name, &keeper[i]);
		} else
			assert(0);	/* FIXME - to be implemented... */
		darg = darg->next;
	}
	assert(darg == NULL);

	if (keeper != NULL)
		free(keeper);

	return r;
}

int expr_get_count_ref() { return expr_count_ref; }

