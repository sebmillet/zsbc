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

	/* Unable to use macro MY_WINDOWS below (defined by common.h) */
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
int dont_stop_execution = FALSE;
#define my_fileno _fileno
#else
#define my_fileno fileno
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
#include <signal.h>

#ifdef MY_LINUX
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#else
#include <io.h>
#define isatty _isatty
#endif

#ifdef HAS_LIB_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

#include <errno.h>

#define LINE_LENGTH_ENV "ZSBC_LINE_LENGTH"
#define DEFAULT_LINE_LENGTH 0
static int rt_line_length = DEFAULT_LINE_LENGTH;
const char *VAR_LAST = "last";

defargs_t *defarg_t_badarg;

#ifdef HAS_LIB_LIBBC
	/* Source data for the libmath library, taken from bc source,
	 * that defines the functions e (exponent), l (logarithm), s (sinus),
	 * c (cosine), a (arctan) and j (bessel) */
extern char libbc_libmath[];
extern const size_t libbc_libmath_len;
#endif

FILE *rl_instream = NULL;
int yywrap();

static int out_level = L_NORMAL;
	/* SCM = Special Check Mode, used for 'make check' checks */
int opt_SCM = FALSE;
	/* To check that arrays are copied only at the last minute, when an update occurs */
int opt_COPYONUPDATE = FALSE;

int is_interactive = FALSE;
static int bc_mathlib = FALSE;

	/* When debug activated, name of files to display the debug of (NULL: display all) */
const char *debug_filenames = NULL;

	/* To manage input files specified in command line arguments */
typedef struct input_t {
	const char *name;
} input_t;

static input_t *input_list = NULL;
static int input_nb_alloc = 0;
static int input_nb = 0;
static int input_cursor;
static const char *input_name;
static FILE *input_FILE;
static void input_register(const char *name);
static void set_input_name(const char *s);
const char *input_get_name();
static void input_terminate();

static int flag_interrupt_execution = FALSE;
static int flag_execution_underway = FALSE;
int flag_quitting = FALSE;

