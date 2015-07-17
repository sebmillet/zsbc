/*
 * =====================================================================================
 *
 *       Filename:  common.h
 *
 *    Description:  Header file for most zsbc source files.
 *
 *        Version:  1.0
 *        Created:  03/06/2015 23:22:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet (smt), milletseb@laposte.net
 *
 * =====================================================================================
 */


#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <assert.h>

#ifdef HAVE_CONFIG_H
#include "../config.h"
#else
/* Defines some PACKAGE* constants in case config.h is not available */
#include "../extracfg.h"
#endif

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

#ifdef DEBUG
#define out_dbg(...) \
	out(L_DEBUG, __VA_ARGS__)
#else
#define out_dbg(...) ;
#endif

#define ERROR_NONE						0
#define ERROR_DIV0						1
#define ERROR_NEGATIVE_EXP				2
#define ERROR_FUNCTION_NOT_DEFINED		3
#define ERROR_PARAMETER_NUMBER_MISMATCH	4
void outln_error_code(int e);

#define L_ENFORCE	(-1)
#define L_ERROR		0
#define L_WARNING	1
#define L_QUIET		2
#define L_NORMAL	3
#define L_VERBOSE	4
#define L_DEBUG		5
int out(int level, const char *fmt, ...);
int outln(int level, const char *fmt, ...);
int outln_error(const char *fmt, ...);
int outln_warning(const char *fmt, ...);
void fatalln(const char *file, int line, const char *fmt, ...);
#define FATAL_ERROR(s, ...) \
	fatalln(__FILE__, __LINE__, s, __VA_ARGS__)

char *s_strncpy(char *dest, const char *src, size_t n);
char *s_strncat(char *dest, const char *src, size_t n);
char *s_alloc_and_copy(char **dst, const char *src);

#endif /* COMMON_H */

