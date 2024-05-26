#pragma once
#include <iostream>
#include <stack>


template <class T>
class FibHeap {
	struct Node {
		T data;
		Node* c;
		Node* r, * l;
		Node* p;
		int deg;
		Node(const T& data_ = {}) : data(data_), c(nullptr), r(nullptr), l(nullptr), p(nullptr), deg(0) {};
		Node(const Node& nd) : data(nd.data), c(nd.c), r(nd.r), l(nd.l), p(nd.p), deg(nd.deg) {};
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
			if (nd1->c)
				nd1->c->l = nd2;
			nd1->c = nd2;
			nd2->l = nullptr;
			nd1->deg++;
			return nd1;
		}
		else {
			nd1->p = nd2;
			nd1->r = nd2->c;
			if (nd2->c)
				nd2->c->l = nd1;
			nd2->c = nd1;
			nd1->l = nullptr;
			nd2->deg++;
			return nd2;
		}
	}
	void merge(FibHeap& H) {
		if (head || H.head) {
			Node** mas = new Node * [int(floor(log(size) / log(2))) + 2] {nullptr};
			//join H to this
			if (head && H.head) {
				std::swap(H.head->l, head->l);
				H.head->l->r = H.head;
				head->l->r = head;
			}
			else if (H.head && head == nullptr) head = H.head;
			mas[head->deg] = head;
			Node* nd = head->r, * tmp;
			while (nd != head) {
				tmp = nd;
				nd = nd->r;
				while (mas[tmp->deg]) {
					tmp = join(mas[tmp->deg], tmp);
					mas[tmp->deg - 1] = nullptr;
				}
				mas[tmp->deg] = tmp;
			}
			int i = 0;
			for (i = 0; mas[i] == nullptr; i++);
			tmp = nd = head = mas[i];
			for (i; i<int(floor(log(size) / log(2))) + 2; i++) {
				if (mas[i]) {
					if (mas[i]->data < head->data) head = mas[i];
					mas[i]->l = nd;
					nd->r = mas[i];
					nd = mas[i];
				}
			}
			nd->r = tmp;
			tmp->l = nd;
			H.head = nullptr;
			delete[]mas;
		}
	}
public:
	FibHeap() : head(nullptr) {};
	FibHeap(const T& val) {
		head = new Node(val);
		head->r = head->l = head;
		size++;
	}
	~FibHeap() {
		if (head) {
			std::stack<Node*> S;
			Node* tmp;
			S.push(head);
			head->l->r = nullptr;
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
			return head->data;
		}
		else throw std::logic_error("There are no elements in this heap");
	}
	void push(const T& val) {
		Node* nd = new Node(val);
		if (head) {
			nd->r = head;
			nd->l = head->l;
			nd->r->l = nd;
			if (nd->l)
				nd->l->r = nd;
			if (val < head->data) head = nd;
		}
		else {
			head = nd;
			head->r = head->l = head;
		}
		size++;
	}
	void pop() {
		if (head) {
			FibHeap tmp;
			if (head->c) {
				tmp.head = head->c;
				head->r->l = head->l;
				head->l->r = head->r;
				if (head != head->r)
					head = head->r;
				else head = nullptr;
				delete tmp.head->p;
				Node* nd = tmp.head;
				tmp.head->p = nullptr;
				for (nd; nd->r; nd = nd->r) nd->r->p = nullptr;
				nd->r = tmp.head;
				tmp.head->l = nd;
			}
			else {
				Node* nd = head;
				if (head != head->r) {
					head->r->l = head->l;
					head->l->r = head->r;
					head = head->r;
				}
				else head = nullptr;
				delete nd;
			}
			size--;
			merge(tmp);
		}
		else throw std::logic_error("There are no elements in this heap");
	}
};