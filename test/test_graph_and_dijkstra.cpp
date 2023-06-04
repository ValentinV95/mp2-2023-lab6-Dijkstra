#include "Graph.h"
#include "red_black_tree.h"
#include "d_heap.h"
#include "binomial_heap.h"

#include <gtest.h>

TEST(WeightedGraph, can_create_graph)
{
	ASSERT_NO_THROW(WeightedGraph G(3, 3));
}

TEST(WeightedGraph, throws_when_create_graph_with_invalid_parameters)
{
	ASSERT_ANY_THROW(WeightedGraph G(0, 3));
	ASSERT_ANY_THROW(WeightedGraph G(3, 0));
	ASSERT_ANY_THROW(WeightedGraph G(-1, 3));
	ASSERT_ANY_THROW(WeightedGraph G(3, -1));
	ASSERT_ANY_THROW(WeightedGraph G(3, 10));
	ASSERT_ANY_THROW(WeightedGraph G(3, 1));
}

TEST(WeightedGraph, can_get_edges_num)
{
	WeightedGraph G(3, 3);
	EXPECT_EQ(3, G.get_edges_num());
}

TEST(WeightedGraph, can_get_vertices_num)
{
	WeightedGraph G(3, 3);
	EXPECT_EQ(3, G.get_vertices_num());
}

TEST(WeightedGraph, can_fill_graph_randomly)
{
	WeightedGraph G(3, 3);
	ASSERT_NO_THROW(G.random_fill());
}

TEST(WeightedGraph, cant_refill_graph_randomly)
{
	WeightedGraph G(3, 3);
	G.random_fill();
	EXPECT_ANY_THROW(G.random_fill());
}

TEST(WeightedGraph, can_add_edge)
{
	WeightedGraph G(2, 1);
	int weight = 5;
	ASSERT_NO_THROW(G.add_edge(0, 1, weight));
}

TEST(WeightedGraph, cant_add_the_same_edge)
{
	WeightedGraph G(3, 2);
	int weight = 5;
	G.add_edge(0, 1, weight);
	EXPECT_ANY_THROW(G.add_edge(0, 1, weight));
}

TEST(WeightedGraph, cant_add_edge_with_invalid_parameters)
{
	WeightedGraph G(2, 1);
	int weight = 5;
	int wrong_weight_1 = -1;
	int wrong_weight_2 = INF;
	EXPECT_ANY_THROW(G.add_edge(2, 1, weight));
	EXPECT_ANY_THROW(G.add_edge(0, 2, weight));
	EXPECT_ANY_THROW(G.add_edge(-1, 1, weight));
	EXPECT_ANY_THROW(G.add_edge(0, -1, weight));
	EXPECT_ANY_THROW(G.add_edge(0, 1, wrong_weight_1));
	EXPECT_ANY_THROW(G.add_edge(0, 1, wrong_weight_2));
}

TEST(WeightedGraph, cant_add_too_many_edges)
{
	WeightedGraph G(3, 2);
	int weight = 5;
	G.add_edge(0, 1, weight);
	G.add_edge(0, 2, weight);
	EXPECT_ANY_THROW(G.add_edge(1, 2, weight));
}

TEST(WeightedGraph, can_get_weight)
{
	WeightedGraph G(2, 1);
	int weight = 5;
	G.add_edge(0, 1, weight);
	EXPECT_EQ(5, G.get_weight(0, 1));
}

TEST(WeightedGraph, cant_get_weight_with_invalid_parameters)
{
	WeightedGraph G(2, 1);
	int weight = 5;
	G.add_edge(0, 1, weight);
	EXPECT_ANY_THROW(G.get_weight(2, 1));
	EXPECT_ANY_THROW(G.get_weight(0, 2));
	EXPECT_ANY_THROW(G.get_weight(-1, 1));
	EXPECT_ANY_THROW(G.get_weight(0, -1));
}

TEST(WeightedGraph, can_check_connectivity)
{
	WeightedGraph G(2, 1);
	int weight = 5;
	G.add_edge(0, 1, weight);
	EXPECT_EQ(true, G.is_connected());

	WeightedGraph G1(3, 3);
	int weight1 = 5;
	G1.add_edge(0, 1, weight1);
	EXPECT_EQ(false, G1.is_connected());
}

TEST(ShortestPaths, can_run_dijkstra_algorithm)
{
	WeightedGraph G(2, 1);
	int weight = 5;
	G.add_edge(0, 1, weight);
	RedBlackTreeQueue<size_t, size_t> Q1;
	DHeapQueue<2, size_t, size_t> Q2;
	BinomialHeapQueue<size_t, size_t> Q3;

	ASSERT_NO_THROW(ShortestPaths SP1(0, G, Q1));
	ASSERT_NO_THROW(ShortestPaths SP2(0, G, Q2));
	ASSERT_NO_THROW(ShortestPaths SP3(0, G, Q3));
}

