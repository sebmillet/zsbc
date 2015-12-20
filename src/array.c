/*
 * =====================================================================================
 *
 *       Filename:  array.c
 *
 *    Description:  Manages arrays.
 *
 *        Version:  1.0
 *        Created:  13/09/2015 13:08:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Sébastien Millet (smt), milletseb@laposte.net
 *
 * =====================================================================================
 */

#include "array.h"
#include "vars.h"

	/*
	 * The max index is equal to
	 *   (2 ^ TREE_SHIFTBITS_BY_LEVEL) ^ TREE_LEVELS - 1
	 *
	 * */
#define TREE_UPPER_INDEX			16777215
#define TREE_LEVELS					3
#define TREE_NB_DESCENDANTS_BY_NODE	256			/* Equals 2 ^ TREE_SHIFTBITS_BY_LEVEL */
#define TREE_MASK					0x00FF		/* Equals TREE_NB_DESCENDANTS_BY_NODE - 1 */
#define TREE_SHIFTBITS_BY_LEVEL		8

extern int opt_COPYONUPDATE;

typedef struct node_t {
	union {
		struct node_t *subnode;
		numptr num;
	};
} node_t;

struct array_t {
	node_t *nodes;

		/* To implement "last minute" copy of attays (passed by value) */
	int copyonupdate_remote_copy;
	array_t *copyonupdate_remote_copy_mate;
	int copyonupdate_self_copy;
	array_t *copyonupdate_self_copy_mate;
};

void copyonupdate_manage_copy(array_t *a, int for_destruct);

static void node_tree_destruct(node_t *nodes, int level)
{
	assert(nodes != NULL);

	int i;
	if (level < TREE_LEVELS - 1) {
		for (i = 0; i < TREE_NB_DESCENDANTS_BY_NODE; ++i) {
			if (nodes[i].subnode != NULL)
				node_tree_destruct(nodes[i].subnode, level + 1);
		}
	} else {
		for (i = 0; i < TREE_NB_DESCENDANTS_BY_NODE; ++i) {
			if (!num_is_not_initialized(nodes[i].num))
				num_destruct(&nodes[i].num);
		}
	}

	free(nodes);
}

void array_destruct(array_t *a)
{
	if (a != NULL) {
		copyonupdate_manage_copy(a, TRUE);
		if (a->nodes != NULL)
			node_tree_destruct(a->nodes, 0);
		free(a);
	}
}

	/*
	 * make_ready_for_assignment means, in all cases, shall return a non-NULL pointer,
	 * that points to a numptr with the value num_undefvalue().
	 *
	 * If make_ready_for_assignment is TRUE:
	 *   - All tree levels must exist up to the last level (create if needed)
	 *   - The pointer returned must be a valid slot (no NULL pointer
	 *     returned)
	 *   - The numptr* returned (the value pointed to by the return value)
	 *     must be an undefined numptr, that is, equal to num_undefvalue().
	 *     Thus if the value already exist, it is to be destructed (the
	 *     *number* is destructed, not the slot).
	 *
	 * If make_ready_for_assignment is FALSE:
	 *   Return a pointer to the value if it exists.
	 *   Return NULL if not.
	 *
	 * */
static numptr *find_index(array_t *a, long int index, int make_ready_for_assignment)
{
	assert(!make_ready_for_assignment || a != NULL);
	assert(index >= 0);

	if (a == NULL)
		return NULL;

	int coord[32];
	int l;
	for (l = TREE_LEVELS - 1; l >= 0; --l) {
		coord[l] = index & TREE_MASK;
		index >>= TREE_SHIFTBITS_BY_LEVEL;
	}

#ifdef DEBUG
	int j;
	for (j = 0; j < TREE_LEVELS; ++j) {
		out_dbg("coord[%d] = %d\n", j, coord[j]);
	}
#endif

		/* The fact that index is in a correct range is to be checked upfront */
	assert(!index);

	node_t **walker = &a->nodes;
	for (l = 0; l < TREE_LEVELS; ++l) {
		if (*walker == NULL) {
			if (!make_ready_for_assignment)
				return NULL;

			out_dbg("Creating level %d\n", l);

			*walker = (node_t *)malloc(sizeof(node_t) * TREE_NB_DESCENDANTS_BY_NODE);
			int i;
			if (l < TREE_LEVELS - 1) {
				out_dbg("Zeroing subnodes\n");
				for (i = 0; i < TREE_NB_DESCENDANTS_BY_NODE; ++i)
					(*walker)[i].subnode = NULL;


			} else {
				out_dbg("Assigning undef value to numbers\n");
				for (i = 0; i < TREE_NB_DESCENDANTS_BY_NODE; ++i) {
					(*walker)[i].num = num_undefvalue();
/*                    out_dbg("i = %d\n", i);*/
					assert(num_is_not_initialized((*walker)[i].num));
				}
			}
		}
		if (l < TREE_LEVELS - 1)
			walker = &(*walker)[coord[l]].subnode;
	}

	assert(l == TREE_LEVELS);

	out_dbg("TREE_LEVELS - 1 = %d, coord[TREE_LEVELS - 1] = %d\n", TREE_LEVELS - 1, coord[TREE_LEVELS - 1]);

	numptr *pnum = &((*walker)[coord[TREE_LEVELS - 1]].num);
	if (make_ready_for_assignment) {
		if (!num_is_not_initialized(*pnum))
			num_destruct(pnum);
		return pnum;
	}
	if (num_is_not_initialized(*pnum))
		return NULL;
	return pnum;
}

