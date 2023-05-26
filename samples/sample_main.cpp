#include"TDHeap.h"
#include"TRBtree.h"
#include"TBinomialHeap.h"
#include"Dijksta.h"

#include<locale>

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "|Тестирование алгоритма Дейкрстры, использующего разные структуры данных в качестве приоритетной очереди|" << endl
		<< "В данном приложении пользователь выбирает структуру данных для приоритетной очереди" << endl
		<< "Далее производится ввод или генерация случайного Графа" << endl
		<< "Поссле инициализации Графа пользователь указывает имя вершины, для которой будут найдены кратчайшие пути" << endl
		<< endl <<"Требования: \n1)Граф должен быть связным" << endl
		<< "2)Ввод графа с клавиатуры производится в следующем формате:" << endl
		<< "Последовательно вводятся имена вершин, а далее матрица смежности - поэлементно (по строкам)" << "\n\n";
	
	cout << "Выберите структуру данных для приоритетной очереди:" << endl
		<< "1 - d-heap, где в качестве d взята 3." << endl
		<< "2 - Биномиальная куча" << endl
		<< "3 - Красно чёрное дерево" << "\n\n";

	PriorityQueue<rec>* queue = nullptr;

	int choose = 0;
	bool cont = true;
	
	while (cont) 
	{
		cin >> choose;
		cont = false;
		switch (choose)
		{
		case 1:
			queue = new TDHeap<rec,3>;
			break;
		case 2:
			queue = new TBinomialHeap<rec>;
			break;
		case 3:
			queue = new TRBTree<rec>;
			break;
		default:
			cout << "Неверный ввод!" << endl;
			cont = true;
			break;
		}
	}

	int V = 0;
	do 
	{
		cout << "Введите размер Графа(число вершин)" << endl;
		cin >> V;
	} while (V < 2);

	Graph graph(V);

	cout << "Выберите способ задания Графа:" << endl
		<< "1 - сгенерировать автоматически" << endl
		<< "2 - ввести с клавиатуры" << endl;
	cin >> choose;
	switch (choose)
	{
	case 1:
		int E;
		cout << "Введите процент связности графа" << endl;
		cin >> E;
		graph.generateGraph(((V * (V - 1) / 2) * E) / 100);
		break;
	case 2:
		graph.setFKb();
		break;
	default:
		cout << "Неверный ввод!" << endl;
		break;
	}
	cout << "Матрица смежности для вашего Графа" << endl;
	cout << graph;
	cout << "\n\n" << "Введите имя вершины, пути для которой хотите найти:" << endl;
	string vName;
	cin >> vName;

	cout << "Таблица с путями до вершин:" << "\n\n";
	Dijkstra<size_t> dijkstra(graph, queue);
	try 
	{
		dijkstra.run(vName);
	}
	catch(exception& ex)
	{
		cout << ex.what() << endl;
		exit(-1);
	}
	dijkstra.showTable();

	while (true) 
	{
		cout << "Введите 1, чтобы узнать путь до вершины" << endl
			<< "Введите 2, чтобы закончить работу с графом" << endl;

		cin >> choose;
		string to;
		switch (choose)
		{
		case 1:
			cout << "Введите вершину, путь до которой хотите найти: ";
			cin >> to;
			cout << endl<<"Путь до вершины: " << endl << dijkstra.getWay(to) << "\n\n";
			break;
		case 2:
			exit(0);
			break;
		default:
			cout << "Неверный ввод!" << endl;
			break;
		}
	}
	delete queue;
}