#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "../src/graph.h"

int main(void)
{
	srand(time(NULL));
	const int size = 50;
	graph_t g = mkgraph(size);
	mkedge(g, 10, 20);
	mkedge(g, 10, 21);
	mkedge(g, 10, 22);
	mkedge(g, 1, 10);
	mkedge(g, 2, 10);
	mkedge(g, 3, 10);
	mkedge(g, 4, 10);
	mkedge(g, 5, 10);
	printf("outdegree %d\n", outdegree(g, 10));
	printf("indegree %d\n", indegree(g, 10));
	destroy_graph(g);
	return 0;
}
