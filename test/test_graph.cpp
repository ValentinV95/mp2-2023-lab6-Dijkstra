#include "graph.h"
#include "gtest.h"

TEST(graph, can_create_graph)
{
	ASSERT_NO_THROW(Graph gr);
	Graph gr1;
	ASSERT_NO_THROW(Graph gr(gr1));
}

TEST(graph, throw_when_create_graph_incorrect_size)
{
	ASSERT_ANY_THROW(Graph gr(0));
	ASSERT_ANY_THROW(Graph gr(-1));
}


TEST(graph, can_add_edge)
{
	Graph gr(4);
	ASSERT_NO_THROW(gr.addEdge('a', 'b', 3));
	ASSERT_NO_THROW(gr.addEdge(1, 3, 4));
}

TEST(graph, throw_when_add_incorrect_edge)
{
	Graph gr(4);
	ASSERT_ANY_THROW(gr.addEdge('a', 'g', 3));
	ASSERT_ANY_THROW(gr.addEdge('a', 'a', 4));
	ASSERT_ANY_THROW(gr.addEdge(0, 10, 3));
	ASSERT_ANY_THROW(gr.addEdge(1, 1, 4));
}


TEST(graph, can_check_graph_connected)
{
	Graph gr(3);
	gr.addEdge('a', 'b', 3);
	gr.addEdge('b', 'c', 3);
	ASSERT_EQ(gr.isConnected(), false);
	gr.addEdge('c', 'a', 3);
	ASSERT_EQ(gr.isConnected(), true);
}

TEST(graph, can_generate_connected_graph)
{
	Graph gr1(3);
	gr1.generateRandom();
	ASSERT_EQ(gr1.isConnected(), true);

	Graph gr(3);
	gr.addEdge('a', 'b', 3);
	gr.addEdge('b', 'c', 3);
	ASSERT_EQ(gr.isConnected(), false);
	gr.addConnected(true);
	ASSERT_EQ(gr.isConnected(), true);
}


TEST(Dijkstra, can_create_graph)
{
	ASSERT_NO_THROW(Dijkstra gr);
}


TEST(Dijkstra, can_find_min_way)
{
	Dijkstra gr(3);
	gr.addEdge('a', 'b', 1);
	gr.addEdge('b', 'c', 2);
	gr.addEdge('c', 'a', 3);
	gr.setStartVert('a');
	ASSERT_NO_THROW(gr.getMinWay('c'));
	ASSERT_EQ(gr.getMinWay('c'), "a->b->c");
	ASSERT_EQ(gr.wayLen('c'), 3);
}

TEST(Dijkstra, throw_when_no_way)
{
	Dijkstra gr(3);
	gr.addEdge('a', 'b', 1);
	gr.addEdge('b', 'c', 2);
	gr.setStartVert('c');
	ASSERT_ANY_THROW(gr.getMinWay('a'));
	ASSERT_ANY_THROW(gr.wayLen('a'));
}