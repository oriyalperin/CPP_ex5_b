/*
sources:
https://github.com/mission-peace/interview/blob/master/src/com/interview/tree/TreeTraversals.java#L105
https://www.cs.odu.edu/~zeil/cs361/latest/Public/treetraversal/index.html
https://www.geeksforgeeks.org/iterative-postorder-traversal-using-stack/
*/
#pragma once
#include <iostream>
#include <unordered_map>
#include <queue>
#include <deque>
#include <stack>
#include <unordered_set>
using namespace std;
namespace ariel
{

    template <typename T>
    class BinaryTree
    {

    private:
        struct Node
        {
            T data;
            Node *parent, *right, *left;
            Node() : data(nullptr), right(nullptr), left(nullptr)
            {
            }
            Node(T data) : data(data), right(nullptr), left(nullptr)
            {
            }
            Node(T data, Node *parent) : data(data), parent(parent), right(nullptr), left(nullptr)
            {
            }
        };

        Node *root;

    public:
        BinaryTree() : root(nullptr) {}
        BinaryTree(const BinaryTree &bt)
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
        BinaryTree &operator=(const BinaryTree &bt)
        {
            if (this != &bt)
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
        void copy_nodes(Node *node)
        {
            if (node != nullptr)
            {
                if (node->left != nullptr && node->right != nullptr)
                {
                    add_left(node->data, node->left->data);
                    copy_nodes(node->left);
                    add_right(node->data, node->right->data);
                    copy_nodes(node->right);
                }
                if (node->left == nullptr && node->right != nullptr)
                {
                    add_right(node->data, node->right->data);
                    copy_nodes(node->right);
                }
                if (node->left != nullptr && node->right == nullptr)
                {
                    add_left(node->data, node->left->data);
                    copy_nodes(node->left);
                }
            }
        }
        void delete_tree(Node *node)
        {
            delete_nodes(node);
            root = nullptr;
        }
        void delete_nodes(Node *node)
        {
            if (node != nullptr)
            {
                while (node->left != nullptr || node->right != nullptr)
                {
                    if (node->left == nullptr && node->right != nullptr)
                    {
                        delete_nodes(node->right);
                        node->right = nullptr;
                    }
                    else if (node->left != nullptr && node->right == nullptr)
                    {
                        delete_nodes(node->left);
                        node->left = nullptr;
                    }
                    else
                    {
                        delete_nodes(node->left);
                        node->left = nullptr;
                        delete_nodes(node->right);
                        node->right = nullptr;
                    }
                }

                if (node->left == nullptr && node->right == nullptr)
                {
                    delete (node);
                }
            }
        }

        Node *find_node(Node *node, T data)
        {
            if (node != nullptr)
            {
                if (node->data == data)
                {
                    return node;
                }
                if (node->left != nullptr && node->right != nullptr)
                {
                    Node *temp = find_node(node->left, data);
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

        void change_data(Node *node, T new_data)
        {
            node->data = new_data;
        }

        /*add root to the tree*/
        BinaryTree<T> &add_root(T data)
        {
            if (root == nullptr)
            {
                root = new Node(data);
                return *this;
            }
            change_data(root, data);
            return *this;
        }

        /*add left son to the parent*/
        BinaryTree<T> &add_left(T parent, T left)
        {
            Node *p = find_node(root, parent);
            if (p == nullptr)
            {
                throw invalid_argument{"the node doesn't exist"};
            }
            if (p->left != nullptr)
            {
                change_data(p->left, left);
                return *this;
            }
            p->left = new Node(left, p);
            return *this;
        }

        /*add right son to the parent*/
        BinaryTree<T> &add_right(T parent, T right)
        {
            Node *p = find_node(root, parent);
            if (p == nullptr)
            {
                throw invalid_argument{"the node doesn't exist"};
            }
            if (p->right != nullptr)
            {
                change_data(p->right, right);
                return *this;
            }
            p->right = new Node(right, p);
            return *this;
        }

        friend ostream &operator<<(ostream &os, BinaryTree<T> &bt)
        {
            if (bt.root == nullptr)
            {
                return os << "The tree is empty" << endl;
            }
            for (auto it = bt.begin_preorder(); it != bt.end_preorder(); ++it)
            {
                os << (*it) << ",";
            }
            return os << endl;
        }

    private:
        class iterator
        {
        public: //fix to protected
            Node *curr;
            Node *last_node;
            deque<Node *> stack;
            queue<Node *> nodes_order;

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

            //public:
            virtual iterator &operator++()
            {
                next_node();
                return *this;
            }
            virtual iterator operator++(int)
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

    public:
        class PreOrderIt : public iterator
        {
        public:
            PreOrderIt(Node *node = nullptr)
            {

                if (node != nullptr)
                {
                    iterator::last_node = node;
                    iterator::stack.push_front(node);
                    order();
                    iterator::curr = iterator::nodes_order.front();
                    iterator::nodes_order.pop();
                }
                else
                {
                    iterator::curr = nullptr;
                }
            }

        private:
            virtual void order()
            {
                while (!iterator::stack.empty())
                {
                    iterator::last_node = iterator::stack.front();
                    iterator::stack.pop_front();
                    iterator::nodes_order.push(iterator::last_node);
                    if (iterator::last_node->right != nullptr)
                    {
                        iterator::stack.push_front(iterator::last_node->right);
                    }
                    if (iterator::last_node->left != nullptr)
                    {
                        iterator::stack.push_front(iterator::last_node->left);
                    }
                    break;
                }
            }
        };

        class InOrderIt : public iterator
        {
        public:
            InOrderIt(Node *node = nullptr)
            {
                if (node != nullptr)
                {
                    iterator::last_node = node;
                    order();
                    iterator::curr = iterator::nodes_order.front();
                    iterator::nodes_order.pop();
                }
                else
                {
                    iterator::curr = nullptr;
                }
            }

        private:
            virtual void order()
            {
                while (true)
                {
                    if (iterator::last_node != nullptr)
                    {
                        iterator::stack.push_front(iterator::last_node);
                        iterator::last_node = iterator::last_node->left;
                    }
                    else
                    {
                        if (iterator::stack.empty())
                        {
                            break;
                        }
                        iterator::last_node = iterator::stack.front();
                        iterator::stack.pop_front();
                        iterator::nodes_order.push(iterator::last_node);
                        iterator::last_node = iterator::last_node->right;
                        break;
                    }
                }
            }
        };

        class PostOrderIt : public iterator
        {
        public:
            PostOrderIt(Node *node = nullptr)
            {
                if (node != nullptr)
                {
                    iterator::last_node = node;
                    order();
                    iterator::curr = iterator::nodes_order.front();
                    iterator::nodes_order.pop();
                }
                else
                {
                    iterator::curr = nullptr;
                }
            }

        private:
            virtual void order()
            {
                if (!iterator::stack.empty() && iterator::curr == iterator::stack.front()->right)
                {

                    Node *temp = iterator::stack.front();
                    iterator::stack.pop_front();
                    iterator::nodes_order.push(temp);
                }
                else
                {
                    while (iterator::last_node != nullptr || !iterator::stack.empty())
                    {
                        if (iterator::last_node != nullptr)
                        {
                            iterator::stack.push_front(iterator::last_node);
                            iterator::last_node = iterator::last_node->left;
                        }
                        else
                        {
                            Node *temp = iterator::stack.front()->right;
                            if (temp == nullptr)
                            {
                                temp = iterator::stack.front();
                                iterator::stack.pop_front();
                                iterator::nodes_order.push(temp);
                                break;
                            }
                            iterator::last_node = temp;
                        }
                    }
                }
            }

            bool order_for_node(Node *temp)
            {
                if (!iterator::stack.empty() && temp == iterator::stack.front()->right)
                {
                    temp = iterator::stack.front();
                    iterator::stack.pop_front();
                    iterator::nodes_order.push(temp);
                    return true;
                }
                return false;
            }
        };

        PreOrderIt begin_preorder()
        {
            return PreOrderIt{root};
        }
        PreOrderIt end_preorder()
        {
            return PreOrderIt{nullptr};
        }

        InOrderIt begin_inorder()
        {
            return InOrderIt{root};
        }
        InOrderIt end_inorder()
        {
            return InOrderIt{nullptr};
        }

        PostOrderIt begin_postorder()
        {
            return PostOrderIt{root};
        }
        PostOrderIt end_postorder()
        {
            return PostOrderIt{nullptr};
        }

        InOrderIt begin()
        {
            return begin_inorder();
        }
        InOrderIt end()
        {
            return end_inorder();
        }
    };
}