/*
 * =====================================================================================
 *
 *       Filename:  vars.c
 *
 *    Description:  Manages variables: simple ones (containing a number)
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
#include "array.h"

#include <string.h>
#include <stdio.h>

#include "uthash.h"

	/* BEWARE OF SIDE EFFECTS! */
int global_check_id = 0;

extern defargs_t *defarg_t_badarg;

const char *type_names[] = {
	"TYPE_NUM",		/* TYPE_NUM */
	"TYPE_ARRAY",	/* TYPE_ARRAY */
	"TYPE_FCNT"		/* TYPE_FCNT */
};

struct vars_t {
	char *name;
	vars_value_t *pvalue;
	int (*update_callback)(const char *name, numptr *pnum);

	UT_hash_handle hh;
};

typedef struct vars_container_t {
	vars_t* heads[TYPE_NB];
} vars_container_t;

struct context_t {
	vars_container_t container;
	int lib_reg_number;
};

static vars_t *vars_t_construct(const char *name, int type, int ftype);
static void vars_t_destruct(vars_t *var);
static vars_t *find_var(const char *name, int type);
static void function_destruct(function_t f);
static void vars_value_soft_copy(vars_value_t *dst, const vars_value_t *src);

context_t *ctx = NULL;

void container_initialize(vars_container_t *container)
{
	int i;
	for (i = 0; i < TYPE_NB; ++i) {
		container->heads[i] = NULL;
	}
}

context_t *context_construct(int lib_reg_number)
{
	context_t *c = malloc(sizeof(context_t));
	container_initialize(&c->container);
	c->lib_reg_number = lib_reg_number;
	return c;
}

void container_terminate(vars_container_t *container)
{
	int i;
	for (i = 0; i < TYPE_NB; ++i) {
		vars_t *w;
		vars_t *tmp;
		HASH_ITER(hh, container->heads[i], w, tmp) {
			vars_t_destruct(w);
		}
	}
}

void context_destruct(context_t *c)
{
	assert(ctx->lib_reg_number == num_get_current_lib_number());

	out_dbg("Call of context_destruct()\n");

	container_terminate(&c->container);
	free(c);
}

void context_switch(context_t *c)
{
	ctx = c;
}

void vars_value_destruct(vars_value_t *pvalue)
{
	assert(pvalue != NULL);

	if (pvalue->num_ref != NULL || pvalue->array_ref != NULL)
		return;

	if (pvalue->type == TYPE_NUM)
		num_destruct(&pvalue->num);
	else if (pvalue->type == TYPE_ARRAY)
		array_destruct(pvalue->array);
	else if (pvalue->type == TYPE_FCNT)
		function_destruct(pvalue->fcnt);
	else
		FATAL_ERROR("Unknown symbol type: %d for vars_value_t: %lu", pvalue->type, pvalue);
}

static vars_t *vars_t_construct(const char *name, int type, int ftype)
{
	out_dbg("Constructing one vars_t, name: %s, type: %d\n", name, type);

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *v = malloc(sizeof(vars_t));
	int slen = strlen(name);
	int l = slen + 1;
	v->name = (char *)malloc(l);
	v->update_callback = NULL;
	s_strncpy(v->name, name, l);
	v->pvalue = (vars_value_t *)malloc(sizeof(vars_value_t));
	v->pvalue->type = type;
	v->pvalue->num_ref = NULL;
	v->pvalue->array_ref = NULL;
	if (type == TYPE_NUM) {
		v->pvalue->num = num_undefvalue();
	} else if (type == TYPE_ARRAY) {
		v->pvalue->array = NULL;
	} else if (type == TYPE_FCNT) {
		v->pvalue->fcnt.ftype = ftype;
		v->pvalue->fcnt.check_id = -1;
		if (ftype != FTYPE_USER && ftype != FTYPE_BUILTIN)
			FATAL_ERROR("vars_t_construct(): unknown ftype: %d", ftype);
		v->pvalue->fcnt.defargs = NULL;
		v->pvalue->fcnt.autolist = NULL;
		v->pvalue->fcnt.program = NULL;
		v->pvalue->fcnt.builtin_nb_args = -1;
		v->pvalue->fcnt.builtin0arg = NULL;
		v->pvalue->fcnt.builtin1arg = NULL;
		v->pvalue->fcnt.builtin2arg = NULL;
		v->pvalue->fcnt.builtin3arg = NULL;
	} else {
		FATAL_ERROR("Unknown symbol type: %d", type);
	}

	HASH_ADD_KEYPTR(hh, ctx->container.heads[type], v->name, slen, v);

	return v;
}

