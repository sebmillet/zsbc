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

enum {TYPE_NUM, TYPE_ARRAY};

typedef struct array_t {
	long int index;
	numptr num;
	struct array_t *next;
} array_t;

typedef struct vars_t {
	char *name;
	int type;
	union {
		numptr num;
		array_t *array;
	};
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

const numptr *vars_get_value(const char *name);
const numptr *vars_array_get_value(const char *name, long int index);
void vars_set_value(const char *name, const numptr new_value);
void vars_array_set_value(const char *name, long int index, const numptr new_value);

#endif	/* VARS_H */

