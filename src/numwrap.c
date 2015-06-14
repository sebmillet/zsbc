/*
 * =====================================================================================
 *
 *       Filename:  numwrap.c
 *
 *    Description:  Wrapper layer to provide a unique interface to zsbc
 *    				for big numbers calculations, while using libgmp or libbc
 *    				behind the scene.
 *
 *        Version:  1.0
 *        Created:  14/06/2015 13:16:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet
 *
 * =====================================================================================
 */

#include "numwrap.h"
#include <stdio.h>
#include <gmp.h>

static int num_count_ref = 0;

static void (*Llib_may_i_ask_you_to_identify_yourself_please)();
static numptr (*Lconstruct)();
static numptr (*Lconstruct_from_num)(const numptr num);
static numptr (*Lconstruct_from_str)(const char *str, int base);
static void (*Ldestruct)();

static void (*Lcopy)(numptr numdest, const numptr numsrc);
static void (*Lreset)(numptr num);
static void (*Lprint)(const numptr num, int base);
static long int (*Lgetlongint)(const numptr num);

static int (*Ladd)(numptr r, const numptr a, const numptr b);
static int (*Lsub)(numptr r, const numptr a, const numptr b);
static int (*Lmul)(numptr r, const numptr a, const numptr b);
static int (*Ldiv)(numptr r, const numptr a, const numptr b);
static int (*Lpow)(numptr r, const numptr a, const numptr b);
static int (*Lmod)(numptr r, const numptr a, const numptr b);
static int (*Lneg)(numptr r, const numptr a);

static void gmp_lib_may_i_ask_you_to_identify_yourself_please();
static numptr gmp_construct();
static numptr gmp_construct_from_num(const numptr num);
static numptr gmp_construct_from_str(const char *str, int base);
static void gmp_destruct(numptr num);
static void gmp_copy(numptr numdest, const numptr numsrc);
static void gmp_reset(numptr num);
static void gmp_print(const numptr num, int base);
static long int gmp_getlongint(const numptr num);
static int gmp_add(numptr r, const numptr a, const numptr b);
static int gmp_sub(numptr r, const numptr a, const numptr b);
static int gmp_mul(numptr r, const numptr a, const numptr b);
static int gmp_div(numptr r, const numptr a, const numptr b);
static int gmp_pow(numptr r, const numptr a, const numptr b);
static int gmp_mod(numptr r, const numptr a, const numptr b);
static int gmp_neg(numptr r, const numptr a);


/*-----------------------------------------------------------------------------
 *  Functions shared across all NUMLIB types
 *-----------------------------------------------------------------------------*/


int num_get_count_ref()
{
	return num_count_ref;
}

void num_lib_may_i_ask_you_to_identify_yourself_please()
{
	Llib_may_i_ask_you_to_identify_yourself_please();
}

numptr num_construct()
{
	out_dbg("Constructing one number with default value (0)\n");
	numptr r = Lconstruct();
	if (r != NULL)
		++num_count_ref;
	return r;
}

numptr num_construct_from_num(const numptr num)
{
	out_dbg("Constructing one number from another one\n");
	numptr r = Lconstruct_from_num(num);
	if (r != NULL)
		++num_count_ref;
	return r;
}

numptr num_construct_from_str(const char *str, int base)
{
	out_dbg("Constructing one number from a string\n");
	numptr r = Lconstruct_from_str(str, base);
	if (r != NULL)
		++num_count_ref;
	return r;
}

void num_destruct(numptr num)
{
	out_dbg("Destructing one number\n");
	Ldestruct(num);
	--num_count_ref;
}

void num_copy(numptr numdest, const numptr numsrc) { Lcopy(numdest, numsrc); }
void num_reset(numptr num) { Lreset(num); }
void num_print(const numptr num, int base) { Lprint(num, base); }
long int num_getlongint(const numptr num) { return Lgetlongint(num); }
int num_add(numptr r, const numptr a, const numptr b) { return Ladd(r, a, b); }
int num_sub(numptr r, const numptr a, const numptr b) { return Lsub(r, a, b); }
int num_mul(numptr r, const numptr a, const numptr b) { return Lmul(r, a, b); }
int num_div(numptr r, const numptr a, const numptr b) { return Ldiv(r, a, b); }
int num_pow(numptr r, const numptr a, const numptr b) { return Lpow(r, a, b); }
int num_mod(numptr r, const numptr a, const numptr b) { return Lmod(r, a, b); }
int num_neg(numptr r, const numptr a) { return Lneg(r, a); }