static vars_t *vars_t_construct_with_value(const char *name, const vars_value_t *pvalue)
{
	vars_t *v = vars_t_construct(name, pvalue->type, -1);
	vars_value_soft_copy(v->pvalue, pvalue);
	return v;
}

static void vars_t_destruct(vars_t *var)
{
	assert(ctx->lib_reg_number == num_get_current_lib_number());

	out_dbg("Destructing vars_t %s of type %s\n", var->name == NULL ? "<NULL>" : var->name, type_names[var->pvalue->type]);

	HASH_DEL(ctx->container.heads[var->pvalue->type], var);

	vars_value_destruct(var->pvalue);

	if (var->name != NULL) {
		free(var->name);
		var->name = NULL;
		free(var->pvalue);
		var->pvalue = NULL;
	}

	free(var);
}

static vars_t *find_var(const char *name, int type)
{
	vars_t *w;
	HASH_FIND_STR(ctx->container.heads[type], name, w);
	return w;
}

void var_delete(const char *name)
{
	vars_t *w;
	if ((w = find_var(name, TYPE_NUM)) != NULL) {
		vars_t_destruct(w);
	}
}

array_t **vars_array_get_ref(const char *name)
{
	vars_t *w;
	if ((w = find_var(name, TYPE_ARRAY)) == NULL) {
		out_dbg("vars_array_get_ref(): did not find array %s, creating one\n", name);
		const numptr *ppv;
		vars_array_set_value(name, 0, num_construct(), &ppv);
		if ((w = find_var(name, TYPE_ARRAY)) == NULL)
			FATAL_ERROR("%s", "Inconsistent data, ref 182");
	}
	return w->pvalue->array_ref ? w->pvalue->array_ref : &w->pvalue->array;
}

const numptr *vars_get_value(const char *name)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	out_dbg("Getting value of %s\n", name);

	vars_t *w = find_var(name, TYPE_NUM);
	if (w != NULL) {
		out_dbg("\t%s is %s\n", name, w->pvalue->num_ref ? "a reference" : "regular");
		return (w->pvalue->num_ref ? w->pvalue->num_ref : &w->pvalue->num);
	}

	out_dbg("\t%s is non-existent\n", name);
	return NULL;
}

const numptr *vars_array_get_value(const char *name, long int index, int is_becoming_lvalue)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	out_dbg("Getting value of %s[%d]\n", name, index);

	vars_t *w = find_var(name, TYPE_ARRAY);
	if (w != NULL) {

		out_dbg("\t%s[] is %s\n", name, w->pvalue->array_ref ? "a reference" : "regular");

		if (is_becoming_lvalue)
			copyonupdate_manage_copy(w->pvalue->array_ref ? *w->pvalue->array_ref : w->pvalue->array, FALSE);

		return array_get_value(w->pvalue->array_ref ? *w->pvalue->array_ref : w->pvalue->array, index);

	}
	out_dbg("\t%s[] is non-existent\n", name);
	return NULL;
}

	/*
	 * Copy the array given its name and returns a pointer to the copy.
	 * If the array does not exist, return NULL.
	 *
	 * */
array_t *vars_array_copy(const char *name)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	out_dbg("Copying array %s\n", name);

	vars_t *w = find_var(name, TYPE_ARRAY);
	if (w == NULL)
		return NULL;
	return array_t_get_a_copy(w->pvalue->array);
}

