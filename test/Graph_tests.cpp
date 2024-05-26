#include "gtest.h"
#include "Graph.h"
#include <string>

TEST(Graph, can_create_Graph) {
	ASSERT_NO_THROW(Graph G);
}

TEST(Graph, can_addV) {
	Graph G;
	ASSERT_NO_THROW(G.addV("A"));
}

TEST(Graph, can_addE) {
	Graph G;
	G.addV("A");
	G.addV("B");
	ASSERT_NO_THROW(G.addE("A", "B", 5));
}

TEST(Graph, throw_when_do_addE_to_non_existent_vertex) {
	Graph G;
	G.addV("A");
	G.addV("B");
	ASSERT_ANY_THROW(G.addE("A", "C", 5));
}

TEST(Graph, throw_when_create_loop) {
	Graph G;
	G.addV("A");
	ASSERT_ANY_THROW(G.addE("A", "A", 5));
}

TEST(Graph, can_delV) {
	Graph G;
	G.addV("A");
	ASSERT_NO_THROW(G.delV("A"));
}

TEST(Graph, dont_throw_when_do_delV_with_non_existent_name) {
	Graph G;
	G.addV("A");
	ASSERT_NO_THROW(G.delV("B"));
}


TEST(Graph, can_delE) {
	Graph G;
	G.addV("A");
	G.addV("B");
	G.addE("A", "B", 5);
	ASSERT_NO_THROW(G.delE("A", "B"));
}

TEST(Graph, dont_throw_when_do_delE_from_non_existent_edge) {
	Graph G;
	G.addV("A");
	G.addV("B");
	ASSERT_NO_THROW(G.delE("A", "B"));
}

TEST(Graph, dont_throw_when_do_delE_from_non_existent_vertex) {
	Graph G;
	G.addV("A");
	G.addV("B");
	G.addE("A", "B", 5);
	ASSERT_NO_THROW(G.delE("A", "C"));
}

TEST(Graph, can_clear) {
	Graph G;
	G.addV("A");
	ASSERT_NO_THROW(G.clear());
}

TEST(Graph, can_clear_empty_graph) {
	Graph G;
	ASSERT_NO_THROW(G.clear());
}

TEST(Graph, can_check_connected) {
	Graph G;
	ASSERT_NO_THROW(G.check_connected());
}

TEST(Graph, check_connected_is_correct) {
	Graph G;
	for (int i = 0; i < 3; i++) {
		G.addV(std::to_string(i));
	}
	EXPECT_FALSE(G.check_connected());
	G.addE("0", "1", 2);
	G.addE("2", "0", -3);
	EXPECT_TRUE(G.check_connected());
}

TEST(Graph, can_create_rnd_graph) {
	Graph G;
	ASSERT_NO_THROW(G.rnd(5, 60));
}

TEST(Graph, rnd_throws_when_countV_leass_than_zero) {
	Graph G;
	ASSERT_ANY_THROW(G.rnd(-5, 60));
}

TEST(Graph, rnd_throws_when_percentE_leass_than_zero_or_greater_than_100) {
	Graph G;
	ASSERT_ANY_THROW(G.rnd(5, -1));
	ASSERT_ANY_THROW(G.rnd(5, 101));
}

TEST(Graph, rnd_generates_connected_graph) {
	Graph G;
	G.rnd(10, 20);
	EXPECT_TRUE(G.check_connected());
}

TEST(Graph, rnd_throws_when_he_cant_generate_connected_graph) {
	Graph G;
	ASSERT_ANY_THROW(G.rnd(10, 19));
}

TEST(Graph, check_Dijkstra_is_correct) {
	Graph G;
	for (int i = 0; i < 3; i++) {
		G.addV(std::to_string(i));
	}
	G.addE("0", "1", 5);
	EXPECT_TRUE(G.check_Dijkstra());
	G.addE("0", "2", -5);
	EXPECT_FALSE(G.check_Dijkstra());
}

TEST(Graph, throw_when_used_path_from_graphs_that_wasnt_used_Dijkstra) {
	Graph G;
	G.rnd(10, 83);
	ASSERT_ANY_THROW(G.path("5"));
}

TEST(Graph, can_run_Dijkstra) {
	Graph G;
	for (int i = 0; i < 3; i++) {
		G.addV(std::to_string(i));
	}
	G.addE("0", "1", 3);
	ASSERT_NO_THROW(G.Dijkstra("0"));

}

