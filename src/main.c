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
#include <unistd.h>

int yywrap();

static int out_level = L_NORMAL;
static int opt_SCM = FALSE;		/* SCM = Special Check Mode, used for 'make check' checks */

static int is_interactive = FALSE;

	/* When debug activated, name of files to display the debug of (NULL: display all) */
const char *debug_filenames = NULL;

	/* To manage input files specified in command line arguments */
static char **argf_list = NULL;
static int argf_nb_alloc = 0;
static int argf_nb = 0;
static int argf_cur;
static char *argf_curname;
static FILE *argf_curfile;
static void argf_register_arg(const char *arg_to_add);

static const char *table_errors[] = {
	NULL,								/* ERROR_NONE */
	"Division by 0",					/* ERROR_DIV0 */
	"Negative exponent not authorized",	/* ERROR_NEGATIVE_EXP */
	"Function not defined",				/* ERROR_FUNCTION_NOT_DEFINED */
	"Parameter number mismatch",		/* ERROR_PARAMETER_NUMBER_MISMATCH */
	NULL,								/* ERROR_BREAK */
	NULL,								/* ERROR_CONTINUE */
	"Illegal return statement",			/* ERROR_RETURN */
	"Parameter type mismatch"			/* ERROR_ARGTYPE_MISMATCH */
};

	/*
	 * Safe string copy -> takes into account the size of the target
	 * buffer (as in strncpy) but also ensures the target string has
	 * a terminating '\0' character even if copied string if longer.
	 * */
char *s_strncpy(char *dest, const char *src, size_t n)
{
	char *r = strncpy(dest, src, n);
	dest[n - 1] = '\0';
	return r;
}

	/*
	 * Same comment as s_strncpy above: safe version of strncat
	 * */
char *s_strncat(char *dest, const char *src, size_t n)
{
	char *r = strncat(dest, src, n);
	dest[n - 1] = '\0';
	return r;
}

	/*
	 * Returns a copied, allocated string. Uses s_strncpy for the string
	 * copy (see comment above).
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

	/*
	 * Output a formatted string. "ln" means, a new line gets printed in the end.
	 * */
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
			r = vfprintf(stderr, fmt, args);
		} else {
			r = vprintf(fmt, args);
		}
		va_end(args);
		return r;
	} else {
		return -1;
	}
}

int out_dbg_core(const char *filename, int line, const char *fmt, ...)
{
	if (out_level >= L_DEBUG && (debug_filenames == NULL || strstr(debug_filenames, filename))) {
		out(L_DEBUG, "%s:%d\t", filename, line);
		va_list args;
		va_start(args, fmt);
		int r = vprintf(fmt, args);
		va_end(args);
		return r;
	} else
		return -1;
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
		const char *msg = table_errors[e];
		if (msg == NULL) {
			FATAL_ERROR("Error code %d has no defined error message!", e);
		} else {
			outln_error("%s", msg);
		}
	} else {

			/*
			 * Should an unknown error immediately stop the program execution?
			 * Not sure of it.
			 * I leave it active for the moment.
			*/
		assert(e >= 0 && e < (sizeof(table_errors) / sizeof(*table_errors)));

		outln_error("Unknown error code %d", e);
	}
}