function_t *vars_get_function(const char *name)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	out_dbg("Getting function object of %s\n", name);

	vars_t *w = find_var(name, TYPE_FCNT);
	if (w != NULL) {

		out_dbg("\tFound %s\n", name);

		return &w->pvalue->fcnt;
	} else
		return NULL;
}

static int vars_set_value_core(const char *name, numptr new_value, vars_t *v, const numptr **ppvarnum)
{
	out_dbg("Setting value of %s\n", name);
	if (v == NULL) {
		out_dbg("\t%s is non-existent\n", name);
		v = vars_t_construct(name, TYPE_NUM, -1);
	} else {

		if (v->update_callback != NULL) {
			int r = v->update_callback(name, &new_value);
			if (r != ERROR_NONE) {
				num_destruct(&new_value);
				return r;
			}
		}

		if (!v->pvalue->num_ref) {
			out_dbg("\t%s is regular\n", name);
			num_destruct(&v->pvalue->num);
		} else {
			out_dbg("\t%s is a reference\n", name);
			num_destruct(v->pvalue->num_ref);
		}
	}

	if (!v->pvalue->num_ref) {
		v->pvalue->num = new_value;
		*ppvarnum = &v->pvalue->num;
	} else {
		*v->pvalue->num_ref = new_value;
		*ppvarnum = v->pvalue->num_ref;
	}

	return ERROR_NONE;
}

int vars_set_value(const char *name, numptr new_value, const numptr **ppvarnum)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *v = find_var(name, TYPE_NUM);
	return vars_set_value_core(name, new_value, v, ppvarnum);
}

void vars_set_update_callback(const char *name, int (*update_callback)(const char *name, numptr *pnum))
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *v = find_var(name, TYPE_NUM);
	if (v == NULL) {
		const numptr *ppvarnum;
		vars_set_value(name, num_construct(), &ppvarnum);
		v = find_var(name, TYPE_NUM);
		assert(v != NULL);
	}

	v->update_callback = update_callback;
}

static void vars_array_set_value_core(const char *name, long int index, const numptr new_value, vars_t *v, const numptr **ppvarnum)
{
	if (v == NULL) {
		v = vars_t_construct(name, TYPE_ARRAY, -1);
	}

	out_dbg("Setting value of %s[%d]\n", name, index);
	out_dbg("\t%s is %s\n", name, v->pvalue->array_ref ? "a reference" : "regular");

	array_set_value(v->pvalue->array_ref ? v->pvalue->array_ref : &v->pvalue->array, index, new_value, ppvarnum);
}

void vars_array_set_value(const char *name, long int index, const numptr new_value, const numptr **ppvarnum)
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *v = find_var(name, TYPE_ARRAY);
	vars_array_set_value_core(name, index, new_value, v, ppvarnum);
}

int vars_sort(void *a, void *b)
{
	return varname_cmp(((vars_t *)a)->name, ((vars_t *)b)->name);
}

void vars_display_all()
{

	assert(ctx->lib_reg_number == num_get_current_lib_number());

	int I;
	for (I = 0; I < TYPE_NB; ++I) {
		HASH_SORT(ctx->container.heads[I], vars_sort);
	}

	vars_t *w;
	for (w = ctx->container.heads[TYPE_NUM]; w != NULL; w = w->hh.next) {
		outstring(w->name, FALSE);
		outstring("=", FALSE);
		num_print(w->pvalue->num);
		outstring("", TRUE);
	}
	for (w = ctx->container.heads[TYPE_ARRAY]; w != NULL; w = w->hh.next) {
		size_t l = strlen(w->name) + 50;
		char *buf = malloc(l);
		snprintf(buf, l, "%s[]: %li element(s)", w->name, array_count(w->pvalue->array));
		outstring(buf, TRUE);
		free(buf);
	}
	for (w = ctx->container.heads[TYPE_FCNT]; w != NULL; w = w->hh.next) {
		outstring(w->name, FALSE);
		outstring("(", FALSE);
		function_t *f = &w->pvalue->fcnt;
		if (f->ftype == FTYPE_BUILTIN) {
			char c = 'a';
			int i;
			for (i = 0; i < f->builtin_nb_args; ++i) {
				outstring_1char(c);
				if (i < f->builtin_nb_args - 1)
					outstring(", ", FALSE);
				++c;
			}
			outstring(")", TRUE);
		} else if (f->ftype == FTYPE_USER) {
			defargs_t *dargs = f->defargs;
			while (dargs != NULL) {
				if (dargs->type == DARG_REF || dargs->type == DARG_ARRAYREF)
					outstring("*", FALSE);
				outstring(dargs->name, FALSE);
				if (dargs->type == DARG_ARRAYVALUE || dargs->type == DARG_ARRAYREF)
					outstring("[]", FALSE);
				dargs = dargs->next;
				if (dargs != NULL)
					outstring(", ", FALSE);
			}
			outstring(")", TRUE);
		} else {
			FATAL_ERROR("Unknown ftype: %d", f->ftype);
		}
	}
}

