/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Manage zsbc execution.
 *
 *        Version:  1.0
 *        Created:  14/06/2015 13:45:56
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet (smt), milletseb@laposte.net
 *
 * =====================================================================================
 */


#ifdef HAVE_CONFIG_H
#include "../config.h"
#else
/* Defines some PACKAGE* constants in case config.h is not available */
#include "../extracfg.h"
#endif

#include "common.h"
#include "vars.h"
#include "expr.h"
#include "parser.h"
#include "numwrap.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

	/* OL stands for Out Level (no link with Olympic Lyonnais) */
typedef enum {OL_QUIET = 0, OL_NORMAL = 1, OL_VERBOSE = 2} out_level_t;
out_level_t opt_ol = OL_NORMAL;

const char *table_errors[] = {
	"No error",			/* ERR_NONE */
	"Division by 0"		/* ERR_DIV0 */
};

char *s_strncpy(char *dest, const char *src, size_t n)
{
	char *r = strncpy(dest, src, n);
	dest[n - 1] = '\0';
	return r;
}

int out(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int r = vprintf(fmt, args);
	va_end(args);
	return r;
}

int out_err(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int r = vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	return r;
}

void out_err_code(int e)
{
	if (e < 0 || e >= (sizeof(table_errors) / sizeof(*table_errors))) {
		out_err("Error code %d", e);
	} else {
		out_err("%s", table_errors[e]);
	}
}

void usage()
{
	out_err("Usage: %s [options] [file ...]", PACKAGE_NAME);
	out_err("  -h  -help     print this usage and exit");
	out_err("  -V  -verbose  verbose output");
	out_err("  -q  -quiet    don't print initial banner");
	out_err("  -v  -version  print version information and exit");
	out_err("  --            end of parameters, next options are file names");
	exit(-1);
}

void version()
{
#if defined(DEBUG) || defined(BISON_DEBUG) || defined(FLEX_DEBUG)
	out(PACKAGE_STRING "d\n");
#else
	out(PACKAGE_STRING "\n");
#endif
	out("Copyright 2015 Sébastien Millet\n");
}

void opt_check(int n, const char *opt)
{
	static int defined_options[2] = {0, 0};

	if (defined_options[n]) {
		out_err("Option %s already set", opt);
		exit(-2);
	} else
		defined_options[n] = 1;
}

void output_count_ref_report(const char *name, int count_ref)
{
	if (opt_ol >= OL_VERBOSE || count_ref != 0) {
		fprintf(stderr, "%s  %s count (should be 0): %i\n", (count_ref != 0 ? "** ERROR **" : "OK         "), name, count_ref);
	}
}

void myputchar(int c)
{
	putchar(c);
}

void rt_warn(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "'bc number' runtime warning: ");
	vfprintf(stderr, fmt, args);
	va_end(args);
}

void rt_error(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "'bc number' runtime error (will stop immediately): ");
	vfprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
}

void fatal(const char *err)
{
	fprintf(stderr, "%s\n", err);
	exit(1);
}

void out_of_memory()
{
	fatal("Out of memory");
}


int main(int argc, char *argv[])
{

#ifdef BISON_DEBUG
	yydebug = 1;
#endif

	num_init_gmp();

	int optset_verbose = 0;
	int optset_quiet = 0;

	int a = 1;
	while (a >= 1 && a < argc) {
		if (!strcmp(argv[a], "-help") || !strcmp(argv[a], "-h")) {
			usage();
		} else if (!strcmp(argv[a], "-version") || !strcmp(argv[a], "-v")) {
			version();
			exit(0);
		} else if (!strcmp(argv[a], "-verbose") || !strcmp(argv[a], "-V")) {
			opt_check(0, argv[a]);
			optset_verbose = 1;
			opt_ol = OL_VERBOSE;
		} else if (!strcmp(argv[a], "-quiet") || !strcmp(argv[a], "-q")) {
			opt_check(1, argv[a]);
			optset_quiet = 1;
			opt_ol = OL_QUIET;
		} else if (argv[a][0] == '-') {
			if (strcmp(argv[a], "--")) {
				out_err("%s: invalid option -- '%s'", PACKAGE_NAME, argv[a]);
				a = -1;
				break;
			} else {
				++a;
				break;
			}
		} else {
			break;
		}
		if (a >= 1)
			++a;
	}

	if (optset_verbose && optset_quiet) {
		opt_ol = OL_NORMAL;
	}
	if (a < 0)
		usage();

	if (opt_ol >= OL_NORMAL) {
		version();
		num_lib_may_i_ask_you_to_identify_yourself_please();
	}

	out_dbg("DEBUG mode activated\n");


	vars_init();

	yyparse();

/*    bc_init_numbers();*/
/*    bc_num num;*/
/*    bc_init_num(&num);*/
/*    bc_str2num(&num, "102", 10);*/
/*    bc_out_num(num, 10, myputchar, 0);*/
/*    printf("\n");*/
/*    bc_free_num(&num);*/

/*    nwptr x = nw_const_number("153");*/
/*    nw_print(x);*/

	vars_terminate();

	int n = num_get_count_ref();
	output_count_ref_report("number", n);
	int e = expr_get_count_ref();
	output_count_ref_report("expr_t *", e);

	return (n == 0 && e == 0 ? 0 : abs(n) + abs(e));
}

