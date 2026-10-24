#include <gtest/gtest.h>
#include "BinaryTree.hpp"
#include <vector>
#include <utility>

bool IsEven(const int &x) {
    return x % 2 == 0;
}

bool IsNone(const int &x) {
    return false;
}

bool IsAll(const int &x) {
    return true;
}

int Square(const int &x) {
    return x * x;
}

int Identity(const int &x) {
    return x;
}

int Constant(const int &x) {
    return 42;
}

int Negate(const int &x) {
    return -x;
}

int Sum(int accumulator, const int& x) {
    return accumulator + x;
}

int Mult(int accumulator, const int& x) {
    return accumulator * x;
}

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

TEST(BinaryTreeTest, FindAndContains) {
    BinaryTree<int> tree;
    std::vector nodes = {10, 5, 20, 3, 7, 6, 8, 15, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    for (auto node : nodes) {
        auto *found = tree.Find(node);

        ASSERT_NE(found, nullptr);
        EXPECT_EQ(found->value, node);
        EXPECT_TRUE(tree.Contains(node));
    }

    EXPECT_EQ(tree.GetSize(), 9u);

    EXPECT_EQ(tree.Find(100), nullptr);
    EXPECT_FALSE(tree.Contains(-100));
}

TEST(BinaryTreeTest, RemoveLeaf) {
    BinaryTree<int> tree;
    std::vector nodes = {10, 5, 20, 3, 7, 6, 8, 15, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    tree.Remove(6);

    EXPECT_EQ(tree.GetSize(), 8u);
    EXPECT_EQ(tree.Find(6), nullptr);

    auto *root = tree.GetRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->left->left, nullptr);
    ASSERT_NE(root->left->right, nullptr);
    ASSERT_NE(root->left->right->right, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->right->left, nullptr);
    ASSERT_NE(root->right->right, nullptr);


    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->left->value, 5);
    EXPECT_EQ(root->left->left->value, 3);
    EXPECT_EQ(root->left->right->value, 7);
    EXPECT_EQ(root->left->right->right->value, 8);
    EXPECT_EQ(root->right->value, 20);
    EXPECT_EQ(root->right->left->value, 15);
    EXPECT_EQ(root->right->right->value, 25);

    EXPECT_EQ(root->left->right->left, nullptr);
    EXPECT_EQ(root->left->right->right->parent, root->left->right);
    EXPECT_EQ(root->left->right->parent, root->left);
}

TEST(BinaryTreeTest, RemoveOneLeftChild) {
    BinaryTree<int> tree;
    std::vector nodes = {10, 5, 20, 3};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    tree.Remove(5);

    EXPECT_EQ(tree.GetSize(), 3u);
    EXPECT_EQ(tree.Find(5), nullptr);

    auto *root = tree.GetRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);

    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->right->value, 20);
    EXPECT_EQ(root->left->value, 3);
    EXPECT_EQ(root->left->parent, root);
    EXPECT_EQ(root->right->parent, root);
    EXPECT_EQ(root->left->left, nullptr);
}

TEST(BinaryTreeTest, RemoveOneRightChild) {
    BinaryTree<int> tree;
    std::vector<int> nodes = {10, 5, 20, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    tree.Remove(20);

    EXPECT_EQ(tree.GetSize(), 3u);
    EXPECT_EQ(tree.Find(20), nullptr);

    auto *root = tree.GetRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);

    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->left->value, 5);
    EXPECT_EQ(root->right->value, 25);
    EXPECT_EQ(root->right->right, nullptr);
    
    EXPECT_EQ(root->right->parent, root);
}

TEST(BinaryTreeTest, RemoveTwoChildren) {
    BinaryTree<int> tree;
    std::vector<int> nodes = {10, 5, 20, 3, 7, 15, 25};

    for (auto node : nodes) {
        tree.Insert(node);
    }

    tree.Remove(10);

    EXPECT_EQ(tree.GetSize(), 6u);
    EXPECT_EQ(tree.Find(10), nullptr);

    auto *root = tree.GetRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->left->left, nullptr);
    ASSERT_NE(root->left->right, nullptr);
    ASSERT_NE(root->right->right, nullptr);

    EXPECT_EQ(root->value, 15);
    EXPECT_EQ(root->left->value, 5);
    EXPECT_EQ(root->left->left->value, 3);
    EXPECT_EQ(root->left->right->value, 7);
    EXPECT_EQ(root->right->value, 20);
    EXPECT_EQ(root->right->right->value, 25);

    EXPECT_EQ(root->right->left, nullptr);

    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->left->parent, root);
    EXPECT_EQ(root->right->parent, root);
    EXPECT_EQ(root->right->right->parent, root->right);
}

