#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <utility>
#include <algorithm>
#include "Stack.hpp"

template<typename T>
class BinaryTree{
private:
    struct Node {
        Node *left;
        Node *right;
        Node *parent;
        T value;
        int height;

        Node(const T &value_) : left(nullptr), right(nullptr), parent(nullptr), value(value_), height(0) {}
    };

    void Clear(Node *node) {
        if (node == nullptr)
            return;

        Clear(node->right);
        Clear(node->left);

        delete node;
    }

    void Transplant(Node *old_node, Node *new_node) {    
        if (new_node != nullptr)
            new_node->parent = old_node->parent;
        
        if (old_node == root) {
            root = new_node;
            return;
        }
        
    
        if (old_node->parent->left == old_node) {
            old_node->parent->left = new_node;
        }
        else if (old_node->parent->right == old_node) {
            old_node->parent->right = new_node;
        }

    }

    Node *root;
    size_t size; 

public:
    BinaryTree() : root(nullptr), size(0) {}
    BinaryTree(const BinaryTree& other) : root(nullptr), size(0) {
        try {
            if (other.root == nullptr) 
                return;   

            root = new Node(other.root->value);
            root->height = other.root->height;
            MakeTree(root, other.root);
            size = other.size;
        }
        catch(...) {
            Clear(root);
            throw;
        }
    }
    BinaryTree(BinaryTree&& other) noexcept {
        root = other.root;
        other.root = nullptr;
        size = other.size;
        other.size = 0;
    }


    void Insert(const T& value) {
        if (root == nullptr) {
            root = new Node(value);
            root->parent = nullptr;
            size++;
            return;
        }
        Node *current = root;
        while (current != nullptr) {
            if (value < current->value) {
                if (current->left == nullptr) {
                    current->left = new Node(value);
                    current->left->parent = current;
                    size++;
                    UpdateHeight(current->left);
                    return;
                }
                current = current->left;
            }

            else if (value > current->value) {
                if (current->right == nullptr) {
                    current->right = new Node(value);
                    current->right->parent = current;
                    size++;
                    UpdateHeight(current->right);
                    return;
                }
                current = current->right;
            }

            else return;
        }
    }

    Node* Find(const T& value) const {
        Node *current = root;

        while (current != nullptr) {
            if (current->value > value) {
                current = current->left;
            }
            else if (current->value < value) {
                current = current->right;
            }
            else 
                return current;
        }

        return nullptr;
    }


    void Remove(const T& value) {
        Node *current = Find(value);

        if (current == nullptr) {
            throw std::logic_error("Remove : subtree don't have node with this value");
        }

        if (current->left == nullptr && current->right == nullptr) {
            Transplant(current, nullptr);
            UpdateHeight(current->parent);
            delete current;
            
        }

        else if (current->left && current->right == nullptr) {
            Transplant(current, current->left);
            UpdateHeight(current->parent);
            delete current;
        }
        
        else if (current->left == nullptr && current->right) {
            Transplant(current, current->right);
            UpdateHeight(current->parent);
            delete current;
        }

        else {
            Node *successor = Successor(current);
            current->value = successor->value;
            Transplant(successor, successor->right);
            UpdateHeight(successor->parent);
            delete successor;
        }
        size--;
    }

    Node* Successor(Node *root) const {
        if (root == nullptr)
            throw std::logic_error("Successor: subtree is empty");
        
        Node *current = root;
        current = current->right;

        while (current->left != nullptr) {
            current = current->left;
        }
        
        return current;
    }

    bool Contains(const T& value) const {
        if (root == nullptr)
            return false;

        Node *current = root;

        while (current != nullptr) {
            if (current->value == value) 
                return true;

            else if (current->value < value) 
                current = current->right;
        
            else 
                current = current->left;
        }

        return false;
    }

    Node* GetRoot() const {
        return root;
    }

    void UpdateHeight(Node *current) {
        while (current) {
            int height_left, height_right;
            height_left = GetHeight(current->left);
            height_right = GetHeight(current->right);
            current->height = std::max(height_left, height_right) + 1;
            current = current->parent;
        }
    }

