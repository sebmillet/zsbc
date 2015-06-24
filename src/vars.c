/*
 * =====================================================================================
 *
 *       Filename:  vars.c
 *
 *    Description:  Manage variables: simple ones (containing a number)
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

static vars_t *vars_t_construct(const char *name)
{
	out_dbg("Constructing one vars_t of name %s\n", name);

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *v = malloc(sizeof(vars_t));
	int l = strlen(name) + 1;
	v->name = (char *)malloc(l);
	s_strncpy(v->name, name, l);
	v->num = num_undefvalue();
	v->next = NULL;
	return v;
}

static void vars_t_destruct(vars_t *var)
{
	out_dbg("Destructing one vars_t of name %s\n", var->name == NULL ? "<NULL>" : var->name);
	assert(ctx->lib_reg_number == num_get_current_lib_number());

	if (var->name != NULL)
		free(var->name);
	num_destruct(&var->num);

	free(var);
}

numptr *vars_get_value(const char *name)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *w;
	for (w = ctx->head; w != NULL; w = w->next) {
		if (!strcmp(w->name, name)) {
			return &w->num;
		}
	}
	return NULL;
}

void vars_set_value(const char *name, const numptr new_value)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	numptr *pval = vars_get_value(name);
	if (pval == NULL) {
		vars_t *var = vars_t_construct(name);
		var->next = ctx->head;
		ctx->head = var;
		pval = &(var->num);
	} else {
		num_destruct(pval);
	}
	*pval = num_construct_from_num(new_value);
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

