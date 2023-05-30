#include <priority_queue.h>
#include <red_black_tree.h>
#include <d_heap.h>
#include <binomial_heap.h>
#include <Graph.h>

#define d 3

using std::cout;
using std::endl;
using std::cin;

void do_actions(WeightedGraph<int>& g, ShortestPaths<int>& sp)
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
		cin >> select;
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
			cin >> vertex;
			try
			{
				cout << "\nShortest path: ";
				cout << sp.get_shortest_path(vertex) << endl;
			}
			catch (const std::exception& except)
			{
				cout << except.what() << endl;
			}
			break;
		}
		case GET_TOTAL_COST:
		{
			int vertex;
			cout << "\nEnter the vertex: ";
			cin >> vertex;
			try
			{
				cout << "\nTotal cost: ";
				cout << sp.get_total_cost(vertex) << endl;
			}
			catch (const std::exception& except)
			{
				cout << except.what() << endl;
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
	cout << "Rules for entering a graph: " << endl;
	cout << " 1 - The vertices of the graph are automatically numbered sequentially starting from zero" << endl;
	cout << " 2 - The number of vertices and edges is greater than zero" << endl;
	cout << " 3 - The weight of each edge must be at least zero" << endl;
	cout << " 4 - The graph must not contain loops" << endl;
	cout << " 5 - The graph must be connected, that is, each vertex must be connected to at least one other vertex" << endl;
	cout << " 6 - It is forbidden to re-enter the same edge" << endl;

	int vertices;
	int edges;

	cout << "\nThe number of vertices of the graph: ";
	cin >> vertices;
	if (vertices <= 0)
	{
		cout << "\nERROR: Invalid number of vertices";
	}
	cout << "\nThe number of edges of the graph: ";
	cin >> edges;
	if (edges < vertices - 1 || edges > vertices * (vertices - 1) / 2)
	{
		cout << "\nERROR: Invalid number of edges";
	}

	WeightedGraph<int> G(vertices, edges);

	int select = 0;
	cout << "Methods of filling in the graph: " << endl;
	cout << " 1 - Manual filling" << endl;
	cout << " 2 - Random filling" << endl;
	cout << "Number: ";
	cin >> select;

	if (select == 1)
	{
		for (int i = 0; i < edges; i++)
		{
			size_t enter_departure;
			size_t enter_destination;
			int enter_weight;
			std::cout << "\nEnter number of departure vertex: ";
			std::cin >> enter_departure;
			std::cout << "\nEnter number of destination vertex: ";
			std::cin >> enter_destination;
			std::cout << "\nEnter edge weight: ";
			std::cin >> enter_weight;

			try
			{
				G.add_edge(enter_departure, enter_destination, enter_weight);
			}
			catch(const std::exception& except)
			{
				cout << except.what() << endl;
				return 1;
			}
		}
	}
	else if (select == 2)
	{
		G.random_fill();
	}
	else
	{
		cout << "ERROR: Invalid number of filling method" << endl;
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
		cin >> start;

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
		cin >> select;

		switch (select)
		{
		case SEARCH_TREE:
		{
			RedBlackTreeQueue<int, size_t> Q_tree;
			ShortestPaths<int> SP(start, G, Q_tree);
			do_actions(G, SP);
			break;
		}
		case DHEAP:
		{
			DHeapQueue<d, int, size_t> Q_Dheap(vertices * edges);
			ShortestPaths<int> SP(start, G, Q_Dheap);
			do_actions(G, SP);
			break;
		}
		case BINOMUAL_HEAP:
		{
			BinomialHeapQueue<int, size_t> Q_binheap;
			ShortestPaths<int> SP(start, G, Q_binheap);
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
		cout << "ERROR: Graph is not connection" << endl;
		return 1;
	}

	return 0;
}