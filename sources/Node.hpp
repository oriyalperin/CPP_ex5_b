#pragma once

namespace ariel
{
    template <typename T>
    struct Node
    {
        T data;
        Node *right, *left;
        Node() : data(nullptr), right(nullptr), left(nullptr) {}
        Node(T data) : data(data), right(nullptr), left(nullptr) {}
    };
}