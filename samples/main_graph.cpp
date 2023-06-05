#include <iostream>

#include "red_black_tree.h"
#include "d_heap.h"
#include "binomial_heap.h"
#include "Graph.h"

#define d 3 // the arity of the d-heap

using std::cout;
using std::endl;

template <typename type>
void input(type& buffer)
{
	std::cin >> buffer;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void do_actions(WeightedGraph& g, ShortestPaths& sp)
{
	enum actions {
		OUTPUT_GRAPH = 1,
		GET_SHORTEST_PATH,
		GET_TOTAL_COST,
		EXIT
	};
	int select = 0;
	while (true)
	{
		cout << "\nChoose an action: " << endl;
		cout << " 1 - Output a graph in the form of an adjacency matrix" << endl;
		cout << " 2 - Get shortest path to the vertex" << endl;
		cout << " 3 - Get total cost of the path to the vertex" << endl;
		cout << " 4 - Exit" << endl;
		cout << "Action: ";
		input(select);
		if (select == EXIT) return;

		switch (select)
		{
		case OUTPUT_GRAPH:
		{
			cout << endl;
			g.print();
			break;
		}
		case GET_SHORTEST_PATH:
		{
			int vertex;
			cout << "\nEnter the vertex: ";
			input(vertex);
			try
			{
				cout << "\nShortest path: ";
				cout << sp.get_shortest_path(vertex) << endl;
			}
			catch (const std::exception& except)
			{
				cout << "ERROR: " << except.what() << endl;
			}
			break;
		}
		case GET_TOTAL_COST:
		{
			int vertex;
			cout << "\nEnter the vertex: ";
			input(vertex);
			try
			{
				cout << "\nTotal cost: ";
				cout << sp.get_total_cost(vertex) << endl;
			}
			catch (const std::exception& except)
			{
				cout << "ERROR: " << except.what() << endl;
			}
			break;
		}
		default:
		{
			cout << "ERROR: Invalid number of action" << endl;
			return;
		}
		}
	}
}

int main()
{
	cout << "Dear user, for the correct operation of the program ";
	cout << "do NOT enter anything other than numbers!" << endl << endl;
	cout << "Rules for entering a graph: " << endl;
	cout << " 1 - The vertices of the graph are automatically numbered sequentially starting from zero" << endl;
	cout << " 2 - The number of vertices is greater than 1" << endl;
	cout << " 3 - Acceptable values of edge weight: (0;";
	cout << std::scientific << std::setprecision(0) << static_cast<double>(INF) << ")" << endl;
	cout << " 4 - The value of edge weight must be an integer" << endl;
	cout << " 5 - The graph must not contain loops so the starting vertex cannot be equal to the destination vertex" << endl;
	cout << " 6 - The graph must be connected" << endl;
	cout << " 7 - It is forbidden to re-enter the same edge" << endl;

	int vertices;
	int edges;

	cout << "\nThe number of vertices of the graph: ";
	input(vertices);
	if (vertices <= 1)
	{
		cout << "\nERROR: Invalid number of vertices";
		return 1;
	}
	cout << "\nAcceptable values of edges number: [" << vertices - 1 << ";" << vertices * (vertices - 1) / 2 << "]" << endl;
	cout << "\nThe number of edges of the graph: ";
	input(edges);
	if (edges < vertices - 1 || edges > vertices * (vertices - 1) / 2)
	{
		cout << "\nERROR: Invalid number of edges";
		return 1;
	}

	WeightedGraph G(vertices, edges);

	int select = 0;
	cout << "Methods of filling in the graph: " << endl;
	cout << " 1 - Manual filling" << endl;
	cout << " 2 - Random filling" << endl;
	cout << "Number: ";
	input(select);

	enum filling_methods {
		MANUAL = 1,
		RANDOM
	};
	switch (select)
	{
	case MANUAL:
	{
		cout << "\nAcceptable values of vertex numbers: [0;" << vertices << ")" << endl;
		for (int i = 0; i < edges; i++)
		{
			int enter_departure;
			int enter_destination;
			int enter_weight;
			cout << "\nEnter number of departure vertex: ";
			input(enter_departure);
			if (enter_departure < 0 || enter_departure >= vertices)
			{
				cout << "ERROR: Invalid vertex number" << endl;
				return 1;
			}
			cout << "\nEnter number of destination vertex: ";
			input(enter_destination);
			if (enter_destination < 0 || enter_destination >= vertices || enter_departure == enter_destination)
			{
				cout << "ERROR: Invalid vertex number" << endl;
				return 1;
			}
			cout << "\nEnter edge weight: ";
			input(enter_weight);

			try
			{
				G.add_edge(enter_departure, enter_destination, enter_weight);
			}
			catch (const std::exception& except)
			{
				cout << "ERROR: " << except.what() << endl;
				return 1;
			}
		}
		break;
	}
	case RANDOM:
	{
		G.random_fill();
		break;
	}
	default:
	{
		cout << "ERROR: Invalid number of filling method" << endl;
		return 1;
	}
	}

	enum priority_queue {
		SEARCH_TREE = 1,
		DHEAP,
		BINOMUAL_HEAP,
	};
	if (G.is_connected())
	{
		cout << "\nSUCCESS: The graph is connected" << endl;
		int start;
		cout << "\nEnter the starting vertex for Dijkstra's algorithm: ";
		input(start);

		if (start < 0 || start >= vertices)
		{
			cout << "ERROR: Invalid starting vertex" << endl;
			return 1;
		}

		cout << "\nChoose a priority queue for Dijkstra's algorithm" << endl;
		cout << " 1 - Binary Search Tree (Red-Black Tree)" << endl;
		cout << " 2 - D-Heap" << endl;
		cout << " 3 - Binomial Heap" << endl;
		cout << "Number: ";
		input(select);

		switch (select)
		{
		case SEARCH_TREE:
		{
			RedBlackTreeQueue<size_t, size_t> Q_tree;
			ShortestPaths SP(start, G, Q_tree);
			do_actions(G, SP);
			break;
		}
		case DHEAP:
		{
			DHeapQueue<d, size_t, size_t> Q_Dheap;
			ShortestPaths SP(start, G, Q_Dheap);
			do_actions(G, SP);
			break;
		}
		case BINOMUAL_HEAP:
		{
			BinomialHeapQueue<size_t, size_t> Q_binheap;
			ShortestPaths SP(start, G, Q_binheap);
			do_actions(G, SP);
			break;
		}
		default:
		{
			cout << "ERROR: Invalid priority queue number" << endl;
			return 1;
		}
		}
	}
	else
	{
		cout << "ERROR: Graph is not connected" << endl;
		return 1;
	}

	return 0;
}
