#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <vector>
#include <string>

#include "priority_queue.h"

using std::vector;

/// a value indicating the absence of a connection between specific vertices
const size_t INF = 1e9;  

class WeightedGraph
{
private:
	vector<vector<size_t>> adjMatrix;  // adjacency matrix for storing weights of graph edges
	size_t vertices_num;               // number of vertices
	size_t edges_num;                  // number of edges
	size_t add_edges_count;            // counter of added edges to regulate graph filling
public:
	/// <param name="V"> number of vertices </param>
	/// <param name="E"> number of edges </param>
	WeightedGraph(int V, int E);

	/// <!--getters-->
	const size_t get_weight(int departure, int destination) const;
	const size_t get_edges_num() const noexcept;
	const size_t get_vertices_num() const noexcept;

	bool is_connected();  // checking the graph for connectivity

	/// adding a new edge when manually filling in a weighted graph
	void add_edge(int departure, int destination, int weight);

	/// random filling of the graph (does not allow re-filling)
	void random_fill();  

	/// output of a weighted graph in the form of an adjacency matrix
	void print();  
};


class ShortestPaths
{
private:
	struct Edge  
	{
		size_t weight;       // weight of the edge (segment of the path)
		size_t departure;    // the vertex of departure to the i-th vertex
	};
	WeightedGraph graph;     // the graph on which the shortest paths are searched
	vector<Edge> paths;      // container for storing information about paths and their costs
	size_t start_vertex;     // the starting vertex for Dijkstra's algorithm
	size_t vertices_number;  // number of vertices

	/// shortest paths search algorithm
	void Dijkstra_algorithm(PriorityQueue<size_t, size_t>& relaxation_queue); 
public:
	/// <param name="S"> the starting vertex for Dijkstra's algorithm </param>
	/// <param name="_graph"> the graph on which the shortest paths are searched </param>
	/// <param name="_queue"> one of the priority queue implementations for Dijkstra's algorithm </param>
	ShortestPaths(int S, const WeightedGraph& _graph, PriorityQueue<size_t, size_t>& _queue);

	/// <!--getters-->
	std::string get_shortest_path(int destination_vertex);
	const size_t get_total_cost(int destination_vertex) const;
};
