/* expr.h */

/* Sébastien Millet 2015 */

#include "common.h"
#include <gmp.h>

typedef enum {TNODE_NUMBER, TNODE_GETVAR, TNODE_SETVAR, TNODE_BUILTIN_OP} expr_node_t;

typedef enum {FN_ADD, FN_SUB, FN_MUL, FN_DIV, FN_POW, FN_MOD, FN_NEG} function_t;

typedef struct expr_t {
	expr_node_t type;
	union {
		char *varname;
		mpz_t *mp;
		function_t fn;
	};
	int nb_args;
	struct expr_t *args[2];
} expr_t;

void expr_destruct(expr_t *e);
expr_t *expr_const_number(mpz_t* mp);
expr_t *expr_const_getvar(char *varname);
expr_t *expr_const_setvar(char *varname, expr_t *e1);
expr_t *expr_const_op1(function_t fn, expr_t *e1);
expr_t *expr_const_op2(function_t fn, expr_t *e1, expr_t *e2);
expr_t *expr_const_op2_and_setvar(char *varname, function_t fn, expr_t *e);

