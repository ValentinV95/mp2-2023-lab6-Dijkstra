#include "Dijkstra.hpp"

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
		size_t maxEdgeCount;
		size_t edgeCount;

		cout << "Enter vertex count: " ;
		cin >> vertexCount;
		cout << "Enter edge count: ";
		cin >> edgeCount;

		graph = Graph(vertexCount, edgeCount);
		graph.printTable();
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
	size_t vertexCount;
	size_t start = 0;
	string choos = "start";
	double fullnessPersent = 0.0;

	setlocale(LC_ALL, "Russian");

	cout << "--------------------------INFO--------------------------" << endl;
	cout << "\tГраф:" << endl  
		<< "\t--Для алгоритма Дейкстры необходим связный граф с неотрицательными весами ребер" << endl
		<< "\t--Вершины графа именуются числами от нуля до число вершин минус один" << endl
		<< "\t--В матрице смежности отображается стоимость пути из одной вершины в другую," << endl
		<< "\tесли пути нет выводится буква n" << endl
		<<"\t--Введенные отрицательные веса ребер и имена вершин буду восприниматься как " << endl
		<< "\tочень большое целое положительное число"<< endl
		<< endl;
	cout << "\tОперации:" << endl
		<< "\t--Задать начальную току -- введите start" << endl
		<< "\t--Напечатать матрицу межности графа -- введите print" << endl
		<< "\t--Найти гратчайший путь из начальной точки в заданнуюю -- введите way" << endl;
	cout << "--------------------------------------------------------" << endl;

	Graph graph = createGraph();
	QueueType queueType = setQueueType();

	Dijkstra dijkstra(graph,start,queueType);

	while (choos != "end")
	{
		try
		{
			if (choos == "print")
			{
				graph.printTable();
			}
			else if (choos == "way")
			{
				size_t v, wayCost = 0;

				cout << "Choose vertex: ";
				cin >> v;

				stack<GraphNode> way = dijkstra.getWay(v);

				while (!way.empty())
				{
					cout << way.top().current << " ";
					wayCost = way.top().weight;
					way.pop();
				}

				if(start != v)
					cout << " total cost: " << wayCost << endl;
				else
					cout << v << v << " total cost: " << 0 << endl;
			}
			else if (choos == "start")
			{
				size_t v;
				cout << "Choose start: ";
				cin >> v;

				dijkstra.setStart(v);
				start = v;
			}
			else
			{
				cout << "Uncnown option" << endl;
			}

			cout << "Enter option: " << endl;
			cin >> choos;
		}
		catch (exception& exc)
		{
			cout << exc.what() << std::endl;
		}
	}
}