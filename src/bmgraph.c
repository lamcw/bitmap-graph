#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "bmgraph.h"

/* given n vertices, calculate the size of column of the matrix */
#ifndef BM_COLSIZE
#define BM_COLSIZE(nv) ((uint_t)ceil((double)nv / 32.0f))
#endif

/* get index of bit in array */
#ifndef POS
#define POS(pos) ((uint_t)floor((double)pos / 32.0f))
#endif
/* get bit offset from right-hand side */
#ifndef POS_OFFSET
#define POS_OFFSET(pos) (1U << (31 - (pos % 32)))
#endif

/* check if vertex is valid */
#ifndef VALID_V
#define VALID_V(g, v) (v < g->nv)
#endif

#ifndef HAS_EDGE
#define HAS_EDGE(g, from, to) (g->bm[from][POS(to)] & POS_OFFSET(to) ? 1 : 0)
#endif

#ifndef PRINT_WORD
#define PRINT_WORD(word)				\
for (uint_t mask = 1 << 31; mask >= 1; mask >>= 1) {	\
	printf("%d", word & mask ? 1 : 0);		\
}							\
putchar('\n');
#endif

struct _bmgraph_t {
	/* n vertices */
	uint_t nv;
	/* n edges */
	uint_t ne;
	/* uint matrix (bitmap) */
	vertex_t **bm;
};

/* malloc a bmgraph_t struct and initialize all values in struct, then return a */
/* pointer to the struct */
bmgraph_t mkgraph(uint_t nv) {
	bmgraph_t new = calloc(1, sizeof(struct _bmgraph_t));
	
	if (new == NULL) {
		/* error: G_ENOMEM */
		return NULL;
	}

	new->nv = nv;
	new->bm = calloc(nv, sizeof(vertex_t *));

	for (uint_t i = 0; i < nv; i++) {
		new->bm[i] = calloc(BM_COLSIZE(nv), sizeof(vertex_t));
		if (new->bm[i] == NULL) {
			/* free all previously allocated memory */
			for (uint_t j = 0; j < i; j++)
				free(new->bm[j]);
			/* error: G_ENOMEM */
			return NULL;
		}
	}

	return new;
}

/* create an edge from vertex @from to vertex @to */
int mkedge(bmgraph_t g, vertex_t from, vertex_t to) {
	/* sanity checks */
	int status = 0;
	if (g == NULL) {
		/* graph is NULL */
		status |= G_ENULL;
	}
	if (!VALID_V(g, from) || !VALID_V(g, to)) {
		/* invalid vertices arguments */
		status |= G_ENUM;
	}
	if (status != 0) {
		return status;
	}

	g->bm[from][POS(to)] |= POS_OFFSET(to);
	return 0;
}

/* remove the edge from vertex @from to vertex @to */
int rmedge(bmgraph_t g, vertex_t from, vertex_t to) {
	/* sanity checks */
	int status = 0;
	if (g == NULL) {
		/* graph is NULL */
		status |= G_ENULL;
	}
	if (!VALID_V(g, from) || !VALID_V(g, to)) {
		/* invalid vertices arguments */
		status |= G_ENUM;
	}
	if (status != 0) {
		return status;
	}

	g->bm[from][POS(to)] &= ~POS_OFFSET(to);
	return 0;
}

/* check if vertex @from has an edge to @to */
int has_edge(bmgraph_t g, vertex_t from, vertex_t to)
{
	/* sanity checks */
	if (g == NULL) {
		/* graph is NULL */
		return 0;
	}
	if (!VALID_V(g, from) || !VALID_V(g, to)) {
		/* invalid vertices arguments */
		return 0;
	}

	return HAS_EDGE(g, from, to);
}

/* find the in degree of vertex @v */
int indegree(bmgraph_t g, vertex_t v)
{
	if (g == NULL) {
		return -1;
	}

	if (!VALID_V(g, v)) {
		return -1;
	}

	int vcount = 0;

	for (uint_t i = 0; i < g->nv; i++) {
		if (HAS_EDGE(g, i, v)) {
			vcount++;
		}
	}

	return vcount;
}

/* find the out degree of vertex @v */
int outdegree(bmgraph_t g, vertex_t v)
{
	if (g == NULL) {
		return -1;
	}

	if (!VALID_V(g, v)) {
		return -1;
	}

	int vcount = 0;

	for (uint_t i = 0; i < g->nv; i++) {
		if (HAS_EDGE(g, v, i)) {
			vcount++;
		}
	}

	return vcount;
}

static void show_mtrx(bmgraph_t g)
{
	if (g == NULL) {
		return;
	}

	for (uint_t i = 0; i < g->nv; i++) {
		for (uint_t j = 0; j < g->nv; j++) {
			printf("%d", HAS_EDGE(g, i, j));
			if (j < g->nv - 1) {
				putchar(' ');
			}
		}
		putchar('\n');
	}
}

static void show_list(bmgraph_t g)
{
	if (g == NULL) {
		return;
	}

	for (uint_t i = 0; i < g->nv; i++) {
		printf("%d ->", i);
		for (uint_t j = 0; j < g->nv; j++) {
			if (HAS_EDGE(g, i, j)) {
				printf(" %d ->", j);
			}
		}
		putchar('\n');
	}
}

static void show_read(bmgraph_t g)
{
	if (g == NULL) {
		return;
	}
}

/* print matrix to stdout */
void show_graph(bmgraph_t g, int mode) {
	for (int mask = 0; mask < 3; mask++) {
		switch (mode & (1U << mask)) {
			case D_MTRX:
				show_mtrx(g);
				break;
			case D_LIST:
				show_list(g);
				break;
			case D_READ:
				show_read(g);
				break;
			default:
				break;
		}
	}
}

/* free memory allocated for @g */
void destroy_graph(bmgraph_t g) {
	if (g == NULL) {
		return;
	}

	/* free bitmap rows */
	for (uint_t i = 0; i < g->nv; i++) {
		free(g->bm[i]);
	}
	/* free bitmap */
	free(g->bm);
	/* free graph struct */
	free(g);
}
