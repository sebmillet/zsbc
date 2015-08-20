/*
 * =====================================================================================
 *
 *       Filename:  vars.c
 *
 *    Description:  Manages variables: simple ones (containing a number)
 *    				and array (var[]) variables.
 *
 *        Version:  1.0
 *        Created:  14/06/2015 14:04:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet (smt), milletseb@laposte.net
 *
 * =====================================================================================
 */


#include "vars.h"

#include <string.h>
#include <stdio.h>

struct array_t {
	long int index;
	numptr num;
	struct array_t *next;
};

struct vars_t {
	char *name;
	vars_value_t value;
	struct vars_t *next;
};

typedef struct vars_container_t {
	vars_t *head;
} vars_container_t;

struct context_t {
	vars_container_t container;
	int lib_reg_number;
};

static void vars_t_destruct(vars_t *var);
static vars_t *find_var(const char *name, int type);
static void function_destruct(function_t f);
static void vars_value_soft_copy(vars_value_t *dst, const vars_value_t *src);
static void array_destruct(array_t *a);

context_t *ctx = NULL;

void container_initialize(vars_container_t *container)
{
	container->head = NULL;
}

context_t *context_construct(int lib_reg_number)
{
	context_t *c = malloc(sizeof(context_t));
	container_initialize(&c->container);
	c->lib_reg_number = lib_reg_number;
	return c;
}

void container_terminate(vars_container_t *container)
{
	vars_t *w;
	vars_t *wnext;
	for (w = container->head; w != NULL; w = wnext) {
		wnext = w->next;
		vars_t_destruct(w);
		w = NULL;
	}
}

void context_destruct(context_t *c)
{
	assert(ctx->lib_reg_number == num_get_current_lib_number());

	container_terminate(&c->container);
	free(c);
}

void context_switch(context_t *c)
{
	ctx = c;
}

void vars_value_destruct(vars_value_t *value)
{
	assert(value != NULL);

	if (value->num_ref != NULL || value->array_ref != NULL)
		return;

	if (value->type == TYPE_NUM)
		num_destruct(&value->num);
	else if (value->type == TYPE_ARRAY)
		array_destruct(value->array);
	else if (value->type == TYPE_FCNT)
		function_destruct(value->fcnt);
	else
		FATAL_ERROR("Unknown symbol type: %d for vars_value_t: %lu", value->type, value);
}

static vars_t *vars_t_construct(const char *name, int type)
{
	out_dbg("Constructing one vars_t, name: %s, type: %d\n", name, type);

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *v = malloc(sizeof(vars_t));
	int l = strlen(name) + 1;
	v->name = (char *)malloc(l);
	s_strncpy(v->name, name, l);
	v->value.type = type;
	v->value.num_ref = NULL;
	v->value.array_ref = NULL;
	if (type == TYPE_NUM) {
		v->value.num = num_undefvalue();
	} else if (type == TYPE_ARRAY) {
		v->value.array = NULL;
	} else if (type == TYPE_FCNT) {
		v->value.fcnt.defargs = NULL;
		v->value.fcnt.program = NULL;
	} else
		FATAL_ERROR("Unknown symbol type: %d", type);

	v->next = ctx->container.head;
	ctx->container.head = v;
	return v;
}

static vars_t *vars_t_construct_with_value(const char *name, const vars_value_t *value)
{
	vars_t *v = vars_t_construct(name, value->type);
	vars_value_soft_copy(&v->value, value);
	return v;
}

static void array_destruct(array_t *a)
{
	while (a != NULL) {
		num_destruct(&a->num);
		array_t *anext = a->next;
		free(a);
		a = anext;
	}
}

static void vars_t_destruct(vars_t *var)
{
	out_dbg("Destructing one vars_t of name %s\n", var->name == NULL ? "<NULL>" : var->name);
	assert(ctx->lib_reg_number == num_get_current_lib_number());

	if (var->name != NULL) {
		free(var->name);
		var->name = NULL;
	}

	vars_value_destruct(&var->value);

	free(var);
}

static vars_t *find_var(const char *name, int type)
{
	vars_t *w;
	for (w = ctx->container.head; w != NULL; w = w->next) {
		if (w->name != NULL && !strcmp(w->name, name) && w->value.type == type) {
			return w;
		}
	}
	return NULL;
}

array_t **vars_array_get_ref(const char *name)
{
	vars_t *w;
	if ((w = find_var(name, TYPE_ARRAY)) == NULL) {
		return NULL;
		const numptr *ppv;
		vars_array_set_value(name, 0, num_construct(), &ppv);
		if ((w = find_var(name, TYPE_ARRAY)) == NULL)
			FATAL_ERROR("%s", "Inconsistent data, ref 182");
	}
	return w->value.array_ref ? w->value.array_ref : &w->value.array;
}

