#include "graph.h"

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

int Graph::vertexsSize() const
{
	return vertexs;
}

int Graph::edgesSize() const
{
	return edges;
}

bool Graph::isEmpty() const
{
	return matrix == nullptr;
}

bool Graph::check() const
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

		for (col = 0; col < vertexs; col++)
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
	if (n < 0 )
	{
		std::string error = "Количество вершин не может быть отрицательным числом";
		throw error;
	}

	if (100 < percent || percent < 0)
	{
		std::string error = "Процент заполненности может изменяться от 0 до 100";
		throw error;
	}

	if (!isEmpty())
	{
		delete[] matrix;
		matrix = nullptr;
		vertexs = 0;
		edges = 0;
	}

	vertexs = n;

	matrix = new int[vertexs * vertexs]();

	for (int i = 0; i < vertexs; i++)
	{
		vertInd.insert({ autoGenerateName(i), i });
		vertNames.push_back(autoGenerateName(i));
	}

	int treeEdges = vertexs - 1;
	int temp;
	int row = 0;

	while (edges != treeEdges)
	{
		for (int i = row + 1; i < vertexs; i++)
		{
			if (matrix[row * vertexs + i] == 0 && rand() % vertexs == 0)
			{
				temp = rand() % (vertexs * 100) + 1;
				matrix[row * vertexs + i] = temp;
				matrix[i * vertexs + row] = temp;
				edges++;
				row++;
				break;
			}
		}
	}

	int maxEdges = vertexs * (vertexs - 1) / 2;
	maxEdges -= edges;
	maxEdges = (maxEdges * percent) / 100;

	int count = 0;
	int col = 1;
	row = 0;

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
		if (matrix[row * vertexs + col] == 0 && rand() % 50 == 0)
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

	for (int i = 0; i < vertexs; i++)
	{
		std::cout << (i + 1) << ") Введите название вершины: ";
		std::cin >> name;

		if (vertInd.count(name))
		{
			std::cout << "__________________________________________" << std::endl;
			std::cout << "Данная вершина уже есть, повторите попытку" << std::endl;
			i--;
		}
		else
		{
			vertNames.push_back(name);
			vertInd.insert(std::pair<std::string, int>(name, i));
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
			std::cout << "Для ввода связной вершины к вершине " << vertNames[i] << " введите 1" << std::endl;
			std::cout << "Для перехода к следующей вершине введите 2" << std::endl;
			std::cout << "Чтобы закончить вводить вершины нажмите любую другую клавишу" << std::endl;
			std::cout << "Ваш выбор: ";
			std::cin >> choice;

			switch (choice) {
			case ENTER:
			{
				std::cout << "__________________________________________" << std::endl;
				std::cout << "Введите связную вершину для вершины " << vertNames[i];
				std::cout << ": ";
				std::cin >> name;
				if (!vertInd.count(name))
				{
					std::cout << "__________________________________________" << std::endl;
					std::cout << "Введенная вершина не найдена. Повторите попытку." << std::endl;
				}
				else if (matrix[i * vertexs + vertInd[name]] || i == vertInd[name])
				{
					std::cout << "__________________________________________" << std::endl;
					std::cout << "Введенная вершина уже связана с данной. Повторите попытку." << std::endl;
				}
				else
				{
					std::cout << "Введите вес ребра между " << vertNames[i];
					std::cout << " и " << name << ": ";
					std::cin >> weight;

					if (weight <= 0)
					{
						std::cout << "Вес ребра не может быть 0 или отрицательным числом. Повторите попытку." << std::endl;
					}
					else
					{
						matrix[i * vertexs + vertInd[name]] = weight;
						matrix[vertInd[name] * vertexs + i] = weight;
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
					return;
				}
			}
			}

			showAdjMatrix();
		}

	}
}

void Graph::showAdjMatrix() const
{
	std::cout << "  ";

	for (int i = 0; i < vertexs; i++)
		std::cout << std::setw(5) << vertNames[i];

	std::cout << std::endl << std::endl;

	for (int i = 0; i < vertexs; i++)
	{
		std::cout << std::setw(2) << vertNames[i];

		for (int j = 0; j < vertexs; j++)
		{
			std::cout << std::setw(5) << matrix[i * vertexs + j];
		}

		std::cout << std::endl;
	}
}

int* Graph::getAdjMatrix() const
{
	return matrix;
}

std::string Graph::toString(int ind) const
{
	if (vertexs <= ind || ind < 0)
	{
		std::string error = "Вершина не найдена. Повторите попытку.";
		throw error;
	}

	return vertNames[ind];
}

int Graph::toInt(std::string name)
{
	if (!vertInd.count(name))
	{
		std::string error = "Вершина не найдена. Повторите попытку.";
		throw error;
	}

	return vertInd[name];
}