#include "TRbTree.hpp"
#include "IPriorityQueue.hpp"
#include "TDHeap.hpp"
#include "Deijkstra.cpp"

QueueType setQueueType()
{
	QueueType queueType;
	size_t choos;

	cout << "Enter queue type:" << endl;
	cout << "-- 0 for use D-Heap" << endl;
	cout << "-- 1 for use RB Tree" << endl;
	cout << "-- 2 for  use FibonacciHep" << endl;

	do {
		cin >> choos;
	} while (choos != 0 && choos != 1 && choos != 2);

	switch (choos)
	{
	case(0):
		queueType = DHeap;
		break;
	case(1):
		queueType = RBTree;
		break;
	case(2):
		queueType = FibonacciHep;
		break;
	}

	return queueType;
}

Graph createGraph()
{
	size_t vertexCount;
	bool choos;
	Graph graph;

	cout << "Choose a way to create the graph: random - 1 / enter by hands - 0" << endl;
	cin >> choos;

	if (choos)
	{
		random_device r;
		vertexCount = r() % 15 + 5;
		size_t maxVertexCount = (vertexCount * (vertexCount - 1) / 2);
		size_t edgeCount = (vertexCount - 1) + (maxVertexCount - r() % (maxVertexCount -2));

		graph = Graph(vertexCount, edgeCount);
		cout << graph;
	}
	else
	{
		cout << "Enter the vertex count: ";
		cin >> vertexCount;

		graph = Graph(vertexCount);

		bool stop = false;
		while (!stop)
		{
			stop = true;
			size_t v1, v2, cost;
			cout << "Enter first vertex name:" << endl;
			cin >> v1;
			cout << "Enter second vertex name:" << endl;
			cin >> v2;
			cout << "Enter way cost:" << endl;
			cin >> cost;

			graph.addEdge(v1, v2, cost);

			cout << "Enter 0 to continue or 1 to stop" << endl;
			cin >> stop;
		}
	}

	return graph;
}

void main()
{
	Graph g(5);
	
	g.addEdge(0,1,10);
	g.addEdge(0, 4, 100);
	g.addEdge(0, 3, 30);
	
	g.addEdge(1,2,50);

	g.addEdge(4, 2,10);
	g.addEdge(4, 3,60);

	g.addEdge(3,2,20);

	g.printTable();

	Dijkstra d(g,0,FibonacciHep);
	d.setStart(0);

	size_t vertexCount;
	size_t start;
	string choos = "reset";
	double fullnessPersent = 0.0;

	Graph graph; /*= createGraph()*/;
	QueueType queueType/* = setQueueType()*/;

	Dijkstra dijkstra(graph,0,queueType);

	while (choos != "end")
	{
		if (choos == "reset")
		{
			Graph graph = createGraph();
			cout << graph <<endl;

			QueueType queueType = setQueueType();
			size_t start = 0;
			cout << "Choose start: ";
			cin >> start;
		}
		else if (choos == "print")
		{
			cout << graph;
		}
		else if (choos == "way")
		{
			size_t v,wayCost = 0;
			cout << "Choose vertex: ";
			cin >> v;
			stack<GraphNode> way = dijkstra.getWay(v);


			while (!way.empty())
			{
				cout << way.top().current << " ";
				wayCost += way.top().weight;
				way.pop();
			}

			cout << " total cost: " << wayCost<<endl;
		}
		else if(choos == "start")
		{
			size_t v;
			cout << "Choose start: ";
			cin >> v;
			dijkstra.setStart(v);
		}
		else
		{
			cout << "Uncnown option" << endl;
		}

		cout << "Enter option: " << endl;
		cin >> choos;
	}
}