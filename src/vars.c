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

static void vars_t_destruct(vars_t *var);
static vars_t *find_var(const char *name, int type);

context_t *ctx = NULL;

context_t *context_construct(int lib_reg_number)
{
	context_t *c = malloc(sizeof(context_t));
	c->head = NULL;
	c->lib_reg_number = lib_reg_number;
	return c;
}

void context_destruct(context_t *c)
{
	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *w;
	vars_t *wnext;
	for (w = c->head; w != NULL; w = wnext) {
		wnext = w->next;
		vars_t_destruct(w); w = NULL;
	}
	free(c);
}

void context_switch(context_t *c)
{
	ctx = c;
}

static vars_t *vars_t_construct(const char *name, int type)
{
	out_dbg("Constructing one vars_t, name: %s, type: %d\n", name, type);

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *v = malloc(sizeof(vars_t));
	int l = strlen(name) + 1;
	v->name = (char *)malloc(l);
	s_strncpy(v->name, name, l);
	v->type = type;
	if (type == TYPE_NUM) {
		v->num = num_undefvalue();
	} else if (type == TYPE_ARRAY) {
		v->array = NULL;
	}
	v->next = ctx->head;
	ctx->head = v;
	return v;
}

static void array_t_destruct(array_t *a)
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

	if (var->name != NULL)
		free(var->name);

	if (var->type == TYPE_NUM) {
		num_destruct(&var->num);
	} else if (var->type == TYPE_ARRAY) {
		array_t_destruct(var->array);
	}

	free(var);
}

static vars_t *find_var(const char *name, int type)
{
	vars_t *w;
	for (w = ctx->head; w != NULL; w = w->next) {
		if (!strcmp(w->name, name) && w->type == type) {
			return w;
		}
	}
	return NULL;
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
		return &w->num;
	return NULL;
}

const numptr *vars_array_get_value(const char *name, long int index)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	out_dbg("Getting value of %s[%d]\n", name, index);

	vars_t *w = find_var(name, TYPE_ARRAY);
	if (w != NULL) {

		out_dbg("\tFound %s[]\n", name);

		array_t *a = find_index(w->array, index);
		if (a != NULL) {

			out_dbg("\tFound index %d\n", index);

			return &a->num;
		}
	}
	return NULL;
}

void vars_set_value(const char *name, const numptr new_value)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *v = find_var(name, TYPE_NUM);
	if (v == NULL) {
		v = vars_t_construct(name, TYPE_NUM);
	} else {
		num_destruct(&v->num);
	}
	v->num = num_construct_from_num(new_value);
}

void vars_array_set_value(const char *name, long int index, const numptr new_value)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *v = find_var(name, TYPE_ARRAY);
	if (v == NULL) {
		v = vars_t_construct(name, TYPE_ARRAY);
	}
	array_t *a = find_index(v->array, index);
	if (a == NULL) {
		a = (array_t *)malloc(sizeof(array_t));
		a->index = index;
		a->num = num_undefvalue();
		a->next = v->array;
		v->array = a;
	} else {
		num_destruct(&a->num);
	}

	a->num = num_construct_from_num(new_value);
}

void vars_display_all()
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *w;
	for (w = ctx->head; w != NULL; w = w->next) {
		printf("%s=", w->name);
		num_print(w->num, 10);
		printf("\n");
	}
}

