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
#include "vars.h"	/* Needed for context management */

#include <stdio.h>
#include <string.h>
int asprintf(char **strp, const char *fmt, ...);
char *strcasestr(const char *haystack, const char *needle);


	/* GMP LIBRARY */
#include <gmp.h>
static void gmp_register();


	/* BC LIBRARY */
#include "number.h"
#define BC_VERSION	"1.06.95"
static void libbc_register();


typedef struct lib_t {
	const char *id;
	const char *description;
	const char *libname;
	const char *version;
	void (*libactivate)();
	void (*libterminate)();

	context_t *context;
	int reg_number;		/* Live ID given at run time to uniquely identify the library */

	struct lib_t *next;
} lib_t;
lib_t *libhead = NULL;
lib_t *libcurrent = NULL;
static void lib_register(const char *id, const char *description, const char *libname, const char *version,
	void (*libactivate)(), void (*libterminate)());
static void libswitch(lib_t *l, int quiet);

static int num_count_ref = 0;

static const char* (*Llib_identify_yourself)();
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
static int (*Lcmplt)(numptr *pr, const numptr a, const numptr b);
static int (*Lcmple)(numptr *pr, const numptr a, const numptr b);
static int (*Lcmpgt)(numptr *pr, const numptr a, const numptr b);
static int (*Lcmpge)(numptr *pr, const numptr a, const numptr b);
static int (*Lcmpeq)(numptr *pr, const numptr a, const numptr b);
static int (*Lcmpne)(numptr *pr, const numptr a, const numptr b);
static int (*Land)(numptr *pr, const numptr a, const numptr b);
static int (*Lor)(numptr *pr, const numptr a, const numptr b);
static int (*Lnot)(numptr *pr, const numptr a);


/*-----------------------------------------------------------------------------
 *  Functions shared across all number libs
 *-----------------------------------------------------------------------------*/


void num_init()
{

	gmp_register();
	libbc_register();

		/* By default, activate the first registered library */
	lib_t *l = libhead;
	while (l->next != NULL)
		l = l->next;
	libswitch(l, FALSE);
}

void num_terminate()
{
	lib_t *l = libhead;
	lib_t *lnext;
	for(l = libhead; l != NULL; l = lnext) {
		libswitch(l, TRUE);

		context_destruct(l->context);
		l->libterminate();

		lnext = l->next;
		free(l); l = NULL;
	}
}

static char *asurround(const char *str)
{
	unsigned int s = strlen(str) + 3;
	char *res = malloc(sizeof(char) * s);
	s_strncpy(res, "|", s);
	s_strncat(res, str, s);
	s_strncat(res, "|", s);
	return res;
}

int num_get_current_lib_number()
{
	return libcurrent->reg_number;
}

int num_libswitch(const char *id)
{
	lib_t *l = libhead;
	for (l = libhead; l != NULL; l = l->next) {
		char *slid = asurround(l->id);
		char *sid = asurround(id);
		out_dbg("Will match '%s' against '%s'\n", sid, slid);
		char *p = strcasestr(slid, sid);
		free(sid);
		free(slid);
		if (p != NULL) {
			out_dbg("** MATCH\n");
			libswitch(l, FALSE);
			return 1;
		}
	}
	return 0;
}

void num_lib_enumerate(char **paraml, const char **id, const char **description, const char **libname, const char **version)
{
	if (*paraml == NULL)
		*paraml = (char *)libhead;
	lib_t *l = (lib_t *)*paraml;
	*id = l->id;
	*description = l->description;
	*libname = l->libname;
	*version = l->version;
	*paraml = (char *)l->next;
}

