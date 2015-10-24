/*
 * =====================================================================================
 *
 *       Filename:  common.h
 *
 *    Description:  Header file for most zsbc source files.
 *
 *        Version:  1.0
 *        Created:  03/06/2015 23:22:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet (smt), milletseb@laposte.net
 *
 * =====================================================================================
 */


#if defined(_WIN32) || defined(_WIN64)
#define MY_WINDOWS
#else
#define MY_LINUX
#endif

#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <assert.h>

#ifdef HAVE_CONFIG_H
#include "../config.h"
#else
/* Defines some PACKAGE* constants in case config.h is not available */
#include "../extracfg.h"
#endif

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#ifdef DEBUG
#define out_dbg(...) \
	out_dbg_core(__FILE__, __LINE__, __VA_ARGS__)
#else
#define out_dbg(...) ;
#endif

#define ENV_ARGS "ZSBC_ENV_ARGS"

const char *VAR_LAST;

	/*
	 * The constants below, in this order, are used to define corresponding error
	 * messages in the array of strings table_errors (main.c)
	 *  */
#define ERROR_NONE						0
#define ERROR_DIV0						1
#define ERROR_NEGATIVE_EXP				2
#define ERROR_FUNCTION_NOT_DEFINED		3
#define ERROR_PARAMETER_NUMBER_MISMATCH	4
#define ERROR_BREAK						5	/* Not an error */
#define ERROR_CONTINUE					6	/* Not an error */
#define ERROR_RETURN					7
#define ERROR_ARGTYPE_MISMATCH			8
#define ERROR_ILLEGAL_VALUE				9
#define ERROR_SQRT_OF_NEG				10
#define ERROR_ARRAY_OUT_OF_BOUNDS		11
#define ERROR_INVALID_NUMBER			12
#define ERROR_CUSTOM					13	/* Error string defined at runtime */
#define ERROR_LAST						13

#define L_ENFORCE	(-1)
#define L_ERROR		0
#define L_WARNING	1
#define L_QUIET		2
#define L_NORMAL	3
#define L_VERBOSE	4
#define L_DEBUG		5
int out(int level, const char *fmt, ...);
int outln(int level, const char *fmt, ...);
int outln_error(const char *fmt, ...);
int outln_warning(const char *fmt, ...);
void fatalln(const char *file, int line, const char *fmt, ...);
#define FATAL_ERROR(s, ...) \
	fatalln(__FILE__, __LINE__, s, __VA_ARGS__)
int out_dbg_core(const char *filename, int line, const char *fmt, ...);

void outstring_1char(int c);
void outstring(const char *s, int append_newline);
void outstring_set_line_length(int ll);

char *s_strncpy(char *dest, const char *src, size_t n);
char *s_strncat(char *dest, const char *src, size_t n);
char *s_alloc_and_copy(char **dst, const char *src);

char *interpret_escape_sequences_alloc(const char *s);

void lib_list();

#define UNUSED(x) (void)(x)

typedef enum {DARG_VALUE, DARG_ARRAYVALUE, DARG_REF, DARG_ARRAYREF} defarg_type_t;
struct defargs_t {
	defarg_type_t type;
	char *name;
	struct defargs_t *next;
};
typedef struct defargs_t defargs_t;
defargs_t *defargs_chain(defargs_t *base, defargs_t *append);

int varname_cmp(const char *n1, const char *n2);

typedef struct code_location_t {
	int is_set;
	const char *file_name;
	int first_line, first_column;
	int last_line, last_column;
} code_location_t;

code_location_t construct_unset_code_location_t();

typedef struct exec_ctx_t {
	const char *function_name;
	const code_location_t *ploc;
	char *error_message;
} exec_ctx_t;

exec_ctx_t construct_exec_ctx_t();
void set_exec_error_message(exec_ctx_t *exec_ctx, const char *fmt, ...);
void outln_exec_error(int e, exec_ctx_t *exec_ctx, int is_warning);

void loc_reset();

struct function_t;
typedef struct function_t function_t;
typedef struct check_t {
	int id;
	int is_void;
	int is_inside_loop;
	int i_want_a_value;
} check_t;
void check_functions();

#endif /* COMMON_H */

