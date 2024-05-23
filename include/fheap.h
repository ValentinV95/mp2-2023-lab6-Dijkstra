#ifndef FHEAP_H
#define FHEAP_H

#include <algorithm>
#include <iterator>
#include <list>
#include <queue>

template<class T>
class FHeap
{
public:
	FHeap() : _min(nullptr), sz(0) {}

	FHeap(const FHeap& h) : sz(h.sz)
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

	~FHeap()
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

	FHeap& operator=(const FHeap& h)
	{
		if (this == &h)
			return *this;

		FHeap tmp(h);
		swap(*this, tmp);
		return *this;
	}

	const T& top() const { return _min->val; }
	int size() const { return sz; }
	bool empty() const { return sz == 0; }

	void push(const T& t)
	{
		std::list<Node*> tmp;
		Node* n = new Node(t);

		if (_min == nullptr)
			_min = n;
		if (t < _min->val)
			_min = n;

		tmp.push_back(n);
		merge(tmp);
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

		if (!root.empty() || !h.empty())
		{
			merge(h);
			_min = *root.begin();
			trim();
		}

		else
			_min = nullptr;

		sz--;
	}

	friend void swap(FHeap& lhs, FHeap& rhs)
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

	void merge(const std::list<Node*>& h){ root.splice(root.end(), std::list<Node*>(h)); }

	void trim()
	{
		Node** arr = new Node * [sz]();
		std::list<Node*> res;

		for (auto it = root.begin(); it != root.end(); ++it)
		{
			int deg = (*it)->deg;
			if (arr[deg] == nullptr)
				arr[deg] = *it;

			else
			{
				Node* n = join(arr[deg], *it);
				arr[deg++] = nullptr;

				for(; arr[deg] != nullptr; ++deg)
				{
					n = join(arr[deg], n);
					arr[deg] = nullptr;
				}

				arr[deg] = n;
			}
		}

		for (int i = 0; i < sz; ++i)
			if (arr[i] != nullptr)
				res.push_back(arr[i]);

		std::swap(root, res);

		_min = *root.begin();
		for (auto it = root.begin(); it != root.end(); ++it)
			if ((*it)->val < _min->val)
				_min = *it;

		delete arr;
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