/* expr.c */

/* Sébastien Millet 2015 */

#include "common.h"
#include "expr.h"
#include <gmp.h>
#include <string.h>

char *copystr(char *dest, const char *src)
{
	if (src == NULL) {
		dest = NULL;
	} else {
		size_t l = strlen(src) + 1;
		dest = (char *)malloc(l);
		s_strncpy(dest, src, l);
	}
	return dest;
}

expr_t *expr_create_integer(mpz_t *mp)
{
	expr_t *enode = (expr_t *)malloc(sizeof(expr_t));
	enode->type = TNODE_INTEGER;
	enode->mp = mp;
	return enode;
}

expr_t *expr_create_var(const char *varname)
{
	expr_t *enode = (expr_t *)malloc(sizeof(expr_t));
	enode->type = TNODE_VARIABLE;
	copystr(enode->name, varname);
}

expr_t *expr_create_builtin1(const char *name,
		void (*f)(mpz_t a, const mpz_t b), expr_t *e)
{
	expr_t *enode = (expr_t *)malloc(sizeof(expr_t));
	enode->type = TNODE_BUILTIN_FUNCTION;
	enode->mpz_func1 = f;
	enode->args[0] = e;
}

expr_t *expr_create_builtin(const char *name,
		void (*f)(mpz_t a, const mpz_t b, const mpz_t), expr_t *e1, expr_t *e2)
{
	expr_t *enode = (expr_t *)malloc(sizeof(expr_t));
	enode->type = TNODE_BUILTIN_FUNCTION;
	enode->mpz_func = f;
	enode->args[0] = e1;
	enode->args[1] = e2;
}

expr_t *expr_create_builtin_ui(const char *name,
		void (*f)(mpz_t a, const mpz_t b, unsigned long int c), expr_t *e1, expr_t *e2)
{
	expr_t *enode = (expr_t *)malloc(sizeof(expr_t));
	enode->type = TNODE_BUILTIN_FUNCTION;
	enode->mpz_func_ui = f;
	enode->args[0] = e1;
	enode->args[1] = e2;
}