static void lib_register(const char *id, const char *description, const char *libname, const char *version,
		void (*libactivate)(), void (*libterminate)())
{
	static int lib_reg_number = 0;

	assert(libactivate != NULL);
	assert(libterminate != NULL);

	lib_t *lib = malloc(sizeof(lib_t));
	lib->next = libhead;
	libhead = lib;

	lib->id = id;
	lib->description = description;
	lib->libname = libname;
	lib->version = version;
	lib->libactivate = libactivate;
	lib->libterminate = libterminate;
	lib->reg_number = ++lib_reg_number;

	lib->context = context_construct(lib->reg_number);

	out_dbg("Registered library\n\tId: %s\n\tDescription: %s\n\tLibname: %s\n\tVersion: %s\n\tReg number: %d\n",
		id, description, libname, version, lib->reg_number);
}

static void libswitch(lib_t *l, int quiet)
{

	/*-----------------------------------------------------------------------------
	 *  Yes it is a bit heavy.
	 *  Programmers need being helped. The below will immediately detect
	 *  (while lib is being registered) a missing function assignment.
	 *-----------------------------------------------------------------------------*/

	Llib_identify_yourself = NULL;
	Lconstruct = NULL;
	Lconstruct_from_num = NULL;
	Lconstruct_from_str = NULL;
	Ldestruct = NULL;
	Lprint = NULL;
	Lis_zero = NULL;
	Lgetlongint = NULL;
	Ladd = NULL;
	Lsub = NULL;
	Lmul = NULL;
	Ldiv = NULL;
	Lpow = NULL;
	Lmod = NULL;
	Lneg = NULL;
	Lcmplt = NULL;
	Lcmple = NULL;
	Lcmpgt = NULL;
	Lcmpge = NULL;
	Lcmpeq = NULL;
	Lcmpne = NULL;
	Land = NULL;
	Lor = NULL;
	Lnot = NULL;

	libcurrent = l;
	libcurrent->libactivate();
	context_switch(libcurrent->context);

	assert(Llib_identify_yourself != NULL);
	assert(Lconstruct != NULL);
	assert(Lconstruct_from_num != NULL);
	assert(Lconstruct_from_str != NULL);
	assert(Ldestruct != NULL);
	assert(Lprint != NULL);
	assert(Lis_zero != NULL);
	assert(Lgetlongint != NULL);
	assert(Ladd != NULL);
	assert(Lsub != NULL);
	assert(Lmul != NULL);
	assert(Ldiv != NULL);
	assert(Lpow != NULL);
	assert(Lmod != NULL);
	assert(Lneg != NULL);
	assert(Lcmplt != NULL);
	assert(Lcmple != NULL);
	assert(Lcmpgt != NULL);
	assert(Lcmpge != NULL);
	assert(Lcmpeq != NULL);
	assert(Lcmpne != NULL);
	assert(Land != NULL);
	assert(Lor != NULL);
	assert(Lnot != NULL);

	if (!quiet)
		outln(L_VERBOSE, "%s", Llib_identify_yourself());
}

int num_get_count_ref()
{
	return num_count_ref;
}

const char *num_identify_yourself()
{
	return Llib_identify_yourself();
}

numptr num_undefvalue() { return NULL; }
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
		return ERROR_DIV0;
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
		return ERROR_DIV0;
	return Lmod(pr, a, b);
}

int num_neg(numptr *pr, const numptr a)
{
	assert(num_is_not_initialized(*pr));
	return Lneg(pr, a);
}

int num_cmplt(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	return Lcmplt(pr, a, b);
}

int num_cmple(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	return Lcmple(pr, a, b);
}

int num_cmpgt(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	return Lcmpgt(pr, a, b);
}

int num_cmpge(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	return Lcmpge(pr, a, b);
}

int num_cmpeq(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	return Lcmpeq(pr, a, b);
}

int num_cmpne(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	return Lcmpne(pr, a, b);
}

int num_and(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	return Land(pr, a, b);
}

int num_or(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	return Lor(pr, a, b);
}

int num_not(numptr *pr, const numptr a)
{
	assert(num_is_not_initialized(*pr));
	return Lnot(pr, a);
}


