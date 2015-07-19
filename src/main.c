/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Manages zsbc execution.
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
#include "program.h"
#include "parser.h"
#include "numwrap.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static int out_level = L_NORMAL;

char **arg_input_files = NULL;
int arg_nb_allocated_input_files = 0;
int arg_nb_input_files = 0;

const char *table_errors[] = {
	"No error",							/* ERROR_NONE */
	"Division by 0",					/* ERROR_DIV0 */
	"Negative exponent not authorized",	/* ERROR_NEGATIVE_EXP */
	"Function not defined",				/* ERROR_FUNCTION_NOT_DEFINED */
	"Parameter number mismatch"			/* ERROR_PARAMETER_NUMBER_MISMATCH */
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

	/*
	 * Returns a copied (allocated) string.
	 * dst can be null, in which case the new string is to be retrieved
	 * by the function return value.
	 */
char *s_alloc_and_copy(char **dst, const char *src)
{
	unsigned int s = strlen(src) + 1;
	char *target = (char *)malloc(s);
	s_strncpy(target, src, s);
	if (dst != NULL)
		*dst = target;
	return target;
}

int outln(int level, const char *fmt, ...)
{
	if (level <= out_level || level == L_ENFORCE) {
		va_list args;
		va_start(args, fmt);
		int r;
		if (level == L_ERROR || level == L_WARNING) {
			r = vfprintf(stderr, fmt, args);
			fprintf(stderr, "\n");
		} else {
			r = vprintf(fmt, args);
			printf("\n");
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
	fprintf(stderr, "Error: ");
	int r = vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	return r;
}

int outln_warning(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "Warning: ");
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

	/* Needed by the bc library */
void rt_warn(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "'bc number' runtime warning: ");
	vfprintf(stderr, fmt, args);
	va_end(args);
}

	/* Needed by the bc library */
void rt_error(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "'bc number' runtime error (will stop immediately): ");
	vfprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
}

void fatalln(const char *file, int line, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, "File %s line %d: ", file, line);
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
	exit(1);
}

void out_of_memory()
{
	rt_error("%s", "Out of memory");
}

void opt_check(int n, const char *opt)
{
	static int defined_options[4] = {0, 0, 0, 0};

	assert(n < sizeof(defined_options) / sizeof(*defined_options));

	if (defined_options[n]) {
		fprintf(stderr, "Option %s already set", opt);
		exit(-2);
	} else
		defined_options[n] = 1;
}

void register_file_arg(const char *arg_to_add)
{
	if (++arg_nb_input_files > arg_nb_allocated_input_files) {
		if (arg_input_files == NULL) {
			arg_nb_allocated_input_files = 4;
			arg_input_files = (char **)malloc(sizeof(char *) * arg_nb_allocated_input_files);
		} else {
			arg_nb_allocated_input_files *= 2;
			arg_input_files = (char **)realloc(arg_input_files, sizeof(char *) * arg_nb_allocated_input_files);
		}
	}
	arg_input_files[arg_nb_input_files - 1] = (char *)arg_to_add;
}

int main(int argc, char *argv[])
{

#ifdef BISON_DEBUG
	activate_bison_debug();
#endif

	int optset_verbose = 0;
	int optset_quiet = 0;
	int optset_debug = 0;

	char *missing_option_value = NULL;
	char *numlib_to_start_with = NULL;

	int a = 1;
	while (a < argc) {
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
		} else if (!strcmp(argv[a], "-lib") || !strcmp(argv[a], "-numlib")) {
			opt_check(3, argv[a]);
			if (++a >= argc) {
				missing_option_value = argv[a - 1] + 1;
				a = -1;
				break;
			}
			numlib_to_start_with = argv[a];
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
			register_file_arg(argv[a]);
		}
		++a;
	}
	while (a >= 1 && a < argc) {
		register_file_arg(argv[a]);
		++a;
	}

	if (optset_verbose && optset_quiet)
		out_level = L_NORMAL;
	if (optset_debug)
		out_level = L_DEBUG;

	if (missing_option_value != NULL) {
		fprintf(stderr, "%s: option '%s' requires one argument\n", PACKAGE_NAME, missing_option_value);
	}
	if (a < 0)
		usage();

	num_init();
	if (numlib_to_start_with != NULL) {
		int r;
		if ((r = num_libswitch(numlib_to_start_with)) == 0) {
			fprintf(stderr, "%s: library '%s' unknown, quitting\n", PACKAGE_NAME, numlib_to_start_with);
			exit(-2);
		}
	}

	if (out_level >= L_NORMAL)
		version();

	out_dbg("DEBUG mode activated\n");

	int i;
	for (i = 0; i < arg_nb_input_files; ++i) {
		out_dbg("Input file #%d: %s\n", i + 1, arg_input_files[i]);
	}

	yyparse();

	num_terminate();

	int n = num_get_count_ref();
	output_count_ref_report("number", n);
	int e = expr_get_count_ref();
	output_count_ref_report("expr_t *", e);

	return (n == 0 && e == 0 ? 0 : abs(n) + abs(e));
}