    BinaryTree& operator=(BinaryTree other) {
        std::swap(size, other.size);
        std::swap(root, other.root);
        return *this;
    }

    int GetBalanceFactor(Node *node) const {
        if (node == nullptr)
            return 0;
        return GetHeight(node->left) - GetHeight(node->right);
    }

    /*void RotateRight(Node *&root) {
        Node *y = root;
        Node *root_right;
        root = root->left;
        root_right = root->right;
        root->right = y;
        root->right->parent = root;
        root->right->left = root_right;
        root->right->left->parent = root->right;
        root->parent = nullptr;
    }*/

    /*void RotateRight(Node *&node) {
        if (node == nullptr || node->left == nullptr)
            return;
        if (node->left)
            node = node->left;
    
        if (node != root)
            node->parent->parent = node;
        else {

        }
        Node *temp = node->right;
        node->right = node->parent;
        node->parent = nullptr;
        node->right->left = temp;
        if (temp)
            temp->parent = node->right; 
    }*/


    void MakeTree(Node *node, Node *other_tree_node) {
        if (other_tree_node->left == nullptr && other_tree_node->right == nullptr) {
            return;
        }

        if (other_tree_node->left) {
            node->left = new Node(other_tree_node->left->value);
            node->left->parent = node;
            node->left->height = other_tree_node->left->height;
            MakeTree(node->left, other_tree_node->left);
        }

        if (other_tree_node->right) {
            node->right = new Node(other_tree_node->right->value);
            node->right->parent = node;
            node->right->height = other_tree_node->right->height;
            MakeTree(node->right, other_tree_node->right);
        }
    }

    bool IsEmpty() const {
        if (size == 0 && root == nullptr)
            return true;
        return false;
    }
    
    void InorderedTreeWalk(Node *x) const {
        if (x != nullptr) {
            InorderedTreeWalk(x->left);
            InorderedTreeWalk(x->right);
        }
    }

    void InorderedTreeWalkIterative(Node *current) const {
        Stack<Node*> stack;

        while (current != nullptr || !stack.IsEmpty()) {
            if (current != nullptr) {
                stack.Push(current);
                current = current->left;
            }
            else {
                current = stack.Get();
                stack.Pop();
                std::cout << current->value << ' ';
                current = current->right;
            }
        }
    }

    size_t GetSize() const {
        return size;
    }

    int GetHeight(Node *node) const {
        if (node == nullptr)
            return -1;
        return node->height;
    }

    BinaryTree Where(bool (*predicate)(const T&)) const {
        BinaryTree result;
        Stack<Node*> stack;
        Node *current = root;
        
        while (current != nullptr || !stack.IsEmpty()) {
            if (current != nullptr) {
                stack.Push(current);
                current = current->left;
            }
            else {
                current = stack.Get();
                stack.Pop();
            
                if (predicate(current->value))
                    result.Insert(current->value);
                current = current->right;
            }
        }

        return result;
    }

    BinaryTree Map(T (*func)(const T&)) const {
        BinaryTree result;
        Stack<Node*> stack;
        Node *current = root;

        while (current != nullptr || !stack.IsEmpty()) {
            if (current != nullptr) {
                stack.Push(current);
                current = current->left;
            }
            else {
                current = stack.Get();
                stack.Pop();

                result.Insert(func(current->value));

                current = current->right;
            }
        }
        
        return result;
    }

    T Reduce(T (*func)(T, const T&), T initial) const {
        T result = initial;

        Stack<Node*> stack;
        Node *current = root;
        
        while (current != nullptr || !stack.IsEmpty()) {
            if (current != nullptr) {
                stack.Push(current);
                current = current->left;
            }
            else {
                current = stack.Get();
                stack.Pop();
                result = func(result, current->value);
                current = current->right;
            }
        }

        return result;
    }


    void Clear() {
        Clear(root);
        size = 0;
        root = nullptr;
    }

    ~BinaryTree() {
        Clear(root);
    }


};

#endif /* BINARY_TREE_HPP */
