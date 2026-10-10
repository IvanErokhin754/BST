#include <gtest/gtest.h>
#include "BinaryTree.hpp"
#include <vector>
#include <utility>

void ExpectNineNodeTree(const BinaryTree<int>& tree) {
    auto *root = tree.GetRoot();
    EXPECT_FALSE(tree.IsEmpty());
    EXPECT_EQ(tree.GetSize(), 9u);

    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->left->left, nullptr);
    ASSERT_NE(root->left->right, nullptr);
    ASSERT_NE(root->left->right->left, nullptr);
    ASSERT_NE(root->left->right->right, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->right->left, nullptr);
    ASSERT_NE(root->right->right, nullptr);

    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->left->parent, root);
    EXPECT_EQ(root->right->parent, root);

    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->left->value, 5);
    EXPECT_EQ(root->left->left->value, 3);
    EXPECT_EQ(root->left->right->value, 7);
    EXPECT_EQ(root->left->right->left->value, 6);
    EXPECT_EQ(root->left->right->right->value, 8);
    EXPECT_EQ(root->right->value, 20);
    EXPECT_EQ(root->right->left->value, 15);
    EXPECT_EQ(root->right->right->value, 25);
}


TEST(BinaryTreeTest, EmptyTree) {
    BinaryTree<int> tree;

    EXPECT_EQ(tree.GetSize(), 0u);
    EXPECT_TRUE(tree.IsEmpty());

    EXPECT_FALSE(tree.Find(20));
}

TEST(BinaryTreeTest, Insert) {
    BinaryTree<int> tree;

    tree.Insert(10);
    tree.Insert(20);
    tree.Insert(5);
    tree.Insert(3);

    EXPECT_EQ(tree.GetSize(), 4u);

    EXPECT_NE(tree.Find(10), nullptr);
    EXPECT_NE(tree.Find(20), nullptr);
    EXPECT_NE(tree.Find(5), nullptr);
    EXPECT_NE(tree.Find(3), nullptr);

    auto *root = tree.GetRoot();

    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->left->left, nullptr);
    ASSERT_NE(root->right, nullptr);


    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->left->value, 5);
    EXPECT_EQ(root->left->left->value, 3);
    EXPECT_EQ(root->right->value, 20);

    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->left->parent, root);
    EXPECT_EQ(root->right->parent, root);
}

TEST(BinaryTreeTest, DuplicateInsert) {
    BinaryTree<int> tree;

    tree.Insert(10);
    tree.Insert(5);
    
    EXPECT_EQ(tree.GetSize(), 2u);

    auto *before = tree.Find(5);
    tree.Insert(5);

    EXPECT_EQ(tree.Find(5), before);
    EXPECT_EQ(tree.GetSize(), 2u);

    auto *root = tree.GetRoot();

    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);

    EXPECT_EQ(root->left->left, nullptr);
    EXPECT_EQ(root->right, nullptr); 
}

TEST(BinaryTreeTest, CopyEmptyTree) {
    BinaryTree<int> tree;
    BinaryTree<int> tree2(tree);

    EXPECT_TRUE(tree2.IsEmpty());
    EXPECT_EQ(tree2.GetSize(), 0u);
    EXPECT_EQ(tree2.GetRoot(), nullptr);
}

TEST(BinaryTreeTest, CopyAssignmentEmptyTree) {
    BinaryTree<int> tree;
    BinaryTree<int> tree2;
    tree2.Insert(10);
    tree2.Insert(20);
    tree2.Insert(123);
    tree2.Insert(101);

    tree2 = tree; 

    EXPECT_EQ(tree2.GetSize(), 0u);
    EXPECT_EQ(tree2.GetRoot(), nullptr);
    EXPECT_TRUE(tree2.IsEmpty());
}

TEST(BinaryTreeTest, MoveEmptyTree) {
    BinaryTree<int> tree;
    BinaryTree<int> tree2(std::move(tree));

    EXPECT_TRUE(tree2.IsEmpty());
    EXPECT_EQ(tree2.GetSize(), 0u);
    EXPECT_EQ(tree2.GetRoot(), nullptr);

    EXPECT_TRUE(tree.IsEmpty());
    EXPECT_EQ(tree.GetSize(), 0u);
    EXPECT_EQ(tree.GetRoot(), nullptr);
}

TEST(BinaryTreeTest, CopyConstructor) {
    BinaryTree<int> tree;
    std::vector nodes = {10, 5, 20, 3, 7, 6, 8, 15, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> tree2(tree);

    EXPECT_NE(tree.GetRoot(), tree2.GetRoot());
    EXPECT_NE(tree.Find(5), tree2.Find(5));
    EXPECT_NE(tree.Find(6), tree2.Find(6));

    EXPECT_EQ(tree.GetSize(), tree2.GetSize());
    ExpectNineNodeTree(tree2);
}

TEST(BinaryTreeTest, MoveConstructor) {
    BinaryTree<int> tree;

    std::vector nodes = {10, 5, 20, 3, 7, 6, 8, 15, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    auto *old_root = tree.GetRoot();

    BinaryTree<int> tree2(std::move(tree));

    EXPECT_TRUE(tree.IsEmpty());
    EXPECT_EQ(tree.GetRoot(), nullptr);
    EXPECT_EQ(tree.GetSize(), 0u);

    auto *root = tree2.GetRoot();
    EXPECT_EQ(old_root, root);
    ExpectNineNodeTree(tree2);
}

TEST(BinaryTreeTest, CopyAssignment) {
    BinaryTree<int> tree;
    std::vector nodes = {10, 5, 20, 3, 7, 6, 8, 15, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> tree2;
    tree2.Insert(100);
    tree2.Insert(200);
    tree2.Insert(300);

    tree2 = tree;
    
    EXPECT_EQ(tree2.Find(100), nullptr);
    EXPECT_EQ(tree2.Find(200), nullptr);
    EXPECT_EQ(tree2.Find(300), nullptr);

    EXPECT_FALSE(tree.IsEmpty());
    EXPECT_NE(tree.GetRoot(), nullptr);
    EXPECT_EQ(tree.GetSize(), 9u);
    EXPECT_NE(tree.GetRoot(), tree2.GetRoot());

    ExpectNineNodeTree(tree2);
}

TEST(BinaryTreeTest, MoveAssignment) {
    BinaryTree<int> tree;
    std::vector nodes = {10, 5, 20, 3, 7, 6, 8, 15, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }
    auto *old_root = tree.GetRoot();

    BinaryTree<int> tree2;

    tree2.Insert(100);
    tree2.Insert(200);
    tree2.Insert(300);

    tree2 = std::move(tree);

    EXPECT_EQ(tree2.Find(100), nullptr);
    EXPECT_EQ(tree2.Find(200), nullptr);
    EXPECT_EQ(tree2.Find(300), nullptr);

    EXPECT_EQ(tree.GetRoot(), nullptr);
    EXPECT_EQ(tree.GetSize(), 0u);
    EXPECT_TRUE(tree.IsEmpty());

    EXPECT_EQ(old_root, tree2.GetRoot());
    
    ExpectNineNodeTree(tree2);
}

TEST(BinaryTreeTest, SelfAssignment) {
    BinaryTree<int> tree;
    std::vector nodes = {10, 5, 20, 3, 7, 6, 8, 15, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }
    tree = tree;

    ExpectNineNodeTree(tree);
}

TEST(BinaryTreeTest, SelfMoveAssignment) {
    BinaryTree<int> tree;
    std::vector nodes = {10, 5, 20, 3, 7, 6, 8, 15, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }
    tree = std::move(tree);

    ExpectNineNodeTree(tree);
}

