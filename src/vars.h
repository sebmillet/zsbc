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
} vars_t;

vars_t *vars;
int vars_nb;
int vars_ar;

void vars_init();
void vars_terminate();
void vars_display_all();

numptr *vars_get_value(const char *name);
void vars_set_value(const char *name, const numptr new_value);

#endif	/* VARS_H */

