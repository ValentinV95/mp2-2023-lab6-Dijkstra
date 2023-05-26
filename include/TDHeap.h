#pragma once

#include"PriorityQueue.h"

#include<vector>
#include<iostream>

using namespace std;

template<class T, int D = 3>
class TDHeap: public PriorityQueue<T>
{
    vector<T> data;

    void swap(size_t a, size_t b)
    {
        T tmp = data[a];
        data[a] = data[b];
        data[b] = tmp;
    }

    size_t parent(size_t ind)
    {
        return (ind - 1) / D;
    }

    size_t minChild(size_t ind)
    {
        size_t min = D * ind + 1;
        for (size_t i = min + 1; i < min + D && i < data.size(); i++)
        {
            if (data[i] < data[min])
            {
                min = i;
            }
        }
        return min;
    }

    void shiftUp(size_t ind)
    {
        if (ind == 0)
        {
            return;
        }
        size_t par = parent(ind);
        size_t cur = ind;
        while (data[cur] < data[par])
        {
            swap(cur, par);
            cur = par;
            if (par == 0)
            {
                return;
            }
            par = parent(par);
        }
    }

    void shiftDown(size_t ind)
    {
        size_t cur = ind;
        size_t min = minChild(ind);
        while (min < data.size() && data[cur] > data[min])
        {
            swap(cur, min);
            cur = min;
            min = minChild(cur);
        }
    }
public:
    TDHeap() = default;

    ~TDHeap() = default;

    TDHeap(const vector<T>& vec) :data(vec)
    {
        for (size_t i = data.size() / 2; i >= 1; i--)
        {
            shiftDown(i);
        }
        shiftDown(0);
    }

    void insert(const T& elem) override
    {
        data.push_back(elem);
        shiftUp(data.size() - 1);
    }

    void extractMin() override
    {
        if (data.size() == 0)
        {
            return;
        }
        swap(0, data.size() - 1);
        data.pop_back();
        shiftDown(0);
    }

    const T& getMin() const override
    {
        return data[0];
    }

    const bool isEmpty() const
    {
        return !data.size();
    }

    void show()
    {
        for(size_t i = 0; i < data.size(); i++)
        {
            cout << data[i] << " ";
        }
    }
};