static array_t *find_index(array_t *a, long int index)
{
	while (a != NULL) {
		if (a->index == index)
			return a;
		a = a->next;
	}
	return NULL;
}

const numptr *vars_get_value(const char *name)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	out_dbg("Getting value of %s\n", name);

	vars_t *w = find_var(name, TYPE_NUM);
	if (w != NULL)
		return (w->value.num_ref ? w->value.num_ref : &w->value.num);
	return NULL;
}

const numptr *vars_array_get_value(const char *name, long int index)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	out_dbg("Getting value of %s[%d]\n", name, index);

	vars_t *w = find_var(name, TYPE_ARRAY);
	if (w != NULL) {

		out_dbg("\tFound %s[]\n", name);

		array_t *a = find_index(w->value.array_ref ? *w->value.array_ref : w->value.array, index);
		if (a != NULL) {

			out_dbg("\tFound index %d\n", index);

			return &a->num;
		}
	}
	return NULL;
}

	/*
	 * Copy an array_t chain.
	 * The copy is done so that the order of elements remains
	 * the same. It'd be acceptable the order becomes reversed (why not?)
	 * but I preferred to keep the order...
	 */
static array_t *array_t_copy(const array_t *src)
{
	array_t *ret = NULL;
	array_t *prec = NULL;
	while (src != NULL) {
		array_t *copy = (array_t *)malloc(sizeof(array_t));
		copy->index = src->index;
		copy->num = num_construct_from_num(src->num);
		copy->next = NULL;
		if (ret == NULL)
			ret = copy;
		if (prec != NULL)
			prec->next = copy;
		prec = copy;
		src = src->next;
	}
	return ret;
}

	/*
	 * Copy the array given its name and returns a pointer to the copy.
	 * If the array does not exist, return NULL.
	 * */
array_t *vars_array_copy(const char *name)
{
	
	assert(ctx->lib_reg_number == num_get_current_lib_number());

	out_dbg("Copying array %s", name);

	vars_t *w = find_var(name, TYPE_ARRAY);
	if (w == NULL)
		return NULL;
	return array_t_copy(w->value.array);
}

function_t *vars_get_function(const char *name)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	out_dbg("Getting function object of %s\n", name);

	vars_t *w = find_var(name, TYPE_FCNT);
	if (w != NULL) {

		out_dbg("\tFound %s\n", name);

		return &w->value.fcnt;
	} else
		return NULL;
}

void vars_set_value_core(const char *name, const numptr new_value, vars_t *v, const numptr **ppvarnum)
{
	if (v == NULL) {
		v = vars_t_construct(name, TYPE_NUM);
	} else if (!v->value.num_ref) {
		num_destruct(&v->value.num);
	} else {
		num_destruct(v->value.num_ref);
	}
	if (!v->value.num_ref) {
		v->value.num = new_value;
		*ppvarnum = &v->value.num;
	} else {
		*v->value.num_ref = new_value;
		*ppvarnum = v->value.num_ref;
	}
}

void vars_set_value(const char *name, const numptr new_value, const numptr **ppvarnum)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *v = find_var(name, TYPE_NUM);
	vars_set_value_core(name, new_value, v, ppvarnum);
}

static void vars_array_set_value_core(const char *name, long int index, const numptr new_value, vars_t *v, const numptr **ppvarnum)
{
	if (v == NULL) {
		v = vars_t_construct(name, TYPE_ARRAY);
	}
	array_t *a = find_index(v->value.array_ref ? *v->value.array_ref : v->value.array, index);
	if (a == NULL) {
		a = (array_t *)malloc(sizeof(array_t));
		a->index = index;
		a->num = num_undefvalue();
		a->next = v->value.array;
		v->value.array = a;
	} else {
		num_destruct(&a->num);
	}

	a->num = new_value;
	*ppvarnum = &a->num;
}

void vars_array_set_value(const char *name, long int index, const numptr new_value, const numptr **ppvarnum)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *v = find_var(name, TYPE_ARRAY);
	vars_array_set_value_core(name, index, new_value, v, ppvarnum);
}

void vars_display_all()
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *w;
	for (w = ctx->container.head; w != NULL; w = w->next) {
			/*  FIXME - At the moment, handles only TYPE_NUM variables */
		if (w->value.type == TYPE_NUM) {
			printf("%s=", w->name);
			num_print(w->value.num, 10);
			printf("\n");
		}
	}
}

static void vars_value_soft_copy(vars_value_t *dst, const vars_value_t *src)
{
	if (src->type == TYPE_NUM)
		dst->num = src->num;
	else if (src->type == TYPE_ARRAY)
		dst->array = src->array;
	else if (src->type == TYPE_FCNT)
		dst->fcnt = src->fcnt;
	else
		FATAL_ERROR("Unknown symbol type: %d for vars_value_t: %lu", src->type, src);

	dst->type = src->type;
	dst->num_ref = src->num_ref;
	dst->array_ref = src->array_ref;
}

