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

vars_t *head;

static vars_t *vars_t_construct(const char *name)
{
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
	if (var->name != NULL)
		free(var->name);
	num_destruct(&var->num);

	free(var);
}

void vars_init()
{
	head = NULL;
}

void vars_terminate()
{
	vars_t *w;
	vars_t *wnext;
	for (w = head; w != NULL; w = wnext) {
		wnext = w->next;
		vars_t_destruct(w);
	}
}

numptr *vars_get_value(const char *name)
{
	vars_t *w;
	for (w = head; w != NULL; w = w->next) {
		if (!strcmp(w->name, name)) {
			return &w->num;
		}
	}
	return NULL;
}

void vars_set_value(const char *name, const numptr new_value)
{
	numptr *pval = vars_get_value(name);
	if (pval == NULL) {
		vars_t *var = vars_t_construct(name);
		var->next = head;
		head = var;
		pval = &(var->num);
	} else {
		num_destruct(pval);
	}
	*pval = num_construct_from_num(new_value);
}

void vars_display_all()
{
	vars_t *w;
	for (w = head; w != NULL; w = w->next) {
		printf("%s=", w->name);
		num_print(w->num, 10);
		printf("\n");
	}
}

