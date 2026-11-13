#include <iostream>
#include "BinaryTree.hpp"


int main()
{
    BinaryTree<int> tree;
    //std::vector<int> nodes = {10, 5, 20, 8};
    //std::vector<int> nodes = {10, -5, 20};
    //std::vector<int> nodes = {10, 20, 5};
    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    //std::vector<int> nodes = {10, 5};
    //std::vector<int> nodes = {1, 2, 3, 4};
    //std::vector<int> nodes = {40, 20, 60, 10, 30, 50, 70, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    auto it = tree.GetEnumerator();

    while (it->HasNext()) {
        std::cout << it->Next() << ' ';
    }

    delete it;

    return 0;
}