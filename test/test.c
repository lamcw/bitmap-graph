#include "../src/graph.h"

int main(void)
{
	graph_t g = mkgraph(10);
	mkedge(g, 1, 2);
	mkedge(g, 1, 1);
	mkedge(g, 1, 9);
	rmedge(g, 1, 9);
	mkedge(g, 4, 8);
	mkedge(g, 9, 1);
	show_graph(g, D_MTRX | D_LIST);
	destroy_graph(g);
	return 0;
}
