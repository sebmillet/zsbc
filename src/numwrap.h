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

void num_init();

int num_get_count_ref();

void num_lib_may_i_ask_you_to_identify_yourself_please();
numptr num_undefvalue();
void num_postcleanup(numptr *pnum);
int num_is_not_initialized(numptr pnum);
numptr num_construct();
numptr num_construct_from_num(const numptr num);
numptr num_construct_from_str(const char *str, int base);
void num_destruct(numptr *pnum);
void num_print(const numptr num, int base);
int num_is_zero(const numptr num);
long int num_getlongint(const numptr num);

int num_add(numptr *pr, const numptr a, const numptr b);
int num_sub(numptr *pr, const numptr a, const numptr b);
int num_mul(numptr *pr, const numptr a, const numptr b);
int num_div(numptr *pr, const numptr a, const numptr b);
int num_pow(numptr *pr, const numptr a, const numptr b);
int num_mod(numptr *pr, const numptr a, const numptr b);
int num_neg(numptr *pr, const numptr a);


/*-----------------------------------------------------------------------------
 *  BC specific
 *-----------------------------------------------------------------------------*/


//void num_init_libbc();


/*-----------------------------------------------------------------------------
 *  GMP specific
 *-----------------------------------------------------------------------------*/


//void num_init_gmp();

#endif	/* NUMWRAP_H */

