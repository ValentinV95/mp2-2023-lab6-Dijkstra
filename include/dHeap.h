#pragma once
#include <iostream>
#include <exception>

template<class T1, int d>
class dHeap
{
private:
    T1* data = nullptr;
    int realSize = 0;
    int size = 0;

    void addData(T1 val)
    {
        if (size == realSize)
        {
            T1* tmp = new T1[realSize * 2];
            for (int i = 0; i < realSize; i++)
                tmp[i] = data[i];
            delete[] data;
            data = tmp;
            realSize *= 2;
        }
        data[size++] = val;
    }
    void clearData()
    {
        size = 0;
    }


    void heapify(int i)
    {
        int largestChild;

        for (; ; )
        {
            largestChild = i;


            for (int j = 1; j <= d; j++)
            {
                int index = d * i + j;
                if (index < size && data[index] < data[largestChild])
                    largestChild = index;
            }

            if (largestChild == i)
            {
                break;
            }

            T1 tmp = data[i];
            data[i] = data[largestChild];
            data[largestChild] = tmp;
            i = largestChild;
        }
    }

public:
    dHeap()
    {
        realSize = 10;
        data = new T1[realSize];
        size = 0;
    }
    dHeap(T1* sourceArray, int size)
    {
        data = new T1[size];
        realSize = size;
        this->size = 0;
        buildHeap(sourceArray, size);
    }

    ~dHeap()
    {
        delete[] data;
    }

    void insert(T1 value)
    {
        addData(value);
        int i = size - 1;
        int parent = (i - d + 1) / d;

        while (i > 0 && data[parent] > data[i])
        {
            T1 temp = data[i];
            data[i] = data[parent];
            data[parent] = temp;

            i = parent;
            parent = (i - d + 1) / d;
        }
    }

    bool isEmpty()
    {
        return size == 0;
    }

    

    void buildHeap(T1* sourceArray, int size)
    {
        clearData();
        for (int i = 0; i < size; i++)
            addData(sourceArray[i]);
        for (int i = size / d; i >= 0; i--)
        {
            heapify(i);
        }
    }


    T1 getMin()
    {
        if (size == 0)
            throw std::exception("heap is empty!");
        T1 result = data[0];
        data[0] = data[--size];
        heapify(0);
        return result;
    }

    void show()
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << data[i] << ";  ";
        }
    }
};