TEST(Graph, throw_when_used_Dijkstra_at_grath_with_negative_vertices) {
	Graph G;
	for (int i = 0; i < 3; i++) {
		G.addV(std::to_string(i));
	}
	G.addE("0", "1", -3);
	ASSERT_ANY_THROW(G.Dijkstra("0"));
}

TEST(Graph, Dijkstra_founds_min_paths) {
	Graph G;
	for (int i = 0; i < 6; i++) {
		G.addV(std::to_string(i));
	}
	G.addE("0", "1", 101);
	G.addE("0", "2", 4);
	G.addE("0", "3", 5);
	G.addE("2", "4", 13);
	G.addE("2", "5", 10);
	G.addE("3", "4", 11);
	G.addE("4", "1", 6);
	G.addE("5", "1", 2);
	G.Dijkstra("0");
	EXPECT_EQ(G.path("0"), 0);
	EXPECT_EQ(G.path("1"), 16);
	EXPECT_EQ(G.path("2"), 4);
	EXPECT_EQ(G.path("3"), 5);
	EXPECT_EQ(G.path("4"), 16);
	EXPECT_EQ(G.path("5"), 14);
}

TEST(Graph, addV_invalidates_the_result_of_algorithm) {
	Graph G;
	for (int i = 0; i < 6; i++) {
		G.addV(std::to_string(i));
	}
	G.addE("0", "1", 101);
	G.addE("0", "2", 4);
	G.addE("0", "3", 5);
	G.addE("2", "4", 13);
	G.addE("2", "5", 10);
	G.addE("3", "4", 11);
	G.addE("4", "1", 6);
	G.addE("5", "1", 2);
	G.Dijkstra("0");
	G.addV("6");
	ASSERT_ANY_THROW(G.path("0"));
}

TEST(Graph, delV_invalidates_the_result_of_algorithm) {
	Graph G;
	for (int i = 0; i < 6; i++) {
		G.addV(std::to_string(i));
	}
	G.addE("0", "1", 101);
	G.addE("0", "2", 4);
	G.addE("0", "3", 5);
	G.addE("2", "4", 13);
	G.addE("2", "5", 10);
	G.addE("3", "4", 11);
	G.addE("4", "1", 6);
	G.addE("5", "1", 2);
	G.Dijkstra("0");
	G.delV("3");
	ASSERT_ANY_THROW(G.path("0"));
}

TEST(Graph, addE_invalidates_the_result_of_algorithm) {
	Graph G;
	for (int i = 0; i < 6; i++) {
		G.addV(std::to_string(i));
	}
	G.addE("0", "1", 101);
	G.addE("0", "2", 4);
	G.addE("0", "3", 5);
	G.addE("2", "4", 13);
	G.addE("2", "5", 10);
	G.addE("3", "4", 11);
	G.addE("4", "1", 6);
	G.addE("5", "1", 2);
	G.Dijkstra("0");
	G.addE("2", "3", 0.1);
	ASSERT_ANY_THROW(G.path("0"));
}

TEST(Graph, delE_invalidates_the_result_of_algorithm) {
	Graph G;
	for (int i = 0; i < 6; i++) {
		G.addV(std::to_string(i));
	}
	G.addE("0", "1", 101);
	G.addE("0", "2", 4);
	G.addE("0", "3", 5);
	G.addE("2", "4", 13);
	G.addE("2", "5", 10);
	G.addE("3", "4", 11);
	G.addE("4", "1", 6);
	G.addE("5", "1", 2);
	G.Dijkstra("0");
	G.delE("0", "1");
	ASSERT_ANY_THROW(G.path("0"));
}

TEST(Graph, rnd_invalidates_the_result_of_algorithm) {
	Graph G;
	for (int i = 0; i < 6; i++) {
		G.addV(std::to_string(i));
	}
	G.Dijkstra("0");
	G.rnd(5, 60);
	ASSERT_ANY_THROW(G.path("0"));
}

TEST(Graph, clear_invalidates_the_result_of_algorithm) {
	Graph G;
	for (int i = 0; i < 6; i++) {
		G.addV(std::to_string(i));
	}
	G.Dijkstra("0");
	G.clear();
	ASSERT_ANY_THROW(G.path("0"));
}