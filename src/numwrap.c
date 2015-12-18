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

/*#define HAS_LIB_GMP*/
/*#define HAS_LIB_LIBBC*/

#include "numwrap.h"
#include "vars.h"	/* Needed for context management */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define NUM_IMPLICIT_INVMOD_DEFAULT FALSE
#define NUM_GET_IMPLICIT_MOD_PTR_DEFAULT NULL

char *strcasestr(const char *haystack, const char *needle);
#ifdef MY_WINDOWS
#define strcasestr(haystack, needle) strstr(haystack, needle)
#endif


#undef I_GOT_ONE

#ifdef HAS_LIB_GMP
#define I_GOT_ONE

	/* GMP LIBRARY */
#include <gmp.h>
static void gmp_register();

#endif


#ifdef HAS_LIB_LIBBC
#define I_GOT_ONE

	/* BC LIBRARY */
#include "number.h"
#define BC_VERSION	"1.06.95"
static void libbc_register();

#endif

#ifndef I_GOT_ONE
#error "Hey, how do you want me to compile this program without at least one bignum library?"
#endif

typedef struct lib_t {
	libinfo_t libinfo;
	void (*libactivate)();
	void (*libterminate)();

	context_t *context;
	int reg_number;		/* Live ID given at run time to uniquely identify the library */

	void (*libfirsttimeinit)();
	int has_done_first_time_init;

	struct lib_t *next;
} lib_t;
lib_t *libhead = NULL;
lib_t *libcurrent = NULL;
static void lib_register(libinfo_t li, void (*libfirsttimeinit)(), void (*libactivate)(), void (*libterminate)());
static void libswitch(lib_t *l, int quiet);

static int num_count_ref = 0;

static const char* (*Llib_identify_yourself)();
static numptr (*Lconstruct)();
static numptr (*Lconstruct_from_num)(const numptr num);
static int (*Lconstruct_from_str)(const char *str, numptr *pnum);
static numptr (*Lconstruct_from_int)(int n);
static void (*Ldestruct)(numptr *pnum);
static void (*Lprint)(const numptr num);
static int (*Lis_zero)(const numptr num);
static long int (*Lgetlongint)(const numptr num);
static int (*Ladd)(numptr *pr, const numptr a, const numptr b);
static int (*Lsub)(numptr *pr, const numptr a, const numptr b);
static int (*Lmul)(numptr *pr, const numptr a, const numptr b);
static int (*Ldiv)(numptr *pr, const numptr a, const numptr b);
static int (*Lpow)(numptr *pr, const numptr a, const numptr b);
static int (*Lpowmod)(numptr *pr, const numptr a, const numptr b, const numptr c);
static int (*Lmod)(numptr *pr, const numptr a, const numptr b);
static int (*Linvmod)(numptr *pr, const numptr a, const numptr b);
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
static int (*Limplicit_invmod)();
static numptr* (*Lget_implicit_mod_ptr)();
static int (*Lread)(numptr *pr);


/*-----------------------------------------------------------------------------
 *  Functions shared across all number libs
 *-----------------------------------------------------------------------------*/


	/*
	 * * WARNING *
	 *
	 * If launched with switch_to_first_registered_library set to FALSE, you
	 * *MUST* call num_libswitch() later otherwise the initialization will be
	 * partial and any call to a num_ function will crash the program.
	 * */
void num_init(int switch_to_first_registered_library)
{

#ifdef HAS_LIB_GMP
	gmp_register();
#endif
#ifdef HAS_LIB_LIBBC
	libbc_register();
#endif

	if (switch_to_first_registered_library) {
		lib_t *l = libhead;
		while (l->next != NULL)
			l = l->next;
		libswitch(l, FALSE);
	}
}

