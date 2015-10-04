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
#include "program.h"
#include "array.h"

struct context_t;
typedef struct context_t context_t;

	/*
	 * The values are used in arrays so, while the ordering of the elements below
	 * doesn't matter, it is important to use integers in the interval
	 * [0, n - 1] where n is the number of TYPE_ constants, and to use each
	 * integer once.
	 *
	 * TYPE_NB is a meta-one and is used only to get the number of constants.
	 *
	 * */
enum {
	TYPE_NUM = 0,
	TYPE_ARRAY = 1,
	TYPE_FCNT = 2,

	TYPE_NB = 3
};

context_t *context_construct(int lib_reg_number);
void context_destruct(context_t *c);
void context_switch(context_t *c);

enum {FTYPE_USER, FTYPE_BUILTIN};

typedef struct function_t {
	int is_void;
	int ftype;
	defargs_t *defargs;
	defargs_t *autolist;
	program_t *program;
	int builtin_nb_args;
	int (*builtin0arg)(numptr *pr);
	int (*builtin1arg)(numptr *pr, const numptr a);
	int (*builtin2arg)(numptr *pr, const numptr a, const numptr b);
} function_t;

typedef struct vars_value_t {
	int type;
	union {
		numptr num;
		array_t *array;
		function_t fcnt;
	};
	numptr *num_ref;
	array_t **array_ref;
} vars_value_t;

typedef struct vars_keeper_t {
	int is_used;
	int holds_a_value;
	int ktype;
	vars_value_t value;
} vars_keeper_t;

struct vars_t;
typedef struct vars_t vars_t;

void vars_display_all();

const numptr *vars_get_value(const char *name);
const numptr *vars_array_get_value(const char *name, long int index);
int vars_set_value(const char *name, numptr new_value, const numptr **ppvarnum);
void vars_set_update_callback(const char *name, int (*update_callback)(const char *name, numptr *pnum));
void vars_array_set_value(const char *name, long int index, const numptr new_value, const numptr **ppvarnum);
function_t *vars_get_function(const char *name);
void var_delete(const char *name);

vars_keeper_t *vars_keeper_array_construct(int n);
void vars_send_to_keeper(vars_keeper_t *keep, const char *name, const vars_value_t *new_value);
void vars_recall_from_keeper(const char *name, vars_keeper_t *keeper);

array_t *vars_array_copy(const char *name);

array_t **vars_array_get_ref(const char *name);

defargs_t *defargs_construct(defarg_type_t type, const char *name);
void defargs_destruct(defargs_t *arg);

void vars_user_function_construct(char *name, defargs_t *args, program_t *program, int is_void);
void register_builtin_function(const char *name, int nb_args, void *f);

#endif	/* VARS_H */

