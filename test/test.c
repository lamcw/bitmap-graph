#include <stdio.h>

#include "../src/graph.h"

int main(void)
{
	graph_t g = mkgraph(10);
	mkedge(g, 1, 2);
	mkedge(g, 1, 1);
	mkedge(g, 1, 9);
	rmedge(g, 1, 9);
	show_graph(g, D_MTRX | D_LIST);
	destroy_graph(g);
	return 0;
}
