#include <gtest.h>
#include "graph.h"

TEST(Graph, can_create_graph)
{
	ASSERT_NO_THROW(Graph A);
}

TEST(Graph, can_generate_graph)
{
	Graph A;
	ASSERT_NO_THROW(A.autoGenerateGraph(100, 1));
}

TEST(Graph, generated_graph_is_linked)
{
	Graph A;
	A.autoGenerateGraph(100, 1);
	EXPECT_EQ(true, A.check());
}

TEST(Graph, can_get_vertexs_number_of_graph)
{
	Graph A;
	A.autoGenerateGraph(100, 1);
	ASSERT_NO_THROW(A.vertSize());
}

TEST(Graph, vertexs_number_of_graph_true)
{
	Graph A;
	A.autoGenerateGraph(100, 0);
	EXPECT_EQ(100, A.vertSize());
}

TEST(Graph, can_get_edges_number_of_graph)
{
	Graph A;
	A.autoGenerateGraph(100, 1);
	ASSERT_NO_THROW(A.edgSize());
}

TEST(Graph, edges_number_of_graph_true)
{
	Graph A;
	A.autoGenerateGraph(100, 0);
	EXPECT_EQ(99, A.edgSize());
}

TEST(Graph, can_use_method_is_empty)
{
	Graph A;
	A.autoGenerateGraph(100, 1);
	ASSERT_NO_THROW(A.isEmpty());
}

TEST(Graph, method_is_empty_true)
{
	Graph A;
	EXPECT_EQ(true, A.isEmpty());
}

TEST(Graph, method_is_empty_false)
{
	Graph A;
	A.autoGenerateGraph(100, 0);
	EXPECT_EQ(false, A.isEmpty());
}