#pragma once
#include <iostream>
#include <queue>
#include <deque>
#include <string>
#include <algorithm>
#include <sstream>
#include "Node.hpp"
#include "BinaryTree.hpp"
using namespace std;
namespace ariel
{
    template <typename T>
    class iterator
    {
    protected:
        Node<T> *curr;
        Node<T> *last_node;
        deque<Node<T> *> stack;
        queue<Node<T> *> nodes_order;
        virtual void order() {}
        virtual void next_node()
        {
            order();
            if (!nodes_order.empty())
            {
                curr = nodes_order.front();
                nodes_order.pop();
            }
            else
            {
                curr = nullptr;
            }
        }

    public:
        iterator<T> &operator++()
        {
            next_node();
            return *this;
        }
        iterator<T> operator++(int)
        {
            iterator temp = *this;
            next_node();
            return temp;
        }

        T &operator*() const
        {
            return curr->data;
        }

        const T *operator->() const
        {
            return &(curr->data);
        }

        bool operator==(const iterator &other) const
        {
            return curr == (other.curr);
        }

        bool operator!=(const iterator &other) const
        {
            return curr != (other.curr);
        }
    };

    template <typename T>
    class PreOrderIt : public iterator<T>
    {
    public:
        PreOrderIt(Node<T> *node = nullptr)
        {
            if (node != nullptr)
            {
                iterator<T>::last_node = node;
                iterator<T>::stack.push_front(node);
                order();
                iterator<T>::curr = iterator<T>::nodes_order.front();
                iterator<T>::nodes_order.pop();
            }
            else
            {
                iterator<T>::curr = nullptr;
            }
        }

    private:
        virtual void order()
        {
            if (!iterator<T>::stack.empty())
            {
                iterator<T>::last_node = iterator<T>::stack.front();
                iterator<T>::stack.pop_front();
                iterator<T>::nodes_order.push(iterator<T>::last_node);
                if (iterator<T>::last_node->right != nullptr)
                {
                    iterator<T>::stack.push_front(iterator<T>::last_node->right);
                }
                if (iterator<T>::last_node->left != nullptr)
                {
                    iterator<T>::stack.push_front(iterator<T>::last_node->left);
                }
            }
        }
    };

    template <typename T>
    class InOrderIt : public iterator<T>
    {
    public:
        InOrderIt(Node<T> *node = nullptr)
        {

            if (node != nullptr)
            {
                iterator<T>::last_node = node;
                order();
                iterator<T>::curr = iterator<T>::nodes_order.front();
                iterator<T>::nodes_order.pop();
            }
            else
            {
                iterator<T>::curr = nullptr;
            }
        }

    private:
        virtual void order()
        {

            while (iterator<T>::last_node != nullptr)
            {
                iterator<T>::stack.push_front(iterator<T>::last_node);
                iterator<T>::last_node = iterator<T>::last_node->left;
            }
            if (!iterator<T>::stack.empty())
            {
                iterator<T>::last_node = iterator<T>::stack.front();
                iterator<T>::stack.pop_front();
                iterator<T>::nodes_order.push(iterator<T>::last_node);
                iterator<T>::last_node = iterator<T>::last_node->right;
            }
        }
    };

    template <typename T>
    class PostOrderIt : public iterator<T>
    {
    public:
        PostOrderIt(Node<T> *node = nullptr)
        {
            if (node != nullptr)
            {
                iterator<T>::last_node = node;
                order();
                iterator<T>::curr = iterator<T>::nodes_order.front();
                iterator<T>::nodes_order.pop();
            }
            else
            {
                iterator<T>::curr = nullptr;
            }
        }

    private:
        virtual void order()
        {
            //int flag = false;
            if (!iterator<T>::stack.empty() && iterator<T>::curr == iterator<T>::stack.front()->right)
            {
                Node<T> *temp = iterator<T>::stack.front();
                iterator<T>::stack.pop_front();
                iterator<T>::nodes_order.push(temp);
            }
            else
            {
                while (iterator<T>::last_node != nullptr || !iterator<T>::stack.empty())
                {
                    if (iterator<T>::last_node != nullptr)
                    {
                        iterator<T>::stack.push_front(iterator<T>::last_node);
                        iterator<T>::last_node = iterator<T>::last_node->left;
                    }
                    else
                    {

                        Node<T> *temp = iterator<T>::stack.front()->right;
                        if (temp == nullptr)
                        {
                            temp = iterator<T>::stack.front();
                            iterator<T>::stack.pop_front();
                            iterator<T>::nodes_order.push(temp);
                            break;
                        }
                        iterator<T>::last_node = temp;
                    }
                }
            }
        }
    };
}