void num_terminate()
{
	lib_t *l = libhead;
	lib_t *lnext;
	for(l = libhead; l != NULL; l = lnext) {
		libswitch(l, TRUE);

		out_dbg("Now terminating library %s\n", l->libinfo.libname);

		l->libterminate();
		context_destruct(l->context);

		lnext = l->next;
		free(l);
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

	/*
	 * Change current "numlib" (number library)
	 * Number libraries are referred to by their id, as recorded in
	 * libinfo_t.id
	 *
	 * Returns 1 in case of success (library is found that corresponds to the provided id),
	 * otherwise returns 0
	 * */
int num_libswitch(const char *id)
{
	lib_t *l = libhead;
	for (l = libhead; l != NULL; l = l->next) {
		char *slid = asurround(l->libinfo.id);
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

void num_lib_enumerate(char **paraml, libinfo_t *libinfo)
{
	if (*paraml == NULL)
		*paraml = (char *)libhead;
	lib_t *l = (lib_t *)*paraml;
	*libinfo = l->libinfo;
	*paraml = (char *)l->next;
}

const libinfo_t *num_lib_get_current()
{
	assert(libcurrent != NULL);

	return &libcurrent->libinfo;
}

static void lib_register(const libinfo_t li, void (*libfirsttimeinit)(), void (*libactivate)(), void (*libterminate)())
{
	static int lib_reg_number = 0;

	assert(libactivate != NULL);
	assert(libterminate != NULL);

	lib_t *lib = malloc(sizeof(lib_t));
	lib->next = libhead;
	libhead = lib;

	lib->libinfo = li;
	lib->libactivate = libactivate;
	lib->libterminate = libterminate;
	lib->reg_number = ++lib_reg_number;
	lib->libfirsttimeinit = libfirsttimeinit;
	lib->has_done_first_time_init = FALSE;

	lib->context = context_construct(lib->reg_number);

	out_dbg("Registered library\n\tId: %s\n\tDescription: %s\n\tLibname: %s\n\tVersion: %s\n\tNumber set: %s\n\tReg number: %d\n",
		li.id, li.description, li.libname, li.version, li.number_set, lib->reg_number);
}

static int shared_functions_check_functions(numptr *pr)
{
	assert(num_is_not_initialized(*pr));
	check_functions();
	return ERROR_NONE;
}

static int lread_getchar()
{
	return getchar();
}

	/*
	 * This function is different from num_construct_from_str():
	 *   While num_construct_from_str takes a complete string, most likely
	 *   provided by the lexer, this one will pull characters one by one
	 *   (from lread_getchar()) and stop reading as soon as a character
	 *   is encountered that can't be in the number.
	 *
	 * It is library-specific as only the library knows how to best parse
	 * a number (with or without a period, depending on ibase etc.)
	 *
	 * */
static int shared_functions_read(numptr *pr)
{
	assert(num_is_not_initialized(*pr));
	return Lread(pr);
}

static void shared_libfirsttimeinit_run_on_every_libs()
{
	register_builtin_function("check_functions", 0, shared_functions_check_functions, TRUE);
	register_builtin_function("read", 0, shared_functions_read, TRUE);
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
	Lconstruct_from_int = NULL;
	Ldestruct = NULL;
	Lprint = NULL;
	Lis_zero = NULL;
	Lgetlongint = NULL;
	Ladd = NULL;
	Lsub = NULL;
	Lmul = NULL;
	Ldiv = NULL;
	Lpow = NULL;
	Lpowmod = NULL;
	Lmod = NULL;
	Linvmod = NULL;
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
	Limplicit_invmod = NULL;
	Lget_implicit_mod_ptr = NULL;
	Lread = NULL;

	libcurrent = l;
	libcurrent->libactivate();
	context_switch(libcurrent->context);

	assert(Llib_identify_yourself != NULL);
	assert(Lconstruct != NULL);
	assert(Lconstruct_from_num != NULL);
	assert(Lconstruct_from_str != NULL);
	assert(Lconstruct_from_int != NULL);
	assert(Ldestruct != NULL);
	assert(Lprint != NULL);
	assert(Lis_zero != NULL);
	assert(Lgetlongint != NULL);
	assert(Ladd != NULL);
	assert(Lsub != NULL);
	assert(Lmul != NULL);
	assert(Ldiv != NULL);
	assert(Lpow != NULL);

		/* Providing powmod is not necessary... */
/*    assert(Lpowmod != NULL);*/

	assert(Lmod != NULL);

		/* Providing invmod is not necessary... */
/*    assert(Linvmod != NULL);*/

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

		/* Providing implicit_invmod is not necessary... */
/*    assert(Limplicit_invmod != NULL);*/
		/* Providing get_implicit_mod_ptr is not necessary... */
/*    assert(Lget_implicit_mod_ptr != NULL);*/

	assert(Lread != NULL);

	if (!quiet)
		outln(L_VERBOSE, "%s", Llib_identify_yourself());

	if (!l->has_done_first_time_init) {
		out_dbg("Library activation done. Now executing %s:libfirsttimeinit()\n", l->libinfo.libname);
		l->libfirsttimeinit();
		out_dbg("Now calling shared_libfirsttimeinit_run_on_every_libs() (run once on each lib, after libfirsttimeinit())\n", l->libinfo.libname);
		shared_libfirsttimeinit_run_on_every_libs();
		l->has_done_first_time_init = TRUE;
	}
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

int num_construct_from_str(const char *str, numptr *pnum)
{
	out_dbg("Constructing one number from a string\n");
	int r = Lconstruct_from_str(str, pnum);
	if (r == ERROR_NONE)
		++num_count_ref;
	return r;
}

numptr num_construct_from_int(int n)
{
	out_dbg("Constructing one number from an int\n");
	numptr r = Lconstruct_from_int(n);
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

void num_print(const numptr num) {
	Lprint(num);
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

int num_powmod(numptr *pr, const numptr a, const numptr e, const numptr m)
{
	assert(num_is_not_initialized(*pr));
	if (Lpowmod != NULL)
		return Lpowmod(pr, a, e, m);

	numptr ee = num_construct_from_num(e);
	numptr two = num_construct_from_int(2);
	numptr result = num_construct_from_int(1);
	numptr factor = num_construct_from_num(a);

	while (!num_is_zero(ee)) {
		numptr mod2 = num_undefvalue();
		num_mod(&mod2, ee, two);
		if (!num_is_zero(mod2)) {
			numptr tmp = num_undefvalue();
			num_mul(&tmp, result, factor);
			num_destruct(&result); num_mod(&result, tmp, m); num_destruct(&tmp);
		}
		num_destruct(&mod2);
		numptr t = num_undefvalue(); num_mul(&t, factor, factor);
		num_destruct(&factor); num_mod(&factor, t, m); num_destruct(&t);
		num_div(&t, ee, two); num_destruct(&ee); ee = num_construct_from_num(t); num_destruct(&t);
	}
	*pr = num_construct_from_num(result);
	num_destruct(&ee);
	num_destruct(&two);
	num_destruct(&result);
	num_destruct(&factor);
	return ERROR_NONE;
}

int num_mod(numptr *pr, const numptr a, const numptr b)
{
	assert(num_is_not_initialized(*pr));
	if (num_is_zero(b))
		return ERROR_DIV0;
	return Lmod(pr, a, b);
}

int num_invmod(numptr *pr, const numptr a, const numptr n)
{
	assert(num_is_not_initialized(*pr));
	if (num_is_zero(n))
		return ERROR_NO_INVMOD;

	if (Linvmod != NULL)
		return Linvmod(pr, a, n);

	numptr one = num_construct_from_int(1);
	numptr zero = num_construct_from_int(0);
	numptr aa = num_construct_from_num(n);
	numptr bb = num_construct_from_num(a);
	numptr r = num_construct_from_int(1);
	numptr t = num_construct_from_int(1);
	numptr anc_t = num_construct_from_int(0);
	while (1) {
		numptr q = num_undefvalue(); num_div(&q, aa, bb);

		numptr tmp = num_undefvalue(); num_mul(&tmp, bb, q);
		num_destruct(&r); num_sub(&r, aa, tmp); num_destruct(&tmp);

/*        out(L_ENFORCE, "aa = "); num_print(aa); outln(L_ENFORCE, "");*/
/*        out(L_ENFORCE, "bb = "); num_print(bb); outln(L_ENFORCE, "");*/
/*        out(L_ENFORCE, "r = "); num_print(r); outln(L_ENFORCE, "");*/
/*        out(L_ENFORCE, "t = "); num_print(t); outln(L_ENFORCE, "");*/

		num_mul(&tmp, q, t); numptr nou_t = num_undefvalue(); num_sub(&nou_t, anc_t, tmp); num_destruct(&tmp);
		num_destruct(&q);

		numptr c = num_undefvalue(); num_cmpge(&c, nou_t, zero);
		if (!num_is_zero(c)) {
			num_mod(&tmp, nou_t, n); num_destruct(&nou_t); nou_t = num_construct_from_num(tmp); num_destruct(&tmp);
		} else {
			num_sub(&tmp, zero, nou_t); numptr tmp2 = num_undefvalue(); num_mod(&tmp2, tmp, n);
			num_destruct(&nou_t); num_sub(&nou_t, n, tmp2); num_destruct(&tmp); num_destruct(&tmp2);
		}
		num_destruct(&c);
		num_destruct(&anc_t); anc_t = num_construct_from_num(t);
		num_destruct(&t); t = num_construct_from_num(nou_t);
		num_destruct(&nou_t);

		num_destruct(&aa); aa = num_construct_from_num(bb);
		num_destruct(&bb); bb = num_construct_from_num(r);

		numptr comp = num_undefvalue(); num_cmple(&comp, r, one);
		int comp_is_zero = num_is_zero(comp);
		num_destruct(&comp);
		if (!comp_is_zero)
			break;
	}

	int result;
	numptr compar = num_undefvalue();
	num_cmpeq(&compar, r, one);
	if (num_is_zero(compar)) {
		result = ERROR_NO_INVMOD;
	} else {
		*pr = num_construct_from_num(t);
		result = ERROR_NONE;
	}
	num_destruct(&compar);

	num_destruct(&one);
	num_destruct(&zero);
	num_destruct(&aa);
	num_destruct(&bb);
	num_destruct(&r);
	num_destruct(&t);
	num_destruct(&anc_t);
	return result;
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

int num_implicit_invmod()
{
	if (Limplicit_invmod == NULL)
		return NUM_IMPLICIT_INVMOD_DEFAULT;
	return Limplicit_invmod();
}

numptr* num_get_implicit_mod_ptr()
{
	if (Lget_implicit_mod_ptr == NULL)
		return NUM_GET_IMPLICIT_MOD_PTR_DEFAULT;
	return Lget_implicit_mod_ptr();
}


#ifdef HAS_LIB_GMP

/*-----------------------------------------------------------------------------
 *  GMP LIBRARY
 *-----------------------------------------------------------------------------*/


	/* ibase */
#define GMP_DEFAULT_IBASE 10
#define GMP_MIN_IBASE 2
#define GMP_MAX_IBASE 62
static int gmp_ibase;

	/* obase */
#define GMP_DEFAULT_OBASE 10
#define GMP_MIN_OBASE 2
#define GMP_MAX_OBASE 62
	/*
	 * gmp itself tends to use lower case alphabetic characters, for obase >= 10.
	 * It'll use upper case only when the output base is >= 37.
	 * The constant below changes this behavior and enforces gmp to output uppercase
	 * alphabetic characters for an output base <= 36.
	 * This is done to stay consistent with input: even while using libgmp, numbers
	 * are input using uppercase letters.
	 *
	 * */
#define GMP_USE_UPPERCASE_UP_TO 36
static int gmp_obase;

	/*  autoinvmod */
#define GMP_AUTOINVMOD_DEFAULT 0
static int gmp_autoinvmod;

	/*  autoinvmod */
#define GMP_AUTOMOD_DEFAULT 0
static int gmp_has_automod;
static numptr gmp_automod;

char *gmp_identify_yourself = NULL;
static int gmp_function_get_version(numptr *pr);
static void gmp_firsttimeinit();
static void gmp_activate();
static void gmp_terminate();
static const char *gmp_lib_identify_yourself();
static numptr gmp_construct();
static numptr gmp_construct_from_num(const numptr num);
static int gmp_construct_from_str(const char *str, numptr *pnum);
static numptr gmp_construct_from_int(int n);
static void gmp_destruct(numptr *num);
static void gmp_print(const numptr num);
static int gmp_is_zero(const numptr num);
static long int gmp_getlongint(const numptr num);
static int gmp_add(numptr *pr, const numptr a, const numptr b);
static int gmp_sub(numptr *pr, const numptr a, const numptr b);
static int gmp_mul(numptr *pr, const numptr a, const numptr b);
static int gmp_div(numptr *pr, const numptr a, const numptr b);
static int gmp_pow(numptr *pr, const numptr a, const numptr b);
static int gmp_powmod(numptr *pr, const numptr a, const numptr b, const numptr c);
static int gmp_mod(numptr *pr, const numptr a, const numptr b);
static int gmp_invmod(numptr *pr, const numptr a, const numptr b);
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
static int gmp_implicit_invmod();
static numptr* gmp_get_implicit_mod_ptr();
static int gmp_read(numptr *pr);

static void gmp_register()
{
	const size_t s = 150;
	gmp_identify_yourself = malloc(s);
	snprintf(gmp_identify_yourself, s, "GMP library version %s", gmp_version);

	libinfo_t li;
	li.id = "gmp|gmpz";
	li.description = "GNU MP integers library";
	li.libname = "libgmp";
	li.version = gmp_version;
	li.number_set = "Relative integers";
	lib_register(li, gmp_firsttimeinit, gmp_activate, gmp_terminate);
}

	/*
	 * This function does 2 things
	 *   1- Enforce the value to being an integer.
	 *   2- Check whether the integer is in the interval [min_val, max_val]
	 *      and return corresponding error code.
	 */
static int gmp_enforce_int_and_range(numptr *pnum, int *pint, int min_val, int max_val)
{
	long l = gmp_getlongint(*pnum);
	if (l < min_val || l > max_val)
		return ERROR_ILLEGAL_VALUE;

	*pint = (int)l;

	num_destruct(pnum);
	*pnum = num_construct_from_int(*pint);

	return ERROR_NONE;
}

static int gmp_var_update(const char *name, numptr *pnum)
{
	int r = ERROR_NONE;

	if (!varname_cmp(name, "ibase")) {
		if ((r = gmp_enforce_int_and_range(pnum, &gmp_ibase, GMP_MIN_IBASE, GMP_MAX_IBASE)) == ERROR_NONE) {
			out_dbg("ibase set to %d\n", gmp_ibase);
		}
	} else if (!varname_cmp(name, "obase")) {
		if ((r = gmp_enforce_int_and_range(pnum, &gmp_obase, GMP_MIN_OBASE, GMP_MAX_OBASE)) == ERROR_NONE) {
			out_dbg("obase set to %d\n", gmp_obase);
		}
	} else if (!varname_cmp(name, "autoinvmod")) {
		if ((r = gmp_enforce_int_and_range(pnum, &gmp_autoinvmod, 0, 1)) == ERROR_NONE) {
			out_dbg("autoinvmod set to %d\n", gmp_autoinvmod);
		}
	} else if (!varname_cmp(name, "automod")) {
		numptr one = num_construct_from_int(1);
		numptr c = num_undefvalue(); num_cmpge(&c, *pnum, one);
		int is_zero = num_is_zero(*pnum);
		int is_ok = is_zero || !num_is_zero(c);
		num_destruct(&c);
		num_destruct(&one);
		if (!is_ok)
			return ERROR_INVALID_NUMBER;

		if (!num_is_not_initialized(gmp_automod))
			num_destruct(&gmp_automod);
		if (is_zero) {
			gmp_has_automod = FALSE;
			out_dbg("automod set to 0 (=> removed)\n");
		} else {
			gmp_has_automod = TRUE;
			gmp_automod = num_construct_from_num(*pnum);
			out_dbg("automod set to a non-zero value\n");
		}

	} else
		FATAL_ERROR("Unknown variable for update_callback: %s\n", name);

	return r;
}

static int gmp_function_get_version(numptr *pr)
{
	out_dbg("Executing gmp_function_get_version()\n");

	char v[50];
	s_strncpy(v, gmp_version, sizeof(v));
	if (v[1] == '.')
		v[1] = '\0';
	else
		v[2] = '\0';
	int ver = atoi(v);

	*pr = num_construct_from_int(ver);
	return ERROR_NONE;
}

static void gmp_firsttimeinit()
{
	const numptr *ppvarnum;

	vars_set_update_callback("ibase", gmp_var_update);
	vars_set_value("ibase", num_construct_from_int(GMP_DEFAULT_IBASE), &ppvarnum);
	assert(gmp_ibase == GMP_DEFAULT_IBASE);

	vars_set_update_callback("obase", gmp_var_update);
	vars_set_value("obase", num_construct_from_int(GMP_DEFAULT_OBASE), &ppvarnum);
	assert(gmp_obase == GMP_DEFAULT_OBASE);

	vars_set_update_callback("autoinvmod", gmp_var_update);
	vars_set_value("autoinvmod", num_construct_from_int(GMP_AUTOINVMOD_DEFAULT), &ppvarnum);
	assert(gmp_autoinvmod == GMP_AUTOINVMOD_DEFAULT);

	gmp_automod = num_undefvalue();
	vars_set_update_callback("automod", gmp_var_update);
	vars_set_value("automod", num_construct_from_int(GMP_AUTOMOD_DEFAULT), &ppvarnum);
	assert(gmp_has_automod == GMP_AUTOMOD_DEFAULT);

	register_builtin_function("gmpversion", 0, gmp_function_get_version, FALSE);
	register_builtin_function("powmod", 3, gmp_powmod, FALSE);
	register_builtin_function("invmod", 2, gmp_invmod, FALSE);
}

static void gmp_activate()
{
	Llib_identify_yourself = gmp_lib_identify_yourself;
	Lconstruct = gmp_construct;
	Lconstruct_from_num = gmp_construct_from_num;
	Lconstruct_from_str = gmp_construct_from_str;
	Lconstruct_from_int = gmp_construct_from_int;
	Ldestruct = gmp_destruct;
	Lprint = gmp_print;
	Lis_zero = gmp_is_zero;
	Lgetlongint = gmp_getlongint;
	Ladd = gmp_add;
	Lsub = gmp_sub;
	Lmul = gmp_mul;
	Ldiv = gmp_div;
	Lpow = gmp_pow;
	Lpowmod = gmp_powmod;
	Lmod = gmp_mod;
	Linvmod = gmp_invmod;
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
	Limplicit_invmod = gmp_implicit_invmod;
	Lget_implicit_mod_ptr = gmp_get_implicit_mod_ptr;
	Lread = gmp_read;

	outstring_set_line_length(-1);
}

static void gmp_terminate()
{
	if (!num_is_not_initialized(gmp_automod))
		num_destruct(&gmp_automod);
	free(gmp_identify_yourself);
}

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

static int gmp_construct_from_str(const char *str, numptr *pnum)
{
	mpz_t *mp = (mpz_t *)malloc(sizeof(mpz_t));
	if (strlen(str) == 1) {
			/*
			 * The bc way: a unique character number is read in the max base, allowing
			 * to write
			 *   ibase=A
			 * to have ibase set to 10 (10 decimal) whatever ibase is.
			 * */
		mpz_init_set_str(*mp, str, GMP_MAX_IBASE);
	} else {
		int code;
		const char *p = str;
		if (*p == '+' || *p == '-')
			++p;
		for (; *p != '\0'; ++p) {
			if (isdigit(*p)) {
				code = *p - '0';
			} else if (*p >= 'A' && *p <= 'Z') {
				code = *p - 'A' + 10;
			} else if (*p >= 'a' && *p <= 'z') {
				code = *p - 'a' + 36;
			} else {
				goto myerror;
			}
			if (code >= gmp_ibase)
				goto myerror;
		}
		mpz_init_set_str(*mp, str, gmp_ibase);
	}
	*pnum = (numptr)mp;
	return ERROR_NONE;

myerror:
	free(mp);
	return ERROR_INVALID_NUMBER;
}

static numptr gmp_construct_from_int(int n)
{
	mpz_t *mp = (mpz_t *)malloc(sizeof(mpz_t));
	mpz_init_set_si(*mp, n);
	return (numptr)mp;
}

static void gmp_destruct(numptr *pnum)
{
	mpz_t *mp = (mpz_t *)(*pnum);
	mpz_clear(*mp);
	free(mp);
	num_postcleanup(pnum);
}

static void gmp_print(const numptr num)
{
	char *buf = mpz_get_str(NULL, gmp_obase, *(const mpz_t *)num);
	char *p = buf;
	while (*p != '\0') {
		if (gmp_obase <= GMP_USE_UPPERCASE_UP_TO && islower(*p))
			*p = toupper(*p);
		++p;
	}

		/*
		 * The below is done so that any string output by gmp_print
		 * can be read 'as is' successfully. Thus, a number cannot
		 * start with a letter and the token when read would be read
		 * as an integer. Note there is no technical reason for doing
		 * it, it is just a matter of consistency.
		 *
		 * */
	p = buf;
	if (isalpha(*p) && islower(*p))
		outstring_1char('0');

	while (*p != '\0') {
		outstring_1char(*p);
		++p;
	}
	free(buf);
}

static int gmp_is_zero(const numptr num)
{
	return !mpz_cmp_ui(*(mpz_t *)num, 0);
}

static long int gmp_getlongint(const numptr num)
{
	if (mpz_fits_slong_p(*(const mpz_t *)num))
		return mpz_get_si(*(mpz_t *)num);
	if (mpz_sgn(*(mpz_t *)num) == 1)
		return LONG_MAX;
	else
		return LONG_MIN;
}

static int gmp_add(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	mpz_add(*(mpz_t *)*pr, *(const mpz_t *)a, *(const mpz_t *)b);
	return ERROR_NONE;
}

static int gmp_sub(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	mpz_sub(*(mpz_t *)*pr, *(const mpz_t *)a, *(const mpz_t *)b);
	return ERROR_NONE;
}

static int gmp_mul(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	mpz_mul(*(mpz_t *)*pr, *(const mpz_t *)a, *(const mpz_t *)b);
	return ERROR_NONE;
}

static int gmp_div(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
		/*  The calling function, num_div, has checked whether or not b is null */
	mpz_tdiv_q(*(mpz_t *)*pr, *(const mpz_t *)a, *(const mpz_t *)b);
	return ERROR_NONE;
}

static int gmp_pow(numptr *pr, const numptr a, const numptr b)
{

	out_dbg("Call to gmp_pow\n");

	long int exp = gmp_getlongint(b);
	if (exp < 0)
		return ERROR_NEGATIVE_EXP;
	*pr = num_construct();
	mpz_pow_ui(*(mpz_t *)*pr, *(const mpz_t *)a, exp);
	return ERROR_NONE;
}

static int gmp_powmod(numptr *pr, const numptr a, const numptr b, const numptr c)
{

	out_dbg("Call to gmp_powmod\n");

	*pr = num_construct();
	mpz_powm(*(mpz_t *)*pr, *(const mpz_t *)a, *(const mpz_t *)b, *(const mpz_t *)c);
	return ERROR_NONE;
}

static int gmp_mod(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
		/*  The calling function, num_mod, has checked whether or not b is null */
	mpz_mod(*(mpz_t *)*pr, *(const mpz_t *)a, *(const mpz_t *)b);
	return ERROR_NONE;
}

static int gmp_invmod(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
		/*  The calling function, num_mod, has checked whether or not b is null */
	if (mpz_invert(*(mpz_t *)*pr, *(const mpz_t *)a, *(const mpz_t *)b))
		return ERROR_NONE;
	else {
		num_destruct(pr);
		return ERROR_NO_INVMOD;
	}
}

static int gmp_neg(numptr *pr, const numptr a)
{
	*pr = num_construct();
	mpz_neg(*(mpz_t *)*pr, *(mpz_t *)a);
	return ERROR_NONE;
}

static int gmp_cmplt(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int c = mpz_cmp(*(const mpz_t *)a, *(const mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, c < 0 ? 1L : 0L);
	return ERROR_NONE;
}

static int gmp_cmple(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int c = mpz_cmp(*(const mpz_t *)a, *(const mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, c <= 0 ? 1L : 0L);
	return ERROR_NONE;
}

static int gmp_cmpgt(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int c = mpz_cmp(*(const mpz_t *)a, *(const mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, c > 0 ? 1L : 0L);
	return ERROR_NONE;
}

static int gmp_cmpge(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int c = mpz_cmp(*(const mpz_t *)a, *(const mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, c >= 0 ? 1L : 0L);
	return ERROR_NONE;
}

static int gmp_cmpeq(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int c = mpz_cmp(*(const mpz_t *)a, *(const mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, c == 0 ? 1L : 0L);
	return ERROR_NONE;
}

static int gmp_cmpne(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int c = mpz_cmp(*(const mpz_t *)a, *(const mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, c != 0 ? 1L : 0L);
	return ERROR_NONE;
}

static int gmp_and(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int logical_a = mpz_get_si(*(mpz_t *)a);
	long int logical_b = mpz_get_si(*(mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, logical_a && logical_b ? 1L : 0L);
	return ERROR_NONE;
}

static int gmp_or(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int logical_a = mpz_get_si(*(mpz_t *)a);
	long int logical_b = mpz_get_si(*(mpz_t *)b);
	mpz_set_si(*(mpz_t *)*pr, logical_a || logical_b ? 1L : 0L);
	return ERROR_NONE;
}

static int gmp_not(numptr *pr, const numptr a)
{
	*pr = num_construct();
	long int logical_a = mpz_get_si(*(mpz_t *)a);
	mpz_set_si(*(mpz_t *)*pr, logical_a ? 0L : 1L);
	return ERROR_NONE;
}

static int gmp_implicit_invmod()
{
	return gmp_autoinvmod;
}

static numptr* gmp_get_implicit_mod_ptr()
{
	if (gmp_has_automod)
		return &gmp_automod;
	return NULL;
}

static int gmp_read(numptr *pr)
{
const int INITIAL_BUF_LENGTH = 2;
const int INCREASE_FACTOR = 2;

	int len = INITIAL_BUF_LENGTH;
	char *buf = (char *)malloc(sizeof(char) * len);
	char *write_head = buf;

	int nb_bytes = 0;
	int has_seen_sign = FALSE;
	int code;

	int c;
	while (TRUE) {
		c = lread_getchar();
		if (++nb_bytes > len) {
			len *= INCREASE_FACTOR;
			buf = (char *)realloc(buf, sizeof(char) * len);
		}
		if (c == EOF)
			break;

		if (!has_seen_sign && (c == '+' || c == '-')) {
			has_seen_sign = TRUE;
		} else {
			if (isdigit(c)) {
				code = c - '0';
			} else if (c >= 'A' && c <= 'Z') {
				code = c - 'A' + 10;
			} else if (c >= 'a' && c <= 'z') {
				code = c - 'a' + 36;
			} else {
				break;
			}
			if (code >= gmp_ibase)
				break;
		}

		*write_head = (char)c;
		++write_head;
	};
	*write_head = '\0';

	int r = num_construct_from_str(buf, pr);
	free(buf);
	return r;
}

#endif


#ifdef HAS_LIB_LIBBC

/*-----------------------------------------------------------------------------
 *  LIBBC LIBRARY
 *-----------------------------------------------------------------------------*/


	/* scale */
static int libbc_scale;
#define LIBBC_DEFAULT_SCALE 0
#define LIBBC_MAX_SCALE INT_MAX

	/* line length */
#define LIBBC_BC_LINE_LENGTH_ENV "BC_LINE_LENGTH"
static int libbc_bc_line_length;
#define LIBBC_DEFAULT_BC_LINE_LENGTH 70

	/* ibase */
#define LIBBC_DEFAULT_IBASE 10
#define LIBBC_MIN_IBASE 2
#define LIBBC_MAX_IBASE 16
static int libbc_ibase;

	/* obase */
#define LIBBC_DEFAULT_OBASE 10
#define LIBBC_MIN_OBASE 2
#define LIBBC_MAX_OBASE INT_MAX
static int libbc_obase;

char *libbc_identify_yourself = NULL;
static int libbc_function_get_version(numptr *pr);
static void libbc_firsttimeinit();
static void libbc_activate();
static void libbc_terminate();
static const char *libbc_lib_identify_yourself();
static numptr libbc_construct();
static numptr libbc_construct_from_num(const numptr num);
static int libbc_construct_from_str(const char *str, numptr *pnum);
static numptr libbc_construct_from_int(int n);
static void libbc_destruct(numptr *pnum);
static void libbc_print(const numptr num);
static int libbc_is_zero(const numptr num);
static long int libbc_getlongint(const numptr num);
static int libbc_add(numptr *pr, const numptr a, const numptr b);
static int libbc_sub(numptr *pr, const numptr a, const numptr b);
static int libbc_mul(numptr *pr, const numptr a, const numptr b);
static int libbc_div(numptr *pr, const numptr a, const numptr b);
static int libbc_pow(numptr *pr, const numptr a, const numptr b);
static int libbc_powmod(numptr *pr, const numptr a, const numptr b, const numptr c);
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
static int libbc_read(numptr *pr);

static void libbc_register()
{
	bc_init_numbers();

	const size_t s = 150;
	libbc_identify_yourself = malloc(s);
	snprintf(libbc_identify_yourself, s, "BC library version %s", BC_VERSION);

	libinfo_t li;
	li.id = "bc|bcnum";
	li.description = "GNU BC library";
	li.libname = "libbc";
	li.version = BC_VERSION;
	li.number_set = "POSIX reals";
	lib_register(li, libbc_firsttimeinit, libbc_activate, libbc_terminate);

	char *env;
	libbc_bc_line_length = LIBBC_DEFAULT_BC_LINE_LENGTH;
	if ((env = getenv(LIBBC_BC_LINE_LENGTH_ENV)) != NULL) {
		libbc_bc_line_length = atoi(env);
		if (strlen(env) == 0 || (env[0] < '0' && env[0] > '9'))
			libbc_bc_line_length = LIBBC_DEFAULT_BC_LINE_LENGTH;
		else if (libbc_bc_line_length < 3 && libbc_bc_line_length != 0)
			libbc_bc_line_length = LIBBC_DEFAULT_BC_LINE_LENGTH;
	}

	out_dbg("libbc_bc_line_length = %d\n", libbc_bc_line_length);
}

	/*
	 * This function does 2 things
	 *   1- Enforce the value to being an integer.
	 *   2- Check whether the integer is in the interval [min_val, max_val]
	 *      and return corresponding error code.
	 */
static int libbc_enforce_int_and_range(numptr *pnum, int *pint, int min_val, int max_val)
{
	long l = bc_num2long((bc_num)*pnum);
	if (l < min_val || l > max_val)
		return ERROR_ILLEGAL_VALUE;

	*pint = (int)l;

	num_destruct(pnum);
	*pnum = num_construct_from_int(*pint);

	return ERROR_NONE;
}

static int libbc_var_update(const char *name, numptr *pnum)
{
	int r = ERROR_NONE;

	if (!varname_cmp(name, "scale")) {
		if ((r = libbc_enforce_int_and_range(pnum, &libbc_scale, 0, LIBBC_MAX_SCALE)) == ERROR_NONE) {
			out_dbg("scale set to %d\n", libbc_scale);
		}
	} else if (!varname_cmp(name, "ibase")) {
		if ((r = libbc_enforce_int_and_range(pnum, &libbc_ibase, LIBBC_MIN_IBASE, LIBBC_MAX_IBASE)) == ERROR_NONE) {
			out_dbg("ibase set to %d\n", libbc_ibase);
		}
	} else if (!varname_cmp(name, "obase")) {
		if ((r = libbc_enforce_int_and_range(pnum, &libbc_obase, LIBBC_MIN_OBASE, LIBBC_MAX_OBASE)) == ERROR_NONE) {
			out_dbg("obase set to %d\n", libbc_obase);
		}
	} else
		FATAL_ERROR("Unknown variable for update_callback: %s\n", name);

	return r;
}

static int libbc_function_get_version(numptr *pr)
{
	out_dbg("Executing libbc_function_get_version()\n");

	char v[50];
	s_strncpy(v, BC_VERSION, sizeof(v));
	if (v[1] == '.')
		v[1] = '\0';
	else
		v[2] = '\0';
	int ver = atoi(v);

	*pr = num_construct_from_int(ver);
	return ERROR_NONE;
}

static int libbc_sqrt(numptr *pr, const numptr a)
{
	*pr = num_construct_from_num(a);
	if (!bc_sqrt((bc_num *)pr, libbc_scale)) {
		num_destruct(pr);
		return ERROR_SQRT_OF_NEG;
	}
	return ERROR_NONE;
}

static int libbc_function_scale(numptr *pr, const numptr a)
{
	*pr = num_construct_from_int(((bc_num)a)->n_scale);
	return ERROR_NONE;
}

static int libbc_function_length(numptr *pr, const numptr a)
{

	const bc_num bn = (bc_num)a;

/* Copied from bc source -> execute.c, 'L' instruction */

		/* For the number 0.xxxx,  0 is not significant. */
	if (bn->n_len == 1 && bn->n_scale != 0 && bn->n_value[0] == 0)
		*pr = num_construct_from_int(bn->n_scale);
	else
		*pr = num_construct_from_int(bn->n_len + bn->n_scale);

	return ERROR_NONE;
}

static void libbc_firsttimeinit()
{

	const numptr *ppvarnum;

	vars_set_update_callback("scale", libbc_var_update);
	vars_set_value("scale", num_construct_from_int(LIBBC_DEFAULT_SCALE), &ppvarnum);
	assert(libbc_scale == LIBBC_DEFAULT_SCALE);

	vars_set_update_callback("ibase", libbc_var_update);
	vars_set_value("ibase", num_construct_from_int(LIBBC_DEFAULT_IBASE), &ppvarnum);
	assert(libbc_ibase == LIBBC_DEFAULT_IBASE);

	vars_set_update_callback("obase", libbc_var_update);
	vars_set_value("obase", num_construct_from_int(LIBBC_DEFAULT_OBASE), &ppvarnum);
	assert(libbc_obase == LIBBC_DEFAULT_OBASE);

	register_builtin_function("bcversion", 0, libbc_function_get_version, FALSE);
	register_builtin_function("sqrt", 1, libbc_sqrt, FALSE);
	register_builtin_function("scale", 1, libbc_function_scale, FALSE);
	register_builtin_function("length", 1, libbc_function_length, FALSE);
	register_builtin_function("powmod", 3, libbc_powmod, FALSE);
}

static void libbc_activate()
{
	Llib_identify_yourself = libbc_lib_identify_yourself;
	Lconstruct = libbc_construct;
	Lconstruct_from_num = libbc_construct_from_num;
	Lconstruct_from_str = libbc_construct_from_str;
	Lconstruct_from_int = libbc_construct_from_int;
	Ldestruct = libbc_destruct;
	Lprint = libbc_print;
	Lis_zero = libbc_is_zero;
	Lgetlongint = libbc_getlongint;
	Ladd = libbc_add;
	Lsub = libbc_sub;
	Lmul = libbc_mul;
	Ldiv = libbc_div;
	Lpow = libbc_pow;
	Lpowmod = libbc_powmod;
	Lmod = libbc_mod;
/*    Linvmod = ...nothing...;*/
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
	Lread = libbc_read;

	outstring_set_line_length(libbc_bc_line_length);
}

static void libbc_terminate()
{
	free(libbc_identify_yourself);
}

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


/*
 * Note (1)
 *   The name 'push_constant' below makes little sense in this context
 *   (there is no stack to push the read number to...)
 *   For the sake of transparency I've left this name.
 *
 * Note (2)
 *   The code below is taken from bc source code.
 *   Some details have been changed to work in zsbc context.
 *   Besides these minimal (but necessary) changes, the code is the
 *   original one.
 *
 * */

/* TAKEN FROM BC SOURCE */

/* Push_constant converts a sequence of input characters as returned
   by IN_CHAR into a number.  The number is pushed onto the execution
   stack.  The number is converted as a number in base CONV_BASE. */

void push_constant(bc_num *pbuild, int (*in_char)(), int conv_base)
{
	int digits;
	bc_num temp, result, mult, divisor;
	int in_ch, first_ch;
	char negative;

		/* Initialize all bc numbers */
	bc_init_num(&temp);
	bc_init_num(&result);
	bc_init_num(&mult);
	*pbuild = bc_copy_num(_zero_);
	negative = FALSE;

		/* The conversion base. */
	bc_int2num(&mult, conv_base);

		/* Get things ready. */
	in_ch = in_char();
	while (in_ch == ' ')
		in_ch = in_char();

	if (in_ch == '+')
		in_ch = in_char();
	else
		if (in_ch == '-') {
		negative = TRUE;
		in_ch = in_char();
	}

		/* Check for the special case of a single digit. */
	if (in_ch < 16) {
		first_ch = in_ch;
		in_ch = in_char();
		if (in_ch < 16 && first_ch >= conv_base)
			first_ch = conv_base - 1;
		bc_int2num(pbuild, (int)first_ch);
	}

		/* Convert the integer part. */
	while (in_ch < 16) {
		if (in_ch < 16 && in_ch >= conv_base)
			in_ch = conv_base - 1;
		bc_multiply(*pbuild, mult, &result, 0);
		bc_int2num(&temp, (int)in_ch);
		bc_add(result, temp, pbuild, 0);
		in_ch = in_char();
	}
	if (in_ch == '.') {
		in_ch = in_char();
		if (in_ch >= conv_base)
			in_ch = conv_base-1;
		bc_free_num(&result);
		bc_free_num(&temp);
		divisor = bc_copy_num(_one_);
		result = bc_copy_num(_zero_);
		digits = 0;
		while (in_ch < 16) {
			bc_multiply(result, mult, &result, 0);
			bc_int2num(&temp, (int)in_ch);
			bc_add(result, temp, &result, 0);
			bc_multiply(divisor, mult, &divisor, 0);
			digits++;
			in_ch = in_char();
			if (in_ch < 16 && in_ch >= conv_base)
				in_ch = conv_base-1;
		}
		bc_divide(result, divisor, &result, digits);
		bc_add(*pbuild, result, pbuild, 0);
	}

		/* Final work.  */
	if (negative)
		bc_sub(_zero_, *pbuild, pbuild, 0);

	bc_free_num(&temp);
	bc_free_num(&result);
	bc_free_num(&mult);
}

/* END OF 'TAKEN FROM BC SOURCE' */

const char *in_char_current;
int in_char()
{
	char c = *in_char_current;
	++in_char_current;

	if (c >= '0' && c <= '9')
		return c - '0';
	else if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	else if (c == '.' || c == ' ' || c == '-' || c == '+')
		return c;
	return 16;
}

	/*
	 * The function below uses the variable in_char_current defined
	 * above. This use of a global variable is necessary due to the logic
	 * of in_char() as called by push_constant().
	 *
	 * */
static int libbc_construct_from_str(const char *str, numptr *pnum)
{
	const char *p = str;
	if (*p == '+' || *p == '-')
		++p;
	int seen_point = FALSE;
	for (; *p != '\0'; ++p) {
		if (*p >= '0' && *p <= '9')
			continue;
		if (*p >= 'A' && *p <= 'F')
			continue;
		if (*p == '.' && !seen_point) {
			seen_point = TRUE;
			continue;
		}
		return ERROR_INVALID_NUMBER;
	}
	in_char_current = str;
	bc_num bcn = NULL;
	push_constant(&bcn, in_char, libbc_ibase);
	*pnum = (numptr)bcn;
	return ERROR_NONE;
}

static numptr libbc_construct_from_int(int n)
{
	bc_num bcn = NULL;
	bc_int2num(&bcn, n);
	return (numptr)bcn;
}

static void libbc_destruct(numptr *pnum)
{
	bc_free_num((bc_num *)pnum);
}

static void libbc_print(const numptr num)
{
	bc_out_num((bc_num)num, libbc_obase, outstring_1char, 0);
}

static int libbc_is_zero(const numptr num)
{
	return bc_is_zero((bc_num)num);
}

static long int libbc_getlongint(const numptr num)
{
	long int i = bc_num2long((bc_num)num);
	if (!bc_is_zero((bc_num)num) && i == 0) {
		if (bc_is_neg((bc_num)num))
			return LONG_MIN;
		else
			return LONG_MAX;
	} else
		return i;
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
	bc_multiply((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_scale);
	return ERROR_NONE;
}

static int libbc_div(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	bc_divide((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_scale);
	return ERROR_NONE;
}

static int libbc_pow(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	bc_raise((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_scale);
	return ERROR_NONE;
}

static int libbc_powmod(numptr *pr, const numptr a, const numptr b, const numptr c)
{
	*pr = num_construct();
	bc_raisemod((bc_num)a, (bc_num)b, (bc_num)c, (bc_num *)pr, libbc_scale);
	return ERROR_NONE;
}

static int libbc_mod(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	bc_modulo((bc_num)a, (bc_num)b, (bc_num *)pr, libbc_scale);
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
	int c = bc_compare((bc_num)a, (bc_num)b);
	*pr = libbc_construct_from_int(c < 0);
	return ERROR_NONE;
}

static int libbc_cmple(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	int c = bc_compare((bc_num)a, (bc_num)b);
	*pr = libbc_construct_from_int(c <= 0);
	return ERROR_NONE;
}

static int libbc_cmpgt(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	int c = bc_compare((bc_num)a, (bc_num)b);
	*pr = libbc_construct_from_int(c > 0);
	return ERROR_NONE;
}

static int libbc_cmpge(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	int c = bc_compare((bc_num)a, (bc_num)b);
	*pr = libbc_construct_from_int(c >= 0);
	return ERROR_NONE;
}

static int libbc_cmpeq(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	int c = bc_compare((bc_num)a, (bc_num)b);
	*pr = libbc_construct_from_int(c == 0);
	return ERROR_NONE;
}

static int libbc_cmpne(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	int c = bc_compare((bc_num)a, (bc_num)b);
	*pr = libbc_construct_from_int(c != 0);
	return ERROR_NONE;
}

static int libbc_and(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int logical_a = bc_num2long((bc_num)a);
	long int logical_b = bc_num2long((bc_num)b);
	*pr = libbc_construct_from_int(logical_a && logical_b);
	return ERROR_NONE;
}

static int libbc_or(numptr *pr, const numptr a, const numptr b)
{
	*pr = num_construct();
	long int logical_a = bc_num2long((bc_num)a);
	long int logical_b = bc_num2long((bc_num)b);
	*pr = libbc_construct_from_int(logical_a || logical_b);
	return ERROR_NONE;
}

static int libbc_not(numptr *pr, const numptr a)
{
	*pr = num_construct();
	long int logical_a = bc_num2long((bc_num)a);
	*pr = libbc_construct_from_int(!logical_a);
	return ERROR_NONE;
}

static int libbc_read(numptr *pr)
{
const int INITIAL_BUF_LENGTH = 2;
const int INCREASE_FACTOR = 2;

	int len = INITIAL_BUF_LENGTH;
	char *buf = (char *)malloc(sizeof(char) * len);
	char *write_head = buf;

	int nb_bytes = 0;
	int has_seen_sign = FALSE;
	int has_seen_period = FALSE;

	int c;
	while (TRUE) {
		c = lread_getchar();
		if (++nb_bytes > len) {
			len *= INCREASE_FACTOR;
			buf = (char *)realloc(buf, sizeof(char) * len);
		}
		if (c == EOF)
			break;

		if (!has_seen_sign && (c == '+' || c == '-')) {
			has_seen_sign = TRUE;
		} else if (!has_seen_period && c == '.') {
			has_seen_period = TRUE;
		} else {
			if (!isdigit(c) && (c < 'A' || c > 'F')) {
				break;
			}
		}

		*write_head = (char)c;
		++write_head;
	};
	*write_head = '\0';

	int r = num_construct_from_str(buf, pr);
	free(buf);
	return r;
}

#endif

