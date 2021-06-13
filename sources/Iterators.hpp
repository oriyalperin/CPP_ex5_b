#pragma once
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <sstream>
#include "Node.hpp"
#include "BinaryTree.hpp"
using namespace std;
namespace ariel
{
    enum class order
    {
        pre,
        in,
        post
    };

    template <typename T, order o>
    class iterator
    {
    private:
        Node<T> *curr;
        Node<T> *last_node;
        stack<Node<T> *> temp_nodes;

    public:
        iterator(Node<T> *node = nullptr) : last_node(node), curr(nullptr)
        {
            if (node != nullptr)
            {
                if (o == order::pre)
                {
                    temp_nodes.push(node);
                }
                order_by();
            }
        }

        iterator<T, o> &operator++()
        {
            order_by();
            return *this;
        }
        iterator<T, o> operator++(int)
        {
            iterator temp = *this;
            order_by();
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

    private:
        void order_by()
        {
            switch (o)
            {
            case order::pre:
                pre_order();
                break;
            case order::in:
                in_order();
                break;
            case order::post:
                post_order();
                break;
            }
        }
        void pre_order()
        {
            if (!temp_nodes.empty())
            {
                last_node = temp_nodes.top();
                temp_nodes.pop();
                curr = last_node;
                if (last_node->right != nullptr)
                {
                    temp_nodes.push(last_node->right);
                }
                if (last_node->left != nullptr)
                {
                    temp_nodes.push(last_node->left);
                }
            }
            else
            {
                curr = nullptr;
            }
        }
        void in_order()
        {
            while (last_node != nullptr)
            {
                temp_nodes.push(last_node);
                last_node = last_node->left;
            }
            if (!temp_nodes.empty())
            {
                last_node = temp_nodes.top();
                temp_nodes.pop();
                curr = last_node;
                last_node = last_node->right;
            }
            else
            {
                curr = nullptr;
            }
        }
        void post_order()
        {
            if (!temp_nodes.empty() && curr == temp_nodes.top()->right)
            {
                Node<T> *temp = temp_nodes.top();
                temp_nodes.pop();
                curr = temp;
            }
            else
            {
                while (last_node != nullptr || !temp_nodes.empty())
                {
                    if (last_node != nullptr)
                    {
                        temp_nodes.push(last_node);
                        last_node = last_node->left;
                    }
                    else
                    {

                        Node<T> *temp = temp_nodes.top()->right;
                        if (temp == nullptr)
                        {
                            temp = temp_nodes.top();
                            temp_nodes.pop();
                            curr = temp;
                            return;
                        }
                        last_node = temp;
                    }
                }
                curr = nullptr;
            }
        }
    };
}
