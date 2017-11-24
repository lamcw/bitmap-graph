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
typedef struct _graph_t *graph_t;

/* malloc a graph_t struct and initialize all values in struct, then return a */
/* pointer to the struct */
graph_t mkgraph(uint32_t nv);
int mkedge(graph_t g, vertex_t from, vertex_t to);
int rmedge(graph_t g, vertex_t from, vertex_t to);
void show_graph(graph_t g, int mode);
void destroy_graph(graph_t g);

#endif
