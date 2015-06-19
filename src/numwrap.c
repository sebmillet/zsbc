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


	/* GMP LIBRARY */
#include <gmp.h>


	/* BC LIBRARY */
#include "number.h"
#define BC_VERSION	"1.06.95"

static int num_count_ref = 0;

static void (*Llib_may_i_ask_you_to_identify_yourself_please)();
static numptr (*Lconstruct)();
static numptr (*Lconstruct_from_num)(const numptr num);
static numptr (*Lconstruct_from_str)(const char *str, int base);
static void (*Ldestruct)(numptr *pnum);

static void (*Lprint)(const numptr num, int base);
static int (*Lis_zero)(const numptr num);
static long int (*Lgetlongint)(const numptr num);

static int (*Ladd)(numptr *pr, const numptr a, const numptr b);
static int (*Lsub)(numptr *pr, const numptr a, const numptr b);
static int (*Lmul)(numptr *pr, const numptr a, const numptr b);
static int (*Ldiv)(numptr *pr, const numptr a, const numptr b);
static int (*Lpow)(numptr *pr, const numptr a, const numptr b);
static int (*Lmod)(numptr *pr, const numptr a, const numptr b);
static int (*Lneg)(numptr *pr, const numptr a);


/*-----------------------------------------------------------------------------
 *  Functions shared across all number libs
 *-----------------------------------------------------------------------------*/


int num_get_count_ref()
{
	return num_count_ref;
}

void num_lib_may_i_ask_you_to_identify_yourself_please()
{
	Llib_may_i_ask_you_to_identify_yourself_please();
}

numptr num_preinit() { return NULL; }
void num_postcleanup(numptr *pnum) { *pnum = NULL; }
int num_is_not_initialized(numptr num) { return (num == NULL); }

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

void num_destruct(numptr *pnum)
{
	if (num_is_not_initialized(*pnum))
		return;
	out_dbg("Destructing one number\n");
	Ldestruct(pnum);
	assert(num_is_not_initialized(*pnum));
	--num_count_ref;
}

void num_print(const numptr num, int base) {
	Lprint(num, base);
}

int num_is_zero(const numptr num) {
	return Lis_zero(num);
}

long int num_getlongint(const numptr num) {
	return Lgetlongint(num);
}

int num_add(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	return Ladd(pr, a, b);
}

int num_sub(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	return Lsub(pr, a, b);
}

int num_mul(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	return Lmul(pr, a, b);
}

int num_div(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	if (num_is_zero(b))
		return ERR_DIV0;
	return Ldiv(pr, a, b);
}

int num_pow(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	return Lpow(pr, a, b);
}

int num_mod(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	if (num_is_zero(b))
		return ERR_DIV0;
	return Lmod(pr, a, b);
}

int num_neg(numptr *pr, const numptr a)
{
	assert(num_is_not_initialized(*pr));
	return Lneg(pr, a);
}


/*-----------------------------------------------------------------------------
 *  GMP library functions
 *-----------------------------------------------------------------------------*/


static void gmp_lib_may_i_ask_you_to_identify_yourself_please();
static numptr gmp_construct();
static numptr gmp_construct_from_num(const numptr num);
static numptr gmp_construct_from_str(const char *str, int base);
static void gmp_destruct(numptr *num);
static void gmp_print(const numptr num, int base);
static int gmp_is_zero(const numptr num);
static long int gmp_getlongint(const numptr num);
static int gmp_add(numptr *pr, const numptr a, const numptr b);
static int gmp_sub(numptr *pr, const numptr a, const numptr b);
static int gmp_mul(numptr *pr, const numptr a, const numptr b);
static int gmp_div(numptr *pr, const numptr a, const numptr b);
static int gmp_pow(numptr *pr, const numptr a, const numptr b);
static int gmp_mod(numptr *pr, const numptr a, const numptr b);
static int gmp_neg(numptr *pr, const numptr a);

