#include "Graph.h"
#include "red_black_tree.h"
#include "d_heap.h"
#include "binomial_heap.h"
#include <gtest.h>

TEST(WeightedGraph, can_create_graph)
{
	ASSERT_NO_THROW(WeightedGraph<int> G(3, 3));
}

TEST(WeightedGraph, throw_when_create_graph_with_invalid_parameters)
{
	ASSERT_ANY_THROW(WeightedGraph<int> G(0, 3));
	ASSERT_ANY_THROW(WeightedGraph<int> G(3, 0));
	ASSERT_ANY_THROW(WeightedGraph<int> G(-1, 3));
	ASSERT_ANY_THROW(WeightedGraph<int> G(3, -1));
	ASSERT_ANY_THROW(WeightedGraph<int> G(3, 10));
	ASSERT_ANY_THROW(WeightedGraph<int> G(3, 1));
}

TEST(WeightedGraph, can_get_edges_num)
{
	WeightedGraph<int> G(3, 3);
	EXPECT_EQ(3, G.get_edges_num());
}

TEST(WeightedGraph, can_get_vertices_num)
{
	WeightedGraph<int> G(3, 3);
	EXPECT_EQ(3, G.get_vertices_num());
}

TEST(WeightedGraph, can_fill_graph_randomly)
{
	WeightedGraph<int> G(3, 3);
	ASSERT_NO_THROW(G.random_fill());
}

TEST(WeightedGraph, can_add_edge)
{
	WeightedGraph<int> G(2, 1);
	int weight = 5;
	ASSERT_NO_THROW(G.add_edge(0, 1, weight));
}

TEST(WeightedGraph, can_get_weight)
{
	WeightedGraph<int> G(2, 1);
	int weight = 5;
	G.add_edge(0, 1, weight);
	EXPECT_EQ(5, G.get_weight(0, 1));
}

TEST(WeightedGraph, can_check_connectivity)
{
	WeightedGraph<int> G(2, 1);
	int weight = 5;
	G.add_edge(0, 1, weight);
	EXPECT_EQ(true, G.is_connected());

	WeightedGraph<int> G1(3, 3);
	int weight1 = 5;
	G1.add_edge(0, 1, weight1);
	EXPECT_EQ(false, G1.is_connected());
}

TEST(ShortestPaths, can_run_dijkstra_algorithm)
{
	WeightedGraph<int> G(2, 1);
	int weight = 5;
	G.add_edge(0, 1, weight);
	RedBlackTreeQueue<int, size_t> Q1;
	DHeapQueue<2, int, size_t> Q2(5);
	BinomialHeapQueue<int, size_t> Q3;

	ASSERT_NO_THROW(ShortestPaths<int> SP1(0, G, Q1));
	ASSERT_NO_THROW(ShortestPaths<int> SP2(0, G, Q2));
	ASSERT_NO_THROW(ShortestPaths<int> SP3(0, G, Q3));
}

TEST(ShortestPaths, can_get_shortest_path)
{
	WeightedGraph<int> G(2, 1);
	RedBlackTreeQueue<int, size_t> Q1;
	DHeapQueue<2, int, size_t> Q2(5);
	BinomialHeapQueue<int, size_t> Q3;


	int weight = 5;
	G.add_edge(0, 1, weight);

	ShortestPaths<int> SP1(0, G, Q1);
	ShortestPaths<int> SP2(0, G, Q2);
	ShortestPaths<int> SP3(0, G, Q3);


	std::string st = "0 -> 1";
	EXPECT_EQ(st, SP1.get_shortest_path(1));
	EXPECT_EQ(st, SP2.get_shortest_path(1));
	EXPECT_EQ(st, SP3.get_shortest_path(1));
}

TEST(ShortestPaths, can_get_total_cost)
{
	WeightedGraph<int> G(2, 1);
	RedBlackTreeQueue<int, size_t> Q1;
	DHeapQueue<2, int, size_t> Q2(5);
	BinomialHeapQueue<int, size_t> Q3;

	int weight = 5;
	G.add_edge(0, 1, weight);

	ShortestPaths<int> SP1(0, G, Q1);
	ShortestPaths<int> SP2(0, G, Q2);
	ShortestPaths<int> SP3(0, G, Q3);

	

	EXPECT_EQ(5, SP1.get_total_cost(1));
	EXPECT_EQ(5, SP2.get_total_cost(1));
	EXPECT_EQ(5, SP3.get_total_cost(1));
}