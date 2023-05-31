#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <limits>
#include <queue>
#include "priorityqueue.hpp"

class Graph
{
private:
	int* matrix;                                 // Матрица смежности
	std::map<std::string, int> vertexNames;      // Названия вершин и их индексы
	std::vector<std::string> vectorNames;        // Индексы вершин и их названия
	std::vector<std::string> minPath;            // Минимальный путь до вершины
	int vertexs;                                 // Число вершин
	int edges;                                   // Число ребер

	std::string autoGenerateName(int n);         // Генерация имени для вершины

public:
	Graph();                                     // Конструктор по умолчанию
	~Graph();                                    // Деструктор
	int vertexsSize();                           // Количество вершин
	int edgesSize();                             // Количество ребер
	bool isEmpty();                              // Проверка на пустоту
	bool check();                                // Проверка на связность графа
	void autoGenerateGraph(int, int);            // Генерация графа
	void setGraph();                             // Ручной ввод графа
	void getAdjacencyMatrix();                   // Вывод на экран матрицу смежности
	std::map<std::string, int> Dijkstra(int type_of_storage_structure,
		             std::string startPoint);    // Алгоритм Дейкстры
	//bool ccheck();
};

std::string Graph::autoGenerateName(int n)
{
	std::string result = "";
	int betSymb = 'Z' - 'A' + 1;

	n += 1;

	while (n)
	{
		result = static_cast<char>('A' + n % betSymb - 1) + result;
		n /= betSymb;
	}

	return result;
}

Graph::Graph() : matrix(nullptr), vertexs(0), edges(0)
{

}

Graph::~Graph()
{
	delete[] matrix;
}

int Graph::vertexsSize()
{
	return vertexs;
}

int Graph::edgesSize()
{
	return edges;
}

bool Graph::isEmpty()
{
	return matrix == nullptr;
}

/*bool Graph::check()
{
	if (isEmpty()) return false;

	bool result = true;
	int* matrix1 = new int[vertexs * vertexs]();
	int* matrix2 = new int[vertexs * vertexs]();
	int* matrix3 = new int[vertexs * vertexs]();

	for (int i = 0; i < vertexs; i++)
	{
		for (int j = i; j < vertexs; j++)
		{
			if (matrix[i * vertexs + j])
			{
				matrix3[i * vertexs + j] = 1;
				matrix3[j * vertexs + i] = 1;
			}
		}
	}

	for (int t = 0; t < vertexs - static_cast<int>(log(vertexs)); t++) 
	{
		for (int i = 0; i < vertexs; i++)
		{
			for (int j = i; j < vertexs; j++)
			{
				if (matrix3[i * vertexs + j])
				{
					matrix1[i * vertexs + j] = 1;
					matrix1[j * vertexs + i] = 1;
					matrix2[i * vertexs + j] = 1;
					matrix2[j * vertexs + i] = 1;
				}
			}
		}

		for (int i = 0; i < vertexs; i++)
		{
			for (int j = 0; j < vertexs; j++)
			{
				matrix3[i * vertexs + j] = 0;

				for (int k = 0; k < vertexs; k++)
				{
					matrix3[i * vertexs + j] += matrix1[i * vertexs + k] * matrix2[k * vertexs + j];
				}
			}
		}
	}

	for (int i = 0; i < vertexs; i++)
	{
		for (int j = i + 1; j < vertexs; j++)
		{
			if (matrix3[i * vertexs + j] == 0)
			{
				result = false;
			}
		}
	}

	delete[] matrix1;
	delete[] matrix2;
	delete[] matrix3;

	return result;
}*/

bool Graph::check()
{
	if (isEmpty()) return false;

	std::vector<int> visVert;                       // Посещенные вершины
	std::queue<int> lnkVert;                        // Очередь посещения
	int row, col;                                   // Строки и столбцы

	lnkVert.push(0);
	visVert.push_back(0);

	while (!lnkVert.empty())
	{
		row = lnkVert.front();
		lnkVert.pop();

		for (col = row + 1; col < vertexs; col++)
		{
			if (matrix[row * vertexs + col] != 0 && 
				std::find(visVert.begin(), visVert.end(), col) == visVert.end())
			{
				visVert.push_back(col);
				lnkVert.push(col);
			}
		}
	}

	if (visVert.size() != vertexs) return false;

	return true;
}

void Graph::autoGenerateGraph(int n, int percent)
{
	if (!isEmpty())
	{
		delete[] matrix;
		matrix = nullptr;
		vertexs = 0;
		edges = 0;
	}

	vertexs = n;

	int maxEdges = n * (n - 1) / 2;
	int temp;

	matrix = new int[vertexs * vertexs]();

	for (int i = 0; i < vertexs; i++)
	{
		vertexNames.insert({ autoGenerateName(i), i });
		vectorNames.push_back(autoGenerateName(i));
	}

	for (int i = 0; i < vertexs - 1; i++)
	{
		temp = rand() % (vertexs * 100) + 1;
		matrix[i * vertexs + i + 1] = temp;
		matrix[(i + 1) * vertexs + i] = temp;
		edges++;
	}

	maxEdges -= edges;
	maxEdges = (maxEdges * percent) / 100;

	int count = 0, row = 0, col = 1;

	while (count < maxEdges)
	{
		if (row == vertexs - 1)
		{
			row = 0;
			col = 1;
		}
		if (col == vertexs)
		{
			row++;
			col = row + 1;
		}
		if (matrix[row * vertexs + col] == 0 && (rand() % 50 + 1) % 50 == 0)
		{
			temp = rand() % (vertexs * 100 + 1);
			matrix[row * vertexs + col] = temp;
			matrix[col * vertexs + row] = temp;
			count++;
			edges++;
		}

		col++;
	}
}