TEST(BinaryTreeTest, RemoveDeepSuccessor) {
    BinaryTree<int> tree;
    std::vector<int> nodes = {50, 30, 80, 60, 90, 70, 65, 75, 68};

    for (auto node : nodes) {
        tree.Insert(node);
    }

    tree.Remove(50);

    EXPECT_EQ(tree.GetSize(), 8u);
    EXPECT_EQ(tree.Find(50), nullptr);

    auto *root = tree.GetRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->right->right, nullptr);
    ASSERT_NE(root->right->left, nullptr);
    ASSERT_NE(root->right->left->right, nullptr);
    ASSERT_NE(root->right->left->left, nullptr);
    ASSERT_NE(root->right->left->left->right, nullptr);

    EXPECT_EQ(root->value, 60);
    EXPECT_EQ(root->left->value, 30);
    EXPECT_EQ(root->right->value, 80);
    EXPECT_EQ(root->right->right->value, 90);
    EXPECT_EQ(root->right->left->value, 70);
    EXPECT_EQ(root->right->left->right->value, 75);
    EXPECT_EQ(root->right->left->left->value, 65);
    EXPECT_EQ(root->right->left->left->right->value, 68);

    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->left->parent, root);
    EXPECT_EQ(root->right->parent, root);
    EXPECT_EQ(root->right->right->parent, root->right);
    EXPECT_EQ(root->right->left->parent, root->right);
    EXPECT_EQ(root->right->left->right->parent, root->right->left);

    EXPECT_EQ(root->right->left->left->left, nullptr);
    EXPECT_EQ(root->right->left->left->parent, root->right->left);
    EXPECT_EQ(root->right->left->left->right->parent, root->right->left->left);
}

TEST(BinaryTreeTest, RemoveRootWithChild) {
    BinaryTree<int> tree;
    std::vector<int> nodes = {10, 5, 3, 6};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    tree.Remove(10);

    EXPECT_EQ(tree.GetSize(), 3u);
    EXPECT_EQ(tree.Find(10), nullptr);

    auto *root = tree.GetRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->left, nullptr);

    EXPECT_EQ(root->value, 5);
    EXPECT_EQ(root->right->value, 6);
    EXPECT_EQ(root->left->value, 3);

    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->right->parent, root);
    EXPECT_EQ(root->left->parent, root);
}

TEST(BinaryTreeTest, RemoveRootWithoutChild) {
    BinaryTree<int> tree;
    tree.Insert(10);

    tree.Remove(10);

    EXPECT_EQ(tree.GetSize(), 0u);
    EXPECT_EQ(tree.Find(10), nullptr);
    EXPECT_EQ(tree.GetRoot(), nullptr);
    EXPECT_TRUE(tree.IsEmpty());
}

TEST(BinaryTreeTest, RemoveNonExistent) {
    BinaryTree<int> tree;
    std::vector<int> nodes = {10, 5, 20, 3};

    for (auto node : nodes) {
        tree.Insert(node);
    }
    EXPECT_THROW(tree.Remove(6), std::logic_error);
    EXPECT_EQ(tree.GetSize(), 4u);
    EXPECT_TRUE(tree.Contains(10));
    EXPECT_TRUE(tree.Contains(5));
    EXPECT_TRUE(tree.Contains(20));
    EXPECT_TRUE(tree.Contains(3));
}

TEST(BinaryTreeTest, RemoveNonExistentEmptyTree) {
    BinaryTree<int> tree;

    EXPECT_THROW(tree.Remove(123), std::logic_error);
    EXPECT_EQ(tree.GetSize(), 0u);
}