static void vars_value_soft_copy(vars_value_t *dst, const vars_value_t *src)
{
	dst->type = src->type;
	dst->num_ref = src->num_ref;
	dst->array_ref = src->array_ref;
	if (src->type == TYPE_NUM) {
		if (!src->num_ref)
			dst->num = src->num;
	} else if (src->type == TYPE_ARRAY) {
		if (!src->array_ref)
			dst->array = src->array;
	} else if (src->type == TYPE_FCNT)
		dst->fcnt = src->fcnt;
	else
		FATAL_ERROR("Unknown symbol type: %d for vars_value_t: %lu", src->type, src);
}

vars_keeper_t *vars_keeper_array_construct(int n)
{
	assert(n >= 0);

	if (n == 0)
		return NULL;

	vars_keeper_t *keeps = (vars_keeper_t *)malloc(sizeof(vars_keeper_t) * n);
	int i;
	for (i = 0; i < n; ++i) {
		keeps[i].is_used = FALSE;
	}
	return keeps;
}

void vars_send_to_keeper(vars_keeper_t *keeper, const char *name, const vars_value_t *new_value)
{

	assert(keeper != NULL);
	assert(!keeper->is_used);

	out_dbg("Sending %s to keeper, keep address = %lu\n", name, keeper);

	keeper->is_used = TRUE;
	keeper->ktype = new_value->type;

	vars_t *w;
	if ((w = find_var(name, new_value->type)) == NULL) {
		out_dbg("\tVariable %s not found\n", name);
		keeper->holds_a_value = FALSE;
		vars_t_construct_with_value(name, new_value);
	} else {
		out_dbg("\tVariable %s found\n", name);
		keeper->holds_a_value = TRUE;
		keeper->pvalue = w->pvalue;
		w->pvalue = (vars_value_t *)malloc(sizeof(vars_value_t));
		vars_value_soft_copy(w->pvalue, new_value);
	}

	out_dbg("New value type: %d, num_ref: %lu, array_ref: %lu\n", new_value->type, new_value->num_ref, new_value->array_ref);

}

void vars_recall_from_keeper(const char *name, vars_keeper_t *keeper)
{

	assert(keeper != NULL);

	if (!keeper->is_used) {
		out_dbg("Recall requested from unused keeper, keep address = %lu\n", keeper);
		return;
	}

	out_dbg("Recalling %s from keeper, keep address = %lu\n", name, keeper);

	vars_t *w = find_var(name, keeper->ktype);

	if (keeper->holds_a_value) {
		assert(w != NULL);
		out_dbg("\tKeeper has a value => replacing variable value with keeper's\n");
/*        if (!w->pvalue->num_ref && !w->pvalue->array_ref) {*/
			vars_value_destruct(w->pvalue);
			free(w->pvalue);
			w->pvalue = keeper->pvalue;
/*        } else {*/
/*            w->pvalue->num_ref = keeper->pvalue->num_ref;*/
/*            w->pvalue->array_ref = keeper->pvalue->array_ref;*/
/*        }*/
	} else if (w != NULL)  {
		out_dbg("\tUndefined keeper value => destructing variable\n");

		vars_t_destruct(w);

	} else {
		out_dbg("\tUndefined keeper value and variable not found => nothing to do\n");
	}
	keeper->is_used = FALSE;
}



