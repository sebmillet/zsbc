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

/* I prefer NOT to have a union here although it'd be possible... */
/*    union {*/
		expr_t *e;
		char *array_name;
/*    };*/

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
	callargs_t *cargs;
};

static int expr_count_ref = 0;

static void callarg_destruct(callargs_t *carg);
static void callarg_set_to_expr(callargs_t *carg, expr_t *e);

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
static int eval_builtin_function_call(const expr_t *self, const function_t *f, const numptr *value_args, numptr *pval);
static int eval_function_call(const expr_t *self, const function_t *f, numptr *pval);

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
	NULL					/* ENODE_FUNCTION_CALL - IT IS MANAGEd SEPARATELY FROM table_eval[] */
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
		out_dbg("\t%lu -> call args[%d] destruct, address: %lu\n", self, i, self->cargs[i]);
		callarg_destruct(&self->cargs[i]);
	}
	if (self->cargs != NULL) {
		free(self->cargs);
		self->cargs = NULL;
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
		self->cargs = (callargs_t *)malloc(sizeof(callargs_t) * nb_args);
	else
		self->cargs = NULL;
	int i;
	for (i = 0; i < nb_args; ++i) {
		self->cargs[i].e = NULL;
		self->cargs[i].array_name = NULL;	/* Necessary because e and array_name are not in a union (but they could be) */
	}
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
	callarg_set_to_expr(&self->cargs[0], e1);
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

static builtin_id str2builtin_id(const char *op)
{
	builtin_id id = FN_UNDEF;
	if (!strcmp(op, ""))
		id = FN_NOOP;	/* Corresponds to a simple assignment ex. a=0 */
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
	callarg_set_to_expr(&self->cargs[0], e1);
	callarg_set_to_expr(&self->cargs[1], e2);
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

/*
 * IMPORTANT
 *
 *   In certain circumstances e1 can be NULL.
 *   It occurs for assignment operators that do not need
 *   a right-hand side expression. It is the decrement
 *   and increment operators, examples:
 *     ++a
 *     b[2+1]--
 *
 *   Even in that case the callarg_t object is of type CARG_EXPR (but e1 is NULL)
 *
 * */

		/*
		 * In case it is a simple assignment, as in
		 *   a=0
		 * the rewritten_op will be an empty string,
		 * recognized by str2builtin_id as FN_NOOP.
		 * */
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
	callarg_set_to_expr(&self->cargs[0], e1);
	return self;
}

callargs_t *callargs_construct(callarg_type_t type, expr_t *e, const char *array_name)
{
	callargs_t *carg = (callargs_t *)malloc(sizeof(callargs_t));
	carg->type = type;
	if (carg->type == CARG_EXPR) {
		assert(array_name == NULL);	/* Linked to e and array_name not in a union... */
		carg->e = e;
		carg->array_name = NULL;
	} else if (carg->type == CARG_ARRAY) {
		assert(e == NULL);
		assert(array_name != NULL);
		carg->e = NULL;
		carg->array_name = (char *)array_name;	/* Linked to e and array_name not in a union... */
	} else
		FATAL_ERROR("Unknown call argument type: %d", carg->type);
	carg->next = NULL;
	return carg;
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

static void callarg_destruct(callargs_t *carg)
{
	if (carg->type == CARG_EXPR) {
		assert(carg->array_name == NULL);	/* Linked to e and array_name not in a union... */
		expr_destruct(carg->e);
	} else if (carg->type == CARG_ARRAY) {
		assert(carg->e == NULL);
		assert(carg->array_name != NULL);	/* Linked to e and array_name not in a union... */
		free(carg->array_name);
	} else
		FATAL_ERROR("Unknown call argument type: %d", carg->type);
}

void callargs_chain_destruct(callargs_t *cargs)
{
	callargs_t *w = cargs;
	callargs_t *wnext;
	while (w != NULL) {
		wnext = w->next;
		callarg_destruct(w);
		w = wnext;
	}
}

static void callarg_set_to_expr(callargs_t *carg, expr_t *e)
{
	carg->type = CARG_EXPR;
	carg->e = e;
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

		self->cargs[i] = *w;
		w = w->next;
	}

	assert(w == NULL);

	return self;
}



/*-----------------------------------------------------------------------------
 *  Evaluation part
 *-----------------------------------------------------------------------------*/



static int myeval(const expr_t *e, numptr *pval)
{
	*pval = num_undefvalue();
	int r;
	if ((r = expr_eval(e, pval)) != ERROR_NONE)
		return r;

		/*
		 * Can happen with a void function, defined as is:
		 *   define void f(...)
		 *
		 * FIXME
		 *   Would be cleaner to ask expr_t if it is supposed to return
		 *   a value or not. An uninitialized *pval could mean an internal
		 *   bug...
		 *
		 * */
	if (num_is_not_initialized(*pval))
		*pval = num_construct();

	return ERROR_NONE;
}

int expr_eval(const expr_t *self, numptr *pval)
{
	if (self == NULL) {
		*pval = num_undefvalue();
		return ERROR_NONE;
	}

	int nbargs = self->nb_args;

	out_dbg("Evaluating expression, type: %s, #args: %d\n", ENODE_TYPES[self->type], nbargs);

	int is_builtin_function_call = FALSE;
	function_t *f;
	if (self->type == ENODE_FUNCTION_CALL) {
		if ((f = vars_get_function(self->var.name)) == NULL)
			return ERROR_FUNCTION_NOT_DEFINED;
		if (f->ftype == FTYPE_USER)
			return eval_function_call(self, f, pval);
		else if (f->ftype == FTYPE_BUILTIN) {
			is_builtin_function_call = TRUE;
			if (f->builtin_nb_args != nbargs)
				return ERROR_PARAMETER_NUMBER_MISMATCH;
		} else
			FATAL_ERROR("Unknown ftype: %d", f->ftype);
	}

	numptr *value_args = NULL;
	if (nbargs >= 1)
		value_args = malloc(sizeof(numptr) * (unsigned)nbargs);
	int i;
	int r = ERROR_NONE;
	for (i = 0; i < nbargs; ++i) {
		callargs_t *ca = &self->cargs[i];
		if (ca->type == CARG_EXPR) {
			if ((r = myeval(ca->e, &value_args[i])) != ERROR_NONE)
				break;
		} else if (ca->type == CARG_ARRAY) {
			r = ERROR_ARGTYPE_MISMATCH;
			break;
		} else
			FATAL_ERROR("Unknown call argument type: %d", ca->type);
	}
	if (r == ERROR_NONE) {
		if (is_builtin_function_call)
			r = eval_builtin_function_call(self, f, (const numptr *)value_args, pval);
		else
			r = (table_eval[self->type])(self, (const numptr *)value_args, pval);
	}
	for (i = 0; i < nbargs; ++i)
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

static void getvar_core(const char *varname, int has_index, long int idxval, const numptr **ppval)
{
	if (has_index) {
		*ppval = vars_array_get_value(varname, idxval);
	} else {
		*ppval = vars_get_value(varname);
	}

}

/*static void getvar(const char *varname, int has_index, long int idxval, numptr *pval)*/
/*{*/
/*    const numptr *pnum;*/
/*    getvar_core(varname, has_index, idxval, &pnum);*/

/*}*/

static int eval_getvar_core(const expr_t *self, const numptr **ppval, int create_if_missing)
{
	long int idxval;
	int r;
	if ((r = getindex(self->var.index, &idxval)) != ERROR_NONE)
		return r;
	getvar_core(self->var.name, self->var.index != NULL, idxval, ppval);

	if (!*ppval && create_if_missing) {
		if (self->var.index != NULL) {
			vars_array_set_value(self->var.name, idxval, num_construct(), ppval);
		} else {
			r = vars_set_value(self->var.name, num_construct(), ppval);
		}
	}

	return r;
}

static int eval_getvar(const expr_t *self, const numptr *value_args, numptr *pval)
{
	assert(self->type == ENODE_GETVAR && self->nb_args == 0 && value_args == NULL);
	assert(num_is_not_initialized(*pval));

	int r;
	const numptr *pnum;
	if ((r = eval_getvar_core(self, &pnum, FALSE)) != ERROR_NONE)
		return r;

	if (pnum == NULL)
		*pval = num_construct();
	else
		*pval = num_construct_from_num(*pnum);

	return ERROR_NONE;
}

static int eval_setvar_core(const expr_t *self, const numptr *value_args, numptr *pval, const numptr **ppvarnum)
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

			/*
			 * Simple assignment case, examples:
			 *   a=2^3
			 *   b[3*4]=18-1
			 *
			 * */
		presult = &value_args[0];

	else {
		const numptr *pnum;
		getvar_core(self->var.name, has_index, idxval, &pnum);
		if (pnum == NULL)
			val = num_construct();
		else
			val = num_construct_from_num(*pnum);

		val_is_to_be_destructed = TRUE;
		numptr valcopy = num_construct_from_num(val);
		expr_t *exprval = expr_construct_number(valcopy);
		expr_t *etmp;
		if (self->cargs[0].e == NULL) {

				/*
				 * Assignment without an expression, examples:
				 *   a++
				 *   --b[3*4]
				 *
				 * */
			etmp = expr_construct_op1_builtin_id(self->var.builtin, exprval);

		} else {

				/*
				 * Assignment with expression, examples:
				 *   a+=2^3
				 *   b[3*4]/=2
				 *
				 * */
			expr_t *earg0 = expr_construct_number(num_construct_from_num(value_args[0]));
			etmp = expr_construct_op2_builtin_id(self->var.builtin, exprval, earg0);
		}
		r = expr_eval(etmp, &res);
		if (r == ERROR_NONE) {
			res_is_to_be_destructed = TRUE;
			presult = &res;
		}
		expr_destruct(etmp);
	}

	if (r == ERROR_NONE) {
		if (has_index) {
			vars_array_set_value(self->var.name, idxval, num_construct_from_num(*presult), ppvarnum);
		} else {
			r = vars_set_value(self->var.name, num_construct_from_num(*presult), ppvarnum);
		}
		if (r == ERROR_NONE)
			*pval = num_construct_from_num(is_postfix ? val : *presult);
	}

	if (res_is_to_be_destructed)
		num_destruct(&res);
	if (val_is_to_be_destructed)
		num_destruct(&val);

	return r;
}

static int eval_setvar(const expr_t *self, const numptr *value_args, numptr *pval)
{
	const numptr *pvarnum;
	return eval_setvar_core(self, value_args, pval, &pvarnum);
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

static int eval_builtin_function_call(const expr_t *self, const function_t *f, const numptr *value_args, numptr *pval)
{
	int n = f->builtin_nb_args;

	assert(((value_args == NULL && self->nb_args == 0) || (value_args != NULL && self->nb_args >= 1)) && self->nb_args == n);

	out_dbg("Evaluating function %s that has %d argument(s)\n", self->var.name, n);

	if (n == 0)
		return f->builtin0arg(pval);
	else if (n == 1)
		return f->builtin1arg(pval, value_args[0]);
	else if (n == 2)
		return f->builtin2arg(pval, value_args[0], value_args[1]);
	else
		FATAL_ERROR("Number of arguments not implemented (%d) for function %s", n, self->var.name);

		/* Never executed... */
	return ERROR_NONE;
}

static int expr_eval_left_value(const expr_t *self, const numptr **ppvarnum)
{
	int r;
	if (self->type == ENODE_GETVAR) {

		assert(self->nb_args == 0);

		if ((r = eval_getvar_core(self, ppvarnum, TRUE)) != ERROR_NONE)
			return r;

		return ERROR_NONE;
	} else if (self->type == ENODE_SETVAR || self->type == ENODE_SETVAR_POSTFIX) {

		assert(self->nb_args == 1 && self->cargs[0].type == CARG_EXPR);

		numptr arg1;
		if ((r = myeval(self->cargs[0].e, &arg1)) != ERROR_NONE)
			return r;
		numptr val = num_undefvalue();
		if ((r = eval_setvar_core(self, &arg1, &val, ppvarnum)) != ERROR_NONE)
			return r;
		num_destruct(&arg1);
		num_destruct(&val);
		return ERROR_NONE;
	} else
		return ERROR_ARGTYPE_MISMATCH;
}

static int count_defargs(defargs_t *darg)
{
	int n = 0;
	while (darg != NULL) {
		darg = darg->next;
		++n;
	}
	return n;
}

static int eval_function_call(const expr_t *self, const function_t *f, numptr *pval)
{
	assert(self->type == ENODE_FUNCTION_CALL);
	assert(num_is_not_initialized(*pval));

	out_dbg("Evaluating user function %s, call has %d argument(s)\n", self->var.name, self->nb_args);

	int nbargs = count_defargs(f->defargs);
	int nbauto = count_defargs(f->autolist);
	if (self->nb_args != nbargs)
		return ERROR_PARAMETER_NUMBER_MISMATCH;

	vars_keeper_t *keeper = vars_keeper_array_construct(nbargs + nbauto);

	int r = ERROR_NONE;

	defargs_t *darg = f->defargs;
	int ii;

	/*-----------------------------------------------------------------------------
	 *  Step 1: walk through function arguments
	 *-----------------------------------------------------------------------------*/

	for (ii = 0; ii < nbargs; ++ii) {
		assert(darg != NULL);

		vars_value_t nv;
		nv.num_ref = NULL;
		nv.array_ref = NULL;

			/* Optional, used to make the code a bit lighter */
		callargs_t *ca = &self->cargs[ii];

		if (darg->type == DARG_VALUE) {
			out_dbg("Argument %d (#%s) is var byval\n", ii, darg->name);
			if (ca->type != CARG_EXPR) {
				r = ERROR_ARGTYPE_MISMATCH;
				break;
			}
			nv.type = TYPE_NUM;
			if ((r = myeval(ca->e, &nv.num)) != ERROR_NONE)
				break;
		} else if (darg->type == DARG_ARRAYVALUE) {
			out_dbg("Argument %d (#%s) is array byval\n", ii, darg->name);
			if (ca->type != CARG_ARRAY) {
				r = ERROR_ARGTYPE_MISMATCH;
				break;
			}
			nv.type = TYPE_ARRAY;
			nv.array = vars_array_copy(ca->array_name);
		} else if (darg->type == DARG_REF) {
			out_dbg("Argument %d (#%s) is var byref\n", ii, darg->name);
			if (ca->type != CARG_EXPR || ca->e == NULL) {
				r = ERROR_ARGTYPE_MISMATCH;
				break;
			}
			expr_t *e = ca->e;
			const numptr *plvnum;
			if ((r = expr_eval_left_value(e, &plvnum)) != ERROR_NONE)
				break;
			nv.type = TYPE_NUM;
			nv.num_ref = (numptr *)plvnum;
		} else if (darg->type == DARG_ARRAYREF) {
			out_dbg("Argument %d (#%s) is array byref\n", ii, darg->name);
			if (ca->type != CARG_ARRAY) {
				r = ERROR_ARGTYPE_MISMATCH;
				break;
			}
			nv.type = TYPE_ARRAY;
			nv.array_ref = vars_array_get_ref(ca->array_name);
		} else
			FATAL_ERROR("Unknown definition argument type: %d for darg #%lu", darg->type, darg);

		vars_send_to_keeper(&keeper[ii], darg->name, &nv);

		darg = darg->next;
	}
	if (r == ERROR_NONE) {
		assert(darg == NULL);
		assert(ii == nbargs);

		/*-----------------------------------------------------------------------------
		 *  Step 2: walk through autolist
		 *-----------------------------------------------------------------------------*/

		darg = f->autolist;
		int n = 0;
		while (darg != NULL) {
			++n;
			vars_value_t nv;
			nv.num_ref = NULL;
			nv.array_ref = NULL;

			if (darg->type == DARG_VALUE) {
				out_dbg("Auto variable %d (#%s) is var\n", n, darg->name);
				nv.type = TYPE_NUM;
				nv.num = num_construct();
			} else if (darg->type == DARG_ARRAYVALUE) {
				out_dbg("Auto variable %d (#%s) is array\n", n, darg->name);
				nv.type = TYPE_ARRAY;
				nv.array = NULL;
			} else
				FATAL_ERROR("Unknown auto variable type: %d for darg #%lu", darg->type, darg);

			vars_send_to_keeper(&keeper[ii], darg->name, &nv);

			++ii;
			darg = darg->next;
		}
	}

	if (r == ERROR_NONE) {
		assert(darg == NULL);
		assert(ii == nbargs + nbauto);
		r = program_execute(f->program, pval);
		if (r == ERROR_NONE || r == ERROR_RETURN) {
			r = ERROR_NONE;
			if (!num_is_not_initialized(*pval) && f->is_void) {
				num_destruct(pval);
				*pval = num_undefvalue();
			} else if (num_is_not_initialized(*pval) && !f->is_void) {
				*pval = num_construct();
			}
		}
	}

	darg = f->defargs;
	for (ii = 0; ii < nbargs; ++ii) {
		assert(darg != NULL);

		vars_recall_from_keeper(darg->name, &keeper[ii]);

		darg = darg->next;
	}
	assert(darg == NULL);
	assert(ii == nbargs);
	darg = f->autolist;
	while (darg != NULL) {

		vars_recall_from_keeper(darg->name, &keeper[ii]);

		++ii;
		darg = darg->next;
	}
	assert(ii == nbargs + nbauto);

	if (keeper != NULL)
		free(keeper);

	return r;
}

int expr_get_count_ref() { return expr_count_ref; }

