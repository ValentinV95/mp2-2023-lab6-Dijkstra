#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <iomanip>

class Graph
{
private:
	int* matrix;                                 // Матрица смежности
	std::map<std::string, int> vertInd;          // Доступ к индексам вершин по названию
	std::vector<std::string> vertNames;          // Доступ к названиям вершин по индексу
	int vertexs;                                 // Число вершин
	int edges;                                   // Число ребер

	std::string autoGenerateName(int n);         // Генерация имени для вершины

public:
	Graph();                                     // Конструктор по умолчанию
	~Graph();                                    // Деструктор
	int vertexsSize() const;                     // Количество вершин
	int edgesSize() const;                       // Количество ребер
	bool isEmpty() const;                        // Проверка на пустоту
	bool check() const;                          // Проверка на связность графа
	void autoGenerateGraph(int, int);            // Генерация графа
	void setGraph();                             // Ручной ввод графа
	int* getAdjMatrix() const;                   // Доступ к матрице смежности
	void showAdjMatrix() const;                  // Вывод на экран матрицы смежности
	std::string toString(int ind) const;         // Перевод индекса в название вершины
	int toInt(std::string name);                 // Перевод названия в индекс вершины

};