void Graph::setGraph()
{
	if (!isEmpty())
	{
		delete[] matrix;
		matrix = nullptr;
		vertexs = 0;
		edges = 0;
	}

	std::string name;
	std::cout << "Введите количество вершин в графе: ";
	std::cin >> vertexs;

	matrix = new int[vertexs * vertexs]();

	//for (int i = 0, j = 0; i < vertexs; i++, j++)
		//matrix[i * vertexs + j] = 1;

	for (int i = 0; i < vertexs; i++)
	{
		std::cout << (i + 1) << ") Введите название вершины: ";
		std::cin >> name;

		if (vertexNames.count(name))
		{
			std::cout << "__________________________________________" << std::endl;
			std::cout << "Данная вершина уже есть, повторите попытку" << std::endl;
			i--;
		}
		else
		{
			vectorNames.push_back(name);
			vertexNames.insert(std::pair<std::string, int>(name, i));
		}
	}

	int choice, loop, weight;
	enum { ENTER = 1, CONTINUE };

	for (int i = 0; i < vertexs; i++)
	{
		loop = 1;

		while (loop)
		{
			std::cout << "__________________________________________" << std::endl;
			std::cout << "Для ввода связной вершины к вершине " << vectorNames[i] << " введите 1" << std::endl;
			std::cout << "Для перехода к следующей вершине введите 2" << std::endl;
			std::cout << "Чтобы закончить вводить вершины нажмите любую другую клавишу" << std::endl;
			std::cout << "Ваш выбор: ";
			std::cin >> choice;

			switch (choice) {
			case ENTER:
			{
				std::cout << "__________________________________________" << std::endl;
				std::cout << "Введите связную вершину для вершины " << vectorNames[i];
				std::cout << ": ";
				std::cin >> name;
				if (!vertexNames.count(name))
				{
					std::cout << "__________________________________________" << std::endl;
					std::cout << "Введенная вершина не найдена. Повторите попытку." << std::endl;
				}
				else if (matrix[i * vertexs + vertexNames[name]] || i == vertexNames[name])
				{
					std::cout << "__________________________________________" << std::endl;
					std::cout << "Введенная вершина уже связана с данной. Повторите попытку." << std::endl;
				}
				else
				{
					std::cout << "Введите вес ребра между " << vectorNames[i];
					std::cout << " и " << name << ": ";
					std::cin >> weight;

					if (weight <= 0)
					{
						std::cout << "Вес ребра не может быть 0 или отрицательным числом. Повторите попытку." << std::endl;
					}
					else
					{
						matrix[i * vertexs + vertexNames[name]] = weight;
						matrix[vertexNames[name] * vertexs + i] = weight;
						edges++;
					}
				}

				break;
			}

			case CONTINUE:
			{
				loop = 0;
				break;
			}

			default:
			{
				if (!this->check())
				{
					std::cout << "__________________________________________" << std::endl;
					std::cout << "Граф не связный. Добавьте новые связи в графе." << std::endl;
					i = 0;
				}
				else
				{
					std::cout << "__________________________________________" << std::endl;
					return;
				}
			}}
		}
	}
}

void Graph::getAdjacencyMatrix()
{
	std::cout << "  ";

	for (int i = 0; i < vertexs; i++)
		std::cout << vectorNames[i] << " ";

	std::cout << std::endl;

	for (int i = 0; i < vertexs; i++)
	{
		std::cout << vectorNames[i] << " ";

		for (int j = 0; j < vertexs; j++)
		{
			std::cout << matrix[i * vertexs + j] << " ";
		}

		std::cout << std::endl;
	}
}

std::map<std::string, int> Graph::Dijkstra(int type_of_storage_structure, std::string startPoint)
{
	if (!vertexNames[startPoint]) throw std::runtime_error("Vertex wasn't found");

	int result;
	int row;
	PriorityQueue<std::pair<std::string, int>> queue;
	std::map<std::string, bool> visitedVertexs;
	std::pair<std::string, int> cur;
	std::map<std::string, int> costWay;

	queue.push({ startPoint, 0 });

	for (int i = 0; i < vertexs; i++)
	{
		costWay.insert({ vectorNames[i], 0});
	}

	while (!queue.isEmpty(type_of_storage_structure))
	{
		cur = *queue.front(type_of_storage_structure);
		queue.pop();
		visitedVertexs.insert({ std::get<0>(cur), true });

		row = vertexNames[startPoint];

		for (int i = 0; i < vertexs; i++)
		{
			if (matrix[row * vertexs + i])
			{
				if (visitedVertexs[vectorNames[i]])
				{
					if (costWay[vectorNames[i]] > (matrix[row * vertexs + i] + std::get<1>(cur)))
					{
						costWay[vectorNames[i]] = matrix[row * vertexs + i] + std::get<1>(cur);
					}
				}
				else
				{
					queue.push({ vectorNames[i], matrix[row * vertexs + i] });
				}
			}
		}
	}

	return costWay;
}

void getMinPath(std::string startPoint)
{

}