/*-----------------------------------------------------------------------------
 *  GMP functions - for when num_lib = NUMLIB_GMP
 *-----------------------------------------------------------------------------*/


void num_init_gmp()
{
	Llib_may_i_ask_you_to_identify_yourself_please = gmp_lib_may_i_ask_you_to_identify_yourself_please;
	Lconstruct = gmp_construct;
	Lconstruct_from_num = gmp_construct_from_num;
	Lconstruct_from_str = gmp_construct_from_str;
	Ldestruct = gmp_destruct;
	Lcopy = gmp_copy;
	Lreset = gmp_reset;
	Lprint = gmp_print;
	Lgetlongint = gmp_getlongint;
	Ladd = gmp_add;
	Lsub = gmp_sub;
	Lmul = gmp_mul;
	Ldiv = gmp_div;
	Lpow = gmp_pow;
	Lmod = gmp_mod;
	Lneg = gmp_neg;
}

static void gmp_lib_may_i_ask_you_to_identify_yourself_please()
{
	out("GMP library version %s\n", gmp_version);
}

static numptr gmp_construct()
{
	mpz_t *mp = (mpz_t *)malloc(sizeof(mpz_t));
	mpz_init(*mp);
	return (numptr)mp;
}

static numptr gmp_construct_from_num(const numptr num)
{
	mpz_t *mp = (mpz_t *)malloc(sizeof(mpz_t));
	mpz_init_set(*mp, *(mpz_t *)num);
	return (numptr)mp;
}

static numptr gmp_construct_from_str(const char *str, int base)
{
	mpz_t *mp = (mpz_t *)malloc(sizeof(mpz_t));
	mpz_init_set_str(*mp, str, base);
	return (numptr)mp;
}

static void gmp_destruct(numptr num)
{
	mpz_t *mp = (mpz_t *)num;
	mpz_clear(*mp);
	free(mp);
}

static void gmp_copy(numptr numdest, const numptr numsrc)
{
	mpz_set(*(mpz_t *)numdest, *(const mpz_t *)numsrc);
}

static void gmp_reset(numptr num)
{
	mpz_set_ui(*(mpz_t *)num, 0);
}

static void gmp_print(const numptr num, int base)
{
	mpz_out_str(NULL, base, *(const mpz_t *)num);
	printf("\n");
}

static long int gmp_getlongint(const numptr num)
{
	return mpz_get_si(*(mpz_t *)num);
}

static int gmp_add(numptr r, const numptr a, const numptr b) { mpz_add(*(mpz_t *)r, *(const mpz_t *)a, *(const mpz_t *)b); return 0; }
static int gmp_sub(numptr r, const numptr a, const numptr b) { mpz_sub(*(mpz_t *)r, *(const mpz_t *)a, *(const mpz_t *)b); return 0; }
static int gmp_mul(numptr r, const numptr a, const numptr b) { mpz_mul(*(mpz_t *)r, *(const mpz_t *)a, *(const mpz_t *)b); return 0; }

static int gmp_div(numptr r, const numptr a, const numptr b)
{
	if (!mpz_cmp_ui(*(mpz_t *)b, 0))
		return ERR_DIV0;
	mpz_tdiv_q(*(mpz_t *)r, *(const mpz_t *)a, *(const mpz_t *)b);
	return 0;
}

static int gmp_pow(numptr r, const numptr a, const numptr b)
{
	unsigned long int exp = mpz_get_ui(*(mpz_t *)b);
	mpz_pow_ui(*(mpz_t *)r, *(const mpz_t *)a, exp);
	return 0;
}

static int gmp_mod(numptr r, const numptr a, const numptr b)
{
	if (!mpz_cmp_ui(*(mpz_t *)b, 0))
		return ERR_DIV0;
	mpz_mod(*(mpz_t *)r, *(const mpz_t *)a, *(const mpz_t *)b);
	return 0;
}

static int gmp_neg(numptr r, const numptr a)
{
	mpz_neg(*(mpz_t *)r, *(mpz_t *)a);
	return 0;
}

