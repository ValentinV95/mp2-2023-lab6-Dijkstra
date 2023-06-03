#include <gtest.h>
#include "graph.h"
#include "dijkstra.h"

TEST(Dijkstra, can_create_dijkstra_obj)
{
	Graph g;
	g.autoGenerateGraph(3, 0);
	ASSERT_NO_THROW(Dijkstra A(g, 1, 1));
}

TEST(Dijkstra, cannot_create_dijkstra_obj_when_type_of_queue_wrong)
{
	Graph g;
	g.autoGenerateGraph(3, 0);
	ASSERT_ANY_THROW(Dijkstra A(g, 1, 0));
}

TEST(Dijkstra, cannot_create_dijkstra_obj_when_start_point_wrong)
{
	Graph g;
	g.autoGenerateGraph(3, 0);
	ASSERT_ANY_THROW(Dijkstra A(g, -1, 1));
}

TEST(Dijkstra, can_use_method_getCostMinWay)
{
	Graph g;
	g.autoGenerateGraph(3, 0);
	Dijkstra A(g, 1, 1);
	ASSERT_NO_THROW(A.getCostMinWay(2));
}

TEST(Dijkstra, cannot_use_method_getCostMinWay_when_end_point_wrong)
{
	Graph g;
	g.autoGenerateGraph(3, 0);
	Dijkstra A(g, 1, 1);
	ASSERT_ANY_THROW(A.getCostMinWay(4));
}

TEST(Dijkstra, can_use_method_getMinWay)
{
	Graph g;
	g.autoGenerateGraph(3, 0);
	Dijkstra A(g, 1, 1);
	ASSERT_NO_THROW(A.getMinWay(2));
}

TEST(Dijkstra, cannot_use_method_getMinWay_when_end_point_wrong)
{
	Graph g;
	g.autoGenerateGraph(3, 0);
	Dijkstra A(g, 1, 1);
	ASSERT_ANY_THROW(A.getMinWay(4));
}