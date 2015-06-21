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

static int out_level = L_NORMAL;

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

char *s_strncat(char *dest, const char *src, size_t n)
{
	char *r = strncat(dest, src, n);
	dest[n - 1] = '\0';
	return r;
}

int outln(int level, const char *fmt, ...)
{
	if (level <= out_level || level == L_ENFORCE) {
		va_list args;
		va_start(args, fmt);
		int r;
		if (level == L_ERROR || level == L_WARNING) {
			r = vprintf(fmt, args);
			printf("\n");
		} else {
			r = vfprintf(stderr, fmt, args);
			fprintf(stderr, "\n");
		}
		va_end(args);
		return r;
	} else {
		return -1;
	}
}

int out(int level, const char *fmt, ...)
{
	if (level <= out_level || level == L_ENFORCE) {
		va_list args;
		va_start(args, fmt);
		int r;
		if (level == L_ERROR || level == L_WARNING) {
			r = vprintf(fmt, args);
		} else {
			r = vfprintf(stderr, fmt, args);
		}
		va_end(args);
		return r;
	} else {
		return -1;
	}
}

int outln_error(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int r = vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	return r;
}

void outln_error_code(int e)
{
	if (e >= 0 && e < (sizeof(table_errors) / sizeof(*table_errors))) {
		outln_error("%s", table_errors[e]);
	} else {
			/* Should an unknown error immediately stop the program execution?
			 * Not sure of it.
			 * I leave it ACTIVE for the moment.
			*/
		assert(e >= 0 && e < (sizeof(table_errors) / sizeof(*table_errors)));
		outln_error("Unknown error code %d", e);
	}
}

void usage()
{
	fprintf(stderr, "Usage: %s [options] [file ...]\n", PACKAGE_NAME);
	fprintf(stderr, "  -h  -help     print this usage and exit\n");
	fprintf(stderr, "  -V  -verbose  verbose output\n");
	fprintf(stderr, "  -q  -quiet    don't print initial banner\n");
	fprintf(stderr, "  -v  -version  print version information and exit\n");
	fprintf(stderr, "  --            end of parameters, next options are file names\n");
	exit(-1);
}

void version()
{
#if defined(DEBUG) || defined(BISON_DEBUG) || defined(FLEX_DEBUG)
	printf("%sd\n", PACKAGE_STRING);
#else
	printf("%s\n", PACKAGE_STRING);
#endif
	printf("Copyright (c) 2015 Sébastien Millet\n");
}

void output_count_ref_report(const char *name, int count_ref)
{
	outln(count_ref != 0 ? L_ERROR : L_VERBOSE,
		"%s  %s count (should be 0): %i", (count_ref != 0 ? "** ERROR **" : "OK         "), name, count_ref);
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

void opt_check(int n, const char *opt)
{
	static int defined_options[3] = {0, 0};

	assert(n < sizeof(defined_options) / sizeof(*defined_options));

	if (defined_options[n]) {
		fprintf(stderr, "Option %s already set", opt);
		exit(-2);
	} else
		defined_options[n] = 1;
}

int main(int argc, char *argv[])
{

#ifdef BISON_DEBUG
	yydebug = 1;
#endif

	int optset_verbose = 0;
	int optset_quiet = 0;
	int optset_debug = 0;

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
			out_level = L_VERBOSE;
		} else if (!strcmp(argv[a], "-quiet") || !strcmp(argv[a], "-q")) {
			opt_check(1, argv[a]);
			optset_quiet = 1;
			out_level = L_QUIET;
		} else if (!strcmp(argv[a], "-debug") || !strcmp(argv[a], "-d")) {
			opt_check(2, argv[a]);
			optset_debug = 1;
			out_level = L_DEBUG;
		} else if (argv[a][0] == '-') {
			if (strcmp(argv[a], "--")) {
				fprintf(stderr, "%s: invalid option -- '%s'\n", PACKAGE_NAME, argv[a]);
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

	if (optset_verbose && optset_quiet)
		out_level = L_NORMAL;
	if (optset_debug)
		out_level = L_DEBUG;

	if (a < 0)
		usage();

	if (out_level >= L_NORMAL)
		version();

	num_init();

	out_dbg("DEBUG mode activated\n");

	yyparse();

	num_terminate();

	int n = num_get_count_ref();
	output_count_ref_report("number", n);
	int e = expr_get_count_ref();
	output_count_ref_report("expr_t *", e);

	return (n == 0 && e == 0 ? 0 : abs(n) + abs(e));
}

