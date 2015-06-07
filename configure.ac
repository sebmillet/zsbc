#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

AC_INIT([zsbc], [0.1], [milletseb@laposte.net])

AC_CONFIG_SRCDIR([src/common.h])
AC_CONFIG_AUX_DIR([admin])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE

AM_MAINTAINER_MODE

AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_YACC
AC_PROG_LEX

# Checks for libraries.

# Checks for header files.
AC_FUNC_ALLOCA
AC_CHECK_HEADERS([inttypes.h libintl.h malloc.h stddef.h stdlib.h string.h unistd.h gmp.h])

dnl ==================== Options ====================================

AC_ARG_ENABLE(debug,
              [  --enable-debug          enable debugging information],
              enable_debug="$enableval", enable_debug="no")

if test "${enable_debug}" = yes ; then
	CFLAGS="$CFLAGS -DDEBUG"
fi

AC_ARG_ENABLE(bison-debug,
		[  --enable-bison-debug          enable debugging information for bison],
		enable_bison_debug="$enableval", enable_bison_debug="no")

AC_ARG_ENABLE(flex-debug,
		[  --enable-flex-debug          enable debugging information for flex],
		enable_flex_debug="$enableval", enable_flex_debug="no")

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
                 src/Makefile])
AC_OUTPUT

