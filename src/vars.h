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

struct context_t;
typedef struct context_t context_t;

enum {TYPE_NUM, TYPE_ARRAY, TYPE_FUNCTION};

typedef enum {DARG_VALUE, DARG_ARRAYVALUE, DARG_REF, DARG_ARRAYREF} defarg_type_t;
struct defargs_t {
	defarg_type_t type;
	char *name;
	struct defargs_t *next;
};
typedef struct defargs_t defargs_t;

context_t *context_construct(int lib_reg_number);
void context_destruct(context_t *c);
void context_switch(context_t *c);

struct array_t;
typedef struct array_t array_t;

typedef struct function_t {
	int is_void;
	defargs_t *defargs;
	program_t *program;
} function_t;

typedef struct vars_value_t {
	int type;
	union {
		numptr num;
		array_t *array;
		function_t fcnt;
	};
} vars_value_t;

typedef struct vars_keeper_t {
	int has_value;
	vars_value_t value;
} vars_keeper_t;

struct vars_t;
typedef struct vars_t vars_t;

void vars_display_all();

const numptr *vars_get_value(const char *name);
const numptr *vars_array_get_value(const char *name, long int index);
void vars_set_value(const char *name, const numptr new_value);
void vars_array_set_value(const char *name, long int index, const numptr new_value);
function_t *vars_get_function(const char *name);

void vars_send_to_keeper(vars_keeper_t *keep, const char *name, const vars_value_t *new_value);
void vars_recall_from_keeper(const char *name, const vars_keeper_t *keeper);

defargs_t *defargs_construct(defarg_type_t type, const char *name);
void defargs_destruct(defargs_t *arg);
defargs_t *defargs_chain(defargs_t *base, defargs_t *append);

int vars_function_construct(const char*name, defargs_t *args, program_t *program, int is_void);

#endif	/* VARS_H */

