/* common.h

Sébastien Millet, May 2015

*/

#ifndef COMMON_H
#define COMMON_H

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

void loc_reset();
void yyerror(char *s, ...);

void count_mpz_add(const long int delta);

#endif /* COMMON_H */

