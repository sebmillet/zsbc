/*
 * =====================================================================================
 *
 *       Filename:  numwrap.h
 *
 *    Description:  Header file of numwrap.c.
 *
 *        Version:  1.0
 *        Created:  14/06/2015 13:18:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet
 *
 * =====================================================================================
 */


#ifndef NUMWRAP_H
#define NUMWRAP_H

#include "common.h"

struct ToBeOrNotToBeAStructThatIsTheQuestion;
typedef struct ToBeOrNotToBeAStructThatIsTheQuestion* numptr;

struct exec_ctx_t {
	const char *function_name;
	const code_location_t *ploc;
	char *error_message;
	exec_ctx_t *parent;
	numptr modulo;
};

typedef struct libinfo_t {
	const char *id;
	const char *description;
	const char *libname;
	const char *version;
	const char *number_set;
} libinfo_t;

void num_init(int switch_to_first_registered_library);
void num_terminate();

int num_get_current_lib_number();
int num_libswitch(const char *id);
void num_lib_enumerate(char **paraml, libinfo_t *libinfo);
const libinfo_t *num_lib_get_current();

int num_get_count_ref();

const char *num_identify_yourself();
numptr num_undefvalue();
void num_postcleanup(numptr *pnum);
int num_is_not_initialized(numptr pnum);
numptr num_construct();
numptr num_construct_from_num(const numptr num);
int num_construct_from_str(const char *str, numptr *pnum);
numptr num_construct_from_int(int n);
void num_destruct(numptr *pnum);
void num_print(const numptr num);
int num_is_zero(const numptr num);
long int num_getlongint(const numptr num);

int num_add(numptr *pr, const numptr a, const numptr b);
int num_sub(numptr *pr, const numptr a, const numptr b);
int num_mul(numptr *pr, const numptr a, const numptr b);
int num_div(numptr *pr, const numptr a, const numptr b);
int num_pow(numptr *pr, const numptr a, const numptr b);
int num_powmod(numptr *pr, const numptr a, const numptr b, const numptr c);
int num_mod(numptr *pr, const numptr a, const numptr b);
int num_invmod(numptr *pr, const numptr a, const numptr b);
int num_neg(numptr *pr, const numptr a);
int num_cmplt(numptr *pr, const numptr a, const numptr b);
int num_cmple(numptr *pr, const numptr a, const numptr b);
int num_cmpgt(numptr *pr, const numptr a, const numptr b);
int num_cmpge(numptr *pr, const numptr a, const numptr b);
int num_cmpeq(numptr *pr, const numptr a, const numptr b);
int num_cmpne(numptr *pr, const numptr a, const numptr b);
int num_and(numptr *pr, const numptr a, const numptr b);
int num_or(numptr *pr, const numptr a, const numptr b);
int num_not(numptr *pr, const numptr a);
int num_want_automatic_invmod();

int num_maxbase();
int num_scalemax();

#endif	/* NUMWRAP_H */

