#include "tree.hpp"

template<>
void Tree<int>::DFS(RBNode<int>* cur) const
{
	if (cur)
	{
		DFS(cur->left);
		std::cout << cur->data << " ";
		DFS(cur->right);
	}
}