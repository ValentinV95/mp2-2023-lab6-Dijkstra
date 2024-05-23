#ifndef BHEAP_H
#define BHEAP_H

#include <algorithm>
#include <iterator>
#include <list>
#include <queue>

template<class T>
class BHeap
{
public:
	BHeap() : _min(nullptr), sz(0) {}

	BHeap(const BHeap& h) : sz(h.sz)
	{
		std::queue<Node*> q;
		std::queue<Node*> q_cur;

		for (auto& i : h.root)
		{
			q.push(i);
			q_cur.push(new Node(i->val));
			q_cur.front()->deg = i->deg;
			root.push_front(q_cur.front());

			while (!q.empty())
			{
				if (q.front()->child != nullptr)
				{
					q.push(q.front()->child);
					Node* n = new Node(q.front()->child->val);
					n->deg = q.front()->child->deg;
					q_cur.front()->child = n;
					q_cur.push(n);
				}

				if (q.front()->right != nullptr)
				{
					q.push(q.front()->right);
					Node* n = new Node(q.front()->right->val);
					n->deg = q.front()->right->deg;
					q_cur.front()->right = n;
					q_cur.push(n);
				}

				q.pop();
				q_cur.pop();
			}
		}

		update_min();
	}

	~BHeap()
	{
		if (root.empty())
			return;

		std::queue<Node*> q;
		for (auto& i : root)
		{
			q.push(i);

			while (!q.empty())
			{
				Node* tmp = q.front();
				if (tmp->child != nullptr)
					q.push(tmp->child);
				if (tmp->right != nullptr)
					q.push(tmp->right);

				delete q.front();
				q.pop();
			}
		}
	}

	BHeap& operator=(const BHeap& h)
	{
		if (this == &h)
			return *this;

		BHeap tmp(h);
		swap(*this, tmp);
		return *this;
	}

	const T& top() const { return _min->val; }
	int size() const { return sz; }
	bool empty() const { return sz == 0; }

	void push(const T& t)
	{
		std::list<Node*> tmp;
		tmp.push_back(new Node(t));
		merge(tmp);
		update_min();
		sz++;
	}

	void pop()
	{
		if (sz == 0)
			return;

		auto m = root.begin();
		for (; m != root.end() && *m != _min; ++m);

		Node* deleted = *m;
		Node* tmp = deleted->child;
		int c = deleted->deg;
		std::list<Node*> h;

		for (int i = 0; i < c; ++i)
		{
			h.push_front(tmp);
			tmp = tmp->right;
		}

		root.erase(m);
		delete deleted;
		deleted = nullptr;

		merge(h);
		update_min();

		sz--;
	}

	friend void swap(BHeap& lhs, BHeap& rhs)
	{
		std::swap(lhs.root, rhs.root);
		std::swap(lhs.sz, rhs.sz);
		std::swap(lhs._min, rhs._min);
	}

private:
	class Node
	{
	public:
		Node() : child(nullptr),
			right(nullptr),
			deg(0),
			val() {}

		Node(const T& t) : child(nullptr),
			right(nullptr),
			deg(0),
			val(t) {}

		Node* child;
		Node* right;
		int deg;
		T val;
	};

	void merge(const std::list<Node*>& h)
	{
		std::list<Node*> res;
		auto cur_1 = root.begin();
		auto cur_2 = h.begin();

		while (cur_1 != root.end() && cur_2 != h.end())
		{
			if ((*cur_1)->deg < (*cur_2)->deg)
			{
				res.push_back(*cur_1);
				++cur_1;
			}

			else
			{
				res.push_back(*cur_2);
				++cur_2;
			}
		}

		if (cur_1 == root.end())
		{
			while (cur_2 != h.end())
			{
				res.push_back(*cur_2);
				++cur_2;
			}
		}

		else
		{
			while (cur_1 != root.end())
			{
				res.push_back(*cur_1);
				++cur_1;
			}
		}

		for (auto it = res.begin(); it != res.end();)
		{
			auto next = std::next(it, 1);
			if (next == res.end())
				break;

			if ((*it)->deg == (*next)->deg)
			{
				Node* tmp1 = *it;
				Node* tmp2 = *next;
				res.insert(next, join(tmp1, tmp2));
				res.erase(it++);
				res.erase(next);
			}

			else
				++it;
		}

		swap(res, root);
	}

	Node* join(Node*& n1, Node*& n2)
	{
		if (n1->val < n2->val)
		{
			n2->right = n1->child;
			n1->child = n2;
			n1->deg++;
			return n1;
		}

		else
		{
			n1->right = n2->child;
			n2->child = n1;
			n2->deg++;
			return n2;
		}
	}

	void update_min() {
		if (root.empty())
			return;

		_min = *root.begin();
		for (auto it = root.begin(); it != root.end(); ++it)
			if ((*it)->val < _min->val)
				_min = *it;
	}

	std::list<Node*> root;
	Node* _min;
	int sz;
};

#endif