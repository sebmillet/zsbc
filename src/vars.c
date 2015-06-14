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
#include "common.h"

#include <string.h>
#include <stdio.h>

void vars_init()
{
	vars = NULL;
	vars_ar = 0;
	vars_nb = 0;
}

void vars_terminate()
{
	int i;
	for (i = 0; i < vars_nb; ++i) {
		free(vars[i].name);
		mpz_clear(vars[i].value);
	}
	free(vars);
	vars = NULL;
	vars_ar = 0;
	vars_nb = 0;
}

mpz_t *vars_get_value(const char *name)
{
	int i;
	for (i = 0; i < vars_nb; ++i) {
		if (!strcmp(vars[i].name, name)) {
			return &(vars[i].value);
		}
	}
	return NULL;
}

void vars_set_value(const char *name, const mpz_t* new_value)
{
	mpz_t *value = vars_get_value(name);
	if (value == NULL) {
		if (++vars_nb >= vars_ar) {
			int new_vars_ar = vars_ar * 2;
			if (new_vars_ar <= 0)
				new_vars_ar = 1;
			vars = (vars_t *)realloc(vars, sizeof(vars_t) * new_vars_ar);
			vars_ar = new_vars_ar;
		}
		int l = strlen(name) + 1;
		vars[vars_nb - 1].name = (char *)malloc(l);
		s_strncpy(vars[vars_nb - 1].name, name, l);
		value = &(vars[vars_nb - 1].value);
	} else {
		mpz_clear(*value);
	}
	mpz_init_set(*value, *new_value);
}

void vars_display_all()
{
	int i;
	for (i = 0; i < vars_nb; ++i) {
		printf("%s=", vars[i].name);
		display_int(&(vars[i].value));
	}
}

