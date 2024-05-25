#pragma once
#include <iostream>
#include <stack>


template <class T>
class BinHeap {
	struct Node {
		T data;
		Node* c;
		Node* r;
		Node* p;
		int deg;
		Node(const T& data_ = {}) : data(data_), c(nullptr), r(nullptr), p(nullptr), deg(0) {};
		Node(const Node& nd) : data(nd.data), c(nd.c), r(nd.r), p(nd.p), deg(nd.deg) {};
		Node& operator=(const Node& nd) {
			data = nd.data;
			c = nd.c;
			r = nd.r;
			p = nd.p;
			deg = nd.deg;
		}
	};
	Node* head;
	size_t size;
	Node* join(Node* nd1, Node* nd2) {
		if (nd1->data < nd2->data) {
			nd2->p = nd1;
			nd2->r = nd1->c;
			nd1->c = nd2;
			nd1->deg++;
			return nd1;
		}
		else {
			nd1->p = nd2;
			nd1->r = nd2->c;
			nd2->c = nd1;
			nd2->deg++;
			return nd2;
		}
	}
	void merge(BinHeap& H) {
		Node** mas = new Node * [int(floor(log(size) / log(2))) + 2] {nullptr};
		Node* nd = H.head,* tmp;
		for (nd = head; nd; nd = nd->r) mas[nd->deg] = nd;
		nd = H.head;
		while(nd) {
			tmp = nd;
			nd = nd->r;
			while (mas[tmp->deg]) {
				tmp = join(mas[tmp->deg], tmp);
				mas[tmp->deg - 1] = nullptr;
			}
			mas[tmp->deg] = tmp;
		}
		int i;
		for (i = 0; mas[i]==nullptr; i++);
		head = mas[i];
		nd = head;
		for (i;i<int(floor(log(size) / log(2))) + 2; i++) {
			if (mas[i]) {
				nd->r = mas[i];
				nd = mas[i];
			}
		}
		nd->r = nullptr;
		H.head = nullptr;
	}
public:
	BinHeap() : head(nullptr), size(0) {};
	BinHeap(const T& val) {
		head = new Node(val);
		size = 1;
	}
	~BinHeap() {
		if (head) {
			std::stack<Node*> S;
			Node* tmp;
			S.push(head);
			while (!S.empty()) {
				tmp = S.top();
				S.pop();
				if (tmp->r) S.push(tmp->r);
				if (tmp->c) S.push(tmp->c);
				delete tmp;
			}
		}
	}
	bool empty() { return head == nullptr; }
	T top() {
		if (head) {
			Node* nd = head;
			Node* tmp = nd;
			while (nd->r)
			{
				nd = nd->r;
				if (nd->data < tmp->data) tmp = nd;
			}
			return tmp->data;
		}
		else throw std::logic_error("There are no elements in this heap");
	}
	void push(const T& val) {
		size++;
		BinHeap B(val);
		merge(B);
	}
	void pop() {
		if (head) {
			size--;
			Node fict(head->data);
			fict.deg = -1;
			fict.r = head;
			Node* nd = &fict, * min = &fict;
			while (nd->r)
			{
				if (nd->r->data < min->data) min = nd;
				nd = nd->r;
			}
			if (min->r == head) head = head->r;
			if (min->r->c) {
				BinHeap tmp;
				tmp.head = min->r->c;
				min->r = min->r->r;
				delete tmp.head->p;
				for (nd = tmp.head; nd; nd = nd->r) nd->p = nullptr;
				merge(tmp);
			}
			else {
				nd = min->r;
				min->r = min->r->r;
				delete nd;
			}
		}
		else throw std::logic_error("There are no elements in this heap");
	}
};