#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../src/graph.h"

int main(void)
{
	srand(time(NULL));
	const int size = 50;
	graph_t g = mkgraph(size);
	for (int i = 0; i < rand() % 10000; i++) {
		mkedge(g, rand() % size, rand() % size);
	}
	show_graph(g, D_MTRX | D_LIST);
	destroy_graph(g);
	return 0;
}
