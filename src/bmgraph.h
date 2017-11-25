/* graph library. */
/* written by Thomas Lam, 2017 */

#ifndef BITMAP_H
#define BITMAP_H

#include <stdint.h>

/* error code */
#define G_ENOMEM (1 << 0)
#define G_ENUM (1 << 1)
#define G_ERANGE (1 << 2)
#define G_ENULL (1 << 3)

/* graph display mode */
#define D_MTRX (1 << 0)	/* adjacency matrix */
#define D_LIST (1 << 1)	/* adjacency list */
#define D_READ (1 << 2)	/* human readable format */

typedef uint32_t vertex_t;
typedef uint32_t uint_t;
typedef struct _bmgraph_t *bmgraph_t;

/* malloc a bmgraph_t struct and initialize all values in struct, then return a */
/* pointer to the struct */
bmgraph_t mkgraph(uint32_t nv);

/* create an edge from vertex @from to vertex @to */
int mkedge(bmgraph_t g, vertex_t from, vertex_t to);

/* remove the edge from vertex @from to vertex @to */
int rmedge(bmgraph_t g, vertex_t from, vertex_t to);

/* check if vertex @from has an edge to @to */
int has_edge(bmgraph_t g, vertex_t from, vertex_t to);

/* find the in degree of vertex @v */
int indegree(bmgraph_t g, vertex_t v);

/* find the out degree of vertex @v */
int outdegree(bmgraph_t g, vertex_t v);

/* print matrix to stdout */
void show_graph(bmgraph_t g, int mode);

/* free memory allocated for @g */
void destroy_graph(bmgraph_t g);

#endif
