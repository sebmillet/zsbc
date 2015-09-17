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
//array_t *find_index(array_t *a, long int index);
array_t *array_t_copy(const array_t *src);

const numptr *array_get_value(array_t *a, long int index);
void array_set_value(array_t **pa, long int index, const numptr new_value, const numptr **ppvarnum);

#endif