/*-----------------------------------------------------------------------------
 *  arg_t and call_arg_t management
 *-----------------------------------------------------------------------------*/



defargs_t *defargs_construct(defarg_type_t type, const char *name)
{
	defargs_t *defarg = (defargs_t *)malloc(sizeof(defargs_t));
	defarg->type = type;
	defarg->name = (char *)name;
	defarg->next = NULL;
	return defarg;
}

void defargs_destruct(defargs_t *defargs)
{
	out_dbg("Entering defargs_destruct for %lu\n", defargs);
	defargs_t *keep_next;
	while (defargs != NULL) {
		keep_next = defargs->next;

		free(defargs->name);
		free(defargs);

		defargs = keep_next;
	}
}

int darg_type_is_of_same_namespace(int t1, int t2)
{
	if ((t1 == DARG_VALUE || t1 == DARG_REF) &&
		(t2 == DARG_VALUE || t2 == DARG_REF))
		return TRUE;
	if ((t1 == DARG_ARRAYVALUE || t1 == DARG_ARRAYREF) &&
		(t2 == DARG_ARRAYVALUE || t2 == DARG_ARRAYREF))
		return TRUE;
	return FALSE;
}

defargs_t *defargs_chain(defargs_t *base, defargs_t *append)
{
	/*
	 * *WARNING*
	 * Should save the base in the list to avoid systematical walk through
	 * the entire list to append one element, that has O(n^2) execution time.
	 *
	 * That said, a list of arguments should rarely go beyond a few dozens,
	 * and never beyond a few hundreds!
	 * By the way, the detection of duplicates is deeply O(n^2). Getting rid
	 * of it would require to do a "clean" quick-sort of the list, but I don't
	 * see the point for a list of arguments.
	 *
	 * Ultimately this warning is a warning, not a FIXME.
	 */
	assert(base != NULL && append != NULL);
	if (base == defarg_t_badarg || append == defarg_t_badarg)
		return defarg_t_badarg;

	defargs_t *w = base;
	defargs_t *prec;
	do {
		out_dbg("Comparing %s(%d) with %s(%d)\n", w->name, w->type, append->name, append->type);
		if (darg_type_is_of_same_namespace(w->type, append->type) && !varname_cmp(w->name, append->name))
			return defarg_t_badarg;
		prec = w;
		w = w->next;
	} while (w != NULL);
	prec->next = append;
	return base;
}



/*-----------------------------------------------------------------------------
 *  function_t management
 *-----------------------------------------------------------------------------*/



	/*
	 *   *WARNING*
	 *
	 * pexec_ctx CAN BE NULL
	 * ... as is the case when called from register_builtin_function()
	 *
	 * */
static void destruct_function_if_defined(const char *name, exec_ctx_t *pexec_ctx)
{
	assert(ctx->lib_reg_number == num_get_current_lib_number());

	vars_t *w;
	if ((w = find_var(name, TYPE_FCNT)) != NULL) {
		vars_t_destruct(w);
		if (pexec_ctx != NULL) {
			set_exec_error_message(pexec_ctx, "Redefinition of function %s", name);
			outln_exec_error(ERROR_CUSTOM, pexec_ctx, TRUE);
		} else {
			outln_warning("Redefinition of function %s", name);
		}
	}
}