vars_keeper_t *vars_keeper_array_construct(int n)
{
	assert(n >= 0);

	if (n == 0)
		return NULL;

	vars_keeper_t *keeps = (vars_keeper_t *)malloc(sizeof(vars_keeper_t) * n);
	int i;
	for (i = 0; i < n; ++i) {
		keeps[i].is_used = FALSE;
	}
	return keeps;
}

void vars_send_to_keeper(vars_keeper_t *keeper, const char *name, const vars_value_t *new_value)
{

	assert(keeper != NULL);
	assert(!keeper->is_used);

	out_dbg("Sending %s to keeper, keep address = %lu\n", name, keeper);

	keeper->is_used = TRUE;

	vars_t *w;
	if ((w = find_var(name, new_value->type)) == NULL) {
		out_dbg("\tVariable %s not found\n", name);
		keeper->holds_a_value = FALSE;
		vars_t_construct_with_value(name, new_value);
	} else {
		out_dbg("\tVariable %s found\n", name);
		keeper->holds_a_value = TRUE;
		vars_value_soft_copy(&keeper->value, &w->value);
		vars_value_soft_copy(&w->value, new_value);
	}

	out_dbg("New value type: %d, num_ref: %lu, array_ref: %lu\n", new_value->type, new_value->num_ref, new_value->array_ref);

}

void vars_recall_from_keeper(const char *name, vars_keeper_t *keeper)
{

	assert(keeper != NULL);

	if (!keeper->is_used) {
		out_dbg("Recall requested from unused keeper, keep address = %lu\n", keeper);
		return;
	}

	out_dbg("Recalling %s from keeper, keep address = %lu\n", name, keeper);

	vars_t *w = find_var(name, keeper->value.type);

	if (keeper->holds_a_value) {
		assert(w != NULL);
		out_dbg("\tKeeper has a value => replacing variable value with keeper's\n");
		vars_value_destruct(&w->value);
		vars_value_soft_copy(&w->value, &keeper->value);
	} else if (w != NULL)  {
		out_dbg("\tUndefined keeper value => destructing variable\n");

			/*  FIXME
			 *  Needs proper destruction function
			 *  */
		free(w->name);
		w->name = NULL;

	} else {
		out_dbg("\tUndefined keeper value and variable not found => nothing to do\n");
	}
	keeper->is_used = FALSE;
}



/*-----------------------------------------------------------------------------
 *  arg_t and call_arg_t management
 *-----------------------------------------------------------------------------*/



defargs_t *defargs_construct(defarg_type_t type, const char *name)
{
	defargs_t *defarg = (defargs_t *)malloc(sizeof(defargs_t));
	defarg->type = type;
	defarg->name = (char *)name;
	defarg->next = NULL;
	return defarg;
}

void defargs_destruct(defargs_t *defargs)
{
	out_dbg("Entering defargs_destruct for %lu\n", defargs);
	defargs_t *keep_next;
	while (defargs != NULL) {
		keep_next = defargs->next;

		free(defargs->name);
		free(defargs);

		defargs = keep_next;
	}
}

defargs_t *defargs_chain(defargs_t *base, defargs_t *append)
{
	/*
	 * FIXME
	 * Should save the base in the list to avoid systematical walk through
	 * the entire list to append one element, that has O(n^2) execution time.
	 */
	assert(base != NULL && append != NULL);
	defargs_t *w = base;
	while (w->next != NULL)
		w = w->next;
	w->next = append;
	return base;
}



/*-----------------------------------------------------------------------------
 *  function_t management
 *-----------------------------------------------------------------------------*/



int vars_function_construct(const char*name, defargs_t *defargs, program_t *program, int is_void)
{
	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *f;
	if ((f = find_var(name, TYPE_FCNT)) != NULL) {

			/*  FIXME
			 *  Needs proper destruction function
			 *  */
		free(f->name);
		f->name = NULL;

		outln_warning("Redefinition of function %s", name);
	}

	f = vars_t_construct(name, TYPE_FCNT);

	f->value.fcnt.is_void = is_void;
	f->value.fcnt.defargs = defargs;
	f->value.fcnt.program = program;

	out_dbg("Constructed function: %lu, name: %s, defargs: %lu, program: %lu\n", f, f->name, f->value.fcnt.defargs, f->value.fcnt.program);

	return ERROR_NONE;
}

static void function_destruct(function_t f)
{

	out_dbg("Destructing function: defargs: %lu, program: %lu\n", f.defargs, f.program);

	if (f.defargs != NULL) {
		defargs_destruct(f.defargs);
		f.defargs = NULL;
	}
	if (f.program != NULL) {
		program_destruct(f.program);
		f.program = NULL;
	}
}