static void node_tree_copy(node_t **dest, const node_t *src, int level)
{
	assert(src != NULL);

	*dest = (node_t *)malloc(sizeof(node_t) * TREE_NB_DESCENDANTS_BY_NODE);

	int i;
	if (level < TREE_LEVELS - 1) {
		for (i = 0; i < TREE_NB_DESCENDANTS_BY_NODE; ++i) {
			if (src[i].subnode != NULL) {
				node_tree_copy(&(*dest)[i].subnode, src[i].subnode, level + 1);
			} else {
				(*dest)[i].subnode = NULL;
			}
		}
	} else {
		for (i = 0; i < TREE_NB_DESCENDANTS_BY_NODE; ++i) {
			if (num_is_not_initialized(src[i].num)) {
				(*dest)[i].num = num_undefvalue();
			} else {
				(*dest)[i].num = num_construct_from_num(src[i].num);
			}
		}
	}
}

const numptr *array_get_value(array_t *a, long int index)
{
	numptr *pnum = find_index(a, index, FALSE);
	if (pnum != NULL) {
		out_dbg("\t[%d] found\n", index);
		return pnum;
	} else {
		out_dbg("\t[%d] not found\n", index);
		return NULL;
	}
}

void copyonupdate_manage_copy(array_t *a, int for_destruct)
{
	if (a->copyonupdate_self_copy) {
		out_dbg("copyonupdate_event: main = %lu, mate = %lu\n", a, a->copyonupdate_self_copy_mate);
		if (a->nodes != NULL) {
			if (for_destruct) {
				out_dbg("copyonupdate_event_for_destruct\n");
				if (opt_COPYONUPDATE)
					outln(L_ENFORCE, "copyonupdate: soft array destruction of %lu", a);
				a->nodes = NULL;
			} else {
				out_dbg("copyonupdate_event_do_real_copy\n");
				if (opt_COPYONUPDATE)
					outln(L_ENFORCE, "copyonupdate: copying array %lu", a);
				node_tree_copy(&a->nodes, a->nodes, 0);
			}
		}
		a->copyonupdate_self_copy = FALSE;
		a->copyonupdate_self_copy_mate->copyonupdate_remote_copy = FALSE;
	}
	if (a->copyonupdate_remote_copy) {
		out_dbg("copyonupdate_event_notify_remote\n");
		copyonupdate_manage_copy(a->copyonupdate_remote_copy_mate, FALSE);
	}
}

static array_t *array_construct()
{
	array_t *a = (array_t *)malloc(sizeof(array_t));
	a->nodes = NULL;
	a->copyonupdate_self_copy = FALSE;
	a->copyonupdate_remote_copy = FALSE;
	return a;
}

array_t *array_t_get_a_copy(array_t *src)
{
	out_dbg("Call to array_t_get_a_copy()\n");

	array_t *copy = array_construct();
	if (src == NULL) {
		out_dbg("\tsrc is null\n");
		return copy;
	}

	copy->nodes = src->nodes;

	out_dbg("src->copyonupdate_self_copy = %d\n", src->copyonupdate_self_copy);
	if (src->copyonupdate_self_copy) {
		out_dbg("\t=> src->copyonupdate_self_copy_mate = %lu\n", src->copyonupdate_self_copy_mate);
	}
	out_dbg("src->copyonupdate_remote_copy = %d\n", src->copyonupdate_remote_copy);
	if (src->copyonupdate_remote_copy) {
		out_dbg("\t=> src->copyonupdate_remote_copy_mate = %lu\n", src->copyonupdate_remote_copy_mate);

			/*
			 * FIXME?
			 *
			 * If the source is already tied to a remote, then an immediate copy
			 * is to be done, otherwise we'll loose track of the current link.
			 * Alternative would be, to manage a list of remotes. But that's too much
			 * for now. I mark it here as a fix me with a question mark (it'll
			 * improve performance marginally I think, and it is not a bug)
			 *
			 * */

		out_dbg("\tarray already tied to a remote, doing a copy immediately\n");
		node_tree_copy(&copy->nodes, src->nodes, 0);
		return copy;
	}

		/* copy is the "mate" to copy on first update */
	copy->copyonupdate_self_copy = TRUE;
	copy->copyonupdate_self_copy_mate = src;

		/* src is the origin, NOT to copy when an update occurs */
	src->copyonupdate_remote_copy = TRUE;
	src->copyonupdate_remote_copy_mate = copy;

	out_dbg("Created a copy with copyonupdate information\n");
	out_dbg("\tsrc:  %lu, mate: %lu\n", src, src->copyonupdate_remote_copy_mate);
	out_dbg("\tcopy: %lu, mate: %lu\n", copy, copy->copyonupdate_self_copy_mate);

	return copy;
}

void array_set_value(array_t **pa, long int index, const numptr new_value, const numptr **ppvarnum)
{
	if (*pa == NULL)
		*pa = array_construct();

	copyonupdate_manage_copy(*pa, FALSE);

	numptr *pnum = find_index(*pa, index, TRUE);

	*pnum = new_value;
	*ppvarnum = pnum;
}

int array_check_index(long int index)
{
	return index >= 0 && index <= TREE_UPPER_INDEX ? ERROR_NONE : ERROR_ARRAY_OUT_OF_BOUNDS;
}

static long int core_array_count(const node_t *nodes, int rec_level)
{
	if (nodes == NULL)
		return 0;

	long int r = 0;

	if (rec_level < TREE_LEVELS - 1) {
		int i;
		for (i = 0; i < TREE_NB_DESCENDANTS_BY_NODE; ++i)
			r += core_array_count(nodes[i].subnode, rec_level + 1);
	} else {
		int i;
		for (i = 0; i < TREE_NB_DESCENDANTS_BY_NODE; ++i) {
			if (!num_is_not_initialized(nodes[i].num))
				++r;
		}
	}
	return r;
}

long int array_count(const array_t *a)
{
	if (a == NULL)
		return 0;

	return core_array_count(a->nodes, 0);
}

