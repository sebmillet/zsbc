/* expr.h */

/* Sébastien Millet 2015 */

#include "common.h"
#include <gmp.h>

typedef enum {TNODE_INTEGER, TNODE_VARIABLE, TNODE_BUILTIN_FUNCTION} expr_node_t;

typedef struct expr_t {
	char *name;
	expr_node_t type;
	union {
		mpz_t *mp;
			/* One argument function like mpz_neg */
		void (*mpz_func1)(mpz_t a, const mpz_t b);
			/* Two argument functions like mpz_add */
		void (*mpz_func)(mpz_t a, const mpz_t b, const mpz_t c);
			/* Two argument functions, the second one being unsigned long int, like mpz_pow_ui */
		void (*mpz_func_ui)(mpz_t a, const mpz_t b, unsigned long int c);
	};
	int nb_args;
	struct expr_t *args[2];
} expr_t;

char *copystr(char *dest, const char *src);
expr_t *expr_create_var(const char *varname);
expr_t *expr_create_builtin1(const char *name, void (*f)(mpz_t a, const mpz_t b), expr_t *e);
expr_t *expr_create_builtin(const char *name,
		void (*f)(mpz_t a, const mpz_t b, const mpz_t), expr_t *e1, expr_t *e2);
expr_t *expr_create_builtin_ui(const char *name,
		void (*f)(mpz_t a, const mpz_t b, unsigned long int c), expr_t *e1, expr_t *e2);

