#include <iostream>
#include "BinaryTree.hpp"

int main()
{
    BinaryTree<int> tree;

    std::vector<int> nodes = {20, 10, 25, 5, 6, 13, 11, 30, 40, 35, 41};

    for (auto it : nodes) {
        tree.Insert(it);
    } 

    BinaryTree<int> tree2(tree);

    tree.InorderedTreeWalk(tree.GetRoot());
    std::cout << std::endl;
    tree2.InorderedTreeWalk(tree2.GetRoot());
    

    std::cout << "size = " << tree.GetSize() << std::endl;
    return 0;
}
/*
BinaryTree<int> tree;
    //std::vector<int> nodes = {20, 10, 25, 5, 6, 13, 11, 30, 40, 35, 41};
    //std::vector<int> nodes = {20, 10, 25, 24, 23};
    std::vector<int> nodes = {50, 30};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    {10, 5, 20, 2, 7, 17, 25};

    //tree.Delete(3);
    //tree.Delete(50);

    tree.InorderedTreeWalk(tree.GetRoot());
    */