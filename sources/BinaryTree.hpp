/*
sources:
https://github.com/mission-peace/interview/blob/master/src/com/interview/tree/TreeTraversals.java
https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
https://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/
*/
#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include "Node.hpp"
#include "Iterators.hpp"
using namespace std;
namespace ariel
{

    template <typename T>
    class BinaryTree
    {

    private:
        Node<T> *root;

    public:
        BinaryTree() : root(nullptr) {}
        BinaryTree(const BinaryTree &bt) //copy constructor
        {
            if (bt.root != nullptr)
            {
                root = nullptr;
                add_root(bt.root->data);
                copy_nodes(bt.root);
            }
        }
        ~BinaryTree()
        {
            delete_tree(root);
        }
        BinaryTree &operator=(const BinaryTree &bt) //= operator
        {
            if (&this->root != &bt.root)
            {
                delete_tree(root);
                *this = BinaryTree(bt);
            }
            return *this;
        }

        BinaryTree(BinaryTree &&other) noexcept // move constructor
        {
            this->root = other.root;
            other.root = nullptr;
        }

        BinaryTree &operator=(BinaryTree &&other) noexcept // move assignment
        {
            this->root = other.root;
            other.root = nullptr;
            return *this;
        }

        /*add root to the tree*/
        BinaryTree<T> &add_root(T data)
        {
            if (root == nullptr)
            {
                root = new Node<T>(data);
                return *this;
            }
            change_data(root, data);
            return *this;
        }

        /*add left son to the parent*/
        BinaryTree<T> &add_left(T parent, T left)
        {
            Node<T> *p = find_node(root, parent);
            if (p == nullptr)
            {
                throw invalid_argument{"the node doesn't exist"};
            }
            if (p->left != nullptr)
            {
                change_data(p->left, left);
                return *this;
            }
            p->left = new Node<T>(left);
            return *this;
        }

        /*add right son to the parent*/
        BinaryTree<T> &add_right(T parent, T right)
        {
            Node<T> *p = find_node(root, parent);
            if (p == nullptr)
            {
                throw invalid_argument{"the node doesn't exist"};
            }
            if (p->right != nullptr)
            {
                change_data(p->right, right);
                return *this;
            }
            p->right = new Node<T>(right);
            return *this;
        }

        friend ostream &operator<<(ostream &os, const BinaryTree<T> &bt)
        {
            if (bt.root == nullptr)
            {
                return os << "The tree is empty" << endl;
            }
            os << "♣ Binary Tree - BEGIN ♣\n";
            bt.print(os, bt.root, 0, "");
            os << "\n♣ Binary Tree - END ♣";
            return os;
        }

    private:
        /*helper functions*/

        /*copy all nodes from the given node*/
        void copy_nodes(Node<T> *node)
        {
            if (node != nullptr)
            {
                if (node->left != nullptr)
                {
                    add_left(node->data, node->left->data);
                    copy_nodes(node->left);
                }
                if (node->right != nullptr)
                {
                    add_right(node->data, node->right->data);
                    copy_nodes(node->right);
                }
            }
        }

        /*delete all the tree that rooted from the given node and reset the root*/
        void delete_tree(Node<T> *node)
        {
            delete_nodes(node);
            root = nullptr;
        }

        /*delete all the tree that rooted from the given node*/
        void delete_nodes(Node<T> *node)
        {
            if (node != nullptr)
            {
                while (node->left != nullptr || node->right != nullptr)
                {
                    if (node->right != nullptr)
                    {
                        delete_nodes(node->right);
                        node->right = nullptr;
                    }
                    if (node->left != nullptr)
                    {
                        delete_nodes(node->left);
                        node->left = nullptr;
                    }
                }

                if (node->left == nullptr && node->right == nullptr)
                {
                    delete (node);
                }
            }
        }

        /*find node in the tree*/
        Node<T> *find_node(Node<T> *node, T data)
        {
            if (node != nullptr)
            {
                if (node->data == data)
                {
                    return node;
                }
                if (node->left != nullptr && node->right != nullptr)
                {
                    Node<T> *temp = find_node(node->left, data);
                    if (temp == nullptr)
                    {
                        return find_node(node->right, data);
                    }
                    return temp;
                }
                if (node->left == nullptr && node->right != nullptr)
                {
                    return find_node(node->right, data);
                }
                if (node->left != nullptr && node->right == nullptr)
                {
                    return find_node(node->left, data);
                }
            }
            return nullptr;
        }

        /*change the data of the given node*/
        void change_data(Node<T> *node, T new_data)
        {
            node->data = new_data;
        }

        /*recursive function for output*/
        void print(ostream &os, Node<T> *node, unsigned space, string next_line) const
        {
            if (node == nullptr)
            {
                return;
            }
            os << node->data;
            stringstream data;
            data << node->data;
            unsigned size = data.str().length();
            next_line += string(space + size - 1, ' ');
            const unsigned arrow = 5;
            if (node->left != nullptr)
            {
                next_line += "|";
            }
            else
            {
                next_line += " ";
            }
            if (node->right != nullptr)
            {
                os << "----→";
                print(os, node->right, arrow, next_line);
            }
            if (node->left != nullptr)
            {

                os << "\n"
                   << next_line
                   << "\n";
                os << next_line << "----→";
                unsigned const size_line = next_line.size();
                next_line.replace(size_line - 1, size_line, " ");
                print(os, node->left, arrow, next_line);
            }
        }

    public:
        iterator<T> begin_preorder()
        {
            return iterator<T>{order::pre, root};
        }
        iterator<T> end_preorder()
        {
            return iterator<T>{order::pre};
        }

        iterator<T> begin_inorder()
        {
            return iterator<T>{order::in, root};
        }
        iterator<T> end_inorder()
        {
            return iterator<T>{order::in};
        }

        iterator<T> begin_postorder()
        {
            return iterator<T>{order::post, root};
        }
        iterator<T> end_postorder()
        {
            return iterator<T>{order::post};
        }

        iterator<T> begin()
        {
            return begin_inorder();
        }
        iterator<T> end()
        {
            return end_inorder();
        }
    };
}