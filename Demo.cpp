
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <queue>
#include <list>
using namespace std;
#include "BinaryTree.hpp"
using namespace ariel;

class person
{
public:
    string name;
    int age;
    person() : name(""), age(0) {}
    person(string name, int age) : name(name), age(age) {}
    friend bool operator==(const person &p1, const person &p2)
    {
        return p1.name == p2.name && p1.age == p2.age;
    }

    friend bool operator!=(const person &p1, const person &p2)
    {
        return !(p1 == p2);
    }
    friend ostream &operator<<(ostream &os, const person &p)
    {
        os << "[name: " << p.name << ", age: " << p.age << "]";
        return os;
    }
    friend ostream &operator<<(ostream &os, const list<person> l)
    {
        os << "[ ";
        for (person p : l)
        {
            os << "{name: " << p.name << ", age: " << p.age << "},";
        }
        return os << " ]";
    }
};

int main()
{

    cout << "***Binary Tree - int***" << endl;
    BinaryTree<int> bt;
    bt.add_root(1);
    bt.add_left(1, 2);
    cout << "---try to add right son to parent 5 that doesn't exist---" << endl;
    try
    {
        bt.add_right(5, 3);
    }
    catch (exception &e)
    {
        cout << "caught exception: " << e.what() << endl;
    }
    bt.add_left(2, 3);
    bt.add_right(2, 4);
    bt.add_right(4, 5);
    bt.add_right(1, 6);
    bt.add_left(6, 7);
    bt.add_right(7, 8);
    bt.add_right(6, 9);
    bt.add_left(9, 10);
    cout << bt << "\n"
         << endl;
    int count = 1;
    cout << "-pre order:-" << endl;
    for (auto it = bt.begin_preorder(); it != bt.end_preorder(); ++it) //10 checks
    {
        cout << (*it) << " is equal to " << count << endl;
        count++;
    }
    cout << "\n"
         << endl;

    cout << "-in order:-" << endl;
    for (auto it = bt.begin_inorder(); it != bt.end_inorder(); ++it) //10 checks
    {
        cout << (*it) << " ";
    }
    cout << "\n"
         << endl;

    cout << "-post order:-" << endl;
    for (auto it = bt.begin_postorder(); it != bt.end_postorder(); it++) //10 checks
    {
        cout << (*it) << " ";
    }
    cout << "\n"
         << endl;

    cout << "***Binary Tree - string***" << endl;
    BinaryTree<string> bts;
    bts.add_root("10");
    bts.add_root("5"); // root=5
    cout << "trying to add left son to node that doesn't exist" << endl;
    try
    {
        bts.add_left("10", "2");
    }
    catch (exception &e)
    {
        cout << e.what() << endl;
    }
    bts.add_left("5", "2");
    bts.add_left("2", "1");
    bts.add_right("2", "3");
    bts.add_right("3", "4");

    bts.add_right("5", "8");
    bts.add_left("8", "6");
    bts.add_right("8", "10");
    bts.add_right("6", "7");
    bts.add_left("10", "9");
    cout << "Binary Tree - operator" << endl;
    cout << bts << "\n"
         << endl;
    count = 1;
    cout << "-in order:-" << endl;
    for (auto it = bts.begin_inorder(); it != bts.end_inorder(); it++) //10 checks
    {
        cout << (*it) << " is equal to " << count << endl;
        count++;
    }
    cout << "\n"
         << endl;
    cout << "-pre order:-" << endl;
    for (auto it = bts.begin_preorder(); it != bts.end_preorder(); it++) //10 checks
    {
        cout << (*it) << " ";
    }
    cout << "\n"
         << endl;
    cout << "-post order:-" << endl;
    for (auto it = bts.begin_postorder(); it != bts.end_postorder(); it++) //10 checks
    {
        cout << (*it) << " ";
    }
    cout << "\n"
         << endl;

    cout << "***Binary Tree - person***" << endl;
    BinaryTree<person> btp;
    person dan{"Dan", 81};
    person rachel{"Rachel", 60};
    person gad{"Gad", 56};
    person ben{"Ben", 40};
    person avi{"Avi", 38};
    person rivka{"Rivka", 30};
    person gil{"Gil", 10};
    person yael{"Yael", 23};
    person noam{"Noam", 15};
    person dor{"Dor", 26};
    btp.add_root(dor);
    btp.add_root(dan);
    btp.add_left(dan, gad);
    btp.add_right(gad, rivka);
    btp.add_left(rivka, gil);
    btp.add_right(dan, rachel);
    btp.add_left(rachel, ben);
    btp.add_right(rachel, avi);
    btp.add_left(ben, dor);
    btp.add_left(ben, yael);
    btp.add_right(ben, noam);
    cout << btp << "\n"
         << endl;
    queue<person> family;
    family.emplace(gad);
    family.emplace(gil);
    family.emplace(rivka);
    family.emplace(dan);
    family.emplace(yael);
    family.emplace(ben);
    family.emplace(noam);
    family.emplace(rachel);
    family.emplace(avi);

    cout << "---default: in order---" << endl;
    for (auto it = btp.begin(); it != btp.end(); it++, family.pop())
    {
        cout << *it << " is equal to: " << family.front() << endl;
    }
    cout << "\n"
         << endl;

    cout << "---pre order---" << endl;
    for (auto it = btp.begin_preorder(); it != btp.end_preorder(); it++)
    {
        cout << *it << " ";
    }
    cout << "\n"
         << endl;
    cout << "---post order---" << endl;
    for (auto it = btp.begin_postorder(); it != btp.end_postorder(); ++it)
    {
        cout << *it << " ";
    }
    cout << "\n"
         << endl;

    return 0;
}