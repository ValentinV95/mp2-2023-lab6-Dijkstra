#include <iostream>
#include <conio.h>

#include "rbtree.h"
#include "dheap.h"
#include "bheap.h"
#include "graph.h"

#define d 3 // арность d-кучи

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
		cout << "\nВыберите действие: " << endl;
		cout << " 1 - Вывести граф в виде матрицы смежности" << endl;
		cout << " 2 - Получить кратчайший путь к вершине" << endl;
		cout << " 3 - Получить общую стоимость пути до вершины" << endl;
		cout << " 4 - Выход" << endl;
		cout << "Действие: ";
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
			cout << "\nВведите вершину: ";
			input(vertex);
			try
			{
				cout << "\nКротчайший путь: ";
				cout << sp.get_shortest_path(vertex) << endl;
			}
			catch (const std::exception& except)
			{
				cout << "ОШИБКА: " << except.what() << endl;
			}
			break;
		}
		case GET_TOTAL_COST:
		{
			int vertex;
			cout << "\nВведите вершину: ";
			input(vertex);
			try
			{
				cout << "\nОбщее количество: ";
				cout << sp.get_total_cost(vertex) << endl;
			}
			catch (const std::exception& except)
			{
				cout << "ОШИБКА: " << except.what() << endl;
			}
			break;
		}
		default:
		{
			cout << "ОШИБКА: Введено неправильно число или индекс" << endl;
			return;
		}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int vertices;
	int edges;

	cout << "\nКоличество вершин графа: ";
	input(vertices);
	if (vertices <= 0)
	{
		cout << "\nОШИБКА: Недопустимое количество вершин";
		return 1;
	}
	cout << "\nКоличество ребер графа: ";
	input(edges);
	if (edges < vertices - 1 || edges > vertices * (vertices - 1) / 2)
	{
		cout << "\nОШИБКА: Недопустимое количество ребер";
		return 1;
	}

	WeightedGraph G(vertices, edges);

	int select = 0;
	cout << "Выберите способ заполнения графа: " << endl;
	cout << " 1 - Ручной ввод" << endl;
	cout << " 2 - Случайный ввод" << endl;
	cout << "Номер: ";
	input(select);

	if (select == 1) // ручной ввод
	{
		cout << "\nДопустимые значения номеров вершин: [0;" << vertices << ")" << endl;
		for (int i = 0; i < edges; i++)
		{
			int enter_departure;
			int enter_destination;
			int enter_weight;
			cout << "\nВведите номер вершины начала: ";
			input(enter_departure);
			if (enter_departure < 0 || enter_departure >= vertices)
			{
				cout << "Ошибка: " << "Неправильный номер вершины" << endl;
				return 1;
			}
			cout << "\nВведите номер конечной вершины: ";
			input(enter_destination);
			if (enter_destination < 0 || enter_destination >= vertices)
			{
				cout << "ОШИБКА: " << "Недопустимый номер вершины" << endl;
				return 1;
			}
			cout << "\nВведите ширину: ";
			input(enter_weight);

			try
			{
				G.add_edge(enter_departure, enter_destination, enter_weight);
			}
			catch (const std::exception& except)
			{
				cout << "ОШИБКА: " << except.what() << endl;
				return 1;
			}
		}
	}
	else if (select == 2) // random filling
	{
		G.random_fill();
	}
	else
	{
		cout << "ОШИБКА: Неверный номер метода заполнения" << endl;
		return 1;
	}

	enum priority_queue {
		SEARCH_TREE = 1,
		DHEAP,
		BINOMUAL_HEAP,
	};
	if (G.is_connected())
	{
		cout << "\nГраф связан!" << endl;
		int start;
		cout << "\nВведите начальную вершину для алгоритма Дейкстры: ";
		input(start);

		if (start < 0 || start >= vertices)
		{
			cout << "ОШИБКА: Недопустимая начальная вершина" << endl;
			return 1;
		}

		cout << "\nВыберите приоритетную очередь для алгоритма Дейкстры" << endl;
		cout << " 1 - Двоичное дерево поиска (Красно-Черное дерево)" << endl;
		cout << " 2 - Двойная куча" << endl;
		cout << " 3 - Биномиальная куча" << endl;
		cout << "Номер: ";
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
			DHeapQueue<d, size_t, size_t> Q_Dheap(vertices * edges);
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
			cout << "ОШИБКА: недопустимый номер приоритетной очереди" << endl;
			return 1;
		}
		}
	}
	else
	{
		cout << "ОШИБКА: Граф не соединен" << endl;
		return 1;
	}
	_getch();
	return 0;
}