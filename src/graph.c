#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "graph.h"

/* given n vertices, calculate the size of column of the matrix */
#ifndef BM_COLSIZE
#define BM_COLSIZE(nv) ((uint32_t)ceil((double)nv / 32.0f))
#endif

/* get index of bit in array */
#ifndef POS
#define POS(pos) ((uint32_t)floor((double)pos / 32.0f))
#endif
/* get bit offset from right-hand side */
#ifndef POS_OFFSET
#define POS_OFFSET(pos) (1U << (31 - (pos % 32)))
#endif

/* check if vertex is valid */
#ifndef VALID_V
#define VALID_V(g, v) (v < g->nv)
#endif
/* check if bit in word is 1 */
#ifndef CKBIT
#define CKBIT(word, pos) (word & (1U << pos))
#endif

#ifndef PRINT_WORD
#define PRINT_WORD(word)				\
for (uint32_t mask = 1 << 31; mask >= 1; mask >>= 1) {	\
	printf("%d", word & mask ? 1 : 0);		\
}							\
putchar('\n');
#endif

struct _graph_t {
	/* n vertices */
	uint32_t nv;
	/* n edges */
	uint32_t ne;
	/* uint matrix (bitmap) */
	vertex_t **bm;
};

/* malloc a graph_t struct and initialize all values in struct, then return a */
/* pointer to the struct */
graph_t mkgraph(uint32_t nv) {
	graph_t new = calloc(1, sizeof(struct _graph_t));
	
	if (new == NULL) {
		/* error: G_ENOMEM */
		return NULL;
	}

	new->nv = nv;
	new->bm = calloc(nv, sizeof(vertex_t *));

	for (uint32_t i = 0; i < nv; i++) {
		new->bm[i] = calloc(BM_COLSIZE(nv), sizeof(vertex_t));
		if (new->bm[i] == NULL) {
			/* free all previously allocated memory */
			for (uint32_t j = 0; j < i; j++)
				free(new->bm[j]);
			/* error: G_ENOMEM */
			return NULL;
		}
	}

	return new;
}

int mkedge(graph_t g, vertex_t from, vertex_t to) {
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

int rmedge(graph_t g, vertex_t from, vertex_t to) {
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

static void show_mtrx(graph_t g)
{
	if (g == NULL) {
		return;
	}

	for (uint32_t i = 0; i < g->nv; i++) {
		/* keep track of numbers of bits printed */
		uint32_t count = 0;
		for (uint32_t j = 0; j < BM_COLSIZE(g->nv); j++) {
			for (uint32_t mask = 1 << 31; mask >= 1; mask >>= 1, count++) {
				if (count >= g->nv) {
					break;
				}
				printf("%d", g->bm[i][j] & mask ? 1 : 0);
				if (count < g->nv - 1) {
					/* do not print trailing whitespace */
					putchar(' ');
				}
			}
			if (count >= g->nv) {
				break;
			}
		}
		putchar('\n');
	}
}

static void show_list(graph_t g)
{
	if (g == NULL) {
		return;
	}
}

static void show_read(graph_t g)
{
	if (g == NULL) {
		return;
	}
}

void show_graph(graph_t g, int mode) {
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

void destroy_graph(graph_t g) {
	if (g == NULL) {
		return;
	}

	/* free bitmap rows */
	for (uint32_t i = 0; i < g->nv; i++) {
		free(g->bm[i]);
	}
	/* free bitmap */
	free(g->bm);
	/* free graph struct */
	free(g);
}