/*-----------------------------------------------------------------------------
 *  GMP library functions
 *-----------------------------------------------------------------------------*/


char *gmp_identify_yourself = NULL;
void gmp_activate();
void gmp_terminate();
static const char *gmp_lib_identify_yourself();
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
static int gmp_cmplt(numptr *pr, const numptr a, const numptr b);
static int gmp_cmple(numptr *pr, const numptr a, const numptr b);
static int gmp_cmpgt(numptr *pr, const numptr a, const numptr b);
static int gmp_cmpge(numptr *pr, const numptr a, const numptr b);
static int gmp_cmpeq(numptr *pr, const numptr a, const numptr b);
static int gmp_cmpne(numptr *pr, const numptr a, const numptr b);
static int gmp_and(numptr *pr, const numptr a, const numptr b);
static int gmp_or(numptr *pr, const numptr a, const numptr b);
static int gmp_not(numptr *pr, const numptr a);

static void gmp_register()
{
	asprintf(&gmp_identify_yourself, "GMP library version %s", gmp_version);
	lib_register("gmp|gmpz|gmp-mpz", "GNU MP integers library", "libgmp", gmp_version, gmp_activate, gmp_terminate);
}

void gmp_activate()
{
	Llib_identify_yourself = gmp_lib_identify_yourself;
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
	Lcmplt = gmp_cmplt;
	Lcmple = gmp_cmple;
	Lcmpgt = gmp_cmpgt;
	Lcmpge = gmp_cmpge;
	Lcmpeq = gmp_cmpeq;
	Lcmpne = gmp_cmpne;
	Land = gmp_and;
	Lor = gmp_or;
	Lnot = gmp_not;
}

void gmp_terminate() { }

