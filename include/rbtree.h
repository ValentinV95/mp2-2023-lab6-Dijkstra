#pragma once

#include "queue.h"

template <class K, class T>
class RedBlackTreeQueue : public PriorityQueue<K, T>
{
private:
    enum class Color { red, black };
    struct Node
    {
        Color color;
        K key;
        T data;
        Node* left;
        Node* right;
        Node* parent;
    };

    Node* root;
    Node* nil;
    Node* find_node(const K& _key)
    {
        if (root == nil) return nullptr;
        Node* node = root;
        while (node != nil)
        {
            if (_key < node->key)
            {
                node = node->left;
            }
            else if (_key > node->key)
            {
                node = node->right;
            }
            else return node;
        }
        return nullptr;
    }
    Node* get_min_node() const
    {
        Node* node = root;
        if (node == nil)
        {
            throw std::exception("Queue is empty");
        }
        while (node->left != nil)
        {
            node = node->left;
        }
        return node;
    }

    void left_rotate(Node* node)
    {
        Node* parent = node->parent;
        if (parent != root)
        {
            if (parent == parent->parent->left)
            {
                parent->parent->left = node;
            }
            else parent->parent->right = node;
        }
        else root = node;
        parent->right = node->left;

        if (node->left != nil)
        {
            node->left->parent = parent;
        }
        node->left = parent;
        node->parent = parent->parent;

        parent->parent = node;
    }
    void right_rotate(Node* node)
    {
        Node* parent = node->parent;
        if (parent != root)
        {
            if (parent == parent->parent->left)
            {
                parent->parent->left = node;
            }
            else parent->parent->right = node;
        }
        else root = node;
        parent->left = node->right;

        if (node->right != nil)
        {
            node->right->parent = parent;
        }
        node->right = parent;
        node->parent = parent->parent;

        parent->parent = node;
    }
    void set_color(Node* node, Color color)
    {
        node->color = color;
    }
    bool cmp_color(Node* node, Color color)
    {
        return node->color == color;
    }

