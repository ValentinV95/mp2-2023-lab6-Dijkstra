#include "Graph.h"

WeightedGraph::WeightedGraph(int V, int E) : vertices_num(V), edges_num(E), add_edges_count(0)
{
	if (vertices_num <= 0)
	{
		throw std::exception("Invalid number of vertex");
	}
	if (edges_num < vertices_num - 1 || edges_num > vertices_num * (vertices_num - 1) / 2)
	{
		throw std::exception("Invalid number of edges");
	}
	adjMatrix = vector<vector<size_t>>(vertices_num, vector<size_t>(vertices_num, INF));

	for (int i = 0; i < vertices_num; i++)
	{
		adjMatrix[i][i] = 0;
	}
}

const size_t WeightedGraph::get_weight(int departure, int destination) const
{
	if (destination < 0 || destination >= vertices_num || departure < 0 || departure >= vertices_num)
	{
		throw std::exception("Invalid vertex number");
	}
	return adjMatrix[departure][destination];
}

const size_t WeightedGraph::get_edges_num() const noexcept
{
	return edges_num;
}
const size_t WeightedGraph::get_vertices_num() const noexcept
{
	return vertices_num;
}

bool WeightedGraph::is_connected()
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

void WeightedGraph::add_edge(int departure, int destination, int weight)
{
	if (add_edges_count == edges_num)
	{
		throw std::exception("The graph is filled");
	}
	if (weight < 0 || weight >= INF)
	{
		throw std::exception("Invalid value of weight");
	}
	if (departure != destination && departure >=0 && departure < vertices_num && destination >=0 && destination < vertices_num)
	{
		if (adjMatrix[departure][destination] != INF)
		{
			throw std::exception("This edge already exists");
		}
		adjMatrix[departure][destination] = weight;
		adjMatrix[destination][departure] = weight;
		add_edges_count++;
	}
	else throw std::exception("Invalid number of vertices");
}
void WeightedGraph::random_fill()
{
	if (add_edges_count == edges_num)
	{
		throw std::exception("The graph is filled");
	}
	std::vector<size_t> arr;
	for (int i = 0; i < vertices_num; i++)
	{
		arr.push_back(i);
	}
	srand(static_cast<unsigned>(time(0)));
	std::random_shuffle(arr.begin(), arr.end());

	int count = 0;
	int root = 0;
	size_t rand_weight;
	for (int i = 1; i < vertices_num;)
	{
		if (count < 2)
		{
			rand_weight = rand() % 100;
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
		rand_weight = rand() % 100;
		if (rand_departure != rand_destination && adjMatrix[rand_departure][rand_destination] == INF)
		{
			adjMatrix[rand_departure][rand_destination] = rand_weight;
			adjMatrix[rand_destination][rand_departure] = rand_weight;
			edge_count++;
		}
	}
	add_edges_count = edges_num;
}

void WeightedGraph::print()
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

void ShortestPaths::Dijkstra_algorithm(PriorityQueue<size_t, size_t>& relaxation_queue)
{
	for (int n = 0; n < vertices_number; n++)
	{
		paths.push_back(Edge{ INF });
	}
	paths[start_vertex] = Edge{ 0, start_vertex };

	relaxation_queue.insert(0, start_vertex);

	while (!relaxation_queue.empty())
	{
		size_t current = relaxation_queue.get_min();
		relaxation_queue.extract_min();

		for (size_t i = 0; i < vertices_number; i++)
		{
			size_t current_weight = paths[current].weight + graph.get_weight(current, i);
			if (current != i && graph.get_weight(current, i) != INF && current_weight < paths[i].weight)
			{
				paths[i] = Edge{ current_weight, current };
				relaxation_queue.insert(current_weight, i);
			}
		}
	}
}

ShortestPaths::ShortestPaths(int S, const WeightedGraph& _graph, PriorityQueue<size_t, size_t>& _queue) : start_vertex(S), graph(_graph)
{
	if (start_vertex < 0 || start_vertex >= graph.get_vertices_num())
	{
		throw std::exception("Invalid number of start vertex");
	}
	vertices_number = graph.get_vertices_num();

	Dijkstra_algorithm(_queue);
}

std::string ShortestPaths::get_shortest_path(int destination_vertex)
{
	if (destination_vertex < 0 || destination_vertex >= vertices_number || destination_vertex == start_vertex)
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

const size_t ShortestPaths::get_total_cost(int destination_vertex) const
{
	if (destination_vertex < 0 || destination_vertex >= vertices_number || destination_vertex == start_vertex)
	{
		throw std::exception("Invalid destination vertex number");
	}
	return paths[destination_vertex].weight;
}