static const char *table_errors[] = {
	NULL,                               /* ERROR_NONE */
	"Divide by zero",                   /* ERROR_DIV0 */
	"Negative exponent not authorized", /* ERROR_NEGATIVE_EXP */
	"Function not defined",             /* ERROR_FUNCTION_NOT_DEFINED */
	"Parameter number mismatch",        /* ERROR_PARAMETER_NUMBER_MISMATCH */
	NULL,                               /* ERROR_BREAK_INSTR */
	NULL,                               /* ERROR_CONTINUE_INSTR */
	"Illegal return statement",         /* ERROR_RETURN */
	"Parameter type mismatch",          /* ERROR_ARGTYPE_MISMATCH */
	"Illegal value",                    /* ERROR_ILLEGAL_VALUE */
	"Square root of a negative number", /* ERROR_SQRT_OF_NEG */
	"Array index out of bounds",        /* ERROR_ARRAY_OUT_OF_BOUNDS */
	"Invalid number",                   /* ERROR_INVALID_NUMBER */
	"Function not implemented",         /* ERROR_FUNCTION_NOT_IMPLEMENTED */
	"No modulo invert",                 /* ERROR_NO_INVMOD */
	"Modulo by zero",                   /* ERROR_MODULO0 */
	"Execution interrupted",            /* ERROR_EXECUTION_INTERRUPTED */
	NULL                                /* ERROR_CUSTOM */
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

int varname_cmp(const char *n1, const char *n2)
{
	return strcmp(n1, n2);
}

char *interpret_escape_sequences_alloc(const char *s)
{
	char *orig_d = (char *)malloc(sizeof(char) * (strlen(s) + 1));
	char *d = orig_d;

	const char *orig_s = s;
UNUSED(orig_s);

	while (*s != '\0') {
		if (*s == '\\') {
			const char *sp1 = s + 1;
			if (*sp1 == 'n') {
				s++;
				*d = '\n';
			} else if (*sp1 == 't') {
				s++;
				*d = '\t';
			} else if (*sp1 == '\\') {
				s++;
				*d = '\\';
			} else {
				*d = *s;
			}
		} else {
			*d = *s;
		}
		++s;
		++d;
	}
	*d = '\0';

/*    out_dbg("String before interpretation: '%s'\n", orig_s);*/
/*    out_dbg("String after interpretation:  '%s'\n", orig_d);*/

	return orig_d;
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

void term_get_geometry(int *rows, int *columns)
{
	if (!is_interactive || !isatty(my_fileno(stdout))) {
		*rows = 0;
		*columns = 0;
		return;
	}
#ifdef MY_WINDOWS
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	*rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	*columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	*rows = w.ws_row;
	*columns = w.ws_col;
#endif
}

int term_getkey(void) {
      struct termios current_settings, new_settings;

      if (tcgetattr(STDIN_FILENO, &current_settings))
		  return EOF;

	  new_settings = current_settings;
      new_settings.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
      if (tcsetattr(STDIN_FILENO, TCSANOW, &new_settings))
		  return EOF;

      int c = getchar();

      tcsetattr(STDIN_FILENO, TCSANOW, &current_settings);

      return c;
}

int outstring_c = 0;
int outstring_l = 0;
int outstring_term_columns = 0;
int outstring_term_lines = 0;

#define OUTSTRING_MODE_NORMAL 0
#define OUTSTRING_MODE_ALL    1
#define OUTSTRING_MODE_ZAP    2
int outstring_mode = OUTSTRING_MODE_NORMAL;

int outstring_line_length = DEFAULT_LINE_LENGTH;

void term_clean_current_line_with_spaces()
{
	putchar('\015');
	int i;
	for (i = 0; i < outstring_term_columns; ++i)
		putchar(' ');
	putchar('\015');
}

void outstring_1char(int c)
{
	if (outstring_mode == OUTSTRING_MODE_ZAP)
		return;
	if (outstring_line_length != 0 && c != '\n' && outstring_c >= outstring_line_length - 2) {
		putchar('\\');
		putchar('\n');
		outstring_c = 0;
		++outstring_l;
	}
	if (outstring_mode != OUTSTRING_MODE_ALL) {
		if (is_interactive && outstring_term_lines >= 1 && (outstring_l + 1 >= outstring_term_lines)) {
			int loop = TRUE;
			while (loop) {
				printf("-- Press <space>, <return>, q, a or h:");
				int ch = term_getkey();
				loop = FALSE;
				switch (tolower(ch)) {
					case ' ':
						outstring_l = 0;
						outstring_c = 0;
						break;
					case '\n':
						--outstring_l;
						outstring_c = 0;
						break;
					case 'a':
						outstring_mode = OUTSTRING_MODE_ALL;
						break;
					case 'q':
						outstring_mode = OUTSTRING_MODE_ZAP;
						break;
					case 'h':
						term_clean_current_line_with_spaces();
						printf("-- " PACKAGE_NAME " quick help for pager\n"
							"   <space>: display next screen\n"
							"   <return>: display next line\n"
							"   q: stop display\n"
							"   a: display all remaining text without paging\n"
							);
						loop = TRUE;
						break;
					case EOF:
							/*
							 * Something went wrong in the key press retrieval from terminal
							 * so we just display all.
							 * */
						outstring_mode = OUTSTRING_MODE_ALL;
						break;
					default:
						loop = TRUE;
				}
				term_clean_current_line_with_spaces();
			}
		}
		if (outstring_mode == OUTSTRING_MODE_ZAP)
			return;
	}
	++outstring_c;
	if (outstring_term_columns >= 1 && outstring_c >= 1 && (outstring_c % outstring_term_columns == 0)) {
		++outstring_l;
	}
	putchar(c);
	if (c == '\n') {
		outstring_c = 0;
		++outstring_l;
	}
}

void outstring(const char *s, int append_newline)
{
	char c;
	while ((c = *s) != '\0') {
		++s;
		outstring_1char(c);
	}
	if (append_newline)
		outstring_1char('\n');
}

void outstring_set_line_length(int ll)
{
	if (ll == -1)
		ll = rt_line_length;
	outstring_line_length = ll;
	out_dbg("Line length set to %d\n", outstring_line_length);
}

void outstring_reset()
{
	out_dbg("outstring_reset(): before reset, outstring_c = %d, outstring_l = %d\n", outstring_c, outstring_l);
	outstring_c = 0;
	outstring_l = 0;
	outstring_mode = OUTSTRING_MODE_NORMAL;
	term_get_geometry(&outstring_term_lines, &outstring_term_columns);
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

exec_ctx_t *construct_exec_ctx_t()
{
	exec_ctx_t *pexec_ctx = (exec_ctx_t *)malloc(sizeof(exec_ctx_t));
	pexec_ctx->function_name = NULL;
	pexec_ctx->ploc = NULL;
	pexec_ctx->error_message = NULL;
	pexec_ctx->modulo = num_undefvalue();
	pexec_ctx->parent = NULL;

	flag_execution_underway = TRUE;

	return pexec_ctx;
}

exec_ctx_t *construct_child_exec_ctx_t(const exec_ctx_t *parent)
{
	exec_ctx_t *pexec_ctx = construct_exec_ctx_t();
	*pexec_ctx = *parent;
	pexec_ctx->error_message = NULL;
	pexec_ctx->modulo = num_undefvalue();
	pexec_ctx->parent = (exec_ctx_t *)parent;
	return pexec_ctx;
}

void destruct_exec_ctx_t(exec_ctx_t *pexec_ctx, int copy_up)
{
	if (pexec_ctx->parent == NULL)
		flag_execution_underway = FALSE;

	if (pexec_ctx->error_message != NULL) {
		if (copy_up && pexec_ctx->parent != NULL) {
			pexec_ctx->parent->error_message = pexec_ctx->error_message;
			pexec_ctx->error_message = NULL;
		} else {
			free(pexec_ctx->error_message);
			pexec_ctx->error_message = NULL;
		}
	}
	if (!num_is_not_initialized(pexec_ctx->modulo)) {
		num_destruct(&pexec_ctx->modulo);
	}

	if (copy_up && pexec_ctx->parent != NULL && pexec_ctx->function_name != NULL)
		pexec_ctx->parent->function_name = pexec_ctx->function_name;
	if (copy_up && pexec_ctx->parent != NULL && pexec_ctx->ploc != NULL)
		pexec_ctx->parent->ploc = pexec_ctx->ploc;

	free(pexec_ctx);

}

code_location_t construct_unset_code_location_t()
{
	code_location_t loc;
	loc.is_set = FALSE;
	loc.file_name = NULL;
	loc.first_line = -1;
	loc.first_column = -1;
	loc.last_line = -1;
	loc.last_column = -1;
	return loc;
}

void set_exec_error_message(exec_ctx_t *pexec_ctx, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

		/*
		 * FIXME
		 *
		 *   Calculation of buffer length is not satisfactory.
		 *   vasnprintf would be best but doesn't compile under msvc.
		 *
		 *   Implement home made "a" *printf functions?
		 *   To be thought about...
		 */
	size_t len = strlen(fmt) + 200;

		/*
		 * FIXME?
		 *
		 *   Stop program if an error was already set?
		 *   For the time being, I prefer to silently remove it.
		 *   But the coding good practice here - it shall even be a *rule* -
		 *   is, that an error raised should always be cleared by a call
		 *   to outln_exec_error().
		 *
		 * */
	if (pexec_ctx->error_message != NULL)
		free(pexec_ctx->error_message);
	pexec_ctx->error_message = (char *)malloc(sizeof(char) * len);

	vsnprintf(pexec_ctx->error_message, len, fmt, args);
	va_end(args);
}

void outln_exec_error(int e, exec_ctx_t *pexec_ctx, int is_warning)
{
	if (is_warning)
		fprintf(stderr, "Warning: ");
	else
		fprintf(stderr, "Error: ");

	const char *builtin_error_message = NULL;
	if (pexec_ctx->error_message == NULL) {
		if (e >= 0 && e < (sizeof(table_errors) / sizeof(*table_errors))) {
			builtin_error_message = table_errors[e];
			if (builtin_error_message == NULL) {
				FATAL_ERROR("Error code %d has no defined error message!", e);
			}
		} else {
				/*
				 * FIXME (?)
				 *   Remove FATAL below and instead, display error code number if ever it is unknown.
				 *   I personally prefer hardened code. Error codes should be controlled.
				 * */
			FATAL_ERROR("Error code %d unknown!", e);
		}
	} else if (e != ERROR_CUSTOM) {
		FATAL_ERROR("Custom error message while error code != ERROR_CUSTOM, e = %d", e);
	}

	const char *error_message = pexec_ctx->error_message != NULL ? pexec_ctx->error_message : builtin_error_message;

	if (pexec_ctx->ploc != NULL && pexec_ctx->ploc->is_set) {
		if (pexec_ctx->ploc->file_name != NULL)
			fprintf(stderr, "%s: ", pexec_ctx->ploc->file_name);
		if (!opt_SCM && pexec_ctx->ploc->first_line >= 1 && pexec_ctx->ploc->first_column >= 1 &&
				pexec_ctx->ploc->last_line >= 1 && pexec_ctx->ploc->last_column >= 1)
			fprintf(stderr, "%d.%d-%d.%d: ", pexec_ctx->ploc->first_line, pexec_ctx->ploc->first_column,
				pexec_ctx->ploc->last_line, pexec_ctx->ploc->last_column);
	}

	if (pexec_ctx != NULL)
		if (pexec_ctx->function_name != NULL)
			fprintf(stderr, "%s(): ", pexec_ctx->function_name);

	fprintf(stderr, "%s\n", error_message);

	if (pexec_ctx->error_message != NULL) {
		free(pexec_ctx->error_message);
		pexec_ctx->error_message = NULL;
	}
}

static void usage()
{
	fprintf(stderr, "Usage: %s [options] [file ...]\n", PACKAGE_NAME);
	fprintf(stderr, "  -h  --help     print this usage and exit\n");
	fprintf(stderr, "  -V  --verbose  verbose output\n");
	fprintf(stderr, "  -q  --quiet    don't print initial banner\n");
	fprintf(stderr, "  -v  --version  print version information and exit\n");
	fprintf(stderr, "  -n  --numlib   (also -lib) defines number library to start with\n");
	fprintf(stderr, "  -t  --liblist  lists number libraries available and exit\n");
	fprintf(stderr, "  -l  --mathlib  use the predefined math routines (same as bc)\n");
	fprintf(stderr, "  --             end of parameters, next options are file names\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "%s will also read environment variable %s to parse options from,\n", PACKAGE_NAME, ENV_ARGS);
	fprintf(stderr, "using same format as command-line options.\n");
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
	fprintf(stderr, "'bc number' runtime error: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);
/*    exit(1);*/
}

	/* Needed by the bc library */
void out_of_memory()
{
	rt_error("%s", "Out of memory");
}

	/*
	 * Needed by FATAL_ERROR macro
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

void interrupt_signal_handler(int sig)
{
#ifdef MY_WINDOWS
	dont_stop_execution = TRUE;
#endif
	if (flag_execution_underway) {
		flag_interrupt_execution = TRUE;
		signal(SIGINT, interrupt_signal_handler);
		return;
	}

	out_dbg("interrupt_signal_handler() executed, sig = %d\n", sig);

	out(L_ENFORCE, "\n(interrupt) use quit to exit.\n");

#ifdef READLINE
	rl_initialize();
#endif

	signal(SIGINT, interrupt_signal_handler);
}

int is_flag_interrupt_execution_set()
{
	int r = flag_interrupt_execution;
	flag_interrupt_execution = FALSE;
	return r;
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
	static int defined_options[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

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
		int *opt_liblist, const char **nlib_tostartwith, const char **dbg_fname, int *o_SCM, int *o_COPYONUPDATE, int *isintrctv,
		int *mathlib)
{
#define OPT_WITH_VALUE_CHECK \
if (shortopt_nb >= 1 && shortopt_i < shortopt_nb - 1) { \
	missing_option_value = argv_a_short + 1; \
	a = -1; \
	break; \
} \
if (++a >= argc) { \
	missing_option_value = argv[a - 1] + 1; \
	a = -1; \
	break; \
}

	char *missing_option_value = NULL;

	int a = 1;
	char *argv_a_short;
	char shortopt[3];
	int shortopt_nb = 0;
	int shortopt_i = -1;
	while (a < argc) {
		if (shortopt_nb == 0) {
			if (strlen(argv[a]) >= 2 && argv[a][0] == '-' && argv[a][1] != '-') {
				shortopt_nb = strlen(argv[a]) - 1;
				shortopt_i = 0;
			}
		}
		if (shortopt_nb >= 1) {

#ifdef ZZDEBUGOPTS
			fprintf(stderr, "A - shortopt_i = %d, shortopt_nb = %d\n", shortopt_i, shortopt_nb);
#endif

			assert(shortopt_i <= shortopt_nb);
			shortopt[0] = '-';
			shortopt[1] = argv[a][shortopt_i + 1];
			shortopt[2] = '\0';
			argv_a_short = shortopt;
		} else {
			argv_a_short = argv[a];
		}

#ifdef ZZDEBUGOPTS
		fprintf(stderr, "argv_a_short = '%s'\n", argv_a_short);
#endif

		if (!strcmp(argv[a], "--help") || !strcmp(argv_a_short, "-h")) {
			usage();
		} else if (!strcmp(argv[a], "--version") || !strcmp(argv_a_short, "-v")) {
			version();
			exit(0);
		} else if (!strcmp(argv[a], "--verbose") || !strcmp(argv_a_short, "-V")) {
			opt_check(0, argv[a]);
			*optset_verbose = TRUE;
			out_level = L_VERBOSE;
		} else if (!strcmp(argv[a], "--SCM")) {
			opt_check(5, argv[a]);
			*o_SCM = TRUE;
			out_level = L_VERBOSE;
		} else if (!strcmp(argv[a], "--COPYONUPDATE")) {
			opt_check(8, argv[a]);
			*o_COPYONUPDATE = TRUE;
			out_level = L_VERBOSE;
		} else if (!strcmp(argv[a], "--interactive") || !strcmp(argv_a_short, "-i")) {
			opt_check(6, argv[a]);
			*isintrctv = TRUE;
		} else if (!strcmp(argv[a], "--mathlib") || !strcmp(argv_a_short, "-l")) {
			opt_check(7, argv[a]);
			*mathlib = TRUE;
		} else if (!strcmp(argv[a], "--quiet") || !strcmp(argv_a_short, "-q")) {
			opt_check(1, argv[a]);
			*optset_quiet = TRUE;
			out_level = L_QUIET;
		} else if (!strcmp(argv[a], "--debug") || !strcmp(argv_a_short, "-d")) {
			opt_check(2, argv[a]);
			*optset_debug = TRUE;
			out_level = L_DEBUG;
		} else if (!strcmp(argv[a], "--debugfile") || !strcmp(argv_a_short, "-D")) {
			opt_check(4, argv[a]);
			*optset_debug = TRUE;
			out_level = L_DEBUG;
			OPT_WITH_VALUE_CHECK
			*dbg_fname = argv[a];
		} else if (!strcmp(argv[a], "--liblist") || !strcmp(argv_a_short, "-t")) {
			*opt_liblist = TRUE;
		} else if (!strcmp(argv[a], "--lib") || !strcmp(argv[a], "--numlib") || !strcmp(argv_a_short, "-n")) {
			opt_check(3, argv[a]);
			OPT_WITH_VALUE_CHECK
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
			input_register(argv[a]);
		}
#ifdef ZZDEBUGOPTS
			fprintf(stderr, "B - shortopt_i = %d, shortopt_nb = %d\n", shortopt_i, shortopt_nb);
#endif
		if (shortopt_nb >= 1) {
			if (++shortopt_i >= shortopt_nb)
				shortopt_nb = 0;
		}
		if (shortopt_nb == 0)
			++a;
#ifdef ZZDEBUGOPTS
			fprintf(stderr, "C - shortopt_i = %d, shortopt_nb = %d\n", shortopt_i, shortopt_nb);
#endif
	}
	while (a >= 1 && a < argc) {
		input_register(argv[a]);
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
static void cut_env_options(int *env_argc, char ***env_argv, char **alloc_env, const char **env_orig)
{
	*env_argc = 0;
	*env_argv = NULL;
	*alloc_env = NULL;
	*env_orig = getenv(ENV_ARGS);
	if (*env_orig == NULL)
		return;

		/*
		 * According to getenv manual, the returned string should not be modified
		 * and we need to modify it...
		 * */
	*alloc_env = s_alloc_and_copy(NULL, *env_orig);

	*env_argc = 1;
	int env_argc_allocated = 2;
	*env_argv = (char **)malloc(sizeof(char *) * env_argc_allocated);

		/* Useless. Done in case argv[0] is ever used */
	(*env_argv)[0] = ENV_ARGS;

	char *p = *alloc_env;
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

#ifdef HAS_LIB_READLINE

/* Code below taken as is (besides some indentation and move to main.c) from bc source in bc/scan.l */

/*
 * Support for the readline and history libraries.  This allows
 * nicer input on the interactive part of input.
 */

	/* Variables to help interface readline with bc */
static char *rl_line = NULL;
static char *rl_start = NULL;
static int rl_len = 0;

	/* Definitions for readline access */
extern FILE *rl_instream;
extern FILE *yyin;
void yyerror(char *s, ...);

/*
 * rl_input puts upto MAX characters into BUF with the number put in
 * BUF placed in *RESULT.  If the yy input file is the same as
 * rl_instream (stdin), use readline.  Otherwise, just read it.
 */

void rl_input(char *buf, long unsigned int *result, int max)
{
	if (yyin != rl_instream || !is_interactive || opt_SCM) {
		while ((*result = read(my_fileno(yyin), buf, max)) < 0 )
			if (errno != EINTR) {
				yyerror("read() in flex scanner failed" );
				exit(1);
			}
		return;
	}

		/* Do we need a new string? */
	if (rl_len == 0) {
		if (rl_start)
			free(rl_start);
		rl_start = readline("");
		if (rl_start == NULL) {
				/* End of file */
			*result = 0;
			rl_len = 0;
			return;
		}
		rl_line = rl_start;
		rl_len = strlen(rl_line)+1;
		if (rl_len != 1)
			add_history (rl_line);
		rl_line[rl_len-1] = '\n';
/*        fflush(stdout);*/
/*        if (ferror(stdout))*/
/*            FATAL_ERROR("%s", "Fatal error writing to stdout");*/
	}

	if (rl_len <= max) {
		strncpy(buf, rl_line, rl_len);
		*result = rl_len;
		rl_len = 0;
	} else {
		strncpy(buf, rl_line, max);
		*result = max;
		rl_line += max;
		rl_len -= max;
	}
}

void init_readline()
{
	rl_instream = stdin;
}

#else /* #ifdef HAS_LIB_READLINE */

#define init_readline()

#endif /* #ifdef AS_LIB_READLINE */

int main(int argc, char *argv[])
{
	init_readline();

		/* done to have a non NULL defarg_t_badarg pointer (any address would be fine) */
	defarg_t_badarg = (defargs_t *)VAR_LAST;

	if (ERROR_LAST + 1 != sizeof(table_errors) / sizeof(*table_errors))
		FATAL_ERROR("%s", "table_errors has initialization inconsistent with ERROR_ constants");

#ifdef BISON_DEBUG
	activate_bison_debug();
#endif

	/* Interactive? */
	/* Credits - the two lines below got copied from bc source (main.c) */
	if (isatty(0) && isatty(1))
		is_interactive = TRUE;

	char *env;
	rt_line_length = DEFAULT_LINE_LENGTH;
	if ((env = getenv(LINE_LENGTH_ENV)) != NULL) {
		rt_line_length = atoi(env);
		if (strlen(env) == 0 || (env[0] < '0' && env[0] > '9'))
			rt_line_length = DEFAULT_LINE_LENGTH;
		else if (rt_line_length < 3 && rt_line_length != 0)
			rt_line_length = DEFAULT_LINE_LENGTH;
	}

	int optset_verbose = FALSE;
	int optset_quiet = FALSE;
	int optset_debug = FALSE;
	int optset_liblist = FALSE;
	const char *numlib_to_start_with = NULL;

	int env_argc;
	char **env_argv;
	const char *orig_env;
	char *alloc_env;
	cut_env_options(&env_argc, &env_argv, &alloc_env, &orig_env);
	parse_options(env_argc, env_argv, &optset_verbose, &optset_quiet, &optset_debug,
		&optset_liblist, &numlib_to_start_with, &debug_filenames, &opt_SCM, &opt_COPYONUPDATE, &is_interactive, &bc_mathlib);
	optset_verbose = FALSE;
	optset_quiet = FALSE;
	optset_debug = FALSE;
	parse_options(argc, argv, &optset_verbose, &optset_quiet, &optset_debug,
		&optset_liblist, &numlib_to_start_with, &debug_filenames, &opt_SCM, &opt_COPYONUPDATE, &is_interactive, &bc_mathlib);

	if (optset_verbose && optset_quiet)
		out_level = L_NORMAL;
	if (optset_debug)
		out_level = L_DEBUG;

	if (env_argc >= 1) {
		out_dbg("Environment variable '%s' found\n\tValue: '%s'\n\tResult of value parsing;\n", ENV_ARGS, orig_env);
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
	const libinfo_t *li = num_lib_get_current();
	out_dbg("Numeric library is '%s'\n", li->libname);
	if (strcmp(li->libname, "libbc") && bc_mathlib) {
		fprintf(stderr, "%s: option -l (a.k. -mathlib) works only with libbc. Consider using option '--numlib bc'.\n", PACKAGE_NAME);
		exit(-3);
	}

	int i;
	for (i = 0; i < input_nb; ++i) {
		out_dbg("Input file #%d: %s\n", i + 1, input_list[i].name);
	}

	input_cursor = -1;

	if (bc_mathlib) {
#ifdef HAS_LIB_LIBBC

#ifdef DEBUG
#if 0
#warning  Are you sure you want to execute this debug code?
#warning  It is meant to see libbc_libmath content (as it is at load time)
#error    in case an error (flex or bison) occurs during loading
		char *p = libbc_libmath;
		FILE *F = fopen("internal-image-libmath.b", "w");
		while (*p != '\0') {
			putc(*p, F);
			++p;
		}
		fclose(F);
#endif
#endif

		set_input_name("<internal libbc>");
		yy_scan_buffer(libbc_libmath, libbc_libmath_len);
		loc_reset();
#else
		FATAL_ERROR("%s", "Bug: bc_mathlib can be used only along with libbc, and libbc can be activated only when HAS_LIB_LIBBC is set");
#endif
	} else
		yywrap();

	signal(SIGINT, interrupt_signal_handler);

/*         FIXME */
/*    sleep(1);*/
/*    int c = term_getkey();*/
/*    printf("Key pressed: %d (%c) [%02X]\n", c, (char)c, (unsigned char)c);*/
/*    return 0;*/

	yyparse();

	num_terminate();
	if (env_argv != NULL)
		free(env_argv);
	if (alloc_env != NULL)
		free(alloc_env);
	input_terminate();

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

	/*
	 * Adds one entry to read when program starts.
	 * Entry can be a file provided in the command-line but also internal
	 * code to define some functions on start-up (ex. with -l option)
	 *
	 * Adds entry at first position if append is FALSE, or at last position if append is TRUE.
	 * */
static void input_register(const char *name)
{
	if (++input_nb > input_nb_alloc) {
		if (input_list == NULL) {
			input_nb_alloc = 1;
			input_list = (input_t *)malloc(sizeof(input_t) * input_nb_alloc);
		} else {
			input_nb_alloc *= 2;
			input_list = (input_t *)realloc(input_list, sizeof(input_t) * input_nb_alloc);
		}
	}
	input_t *new_input;
	new_input = &input_list[input_nb - 1];
	new_input->name = name;
}

static void input_terminate()
{
	if (input_list != NULL)
		free(input_list);
}

const char *input_get_name()
{
	return input_name;
}

static void set_input_name(const char *s)
{
	input_name = s;
}

	/*
	 * Returns the FILE* of the next file to read. Files to read come in the order
	 * they were provided in the arguments.
	 * Once the end of the list is reached, returns stdin.
	 * Then returns NULL to say it is over.
	 * */
FILE *input_get_next()
{

	if (input_cursor >= 0 && input_cursor < input_nb && input_FILE != NULL) {
		fclose(input_FILE);
		out_dbg("input_get_next(): closed file %s\n", input_get_name());
	}

	++input_cursor;
	out_dbg("input_get_next(): input_cursor = %d, input_nb = %d\n", input_cursor, input_nb);

	if (input_cursor < input_nb) {

/* Input is a file (provided in the command-line options) */

		input_t *inp = &input_list[input_cursor];
		input_name = inp->name;
		out_dbg("input_get_next() is now on entry: %s\n", input_name);

		if ((input_FILE = fopen(input_name, "r")) == NULL) {
			outln_error("File '%s' is unavailable", input_name);
			exit(-99);
		} else {
			out_dbg("input_get_next(): opened file %s, it is the next yyin-to-be\n", input_name);
		}

		return input_FILE;
	}

	int go_to_stdin = (input_cursor == input_nb);
#ifdef MY_WINDOWS
	if (input_cursor > input_nb && !flag_quitting) {
			/*
			 * FIXME - FIXME
			 *
			 * Sleep 1/10 of second, to allow ctrl-c (caught by interrupt_signal_handler)
			 * to set dont_stop_execution to TRUE.
			 *
			 * Yes, this code is extremly uggly. There is a race condition and we solve it
			 * with a call to Sleep()!
			 *
			 * */
		Sleep(100);
		go_to_stdin = dont_stop_execution;
		dont_stop_execution = FALSE;
	}
#endif

	if (go_to_stdin) {

/* Input will be stdin */

		input_name = "";
		input_FILE = stdin;
		out_dbg("input_get_next(): stdin is the next yyin-to-be\n");
		check_functions();
	} else {

/* Input terminated... */

		input_name = NULL;
		input_FILE = NULL;
		out_dbg("input_get_next(): NULL is the next yyin-to-be\n");
	}
	return input_FILE;
}

