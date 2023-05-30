#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <vector>
#include <string>

#include "red_black_tree.h"
#include "d_heap.h"
#include "binomial_heap.h"

using std::vector;

template <typename T>
class WeightedGraph
{
private:
	const T INF = std::numeric_limits<T>::max();
	vector<vector<T>> adjMatrix;
	size_t vertices_num;
	size_t edges_num;
public:
	WeightedGraph() {}
	WeightedGraph(size_t V, size_t E) : vertices_num(V), edges_num(E)
	{
		if (vertices_num <= 0)
		{
			throw std::exception("Invalid number of vertex");
		}
		if (edges_num < vertices_num - 1 || edges_num > vertices_num * (vertices_num - 1) / 2)
		{
			throw std::exception("Invalid number of edges");
		}
		adjMatrix = vector<vector<T>>(vertices_num, vector<T>(vertices_num, INF));
		
		for (int i = 0; i < vertices_num; i++)
		{
			adjMatrix[i][i] = static_cast<T>(0);
		}
	}

	T& get_weight(size_t departure, size_t destination)
	{
		if (destination < 0 || destination >= vertices_num || departure < 0 || departure >= vertices_num)
		{
			throw std::exception("Invalid vertex number");
		}
		return adjMatrix[departure][destination];
	}
	size_t& get_edges_num()
	{
		return edges_num;
	}
	size_t& get_vertices_num()
	{
		return vertices_num;
	}

	bool is_connected()
	{
		for (int i = 0; i < vertices_num; i++)
		{
			int existing_connection_count = 0;
			for (int j = 0; j < vertices_num; j++)
			{
				if (i != j && adjMatrix[i][j] != INF)
				{
					existing_connection_count++;
					break;
				}
			}
			if (existing_connection_count == 0)
			{
				return false;
			}
		}
		return true;
	}

	void add_edge(size_t departure, size_t destination, T& weight)
	{
		if (departure != destination && departure < vertices_num && destination < vertices_num && weight >= 0)
		{
			if (adjMatrix[departure][destination] != INF)
			{
				throw std::exception("This edge already exists");
			}
			adjMatrix[departure][destination] = weight;
			adjMatrix[destination][departure] = weight;
		}
		else throw std::exception("Invalid input");
	}

	void random_fill()
	{
		std::vector<size_t> arr;
		for (int i = 0; i < vertices_num; i++)
		{
			arr.push_back(i);
		}
		srand(static_cast<unsigned>(time(0)));
		std::random_shuffle(arr.begin(), arr.end());

		int count = 0;
		int root = 0;
		T rand_weight;
		for (int i = 1; i < vertices_num;)
		{
			if (count < 2)
			{
				rand_weight = static_cast<T>(rand() % 100);
				adjMatrix[arr[root]][arr[i]] = rand_weight;
				adjMatrix[arr[i]][arr[root]] = rand_weight;
				count++;
				i++;
			}
			else
			{
				root++;
				count = 0;
			}
		}
		int edge_count = vertices_num - 1;
		int rand_departure;
		int rand_destination;
		while (edge_count < edges_num)
		{
			rand_departure = rand() % vertices_num;
			rand_destination = rand() % vertices_num;
			rand_weight = static_cast<T>(rand() % 100);
			if (rand_departure != rand_destination && adjMatrix[rand_departure][rand_destination] == INF)
			{
				adjMatrix[rand_departure][rand_destination] = rand_weight;
				adjMatrix[rand_destination][rand_departure] = rand_weight;
				edge_count++;
			}
		}
	}

	void print()
	{
		std::cout << "     ";
		for (int n = 0; n < vertices_num; n++)
		{
			std::cout << std::setw(2) << n << "  ";
		}
		std::cout << std::endl << std::endl;
		for (int i = 0; i < vertices_num; i++)
		{
			std::cout << std::setw(2) << i << "|  ";
			for (int j = 0; j < vertices_num; j++)
			{
				if (adjMatrix[i][j] != INF)
				{
					std::cout << std::setw(2) << adjMatrix[i][j] << "  ";
				}
				else std::cout << std::setw(2) << "--" << "  ";
			}
			std::cout << std::endl << std::endl;
		}
	}
};


template<typename T>
class ShortestPaths
{
private:
	const T INF = std::numeric_limits<T>::max();
	struct Edge
	{
		bool relaxed;
		T weight;
		size_t departure;
		size_t destination;
	};
	WeightedGraph<T> graph;
	vector<Edge> paths;
	size_t start_vertex;
	size_t vertices_number;

	void Dijkstra_algorithm(WeightedGraph<T>& graph, PriorityQueue<T, size_t>& relaxation_queue)
	{
		for (int n = 0; n < vertices_number; n++)
		{
			paths.push_back(Edge{ false, INF });
		}
		
		paths[start_vertex] = Edge{ false, static_cast<T>(0), start_vertex, start_vertex };

		relaxation_queue.insert(paths[start_vertex].weight, paths[start_vertex].destination);

		int relaxation_counter = 0;
		while (!relaxation_queue.empty() && relaxation_counter < vertices_number)
		{
			size_t current = relaxation_queue.extract_min();

			paths[current].relaxed = true;
			relaxation_counter++;

			for (size_t i = 0; i < vertices_number; i++)
			{
				if (current != i && graph.get_weight(current, i) != INF && paths[i].relaxed == false && paths[current].weight + graph.get_weight(current, i) < paths[i].weight)
				{
					T current_weight = paths[current].weight + graph.get_weight(current, i);
					paths[i] = Edge{ false, current_weight, current, i };
					relaxation_queue.insert(current_weight, i);
				}
			}
		}
	}
public:
	ShortestPaths(size_t S, WeightedGraph<T>& _graph, PriorityQueue<T, size_t>& _queue) : start_vertex(S)
	{
		if (start_vertex < 0 || start_vertex > _graph.get_edges_num())
		{
			throw std::exception("Invalid number of start vertex");
		}
		vertices_number = _graph.get_vertices_num();

		Dijkstra_algorithm(_graph, _queue);
	}

	std::string get_shortest_path(size_t destination_vertex)
	{
		if (destination_vertex < 0 || destination_vertex >= vertices_number)
		{
			throw std::exception("Invalid destination vertex number");
		}
		vector<std::string> reverse_path;
		reverse_path.push_back(std::to_string(destination_vertex));

		size_t current = paths[destination_vertex].departure;
		reverse_path.push_back(std::to_string(current));
		while (current != start_vertex)
		{
			current = paths[current].departure;
			reverse_path.push_back(std::to_string(current));
		}
		
		std::string path = reverse_path.back();
		
		reverse_path.pop_back();
		while (!reverse_path.empty())
		{
			path += " -> ";
			path += reverse_path.back();
			reverse_path.pop_back();
		}
		return path;
	}

	T& get_total_cost(size_t destination_vertex)
	{
		if (destination_vertex < 0 || destination_vertex >= vertices_number)
		{
			throw std::exception("Invalid destination vertex number");
		}
		return paths[destination_vertex].weight;
	}
};
