/* expr.h */

/* Sébastien Millet 2015 */

#include "common.h"
#include <gmp.h>

typedef enum {TNODE_NUMBER = 0, TNODE_GETVAR, TNODE_SETVAR, TNODE_BUILTIN_OP, TNODE_LAST = TNODE_BUILTIN_OP} expr_node_t;

typedef enum {FN_ADD, FN_SUB, FN_MUL, FN_DIV, FN_POW, FN_MOD, FN_NEG} builtin_id;

typedef struct expr_t {
	expr_node_t type;
	union {
		char *varname;
		mpz_t *mp;
		builtin_id builtin;
	};
	int nb_args;
	struct expr_t *args[2];
} expr_t;

void expr_destruct(expr_t *self);

expr_t *expr_const_number(mpz_t* mp);
expr_t *expr_const_getvar(char *varname);
expr_t *expr_const_setvar(char *varname, expr_t *e1);
expr_t *expr_const_op1(builtin_id builtin, expr_t *e1);
expr_t *expr_const_op2(builtin_id builtin, expr_t *e1, expr_t *e2);
expr_t *expr_const_op2_and_setvar(char *varname, builtin_id builtin, expr_t *e1);

int expr_eval(const expr_t *self, mpz_t* const value);
int expr_get_count_ref();

