#include <iostream>
#include <ctime>
#include <list>
#include "graph.h"
#include "dijkstra.h"

using namespace std;

enum {ENTER = 1, EOUT, MINPATH};
enum {MANUAL = 1, AUTO};
enum {CONT = 1};

void inform()
{
	cout << "Программа позволяет генерировать связные графы и находить в них минимальные пути." << endl;
	cout << "Примечания: " << endl;
	cout << "Вес ребра не может быть отрицательным." << endl;
	cout << "Граф должен быть связным. При ручном вводе нужно дополнить граф новыми ребрами до связности." << endl;
	cout << "Создание петли у вершины невозможно." << endl;
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Russian");

	int choice1, choice2, choice3, exit = true, exit2 = true;
	int num, perc, tp;
	string stP, endP;
	Graph sample;

	inform();

	while (exit)
	{
		std::cout << "__________________________________________" << std::endl;
		cout << "Выберите действие с графом: " << endl;
		cout << "1) Генерация графа" << endl;
		cout << "2) Вывод на экран графа" << endl;
		cout << "3) Нахождение минимального пути" << endl;
		cout << "Любая другая клавиша - выйти из программы" << endl;
		cout << "Ваш выбор: ";
		cin >> choice1;

		try
		{
			switch (choice1)
			{
			case ENTER:
			{
				std::cout << "__________________________________________" << std::endl;
				cout << "Выберите способ генерации графа: " << endl;
				cout << "1) Ручной ввод" << endl;
				cout << "2) Случайная генерация" << endl;
				cout << "Любая другая клавиша - вернуться к уже введенному графу" << endl;
				cout << "Ваш выбор: ";
				cin >> choice2;

				switch (choice2)
				{
				case MANUAL:
				{
					std::cout << "__________________________________________" << std::endl;
					sample.setGraph();

					break;
				}
				case AUTO:
				{
					std::cout << "__________________________________________" << std::endl;
					cout << "Введите количество вершин: ";
					cin >> num;
					cout << "Введите процент связности: ";
					cin >> perc;
					sample.autoGenerateGraph(num, perc);

					break;
				}
				default:
				{
					break;
				}
				}

				break;
			}
			case EOUT:
			{
				std::cout << "__________________________________________" << std::endl;
				sample.showAdjMatrix();

				break;
			}
			case MINPATH:
			{
				std::cout << "__________________________________________" << std::endl;

				sample.showAdjMatrix();

				cout << endl << "Введите вершину, от которой просчитать минимальные пути: ";
				cin >> stP;
				std::cout << "__________________________________________" << std::endl;
				cout << "Выберите структуру для приоритетной очереди: " << endl;
				cout << "1) Двоичная куча" << endl;
				cout << "2) Биномиальная куча" << endl;
				cout << "3) Красно-черное дерево" << endl;
				cout << "Ваш выбор: ";
				cin >> tp;

				Dijkstra dj(sample, sample.toInt(stP), tp);
				exit2 = true;
				while (exit2)
				{
					std::cout << "__________________________________________" << std::endl;
					cout << "1) Минимальный путь" << endl;
					cout << "Любая другая клавиша - выйти" << endl;
					cout << "Ваш выбор: ";
					cin >> choice3;

					switch (choice3)
					{
					case CONT:
					{
						std::cout << "__________________________________________" << std::endl;
						sample.showAdjMatrix();
						cout << endl << "Введите вершину, до которой просчитать минимальный путь: ";
						cin >> endP;
						std::cout << "__________________________________________" << std::endl;

						list<int> lst = dj.getMinWay(sample.toInt(endP));
						auto it = lst.begin();

						cout << sample.toString(*it);
						++it;

						for (it; it != lst.end(); ++it)
						{
							cout << "---";
							cout << sample.toString(*it);
						}

						cout << endl;

						cout << "Минимальный путь от " << stP << " до " << endP << ": ";
						cout << dj.getCostMinWay(sample.toInt(endP)) << endl;

						break;
					}
					default:
					{
						exit2 = false;
						break;
					}
					}
				}

				break;
			}
			default:
			{
				exit = false;
				break;
			}
			}
		}
		catch (string error)
		{
			std::cout << "__________________________________________" << std::endl;
			cout << error << endl;
		}
	}
}