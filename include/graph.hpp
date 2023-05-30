#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <cmath>
#include <limits>

class Graph
{
private:
	int* matrix;                                 // Матрица смежности
	std::map<std::string, int> vertexNames;      // Названия вершин и их индексы
	std::vector<std::string> vectorNames;        // Индексы вершин и их названия
	int vertexs;
	int edges;

	std::string autoGenerateName(int n);

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
	std::vector<std::string> Dijkstra(std::string); // Алгоритм Дейкстры

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

bool Graph::check()
{
	if (isEmpty()) return false;

	bool result = true;
	int* temp = new int[vertexs * vertexs]();
	int* temp1 = new int[vertexs * vertexs]();

	for (int i = 0; i < vertexs; i++)
		for (int j = 0; j < vertexs; j++)
			temp[i * vertexs + j] = matrix[i * vertexs + j];

	//for (int t = 0; t < vertexs)
	for (int i = 0; i < vertexs; i++)
		for (int k = 0; k < vertexs; k++)
			for (int j = 0; j < vertexs; j++)
				temp1[i * vertexs + j] += matrix[i * vertexs + k] * temp[k * vertexs + j];

	for (int i = 0; i < vertexs; i++)
		for (int j = i + 1; j < vertexs; j++)
			if (temp1[i * vertexs + j] == 0)
				result = false;

	delete[] temp;
	delete[] temp1;

	return result;
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

	int maxElement = n * n * percent / 100;
	int temp;
	bool flag = true;

	matrix = new int[vertexs * vertexs]();

	for (int i = 0, j = 0; i < vertexs; i++, j++)
	{
		matrix[i * vertexs + j] = 1;
		vertexNames.insert({ autoGenerateName(i), i });
		vectorNames.push_back(autoGenerateName(i));
	}

	for (int i = 0; i < vertexs; i++)
	{
		for (int j = i + 1; j < vertexs; j++)
		{
			if (matrix[i * vertexs + j] == 0)
			{
				temp = rand() % 10;

				if (!(temp % (maxElement + 1)))
				{
					matrix[i * vertexs + j] = temp;
					matrix[j * vertexs + i] = temp;
					edges++;
					break;
				}
				if (j + 1 == vertexs)
				{
					i = 0;
				}
			}
		}
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

	for (int i = 0, j = 0; i < vertexs; i++, j++)
		matrix[i * vertexs + j] = 1;

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
				else if (matrix[i * vertexs + vertexNames[name]])
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
			//if (i > 0) std::cout << vectorNames[i] << " ";
			//else std::cout << " ";

			std::cout << matrix[i * vertexs + j] << " ";
		}

		std::cout << std::endl;
	}
}
