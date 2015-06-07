/* common.h

Sébastien Millet, May 2015

*/

#ifndef COMMON_H
#define COMMON_H

#ifdef HAVE_CONFIG_H
#include "../config.h"
#else
/* Defines some PACKAGE* constants in case config.h is not available */
#include "../extracfg.h"
#endif

#define COUNT_MPZ

#ifdef COUNT_MPZ

#define COUNT_MPZ_DEC \
	count_mpz_add(-1);

#define COUNT_MPZ_INC \
	count_mpz_add(1);

#else /* COUNT_MPZ */

#define COUNT_MPZ_DEC
#define COUNT_MPZ_INC

#endif /* COUNT_MPZ */

#ifdef DEBUG
#define out_dbg(...) \
	out(__VA_ARGS__)
#else
#define out_dbg(...) ;
#endif

void count_mpz_add(const long int delta);
void yyerror(char *s, ...);

#endif /* COMMON_H */