    void fix_insert(Node* child)
    {
        Node* parent = nullptr;
        Node* grandparent = nullptr;
        while (child != root && cmp_color(child, Color::red) && cmp_color(child->parent, Color::red))
        {
            parent = child->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left) // INSERT-CASE 1: LEFT-SUBTREE
            {
                if (cmp_color(grandparent->right, Color::red)) // INSERT-CASE 1.1: RED-UNCLE
                {
                    set_color(parent, Color::black);
                    set_color(grandparent, Color::red);
                    set_color(grandparent->right, Color::black);
                    child = grandparent;
                }
                else // INSERT-CASE 1.2: BLACK-UNCLE
                {
                    if (child == parent->right)
                    {
                        left_rotate(child);
                        child = child->left;
                        parent = child->parent;
                        grandparent = parent->parent;
                    }
                    set_color(parent, Color::black);
                    set_color(grandparent, Color::red);
                    right_rotate(parent);
                }
            }
            else // INSERT-CASE 2: RIGHT-SUBTREE
            {
                if (cmp_color(grandparent->left, Color::red)) // INSERT-CASE 2.1: RED-UNCLE
                {
                    set_color(parent, Color::black);
                    set_color(grandparent, Color::red);
                    set_color(grandparent->left, Color::black);
                    child = grandparent;
                }
                else // INSERT-CASE 2.2: BLACK-UNCLE
                {
                    if (child == parent->left)
                    {
                        right_rotate(child);
                        child = child->right;
                        parent = child->parent;
                        grandparent = parent->parent;
                    }
                    set_color(parent, Color::black);
                    set_color(grandparent, Color::red);
                    left_rotate(parent);
                }
            }
        }
        set_color(root, Color::black);
    }
    void fix_remove(Node* child)
    {
        if (cmp_color(child, Color::red)) // REMOVE-CASE 0: RED-CHILD
        {
            set_color(child, Color::black);
            return;
        }
        Node* parent = nullptr;
        Node* sibling = nullptr;
        while (child != root && cmp_color(child, Color::black))
        {
            parent = child->parent;
            /// if the child of the node being deleted or the node being deleted itself is passed
            if (child == parent->left || parent->left == nil) // REMOVE-CASE 1: LEFT-SUBTREE
            {
                sibling = parent->right;
                if (cmp_color(sibling, Color::red)) // REMOVE-CASE 1.1: RED-SIBLING
                {
                    set_color(parent, Color::red);
                    set_color(sibling, Color::black);
                    left_rotate(sibling);
                }
                else // REMOVE-CASE 1.2: BLACK-SIBLING
                {
                    if (cmp_color(sibling->right, Color::red)) // REMOVE-CASE 1.2.1: RED-RIGHT-NEPHEW
                    {
                        set_color(sibling, parent->color);
                        set_color(sibling->right, Color::black);
                        set_color(parent, Color::black);
                        left_rotate(sibling);
                        break;
                    }
                    else if (cmp_color(sibling->left, Color::red)) // REMOVE-CASE 1.2.2: RED-LEFT-NEPHEW
                    {
                        set_color(sibling->left, Color::black);
                        set_color(sibling, Color::red);
                        right_rotate(sibling->left);
                    }
                    else // REMOVE-CASE 1.2.3: BLACK-ALL-NEPHEW
                    {
                        set_color(sibling, Color::red);
                        set_color(sibling, Color::red);
                        if (cmp_color(parent, Color::red))
                        {
                            set_color(parent, Color::black);
                            break;
                        }
                        child = parent;
                    }
                }
            }
            else // REMOVE-CASE 2: RIGHT-SUBTREE
            {
                sibling = parent->left;
                if (cmp_color(sibling, Color::red)) // REMOVE-CASE 2.1: RED-SIBLING
                {
                    set_color(parent, Color::red);
                    set_color(sibling, Color::black);
                    right_rotate(sibling);
                }
                else // REMOVE-CASE 2.2: BLACK-SIBLING
                {
                    if (cmp_color(sibling->left, Color::red)) // REMOVE-CASE 2.2.1: RED-LEFT-NEPHEW
                    {
                        set_color(sibling, parent->color);
                        set_color(sibling->left, Color::black);
                        set_color(parent, Color::black);
                        right_rotate(sibling);
                        break;
                    }
                    else if (cmp_color(sibling->right, Color::red)) // REMOVE-CASE 2.2.2: RED-RIGHT-NEPHEW
                    {
                        set_color(sibling->right, Color::black);
                        set_color(sibling, Color::red);
                        left_rotate(sibling->right);
                    }
                    else // REMOVE-CASE 2.2.3: BLACK-ALL-NEPHEW
                    {
                        set_color(sibling, Color::red);
                        if (cmp_color(parent, Color::red))
                        {
                            set_color(parent, Color::black);
                            break;
                        }
                        child = parent;
                    }
                }
            }
        }
        set_color(root, Color::black);
    }
    void remove(const K& _key)
    {
        Node* node = find_node(_key);
        if (node == nullptr)
        {
            throw std::exception("key was not found");
        }
        if (node->left == nil && node->right == nil)
        {
            if (node != root)
            {
                if (node->parent->left == node)
                {
                    node->parent->left = nil;
                }
                else node->parent->right = nil;
                fix_remove(node);
            }
            else root = nil;
        }
        else if (node->left != nil && node->right == nil)
        {
            if (node != root)
            {
                if (node->parent->left == node)
                {
                    node->parent->left = node->left;
                }
                else node->parent->right = node->left;
                node->left->parent = node->parent;
            }
            else root = node->left;
            fix_remove(node->left);
        }
        else if (node->left == nil && node->right != nil)
        {
            if (node != root)
            {
                if (node->parent->right == node)
                {
                    node->parent->right = node->right;
                }
                else node->parent->left = node->right;
                node->right->parent = node->parent;
            }
            else root = node->right;
            fix_remove(node->right);
        }
        else
        {
            Node* sub = node->left;
            while (sub->right != nil)
            {
                sub = sub->right;
            }
            Node* first_sub_parent = sub->parent;
            Node* first_sub_left = sub->left;

            // processing of parents and childs
            if (sub->parent != node)
            {
                if (sub->left != nil)
                {
                    sub->left->parent = sub->parent;
                }
                sub->parent->right = sub->left;
                sub->left = node->left;
                node->left->parent = sub;
            }
            sub->right = node->right;
            node->right->parent = sub;
            sub->parent, node->parent;

            // processing of root
            if (node != root)
            {
                if (node->parent->left == node)
                {
                    node->parent->left = sub;
                }
                else node->parent->right = sub;
            }
            else root = sub;

            // *** processing of colors ***
            Color sub_color = sub->color;
            set_color(sub, node->color);
            set_color(node, sub_color);

            // fixing properties after removal
            if (first_sub_left != nil)
            {
                fix_remove(first_sub_left);
            }
            else
            {
                if (node != first_sub_parent)
                {
                    node->parent = first_sub_parent;
                }
                else node->parent = sub;
                fix_remove(node);
            }
        }
        delete node;
    }
public:
    RedBlackTreeQueue()
    {
        nil = new Node{ Color::black };
        root = nil;
    }

    const T& get_min() const override
    {
        return get_min_node()->data;
    }
    void extract_min() override
    {
        remove(get_min_node()->key);
    }
    void insert(const K& _key, const T& _data) override
    {
        if (root == nil)
        {
            root = new Node{ Color::black, _key, _data, nil, nil, nullptr };
            return;
        }
        Node* node = root;
        while (_key != node->key)
        {
            if (_key <= node->key)
            {
                if (node->left == nil)
                {
                    node->left = new Node{ Color::red, _key, _data, nil, nil, node };
                    fix_insert(node->left);
                    return;
                }
                else node = node->left;
            }
            else
            {
                if (node->right == nil)
                {
                    node->right = new Node{ Color::red, _key, _data, nil, nil, node };
                    fix_insert(node->right);
                    return;
                }
                else node = node->right;
            }
        }
    }

    ~RedBlackTreeQueue()
    {
        Node* node = root;
        if (root != nil)
        {
            Node* tmpNode = nullptr;
            while (!(node == root && node->left == nil && node->right == nil))
            {
                if (node->left != nil)
                {
                    node = node->left;
                }
                else
                {
                    if (node->right != nil)
                    {
                        node = node->right;
                    }
                    else
                    {
                        do
                        {
                            tmpNode = node;
                            node = node->parent;
                            if (tmpNode == node->left)
                            {
                                node->left = nil;
                            }
                            else node->right = nil;
                            delete tmpNode;
                        } while (node != root && node->right == nil);
                    }
                }
            }
            delete node;
        }
        delete nil;
    }
};