#include <sstream>
#include <gtest.h>
#include "graph.h"
#include "dheap.h"

TEST(Graph, can_create_graph)
{
	ASSERT_NO_THROW(Graph g = generateConnectedGraph(4, 6));
}

TEST(Graph, can_use_dijkstra)
{
	Graph g = generateConnectedGraph(4, 6);
	ASSERT_NO_THROW(g.dijkstra<DHeap>(2));
}