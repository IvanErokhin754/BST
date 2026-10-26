#include <iostream>
#include "BinaryTree.hpp"


int main()
{
    BinaryTree<int> tree;
    BinaryTree<int> tree2;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    nodes = {20};
    for (auto node : nodes) {
        tree2.Insert(node);
    }


    std::cout << tree.ContainsSubtree(tree2);
    return 0;
}