#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

AC_INIT([zsbc], [0.1], [milletseb@laposte.net])

AC_CONFIG_SRCDIR([src/common.h])
AC_CONFIG_AUX_DIR([admin])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE([subdir-objects])

AM_MAINTAINER_MODE

AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_YACC
AC_PROG_LEX
AC_PROG_RANLIB

# Checks for header files.
AC_FUNC_ALLOCA
AC_FUNC_VPRINTF
AC_CHECK_HEADERS([inttypes.h libintl.h malloc.h stddef.h stdlib.h string.h unistd.h lib.h gmp.h readline.h history.h])

dnl ==================== Options ====================================

has_one_numlib="no"

AC_ARG_ENABLE(debug,
			  [  --enable-debug          enable debugging information],
			  enable_debug="$enableval", enable_debug="no")

if test "${enable_debug}" = yes ; then
	CFLAGS="$CFLAGS -DDEBUG"
fi

if test "x$USE_MAINTAINER_MODE" = "xyes"; then
	build_docs=yes
else
	build_docs=no
fi

AM_CONDITIONAL(BUILD_DOCS, test $build_docs = yes)

AC_ARG_ENABLE(bison-debug,
		[  --enable-bison-debug          enable debugging information for bison],
		enable_bison_debug="$enableval", enable_bison_debug="no")

AC_ARG_ENABLE(flex-debug,
		[  --enable-flex-debug           enable debugging information for flex],
		enable_flex_debug="$enableval",  enable_flex_debug="no")

AC_ARG_ENABLE(gmp,
			  [  --disable-gmp                 compile without the GNU Multi Precision library (gmp)])
test -z "$enable_gmp" && enable_gmp="yes"
if test "${enable_gmp}" = yes ; then
	has_one_numlib="yes"
	AC_CHECK_LIB(gmp, __gmpz_init, , [AC_MSG_ERROR([GNU MP not found, see https://gmplib.org/ or try to install gmp dev lib on your system (libgmp-dev for deb, gmp-devel for rpm)])])
	CPPFLAGS="$CPPFLAGS -DHAS_LIB_GMP"
fi

AC_ARG_ENABLE(libbc,
		[  --disable-libbc               compile without the bc/dc number library (libbc)])
test -z "$enable_libbc" && enable_libbc="yes"
if test "${enable_libbc}" = yes ; then
	has_one_numlib="yes"
	CPPFLAGS="$CPPFLAGS -DHAS_LIB_LIBBC"
fi

if test "${enable_bison_debug}" = yes ; then
	CFLAGS="$CFLAGS -DBISON_DEBUG"
	if test "x$USE_MAINTAINER_MODE" != "xyes"; then
		AC_MSG_ERROR([Enabling bison debug without --enable-maintainer-mode is useless])
	fi
fi

debug_flex=no
if test "${enable_flex_debug}" = yes ; then
	CFLAGS="$CFLAGS -DFLEX_DEBUG"
	debug_flex=yes
	if test "x$USE_MAINTAINER_MODE" != "xyes"; then
		AC_MSG_ERROR([Enabling flex debug without --enable-maintainer-mode is useless])
	fi
fi
AM_CONDITIONAL(DEBUG_FLEX, test $debug_flex = yes)

AC_ARG_ENABLE(readline,
			  [  --disable-readline                 compile without the readline library])
test -z "$enable_readline" && enable_readline="yes"
if test "${enable_readline}" = yes ; then
	AC_CHECK_LIB(readline, readline, , [AC_MSG_ERROR([readline not found, use --disable-readline option if you wish to compile without readline])])
	CPPFLAGS="$CPPFLAGS -DHAS_LIB_READLINE"
fi

AM_CONDITIONAL(WITH_GMP, [ test "${enable_gmp}" = yes ])
AM_CONDITIONAL(WITH_LIBBC, [ test "${enable_libbc}" = yes ])
AM_CONDITIONAL(WITH_READLINE, [ test "${enable_readline}" = yes ])

if test "${has_one_numlib}" = no ; then
	AC_MSG_ERROR([You have to compile with at least one num library])
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile
				src/Makefile
				lib/Makefile
				doc/Makefile])
AC_OUTPUT

