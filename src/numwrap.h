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

struct IndianKO;
typedef struct IndianKO* numptr;

enum {NUMLIB_GMP = 0, NUMLIB_LAST = NUMLIB_GMP};

int num_get_count_ref();

void num_init_gmp();

void num_lib_may_i_ask_you_to_identify_yourself_please();
numptr num_construct();
numptr num_construct_from_num(const numptr num);
numptr num_construct_from_str(const char *str, int base);
void num_destruct(numptr num);
void num_copy(numptr numdest, const numptr numsrc);
void num_reset(numptr num);
void num_print(const numptr num, int base);
long int num_getlongint(const numptr num);

int num_add(numptr r, const numptr a, const numptr b);
int num_sub(numptr r, const numptr a, const numptr b);
int num_mul(numptr r, const numptr a, const numptr b);
int num_div(numptr r, const numptr a, const numptr b);
int num_pow(numptr r, const numptr a, const numptr b);
int num_mod(numptr r, const numptr a, const numptr b);
int num_neg(numptr r, const numptr a);

#endif	/* NUMWRAP_H */

