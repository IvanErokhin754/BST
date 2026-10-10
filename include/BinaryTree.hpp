#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <utility>

template<typename T>
class BinaryTree{
private:
    struct Node {
        Node *left;
        Node *right;
        Node *parent;

        T value;

        Node(const T &value_) : left(nullptr), right(nullptr), parent(nullptr), value(value_) {}
    };

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
                    return;
                }
                current = current->left;
            }

            else if (value > current->value) {
                if (current->right == nullptr) {
                    current->right = new Node(value);
                    current->right->parent = current;
                    size++;
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
            delete current;
        }

        else if (current->left && current->right == nullptr) {
            Transplant(current, current->left);
            delete current;
        }
        
        else if (current->left == nullptr && current->right) {
            Transplant(current, current->right);
            delete current;
        }

        else {
            Node *successor = Successor(current);
            current->value = successor->value;
            Transplant(successor, successor->right);
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

    BinaryTree& operator=(BinaryTree other) {
        std::swap(size, other.size);
        std::swap(root, other.root);
        return *this;
    }


    void MakeTree(Node *node, Node *other_tree_node) {
        if (other_tree_node->left == nullptr && other_tree_node->right == nullptr) {
            return;
        }

        if (other_tree_node->left) {
            node->left = new Node(other_tree_node->left->value);
            node->left->parent = node;
            MakeTree(node->left, other_tree_node->left);
        }

        if (other_tree_node->right) {
            node->right = new Node(other_tree_node->right->value);
            node->right->parent = node;
            MakeTree(node->right, other_tree_node->right);
        }
    }

    bool IsEmpty() const {
        if (size == 0 && root == nullptr)
            return true;
        return false;
    }

    void Clear(Node *node) {
        if (node == nullptr)
            return;

        Clear(node->right);
        Clear(node->left);

        size = 0;

        delete node;
    }
    
    void InorderedTreeWalk(Node *x) const {
        if (x != nullptr) {
            InorderedTreeWalk(x->left);
            std::cout << x->value << ' ';
            if (x->parent)
                 std::cout << "parent: " << x->parent->value << std::endl;
            else
                std::cout << std::endl;
            InorderedTreeWalk(x->right);
        }
    }

    size_t GetSize() const {
        return size;
    }

    ~BinaryTree() {
        Clear(root);
    }


};

#endif /* BINARY_TREE_HPP */