void num_init_gmp()
{
	Llib_may_i_ask_you_to_identify_yourself_please = gmp_lib_may_i_ask_you_to_identify_yourself_please;
	Lconstruct = gmp_construct;
	Lconstruct_from_num = gmp_construct_from_num;
	Lconstruct_from_str = gmp_construct_from_str;
	Ldestruct = gmp_destruct;
	Lprint = gmp_print;
	Lis_zero = gmp_is_zero;
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

static void gmp_destruct(numptr *pnum)
{
	mpz_t *mp = (mpz_t *)(*pnum);
	mpz_clear(*mp);
	free(mp);
	num_postcleanup(pnum);
}

static void gmp_print(const numptr num, int base)
{
	mpz_out_str(NULL, base, *(const mpz_t *)num);
	printf("\n");
}

static int gmp_is_zero(const numptr num)
{
	return !mpz_cmp_ui(*(mpz_t *)num, 0);
}

static long int gmp_getlongint(const numptr num)
{
	return mpz_get_ui(*(mpz_t *)num);
}

static int gmp_add(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	mpz_add(*(mpz_t *)*pr, *(const mpz_t *)a, *(const mpz_t *)b);
	return 0;
}

static int gmp_sub(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	mpz_sub(*(mpz_t *)*pr, *(const mpz_t *)a, *(const mpz_t *)b);
	return 0;
}

static int gmp_mul(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	mpz_mul(*(mpz_t *)*pr, *(const mpz_t *)a, *(const mpz_t *)b);
	return 0;
}

static int gmp_div(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
		/*  The calling function, num_div, has checked whether or not b is null */
	mpz_tdiv_q(*(mpz_t *)*pr, *(const mpz_t *)a, *(const mpz_t *)b);
	return 0;
}

static int gmp_pow(numptr *pr, const numptr a, const numptr b)
{
	unsigned long int exp = mpz_get_ui(*(mpz_t *)b);
	*pr = num_construct();
	mpz_pow_ui(*(mpz_t *)*pr, *(const mpz_t *)a, exp);
	return 0;
}

static int gmp_mod(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
		/*  The calling function, num_mod, has checked whether or not b is null */
	mpz_mod(*(mpz_t *)*pr, *(const mpz_t *)a, *(const mpz_t *)b);
	return 0;
}

static int gmp_neg(numptr *pr, const numptr a)
{
	*pr = num_construct();
	mpz_neg(*(mpz_t *)*pr, *(mpz_t *)a);
	return 0;
}


/*-----------------------------------------------------------------------------
 *  BC functions
 *-----------------------------------------------------------------------------*/


static int libbc_scale;
#define LIBBC_DEFAULT_SCALE	0
static int libbc_get_scale();
static void libbc_set_scale(int scale);

static void libbc_lib_may_i_ask_you_to_identify_yourself_please();
static numptr libbc_construct();
static numptr libbc_construct_from_num(const numptr num);
static numptr libbc_construct_from_str(const char *str, int base);
static void libbc_destruct(numptr *pnum);
static void libbc_print(const numptr num, int base);
static int libbc_is_zero(const numptr num);
static long int libbc_getlongint(const numptr num);
static int libbc_add(numptr *pr, const numptr a, const numptr b);
static int libbc_sub(numptr *pr, const numptr a, const numptr b);
static int libbc_mul(numptr *pr, const numptr a, const numptr b);
static int libbc_div(numptr *pr, const numptr a, const numptr b);
static int libbc_pow(numptr *pr, const numptr a, const numptr b);
static int libbc_mod(numptr *pr, const numptr a, const numptr b);
static int libbc_neg(numptr *pr, const numptr a);

int libbc_get_scale()
{
	return libbc_scale;
}

void libbc_set_scale(int scale)
{
	libbc_scale = scale;
}

void num_init_libbc()
{
	bc_init_numbers();
	libbc_set_scale(LIBBC_DEFAULT_SCALE);

	Llib_may_i_ask_you_to_identify_yourself_please = libbc_lib_may_i_ask_you_to_identify_yourself_please;
	Lconstruct = libbc_construct;
	Lconstruct_from_num = libbc_construct_from_num;
	Lconstruct_from_str = libbc_construct_from_str;
	Ldestruct = libbc_destruct;
	Lprint = libbc_print;
	Lis_zero = libbc_is_zero;
	Lgetlongint = libbc_getlongint;
	Ladd = libbc_add;
	Lsub = libbc_sub;
	Lmul = libbc_mul;
	Ldiv = libbc_div;
	Lpow = libbc_pow;
	Lmod = libbc_mod;
	Lneg = libbc_neg;
}

static void libbc_lib_may_i_ask_you_to_identify_yourself_please()
{
	out("BC library version %s\n", BC_VERSION);
}

static numptr libbc_construct()
{
	bc_num bcn = NULL;
	bc_init_num(&bcn);
	return (numptr)bcn;
}

static numptr libbc_construct_from_num(const numptr num)
{
	bc_num bcn = bc_copy_num((bc_num)num);
	return (numptr)bcn;
}

static numptr libbc_construct_from_str(const char *str, int base)
{
		/* FIXME
		 * At the moment, ignores the base parameter as bc_str2num works
		 * in base 10 only.
		 * Need to write a function that walks through str assuming 'base'
		 * being used, ranging from 2 to 16 as per libbc usage.
		*/
	bc_num bcn = NULL;
	bc_str2num(&bcn, (char *)str, libbc_get_scale());
	return (numptr)bcn;
}

static void libbc_destruct(numptr *pnum)
{
	bc_free_num((bc_num *)pnum);
}

static void myputchar(int c)
{
	putchar(c);
}

static void libbc_print(const numptr num, int base)
{
	bc_out_num((bc_num)num, 10, myputchar, 0);
	printf("\n");
}

static int libbc_is_zero(const numptr num)
{
	return bc_is_zero((bc_num)num);
}

static long int libbc_getlongint(const numptr num)
{
	return bc_num2long((bc_num)num);
}

static int libbc_add(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	int na = ((bc_num)a)->n_scale;
	int nb = ((bc_num)b)->n_scale;
	int scale_min = (na < nb ? nb : na);
	bc_add((bc_num)a, (bc_num)b, (bc_num *)pr, scale_min);
	return 0;
}

static int libbc_sub(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	int na = ((bc_num)a)->n_scale;
	int nb = ((bc_num)b)->n_scale;
	int scale_min = (na < nb ? nb : na);
	bc_sub((bc_num)a, (bc_num)b, (bc_num *)pr, scale_min);
	return 0;
}

static int libbc_mul(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	bc_multiply((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());
	return 0;
}

static int libbc_div(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	bc_divide((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());
	return 0;
}

static int libbc_pow(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	bc_raise((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());
	return 0;
}

static int libbc_mod(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	bc_modulo((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());
	return 0;
}

static int libbc_neg(numptr *pr, const numptr a)
{
	*pr = num_construct();
	int na = ((bc_num)a)->n_scale;
	bc_sub(_zero_, (bc_num)a, (bc_num *)pr, na);
	return 0;
}

