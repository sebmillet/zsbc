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

#ifdef DEBUG
#define out_dbg(...) \
	out(__VA_ARGS__)
#else
#define out_dbg(...) ;
#endif

enum {ERR_NONE = 0, ERR_DIV0};

int out(const char *fmt, ...);
int out_err(const char *fmt, ...);
void out_err_code(int e);

char *s_strncpy(char *dest, const char *src, size_t n);

#endif /* COMMON_H */

