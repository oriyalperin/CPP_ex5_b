#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <sstream>
#include "Node.hpp"
#include "BinaryTree.hpp"
namespace ariel
{
    enum class order
    {
        pre,
        in,
        post
    };

    template <typename T>
    class iterator
    {
    private:
        order o;
        Node<T> *curr;
        Node<T> *last_node;
        std::stack<Node<T> *> temp_nodes;

    public:
        iterator(order o, Node<T> *node = nullptr) : last_node(node), curr(nullptr), o(o)
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

        iterator<T> &operator++()
        {
            order_by();
            return *this;
        }
        iterator<T> operator++(int)
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
