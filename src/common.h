/* common.h

Sébastien Millet, May 2015

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

void yyerror(char *s, ...);

int out(const char *fmt, ...);
char *s_strncpy(char *dest, const char *src, size_t n);

#endif /* COMMON_H */

