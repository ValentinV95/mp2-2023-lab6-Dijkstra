#pragma once
#include <exception>

template<class KEY, class VAL>
class FibonacciHeap
{
private:
    struct Node
    {
        Node* parent;
        Node* child;
        Node* left;
        Node* right;
        KEY key;
        VAL data;
        int degree;
        bool mark;
        Node() {};
        Node operator = (const Node& r)
        {
            parent = r.parent;
            child = r.child;
            left = r.left;
            right = r.right;
            KEY key = r.key;
            VAL data = r.data;
            int degree = r.degree;
            bool mark = r.mark;
        }
    };

    int size;
    Node* head;

    void Link(Node* node2, Node* node1)
    {
        (node2->left)->right = node2->right;
        (node2->right)->left = node2->left;
        if (node1->right == node1)
            head = node1;
        node2->left = node2;
        node2->right = node2;
        node2->parent = node1;
        if (node1->child == nullptr)
            node1->child = node2;
        node2->right = node1->child;
        node2->left = (node1->child)->left;
        ((node1->child)->left)->right = node2;
        (node1->child)->left = node2;
        if (node2->key < (node1->child)->key)
            node1->child = node2;
        node1->degree++;
    }

    void Consolidate()
    {
        int degr;
        int arrSize = (log(size)) / (log(2)) + 1;
        Node** array = new Node * [arrSize];
        for (int i = 0; i < arrSize; i++)
            array[i] = nullptr;
        Node* ptr1 = head;
        Node* ptr2;
        Node* ptr3 = head;
        Node* tmp;
        do {
            ptr3 = ptr3->right;
            degr = ptr1->degree;
            while (array[degr] != nullptr)
            {
                ptr2 = array[degr];
                if (ptr1->key > ptr2->key)
                {
                    tmp = ptr1;
                    ptr1 = ptr2;
                    ptr2 = tmp;
                }
                if (ptr2 == head)
                    head = ptr1;
                Link(ptr2, ptr1);
                if (ptr1->right == ptr1)
                    head = ptr1;
                array[degr] = nullptr;
                degr++;
            }
            array[degr] = ptr1;
            ptr1 = ptr1->right;
        } while (ptr1 != head);

        head = nullptr;
        for (int j = 0; j < arrSize; j++)
        {
            if (array[j] != nullptr)
            {
                array[j]->left = array[j];
                array[j]->right = array[j];
                if (head != nullptr)
                {
                    (head->left)->right = array[j];
                    array[j]->right = head;
                    array[j]->left = head->left;
                    head->left = array[j];
                    if (array[j]->key < head->key)
                        head = array[j];
                }
                else
                    head = array[j];
                if (head == nullptr)
                    head = array[j];
                else if (array[j]->key < head->key)
                    head = array[j];
            }
        }
        delete[] array;
    }
public:
    FibonacciHeap() 
    {
        size = 0;
        head = nullptr;
    }
    ~FibonacciHeap() 
    {
        while (!isEmpty())
        {
            getMin();
        }
    }

    void insert(KEY key, VAL value)
    {
        Node* new_node = new Node();
        new_node->key = key;
        new_node->data = value;
        new_node->degree = 0;
        new_node->mark = false;
        new_node->parent = nullptr;
        new_node->child = nullptr;
        new_node->left = new_node;
        new_node->right = new_node;
        if (head != nullptr) 
        {
            (head->left)->right = new_node;
            new_node->right = head;
            new_node->left = head->left;
            head->left = new_node;
            if (new_node->key < head->key)
                head = new_node;
        }
        else 
        {
            head = new_node;
        }

        size++;
    }


    VAL getMin()
    {
        if (head == nullptr)
            throw std::exception("Heap is empty!");

        VAL retValue = head->data;
        Node* forDel = head;
        Node* tmp = head;
        Node* pntr = tmp;
        Node* children = nullptr;
        if (tmp->child != nullptr) {

            children = tmp->child;
            do {
                pntr = children->right;
                (head->left)->right = children;
                children->right = head;
                children->left = head->left;
                head->left = children;
                if (children->key < head->key)
                    head = children;
                children->parent = nullptr;
                children = pntr;
            } while (pntr != tmp->child);
        }
        (tmp->left)->right = tmp->right;
        (tmp->right)->left = tmp->left;
        head = tmp->right;
        if (tmp == tmp->right && tmp->child == nullptr)
            head = nullptr;
        else {
            head = tmp->right;
            Consolidate();
        }
        size--;
        delete forDel;
        return retValue;
    }



    bool isEmpty()
    {
        return size == 0;
    }
};



