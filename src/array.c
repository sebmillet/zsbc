/*
 * =====================================================================================
 *
 *       Filename:  array.c
 *
 *    Description:  Manages arrays.
 *
 *        Version:  1.0
 *        Created:  13/09/2015 13:08:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet (smt), milletseb@laposte.net
 *
 * =====================================================================================
 */

#include "array.h"
#include "vars.h"

struct array_t {
	long int index;
	numptr num;
	struct array_t *next;
};

void array_destruct(array_t *a)
{
	while (a != NULL) {
		num_destruct(&a->num);
		array_t *anext = a->next;
		free(a);
		a = anext;
	}
}

array_t *find_index(array_t *a, long int index)
{
	while (a != NULL) {
		if (a->index == index)
			return a;
		a = a->next;
	}
	return NULL;
}

	/*
	 * Copy an array_t chain.
	 * The copy is done so that the order of elements remains
	 * the same. It'd be acceptable the order becomes reversed (why not?)
	 * but I preferred to keep the order...
	 */
array_t *array_t_copy(const array_t *src)
{
	const array_t *orig_src = src;
#if !DEBUG
UNUSED(orig_src);
#endif

	array_t *ret = NULL;
	array_t *prec = NULL;

	int n = 0;


	while (src != NULL) {
		array_t *copy = (array_t *)malloc(sizeof(array_t));
		copy->index = src->index;
		copy->num = num_construct_from_num(src->num);
		copy->next = NULL;
		if (ret == NULL)
			ret = copy;
		if (prec != NULL)
			prec->next = copy;
		prec = copy;
		src = src->next;
		++n;
	}

	out_dbg("\tCopied array of %d element(s) from %lu to %lu\n", n, orig_src, ret);

	return ret;
}

const numptr *array_get_value(array_t *a, long int index)
{
	array_t *e = find_index(a, index);
	if (e != NULL) {
		out_dbg("\t[%d] found\n", index);
		return &e->num;
	} else {
		out_dbg("\t[%d] not found\n", index);
		return NULL;
	}
}

void array_set_value(array_t **pa, long int index, const numptr new_value, const numptr **ppvarnum)
{
	array_t *e = find_index(*pa, index);

	if (e == NULL) {
		out_dbg("\t[%d] not found\n", index);
		e = (array_t *)malloc(sizeof(array_t));
		e->index = index;
		e->num = num_undefvalue();
		if (*pa != NULL) {
			e->next = (*pa)->next;
			(*pa)->next = e;
		} else {
			e->next = *pa;
			*pa = e;
		}
	} else {
		out_dbg("\t[%d] found\n", index);
		num_destruct(&e->num);
	}

	e->num = new_value;
	*ppvarnum = &e->num;

}

