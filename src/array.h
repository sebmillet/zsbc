/*
 * =====================================================================================
 *
 *       Filename:  array.h
 *
 *    Description:  Header file of array.c.
 *
 *        Version:  1.0
 *        Created:  13/09/2015 13:16:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet (smt), milletseb@laposte.net
 *
 * =====================================================================================
 */

#ifndef ARRAY_H
#define ARRAY_H

#include "common.h"
#include "numwrap.h"

struct array_t;
typedef struct array_t array_t;

void array_destruct(array_t *a);
array_t *array_t_get_a_copy(array_t *src);

const numptr *array_get_value(array_t *a, long int index);
void array_set_value(array_t **pa, long int index, const numptr new_value, const numptr **ppvarnum);
long int array_count(const array_t *a);

int array_check_index(long int index);

void copyonupdate_manage_copy(array_t *a, int for_destruct);

#endif

