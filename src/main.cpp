#include <iostream>
#include "BinaryTree.hpp"

bool IsAll(const int &x) {
    return true;
}

bool IsEven(const int &x) {
    return x % 2 == 0;
}

int Double(const int &x) {
    return x * x;
}

int Sum(int accumulator, const int& x) {
    return accumulator + x;
}

int main()
{
    BinaryTree<int> tree;
    std::vector<int> nodes = {10, 5, 15, 20, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    tree.InorderedTreeWalkIterative(tree.GetRoot());
    
    int result = tree.Reduce(Sum, 0);
    std::cout << std::endl;
    
    std::cout << result;


    return 0;
}






/*#include <iostream>
#include "BinaryTree.hpp"

int main()
{
    BinaryTree<int> tree;
    //std::vector<int> nodes = {10, 15, 5, 3, 7, 13, 20};
    //std::vector<int> nodes = {10, 5, 15, 3, 7};
    //std::vector<int> nodes = {30, 20, 10, 25};
    //std::vector<int> nodes = {10, 5, 3, 2, 1};
    std::vector<int> nodes = {20, 10, 5};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    auto *root = tree.GetRoot();

    //std::cout << "old_root = " << root->value << std::endl;
    
    // tree.RotateRightWithTransplant(root);

    // std::cout << "root = " << root->value << std::endl;
    // std::cout << "root->left = " << root->left->value << std::endl;
    // std::cout << "root->right = " << root->right->value << std::endl;
    // std::cout << "root->right->left = " << root->right->left->value << std::endl;
    // std::cout << "root->right->right = " << root->right->right->value << std::endl;
    
    // std::cout << std::endl << std::endl;

    // std::cout << "root->parent = " << root->parent << std::endl;
    // std::cout << "root->left->parent = " << root->left->parent << ' ' << "root = " << root << std::endl;
    // std::cout << "root->right->parent = " << root->right->parent << ' ' << "root = " << root << std::endl;
    // std::cout << "root->right->right->parent = " << root->right->right->parent << ' ' << "root->right" << root->right << std::endl; 
    // std::cout << "root->right->left->parent = " << root->right->left->parent << ' ' << "root->right" << root->right << std::endl;



    
    tree.RotateRight(root);
    //tree.RotateRight(root);

    tree.InorderedTreeWalk(root);
    
    

    return 0;
}*/
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