void vars_user_function_construct(char *name, defargs_t *defargs, program_t *program, int is_void, const code_location_t loc)
{
	assert(ctx->lib_reg_number == num_get_current_lib_number());

	exec_ctx_t exec_ctx = construct_exec_ctx_t();
	exec_ctx.ploc = &loc;

	if (defargs == defarg_t_badarg) {

		set_exec_error_message(&exec_ctx, "Function %s not created: duplicate parameter names", name);
		outln_exec_error(ERROR_CUSTOM, &exec_ctx, FALSE);

		program_destruct(program);
		free(name);
		destruct_exec_ctx_t(&exec_ctx);
		return;
	}

	destruct_function_if_defined(name, &exec_ctx);

	vars_t *f = vars_t_construct(name, TYPE_FCNT, FTYPE_USER);

	f->pvalue->fcnt.is_void = is_void;
	f->pvalue->fcnt.defargs = defargs;
	f->pvalue->fcnt.program = program;
	program_gather_defargs(&f->pvalue->fcnt.autolist, &f->pvalue->fcnt.program);
	defargs_t *al = f->pvalue->fcnt.autolist;
	while (al != NULL) {
		defargs_t *param = f->pvalue->fcnt.defargs;
		while (param != NULL) {
			if (darg_type_is_of_same_namespace(param->type, al->type) && !varname_cmp(param->name, al->name)) {

				set_exec_error_message(&exec_ctx, "Function %s not created: duplicate names between parameters and autolist", name);
				outln_exec_error(ERROR_CUSTOM, &exec_ctx, FALSE);

				vars_t_destruct(f);
				destruct_exec_ctx_t(&exec_ctx);
				return;
			}
			param = param->next;
		}
		al = al->next;
	}
	destruct_exec_ctx_t(&exec_ctx);

	out_dbg("Constructed function: %lu, name: %s, defargs: %lu, autolist: %lu, program: %lu\n", f, f->name, f->pvalue->fcnt.defargs, f->pvalue->fcnt.autolist, f->pvalue->fcnt.program);
}

void register_builtin_function(const char *name, int nb_args, void *f, int is_void)
{
	assert(ctx->lib_reg_number == num_get_current_lib_number());

	destruct_function_if_defined(name, NULL);

	vars_t *v = vars_t_construct(name, TYPE_FCNT, FTYPE_BUILTIN);
	v->pvalue->fcnt.is_void = is_void;
	v->pvalue->fcnt.builtin_nb_args = nb_args;
	if (nb_args == 0)
		v->pvalue->fcnt.builtin0arg = f;
	else if (nb_args == 1)
		v->pvalue->fcnt.builtin1arg = f;
	else if (nb_args == 2)
		v->pvalue->fcnt.builtin2arg = f;
	else if (nb_args == 3)
		v->pvalue->fcnt.builtin3arg = f;
	else if (nb_args > 3)
		FATAL_ERROR("Builtin functions with %d arguments is not supported (maximum: 3)", nb_args);
	out_dbg("Constructed function: %lu, name: %s, nb args: %d, function: %lu\n", v, v->name, nb_args, f);
}

static void function_destruct(function_t f)
{

	out_dbg("Destructing function: defargs: %lu, program: %lu\n", f.defargs, f.program);

	if (f.ftype == FTYPE_USER) {
		if (f.defargs != NULL) {
			defargs_destruct(f.defargs);
			f.defargs = NULL;
		}
		if (f.autolist != NULL) {
			defargs_destruct(f.autolist);
			f.autolist = NULL;
		}
		if (f.ftype == FTYPE_USER) {
			program_destruct(f.program);
			f.program = NULL;
		}
	}
}

void check_functions()
{
	out_dbg("check_functions execution\n");
	exec_ctx_t exec_ctx = construct_exec_ctx_t();
	vars_t *w;
	check_t check;
	check.id = global_check_id;
	for (w = ctx->container.heads[TYPE_FCNT]; w != NULL; w = w->hh.next) {
		if (w->pvalue->fcnt.ftype == FTYPE_USER) {
			out_dbg("Will now check the function %s\n", w->name);
			function_t *f = &w->pvalue->fcnt;
			exec_ctx.function_name = w->name;
			check.is_void = f->is_void;
			check.is_inside_loop = FALSE;
			check.i_want_a_value = FALSE;

				/*
				 * Assign check_id *before* call to program_check() to avoid a duplicate warning or error message
				 * in case it occurs in a recursive function.
				 *
				 * */
			f->check_id = check.id;

			program_check(f->program, &exec_ctx, &check);
		}
	}
	destruct_exec_ctx_t(&exec_ctx);
	++global_check_id;
}