static const char *gmp_lib_identify_yourself()
{
	return gmp_identify_yourself;
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

static int gmp_cmplt(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int c = mpz_cmp(*(const mpz_t *)a, *(const mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, c < 0 ? 1L : 0L);
	return 0;
}

static int gmp_cmple(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int c = mpz_cmp(*(const mpz_t *)a, *(const mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, c <= 0 ? 1L : 0L);
	return 0;
}

static int gmp_cmpgt(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int c = mpz_cmp(*(const mpz_t *)a, *(const mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, c > 0 ? 1L : 0L);
	return 0;
}

static int gmp_cmpge(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int c = mpz_cmp(*(const mpz_t *)a, *(const mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, c >= 0 ? 1L : 0L);
	return 0;
}

static int gmp_cmpeq(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int c = mpz_cmp(*(const mpz_t *)a, *(const mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, c == 0 ? 1L : 0L);
	return 0;
}

static int gmp_cmpne(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int c = mpz_cmp(*(const mpz_t *)a, *(const mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, c != 0 ? 1L : 0L);
	return 0;
}

static int gmp_and(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int logical_a = mpz_get_si(*(mpz_t *)a);
	long int logical_b = mpz_get_si(*(mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, logical_a && logical_b ? 1L : 0L);
	return 0;
}

static int gmp_or(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int logical_a = mpz_get_si(*(mpz_t *)a);
	long int logical_b = mpz_get_si(*(mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, logical_a || logical_b ? 1L : 0L);
	return 0;
}

static int gmp_not(numptr *pr, const numptr a)
{
	*pr = num_construct();
	long int logical_a = mpz_get_si(*(mpz_t *)a);
	mpz_set_si(*(mpz_t *)*pr, logical_a ? 0L : 1L);
	return 0;
}


/*-----------------------------------------------------------------------------
 *  BC functions
 *-----------------------------------------------------------------------------*/


char *libbc_identify_yourself = NULL;
static int libbc_scale;
#define LIBBC_DEFAULT_SCALE	0
static int libbc_get_scale();
static void libbc_set_scale(int scale);

void libbc_activate();
void libbc_terminate();
static const char *libbc_lib_identify_yourself();
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
static int libbc_cmplt(numptr *pr, const numptr a, const numptr b);
static int libbc_cmple(numptr *pr, const numptr a, const numptr b);
static int libbc_cmpgt(numptr *pr, const numptr a, const numptr b);
static int libbc_cmpge(numptr *pr, const numptr a, const numptr b);
static int libbc_cmpeq(numptr *pr, const numptr a, const numptr b);
static int libbc_cmpne(numptr *pr, const numptr a, const numptr b);
static int libbc_and(numptr *pr, const numptr a, const numptr b);
static int libbc_or(numptr *pr, const numptr a, const numptr b);
static int libbc_not(numptr *pr, const numptr a);

static void libbc_register()
{
	bc_init_numbers();
	libbc_set_scale(LIBBC_DEFAULT_SCALE);

	asprintf(&libbc_identify_yourself, "BC library version %s", BC_VERSION);

	lib_register("bc|bcnum", "GNU BC library", "libbc", BC_VERSION, libbc_activate, libbc_terminate);
}

int libbc_get_scale()
{
	return libbc_scale;
}

void libbc_set_scale(int scale)
{
	libbc_scale = scale;
}

void libbc_activate()
{
	Llib_identify_yourself = libbc_lib_identify_yourself;
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
	Lcmplt = libbc_cmplt;
	Lcmple = libbc_cmple;
	Lcmpgt = libbc_cmpgt;
	Lcmpge = libbc_cmpge;
	Lcmpeq = libbc_cmpeq;
	Lcmpne = libbc_cmpne;
	Land = libbc_and;
	Lor = libbc_or;
	Lnot = libbc_not;
}

void libbc_terminate() { }

static const char *libbc_lib_identify_yourself()
{
	return libbc_identify_yourself;
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
	return ERROR_NONE;
}

static int libbc_sub(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	int na = ((bc_num)a)->n_scale;
	int nb = ((bc_num)b)->n_scale;
	int scale_min = (na < nb ? nb : na);
	bc_sub((bc_num)a, (bc_num)b, (bc_num *)pr, scale_min);
	return ERROR_NONE;
}

static int libbc_mul(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	bc_multiply((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());
	return ERROR_NONE;
}

static int libbc_div(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	bc_divide((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());
	return ERROR_NONE;
}

static int libbc_pow(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	bc_raise((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());
	return ERROR_NONE;
}

static int libbc_mod(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	bc_modulo((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());
	return ERROR_NONE;
}

static int libbc_neg(numptr *pr, const numptr a)
{
	*pr = num_construct();
	int na = ((bc_num)a)->n_scale;
	bc_sub(_zero_, (bc_num)a, (bc_num *)pr, na);
	return ERROR_NONE;
}

static int libbc_cmplt(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
/*    bc_multiply((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());*/
	return ERROR_NONE;
}

static int libbc_cmple(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
/*    bc_multiply((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());*/
	return ERROR_NONE;
}

static int libbc_cmpgt(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
/*    bc_multiply((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());*/
	return ERROR_NONE;
}

static int libbc_cmpge(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
/*    bc_multiply((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());*/
	return ERROR_NONE;
}

static int libbc_cmpeq(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
/*    bc_multiply((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());*/
	return ERROR_NONE;
}

static int libbc_cmpne(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
/*    bc_multiply((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());*/
	return ERROR_NONE;
}

static int libbc_and(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
/*    bc_multiply((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());*/
	return ERROR_NONE;
}

static int libbc_or(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
/*    bc_multiply((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_get_scale());*/
	return ERROR_NONE;
}

static int libbc_not(numptr *pr, const numptr a)
{
	*pr = num_construct();
/*    int na = ((bc_num)a)->n_scale;*/
/*    bc_sub(_zero_, (bc_num)a, (bc_num *)pr, na);*/
	return ERROR_NONE;
}