static void usage()
{
	fprintf(stderr, "Usage: %s [options] [file ...]\n", PACKAGE_NAME);
	fprintf(stderr, "  -h  -help     print this usage and exit\n");
	fprintf(stderr, "  -V  -verbose  verbose output\n");
	fprintf(stderr, "  -q  -quiet    don't print initial banner\n");
	fprintf(stderr, "  -v  -version  print version information and exit\n");
	fprintf(stderr, "      -numlib   (also -lib) defines number library to start with\n");
	fprintf(stderr, "      -liblist  lists number libraries available and exit\n");
	fprintf(stderr, "  --            end of parameters, next options are file names\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "  %s will also read environment variable %s to parse options from,\n", PACKAGE_NAME, ENV_ARGS);
	fprintf(stderr, "  using same format as command-line options.\n");
	exit(-1);
}

static void version()
{
#if defined(DEBUG) || defined(BISON_DEBUG) || defined(FLEX_DEBUG)
	printf("%sd\n", PACKAGE_STRING);
#else
	printf("%s\n", PACKAGE_STRING);
#endif
	printf("Copyright 2015 Sébastien Millet.\n");
	printf("This is free software with ABSOLUTELY NO WARRANTY.\n");
}

static void output_count_ref_report(const char *name, int count_ref)
{
	outln(count_ref != 0 ? L_ERROR : (opt_SCM ? L_NORMAL : L_DEBUG),
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

	/* Needed by the bc library */
void out_of_memory()
{
	rt_error("%s", "Out of memory");
}

	/*
	 * Needed by FATAL_ERROR marco
	 * */
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

	/*
	 * Used to track multiple assignment of the same option.
	 * If called with n set to -1, will reset the "knowledge" of
	 * already assigned options (used to allow re-assignment of
	 * options between ENV_ARGS and command-line arguments). In
	 * that case (if called with -1), make sure opt is set to NULL.
	 * */
static void opt_check(int n, const char *opt)
{
	static int defined_options[7] = {0, 0, 0, 0, 0, 0, 0};

	if (n == -1) {
		assert(opt == NULL);
		int i;
		for (i = 0; i < sizeof(defined_options) / sizeof(*defined_options); ++i) {
			defined_options[i] = FALSE;
		}
		return;
	}

	assert(n < sizeof(defined_options) / sizeof(*defined_options));

	if (defined_options[n]) {
		fprintf(stderr, "Option %s already set\n", opt);
		exit(-2);
	} else
		defined_options[n] = TRUE;
}

static void parse_options(int argc, char *argv[], int *optset_verbose, int *optset_quiet, int *optset_debug,
		int *opt_liblist, const char **nlib_tostartwith, const char **dbg_fname, int *o_SCM, int *isintrctv)
{
	char *missing_option_value = NULL;

	int a = 1;
	while (a < argc) {
		if (!strcmp(argv[a], "-help") || !strcmp(argv[a], "-h")) {
			usage();
		} else if (!strcmp(argv[a], "-version") || !strcmp(argv[a], "-v")) {
			version();
			exit(0);
		} else if (!strcmp(argv[a], "-verbose") || !strcmp(argv[a], "-V")) {
			opt_check(0, argv[a]);
			*optset_verbose = TRUE;
			out_level = L_VERBOSE;
		} else if (!strcmp(argv[a], "-SCM")) {
			opt_check(5, argv[a]);
			*o_SCM = TRUE;
			out_level = L_VERBOSE;
		} else if (!strcmp(argv[a], "-interactive") || !strcmp(argv[a], "-i")) {
			opt_check(6, argv[a]);
			*isintrctv = TRUE;
		} else if (!strcmp(argv[a], "-quiet") || !strcmp(argv[a], "-q")) {
			opt_check(1, argv[a]);
			*optset_quiet = TRUE;
			out_level = L_QUIET;
		} else if (!strcmp(argv[a], "-debug") || !strcmp(argv[a], "-d")) {
			opt_check(2, argv[a]);
			*optset_debug = TRUE;
			out_level = L_DEBUG;
		} else if (!strcmp(argv[a], "-debugfile") || !strcmp(argv[a], "-D")) {
			opt_check(4, argv[a]);
			*optset_debug = TRUE;
			out_level = L_DEBUG;
			if (++a >= argc) {
				missing_option_value = argv[a - 1] + 1;
				a = -1;
				break;
			}
			*dbg_fname = argv[a];
		} else if (!strcmp(argv[a], "-liblist")) {
			*opt_liblist = TRUE;
		} else if (!strcmp(argv[a], "-lib") || !strcmp(argv[a], "-numlib")) {
			opt_check(3, argv[a]);
			if (++a >= argc) {
				missing_option_value = argv[a - 1] + 1;
				a = -1;
				break;
			}
			*nlib_tostartwith = argv[a];
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
			argf_register_arg(argv[a]);
		}
		++a;
	}
	while (a >= 1 && a < argc) {
		argf_register_arg(argv[a]);
		++a;
	}

	if (missing_option_value != NULL) {
		fprintf(stderr, "%s: option '%s' requires one argument\n", PACKAGE_NAME, missing_option_value);
	}
	if (a < 0)
		usage();

		/*  Reset memorization of options already set between calls to parse_options */
	opt_check(-1, NULL);
}

	/*
	 * Acquire ENV_ARGS environment variable and cut it into an array
	 * of strings, the delimiter being space or tab character.
	 * */
static void cut_env_options(int *env_argc, char ***env_argv, const char **env_orig)
{
	*env_argc = 0;
	*env_argv = NULL;
	*env_orig = getenv(ENV_ARGS);
	if (*env_orig == NULL)
		return;

		/*
		 * According to getenv manual, the returned string should not be modified
		 * and we need to modify it...
		 * */
	char *env = s_alloc_and_copy(NULL, *env_orig);

	*env_argc = 1;
	int env_argc_allocated = 2;
	*env_argv = (char **)malloc(sizeof(char *) * env_argc_allocated);

		/* Useless. Done in case argv[0] is ever used */
	(*env_argv)[0] = ENV_ARGS;

	char *p = env;
	char *start_p;
	while (*p != '\0') {
		while (*p == ' ' || *p == '\t')
			++p;
		start_p = p;
		while (*p != ' ' && *p != '\t' && *p != '\0')
			++p;

		int reached_end_of_string = FALSE;
		if (*p == '\0')
			reached_end_of_string = TRUE;
		*p = '\0';

		if (strlen(start_p) >= 1) {
			++(*env_argc);
			if (*env_argc > env_argc_allocated) {
				env_argc_allocated *= 2;
				*env_argv = (char **)realloc(*env_argv, sizeof(char *) * env_argc_allocated);
			}
			(*env_argv)[*env_argc - 1] = start_p;
		}

		if (!reached_end_of_string)
			++p;
	}
}

int main(int argc, char *argv[])
{

	if (ERROR_LAST + 1 != sizeof(table_errors) / sizeof(*table_errors))
		FATAL_ERROR("%s", "table_errors has initialization inconsistent with ERROR_ constants");

#ifdef BISON_DEBUG
	activate_bison_debug();
#endif

	/* Interactive? */
	/* Credits - the two lines below got copied from bc source (main.c) */
	if (isatty(0) && isatty(1)) 
		is_interactive = TRUE;

	int optset_verbose = FALSE;
	int optset_quiet = FALSE;
	int optset_debug = FALSE;
	int optset_liblist = FALSE;
	const char *numlib_to_start_with = NULL;

	int env_argc;
	char **env_argv;
	const char *env;
	cut_env_options(&env_argc, &env_argv, &env);
	parse_options(env_argc, env_argv, &optset_verbose, &optset_quiet, &optset_debug,
		&optset_liblist, &numlib_to_start_with, &debug_filenames, &opt_SCM, &is_interactive);
	optset_verbose = FALSE;
	optset_quiet = FALSE;
	optset_debug = FALSE;
	parse_options(argc, argv, &optset_verbose, &optset_quiet, &optset_debug,
		&optset_liblist, &numlib_to_start_with, &debug_filenames, &opt_SCM, &is_interactive);

	if (optset_verbose && optset_quiet)
		out_level = L_NORMAL;
	if (optset_debug)
		out_level = L_DEBUG;

	if (env_argc >= 1) {
		out_dbg("Environment variable '%s' found\n\tValue: '%s'\n\tResult of value parsing;\n", ENV_ARGS, env);
		int i;
		for (i = 0; i < env_argc; ++i) {
			out_dbg("\t\tenv_argv[%d] = '%s'\n", i, env_argv[i]);
		}
	} else {
		out_dbg("No environment variable '%s'\n", ENV_ARGS);
	}

	if (out_level >= L_NORMAL && is_interactive)
		version();

	out_dbg("DEBUG mode activated\n");

	if (optset_liblist) {
		num_init(FALSE);
		lib_list();
		exit(0);
	}

	num_init(numlib_to_start_with == NULL);
	if (numlib_to_start_with != NULL) {
		int r;
		if ((r = num_libswitch(numlib_to_start_with)) == 0) {
			fprintf(stderr, "%s: library '%s' unknown, quitting\n", PACKAGE_NAME, numlib_to_start_with);
			exit(-2);
		}
	}

	int i;
	for (i = 0; i < argf_nb; ++i) {
		out_dbg("Input file #%d: %s\n", i + 1, argf_list[i]);
	}

		/*
		 * Have to call yywrap() one first time for proper initialization
		 * of yyin.
		 * The -1 below is important, see goto_next_input_file() (called
		 * by yywrap()) to see why.
		 * */
	argf_cur = -1;
	yywrap();

	yyparse();

	num_terminate();

	int n = num_get_count_ref();
	output_count_ref_report("number", n);
	int e = expr_get_count_ref();
	output_count_ref_report("expr_t *", e);

	return (n == 0 && e == 0 ? 0 : abs(n) + abs(e));
}

void lib_list()
{
	char *w = NULL;
	libinfo_t li;
	outln(L_ENFORCE, "%-12s %-30s %-10s %-10s %-10s", "ID", "DESCRIPTION", "LIBNAME", "VERSION", "NUMSET");
	outln(L_ENFORCE, "%-12s %-30s %-10s %-10s %-10s", "------------", "------------------------------",
			"----------", "----------", "----------");
	do {
		num_lib_enumerate(&w, &li);
		outln(L_ENFORCE, "%-12s %-30s %-10s %-10s %-10s", li.id, li.description, li.libname, li.version, li.number_set);
	} while (w != NULL);
}

	/* Adds one input file to read when program starts */
static void argf_register_arg(const char *arg_to_add)
{
	if (++argf_nb > argf_nb_alloc) {
		if (argf_list == NULL) {
			argf_nb_alloc = 4;
			argf_list = (char **)malloc(sizeof(char *) * argf_nb_alloc);
		} else {
			argf_nb_alloc *= 2;
			argf_list = (char **)realloc(argf_list, sizeof(char *) * argf_nb_alloc);
		}
	}
	argf_list[argf_nb - 1] = (char *)arg_to_add;
}

char *argf_get_curname()
{
	return argf_curname;
}

	/*
	 * Returns the FILE* of the next file to read. Files to read come in the order
	 * they were provided in the arguments.
	 * Once the end of the list is reached, returns stdin.
	 * Then returns NULL to say it is over.
	 * */
FILE *argf_get_next()
{

	if (argf_cur >= 0 && argf_cur < argf_nb && argf_curfile != NULL) {
		fclose(argf_curfile);
		out_dbg("argf_get_next(): closed file %s\n", argf_get_curname());
	}

	++argf_cur;

	if (argf_cur < argf_nb) {
		argf_curname = argf_list[argf_cur];
		out_dbg("argf_get_next() is now on file: %s\n", argf_curname);
		if ((argf_curfile = fopen(argf_curname, "r")) == NULL) {
			outln_error("File '%s' is unavailable", argf_curname);
			exit(-99);
		} else {
			out_dbg("argf_get_next(): opened file %s, it is the next yyin-to-be\n", argf_curname);
		}
	} else if (argf_cur == argf_nb) {
		argf_curname = "";
		argf_curfile = stdin;
		out_dbg("argf_get_next(): stdin is the next yyin-to-be\n");
	} else {
		argf_curname = NULL;
		argf_curfile = NULL;
		out_dbg("argf_get_next(): NULL is the next yyin-to-be\n");
	}
	return argf_curfile;
}

