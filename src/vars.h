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


#include <gmp.h>

typedef struct vars_t {
	char *name;
	mpz_t value;
} vars_t;

vars_t *vars;
int vars_nb;
int vars_ar;

void vars_init();
void vars_terminate();
void vars_display_all();