TEST(BinaryTreeTest, CopyIndependence) {
    BinaryTree<int> tree;
    BinaryTree<int> tree2;
    std::vector nodes = {10, 5, 20, 3, 7, 6, 8, 15, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    tree2 = tree;
 
    tree.Remove(7);

    EXPECT_NE(tree.GetRoot(), tree2.GetRoot());
    EXPECT_EQ(tree.GetSize(), 8u);
    EXPECT_EQ(tree2.GetSize(), 9u);

    EXPECT_FALSE(tree.Contains(7));
    EXPECT_TRUE(tree2.Contains(7));
}

TEST(BinaryTreeTest, ClearTree) {
    BinaryTree<int> tree;
    std::vector<int> nodes = {50, 30, 80, 60, 90, 70, 65, 75, 68};

    for (auto node : nodes) {
        tree.Insert(node);
    }
    tree.Clear();

    EXPECT_EQ(tree.GetSize(), 0u);
    EXPECT_EQ(tree.GetRoot(), nullptr);
    EXPECT_TRUE(tree.IsEmpty());
    EXPECT_EQ(tree.Find(50), nullptr);

    tree.Clear();

    tree.Insert(10);

    ASSERT_NE(tree.GetRoot(), nullptr);
    EXPECT_EQ(tree.GetRoot()->value, 10);
    EXPECT_NE(tree.Find(10), nullptr);
    EXPECT_EQ(tree.GetSize(), 1u);
}

TEST(BinaryTreeTest, WhereEven) {
    BinaryTree<int> tree;
    std::vector<int> nodes = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> temp = tree.Where(IsEven);

    EXPECT_EQ(temp.GetSize(), 5u);
    
    auto *root = temp.GetRoot();

    EXPECT_EQ(root->value, 2);
    EXPECT_EQ(root->right->value, 4);
    EXPECT_EQ(root->right->right->value, 6);
    EXPECT_EQ(root->right->right->right->value, 8);
    EXPECT_EQ(root->right->right->right->right->value, 10);
}

TEST(BinaryTreeTest, WhereNone) {
    BinaryTree<int> tree;
    std::vector<int> nodes = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> temp = tree.Where(IsNone);

    EXPECT_EQ(temp.GetSize(), 0u);
    EXPECT_EQ(temp.GetRoot(), nullptr);
}

TEST(BinaryTreeTest, WhereAll) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {10, 5, 15, 20, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> temp = tree.Where(IsAll);

    EXPECT_EQ(temp.GetSize(), 5u);

    auto *root = temp.GetRoot();
    EXPECT_EQ(root->value, 5);
    EXPECT_EQ(root->right->value, 10);
    EXPECT_EQ(root->right->right->value, 15);
    EXPECT_EQ(root->right->right->right->value, 20);
    EXPECT_EQ(root->right->right->right->right->value, 25);
}

TEST(BinaryTreeTest, MapSquare) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {10, 5, 15, 20, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> temp = tree.Map(Square);

    EXPECT_EQ(temp.GetSize(), 5u);

    auto *root = temp.GetRoot();
    EXPECT_EQ(root->value, 5*5);
    EXPECT_EQ(root->right->value, 10*10);
    EXPECT_EQ(root->right->right->value, 15*15);
    EXPECT_EQ(root->right->right->right->value, 20*20);
    EXPECT_EQ(root->right->right->right->right->value, 25*25);
}

TEST(BinaryTreeTest, MapEmptyTree) {
    BinaryTree<int> tree;
    
    BinaryTree<int> temp = tree.Map(Square);

    EXPECT_EQ(temp.GetSize(), 0u);
    EXPECT_TRUE(temp.IsEmpty());
    EXPECT_EQ(temp.GetRoot(), nullptr);
}

TEST(BinaryTreeTest, MapIdentity) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {10, 5, 15, 20, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> temp = tree.Map(Identity);
    EXPECT_EQ(temp.GetSize(), 5u);

    auto *root = temp.GetRoot();
    EXPECT_EQ(root->value, 5);
    EXPECT_EQ(root->right->value, 10);
    EXPECT_EQ(root->right->right->value, 15);
    EXPECT_EQ(root->right->right->right->value, 20);
    EXPECT_EQ(root->right->right->right->right->value, 25);
}

TEST(BinaryTreeTest, MapDuplicates) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {10, 5, 15, 20, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> temp = tree.Map(Constant);

    EXPECT_EQ(temp.GetSize(), 1u);
    EXPECT_EQ(temp.GetRoot()->value, 42);
}

TEST(BinaryTreeTest, MapNegative) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {10, 5, 15, 20, 25};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> temp = tree.Map(Negate);

    EXPECT_EQ(temp.GetSize(), 5u);
    auto *root = temp.GetRoot();

    EXPECT_EQ(root->value, -5);
    EXPECT_EQ(root->left->value, -10);
    EXPECT_EQ(root->left->left->value, -15);
    EXPECT_EQ(root->left->left->left->value, -20);
    EXPECT_EQ(root->left->left->left->left->value, -25);
}

TEST(BinaryTreeTest, ReduceSum) {
    BinaryTree<int> tree;
    int sum = 0;
    std::vector<int> nodes = {10, 5, 15, 20, 25};
    for (auto node : nodes) {
        tree.Insert(node);
        sum += node;
    }

    int result = tree.Reduce(Sum, 0);

    EXPECT_EQ(result, sum);
}

TEST(BinaryTreeTest, ReduceMultiply) {
    BinaryTree<int> tree;
    int mult = 1;
    std::vector<int> nodes = {10, 5, 15, 20, 25};
    for (auto node : nodes) {
        tree.Insert(node);
        mult *= node;
    }

    int result = tree.Reduce(Mult, 1);

    EXPECT_EQ(result, mult);
}

TEST(BinaryTreeTest, ReduceEmptyTree) {
    BinaryTree<int> tree;

    int result = tree.Reduce(Mult, 1);

    EXPECT_EQ(result, 1);
}

TEST(BinaryTreeTest, ReduceInitialValue) {
    BinaryTree<int> tree;

    tree.Insert(10);
    tree.Insert(20);

    EXPECT_EQ(tree.Reduce(Sum, 100), 130);
}
