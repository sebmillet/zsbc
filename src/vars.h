/*
 * =====================================================================================
 *
 *       Filename:  vars.h
 *
 *    Description:  Header file of vars.c.
 *
 *        Version:  1.0
 *        Created:  14/06/2015 14:05:02
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet (smt), milletseb@laposte.net
 *
 * =====================================================================================
 */


#ifndef VARS_H
#define VARS_H

#include "common.h"
#include "numwrap.h"

typedef struct vars_t {
	char *name;
	numptr num;
	struct vars_t *next;
} vars_t;

typedef struct context_t {
	vars_t *head;
	int lib_reg_number;
} context_t;

context_t *context_construct(int lib_reg_number);
void context_destruct(context_t *c);
void context_switch(context_t *c);

void vars_display_all();

numptr *vars_get_value(const char *name);
void vars_set_value(const char *name, const numptr new_value);

#endif	/* VARS_H */