TEST(ShortestPaths, cant_run_dijkstra_algorithm_with_invalid_start_vertex)
{
	WeightedGraph G(2, 1);
	int weight = 5;
	G.add_edge(0, 1, weight);
	RedBlackTreeQueue<size_t, size_t> Q1;
	DHeapQueue<2, size_t, size_t> Q2;
	BinomialHeapQueue<size_t, size_t> Q3;

	EXPECT_ANY_THROW(ShortestPaths SP1(-1, G, Q1));
	EXPECT_ANY_THROW(ShortestPaths SP2(-1, G, Q2));
	EXPECT_ANY_THROW(ShortestPaths SP3(-1, G, Q3));
	EXPECT_ANY_THROW(ShortestPaths SP1(2, G, Q1));
	EXPECT_ANY_THROW(ShortestPaths SP2(2, G, Q2));
	EXPECT_ANY_THROW(ShortestPaths SP3(2, G, Q3));
}

TEST(ShortestPaths, can_get_shortest_path)
{
	WeightedGraph G(2, 1);
	RedBlackTreeQueue<size_t, size_t> Q1;
	DHeapQueue<2, size_t, size_t> Q2;
	BinomialHeapQueue<size_t, size_t> Q3;

	int weight = 5;
	G.add_edge(0, 1, weight);

	ShortestPaths SP1(0, G, Q1);
	ShortestPaths SP2(0, G, Q2);
	ShortestPaths SP3(0, G, Q3);

	std::string st = "0 -> 1";
	EXPECT_EQ(st, SP1.get_shortest_path(1));
	EXPECT_EQ(st, SP2.get_shortest_path(1));
	EXPECT_EQ(st, SP3.get_shortest_path(1));
}

TEST(ShortestPaths, cant_get_shortest_path_with_invalid_destination_vertex)
{
	WeightedGraph G(2, 1);
	RedBlackTreeQueue<size_t, size_t> Q1;
	DHeapQueue<2, size_t, size_t> Q2;
	BinomialHeapQueue<size_t, size_t> Q3;

	int weight = 5;
	G.add_edge(0, 1, weight);

	ShortestPaths SP1(0, G, Q1);
	ShortestPaths SP2(0, G, Q2);
	ShortestPaths SP3(0, G, Q3);

	EXPECT_ANY_THROW(SP1.get_shortest_path(-1));
	EXPECT_ANY_THROW(SP2.get_shortest_path(-1));
	EXPECT_ANY_THROW(SP3.get_shortest_path(-1));
	EXPECT_ANY_THROW(SP1.get_shortest_path(2));
	EXPECT_ANY_THROW(SP2.get_shortest_path(2));
	EXPECT_ANY_THROW(SP3.get_shortest_path(2));
	EXPECT_ANY_THROW(SP1.get_shortest_path(0));
	EXPECT_ANY_THROW(SP2.get_shortest_path(0));
	EXPECT_ANY_THROW(SP3.get_shortest_path(0));
}

TEST(ShortestPaths, can_get_total_cost)
{
	WeightedGraph G(2, 1);
	RedBlackTreeQueue<size_t, size_t> Q1;
	DHeapQueue<2, size_t, size_t> Q2;
	BinomialHeapQueue<size_t, size_t> Q3;

	int weight = 5;
	G.add_edge(0, 1, weight);

	ShortestPaths SP1(0, G, Q1);
	ShortestPaths SP2(0, G, Q2);
	ShortestPaths SP3(0, G, Q3);

	EXPECT_EQ(5, SP1.get_total_cost(1));
	EXPECT_EQ(5, SP2.get_total_cost(1));
	EXPECT_EQ(5, SP3.get_total_cost(1));
}


TEST(ShortestPaths, cant_get_total_cost_with_invalid_destination_vertex)
{
	WeightedGraph G(2, 1);
	RedBlackTreeQueue<size_t, size_t> Q1;
	DHeapQueue<2, size_t, size_t> Q2;
	BinomialHeapQueue<size_t, size_t> Q3;

	int weight = 5;
	G.add_edge(0, 1, weight);

	ShortestPaths SP1(0, G, Q1);
	ShortestPaths SP2(0, G, Q2);
	ShortestPaths SP3(0, G, Q3);

	EXPECT_ANY_THROW(SP1.get_total_cost(-1));
	EXPECT_ANY_THROW(SP2.get_total_cost(-1));
	EXPECT_ANY_THROW(SP3.get_total_cost(-1));
	EXPECT_ANY_THROW(SP1.get_total_cost(2));
	EXPECT_ANY_THROW(SP2.get_total_cost(2));
	EXPECT_ANY_THROW(SP3.get_total_cost(2));
	EXPECT_ANY_THROW(SP1.get_total_cost(0));
	EXPECT_ANY_THROW(SP2.get_total_cost(0));
	EXPECT_ANY_THROW(SP3.get_total_cost(0));
}
