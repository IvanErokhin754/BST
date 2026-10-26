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
    EXPECT_FALSE(tree.IsEmpty());
    EXPECT_EQ(tree.GetSize(), 9u);

    std::vector<int> values = {10, 5, 20, 3, 7, 6, 8, 15, 25};

    for (int value : values) {
        EXPECT_TRUE(tree.Contains(value));
    }
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
    std::vector nodes = {10, 5, 20, 3, 7, 6};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    tree.Remove(6);

    EXPECT_EQ(tree.GetSize(), 5u);

    auto *root = tree.GetRoot();

    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->left->left, nullptr);
    ASSERT_NE(root->right->right, nullptr);

    EXPECT_EQ(root->value, 7);
    EXPECT_EQ(root->left->value, 5);
    EXPECT_EQ(root->right->value, 10);
    EXPECT_EQ(root->left->left->value, 3);
    EXPECT_EQ(root->right->right->value, 20);
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

TEST(BinaryTreeTest, RemoveRootWithChild) {
    BinaryTree<int> tree;

    tree.Insert(10);
    tree.Insert(5);

    tree.Remove(10);

    ASSERT_NE(tree.GetRoot(), nullptr);
    EXPECT_EQ(tree.GetRoot()->value, 5);
    EXPECT_EQ(tree.GetRoot()->parent, nullptr);
    EXPECT_EQ(tree.GetSize(), 1u);
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

    EXPECT_EQ(root->value, 4);
    EXPECT_EQ(root->left->value, 2);
    EXPECT_EQ(root->right->value, 8);
    EXPECT_EQ(root->right->left->value, 6);
    EXPECT_EQ(root->right->right->value, 10);
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
    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->left->value, 5);
    EXPECT_EQ(root->right->value, 20);
    EXPECT_EQ(root->right->left->value, 15);
    EXPECT_EQ(root->right->right->value, 25);
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
    EXPECT_EQ(root->value, 10 * 10);
    EXPECT_EQ(root->left->value, 5 * 5);
    EXPECT_EQ(root->right->value, 20 * 20);
    EXPECT_EQ(root->right->left->value, 15 * 15);
    EXPECT_EQ(root->right->right->value, 25 * 25);
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
    EXPECT_EQ(root->value, 10);
    EXPECT_EQ(root->left->value, 5);
    EXPECT_EQ(root->right->value, 20);
    EXPECT_EQ(root->right->left->value, 15);
    EXPECT_EQ(root->right->right->value, 25);
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

    EXPECT_EQ(root->value, -10);
    EXPECT_EQ(root->left->value, -20);
    EXPECT_EQ(root->left->left->value, -25);
    EXPECT_EQ(root->left->right->value, -15);
    EXPECT_EQ(root->right->value, -5);
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

TEST(BinaryTreeTest, InsertAVL_LL) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {30, 20, 10};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    EXPECT_EQ(tree.GetSize(), 3u);

    auto *root = tree.GetRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);

    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->left->parent, root);
    EXPECT_EQ(root->right->parent, root);

    EXPECT_EQ(root->value, 20);
    EXPECT_EQ(root->left->value, 10);
    EXPECT_EQ(root->right->value, 30);
}

TEST(BinaryTreeTest, InsertAVL_RR) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {10, 20, 30};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    EXPECT_EQ(tree.GetSize(), 3u);

    auto *root = tree.GetRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);

    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->left->parent, root);
    EXPECT_EQ(root->right->parent, root);

    EXPECT_EQ(root->value, 20);
    EXPECT_EQ(root->left->value, 10);
    EXPECT_EQ(root->right->value, 30);
}

TEST(BinaryTreeTest, InsertAVL_LR) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {30, 10, 20};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    EXPECT_EQ(tree.GetSize(), 3u);

    auto *root = tree.GetRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);

    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->left->parent, root);
    EXPECT_EQ(root->right->parent, root);

    EXPECT_EQ(root->value, 20);
    EXPECT_EQ(root->left->value, 10);
    EXPECT_EQ(root->right->value, 30);
}

TEST(BinaryTreeTest, InsertAVL_RL) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {10, 30, 20};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    EXPECT_EQ(tree.GetSize(), 3u);

    auto *root = tree.GetRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);


    EXPECT_EQ(root->value, 20);
    EXPECT_EQ(root->left->value, 10);
    EXPECT_EQ(root->right->value, 30);
}

TEST(BinaryTreeTest, RemoveAVL_RebalanceLL) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {30, 20, 40, 10};

    for (auto node : nodes) {
        tree.Insert(node);
    }

    tree.Remove(40);

    EXPECT_EQ(tree.GetSize(), 3u);

    auto *root = tree.GetRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);

    EXPECT_EQ(root->value, 20);
    EXPECT_EQ(root->left->value, 10);
    EXPECT_EQ(root->right->value, 30);

    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->left->parent, root);
    EXPECT_EQ(root->right->parent, root);

    EXPECT_EQ(tree.GetHeight(root), 1);
    EXPECT_EQ(tree.GetHeight(root->left), 0);
    EXPECT_EQ(tree.GetHeight(root->right), 0);
    EXPECT_EQ(tree.GetBalanceFactor(root), 0);

    EXPECT_FALSE(tree.Contains(40));
}

TEST(BinaryTreeTest, RemoveAVL_SuccessorRebalance) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 60, 80, 90};

    for (auto value : nodes)
        tree.Insert(value);

    tree.Remove(50);

    auto* root = tree.GetRoot();

    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->right->left, nullptr);
    ASSERT_NE(root->right->right, nullptr);

    EXPECT_EQ(root->value, 60);
    EXPECT_EQ(root->right->value, 80);
    EXPECT_EQ(root->right->left->value, 70);
    EXPECT_EQ(root->right->right->value, 90);

    EXPECT_EQ(tree.GetSize(), 6u);
    EXPECT_FALSE(tree.Contains(50));
    EXPECT_EQ(tree.GetBalanceFactor(root->right), 0);
}

TEST(BinaryTreeTest, RemoveAVL_ZeroBalanceChild) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {30, 20, 40, 10, 25};
    for (auto node : nodes)
        tree.Insert(node);

    tree.Remove(40);

    auto* root = tree.GetRoot();

    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->right->left, nullptr);

    EXPECT_EQ(root->value, 20);
    EXPECT_EQ(root->left->value, 10);
    EXPECT_EQ(root->right->value, 30);
    EXPECT_EQ(root->right->left->value, 25);

    EXPECT_EQ(tree.GetSize(), 4u);
    EXPECT_EQ(tree.GetBalanceFactor(root), -1);
}

TEST(BinaryTreeTest, ExtraсtSubtreeBasic) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> subtree = tree.ExtractSubtree(tree.GetRoot()->left);
    auto *root = subtree.GetRoot();

    
    EXPECT_EQ(subtree.GetSize(), 3u);

    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);
    ASSERT_NE(root->right, nullptr);

    EXPECT_EQ(root->value, 30);
    EXPECT_EQ(root->left->value, 20);
    EXPECT_EQ(root->right->value, 40);

    EXPECT_EQ(tree.GetSize(), 7u);
}

TEST(BinaryTreeTest, ExtractSubtreeDeepCopy) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> subtree = tree.ExtractSubtree(tree.GetRoot()->left);
    auto *root = subtree.GetRoot();
    auto *root2 = tree.GetRoot();

    ASSERT_NE(root, nullptr);
    ASSERT_NE(root2, nullptr);
    ASSERT_NE(root2->left, nullptr);
    ASSERT_NE(root2->left->left, nullptr);
    ASSERT_NE(root2->left->right, nullptr);

    EXPECT_NE(root, root2->left);
    EXPECT_NE(root->left, root2->left->left);
    EXPECT_NE(root->right, root2->left->right);
}

TEST(BinaryTreeTest, ExtractSubrtreeIndependence) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> subtree = tree.ExtractSubtree(tree.GetRoot()->left);

    subtree.Remove(20);

    EXPECT_EQ(tree.GetSize(), 7u);
    EXPECT_TRUE(tree.Contains(20));

    EXPECT_FALSE(subtree.Contains(20));
    EXPECT_EQ(subtree.GetSize(), 2u);
}

TEST(BinaryTreeTest, ExtractSubtreeParentAndHeight) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> subtree = tree.ExtractSubtree(tree.GetRoot()->left);

    auto *root = subtree.GetRoot();

    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->right, nullptr);
    ASSERT_NE(root->left, nullptr);

    EXPECT_EQ(root->parent, nullptr);
    EXPECT_EQ(root->left->parent, root);
    EXPECT_EQ(root->right->parent, root);

    EXPECT_EQ(root->height, 1);
    EXPECT_EQ(root->left->height, 0);
    EXPECT_EQ(root->right->height, 0);

    EXPECT_EQ(subtree.GetBalanceFactor(root), 0);
}

TEST(BinaryTreeTest, ExtractSubtreeNullptr) {
    BinaryTree<int> tree;
    BinaryTree<int> subtree = tree.ExtractSubtree(tree.GetRoot());

    EXPECT_EQ(subtree.GetSize(), 0u);
    EXPECT_EQ(subtree.GetRoot(), nullptr);
    EXPECT_TRUE(subtree.IsEmpty());
}

TEST(BinaryTreeTest, ExtractSubtreeRoot) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> subtree = tree.ExtractSubtree(tree.GetRoot());

    EXPECT_EQ(subtree.GetSize(), 7u);
    for (auto node : nodes) {
        EXPECT_TRUE(subtree.Contains(node));
        EXPECT_NE(subtree.Find(node), tree.Find(node));
    }
}

TEST(BinaryTreeTest, ExtractSubtreeLeaf) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> subtree = tree.ExtractSubtree(tree.GetRoot()->left->left);

    EXPECT_EQ(subtree.GetSize(), 1u);

    auto *root = subtree.GetRoot();
    ASSERT_NE(root, nullptr);

    EXPECT_EQ(root->value, 20);
    EXPECT_EQ(root->right, nullptr);
    EXPECT_EQ(root->left, nullptr);
}

TEST(BinaryTreeTest, ContainsSubtreeExisting) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> tree2;
    nodes = {30, 20, 40};
    for (auto node : nodes) {
        tree2.Insert(node);
    }

    EXPECT_TRUE(tree.ContainsSubtree(tree2));
    EXPECT_EQ(tree.GetSize(), 7u);
    EXPECT_EQ(tree2.GetSize(), 3u);
}

TEST(BinaryTreeTest, ContainsSubtreeStructureMismatch) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> tree2;
    nodes = {30, 20};
    for (auto node : nodes) {
        tree2.Insert(node);
    }

    auto *root = tree2.GetRoot();
    
    ASSERT_NE(root, nullptr);
    ASSERT_NE(root->left, nullptr);

    EXPECT_FALSE(tree.ContainsSubtree(tree2));
    EXPECT_TRUE(tree.Contains(root->value));
    EXPECT_TRUE(tree.Contains(root->left->value));
}

TEST(BinaryTreeTest, ContainsSubtreeRight) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> tree2;
    nodes = {70, 60, 80};
    for (auto node : nodes) {
        tree2.Insert(node);
    }

    EXPECT_TRUE(tree.ContainsSubtree(tree2));
}

TEST(BinaryTreeTest, ContainsSubtreeLeaf) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> tree2;
    nodes = {20};
    for (auto node : nodes) {
        tree2.Insert(node);
    }

    EXPECT_TRUE(tree.ContainsSubtree(tree2));
}

TEST(BinaryTreeTest, ContainsSubtreeWholeTree) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> tree2;
    for (auto node : nodes) {
        tree2.Insert(node);
    }
    
    EXPECT_TRUE(tree.ContainsSubtree(tree2));
}

TEST(BinaryTreeTest, ContainsSubtreeDifferentValues) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    nodes = {70, 60, 90};

    BinaryTree<int> tree2;

    for (auto node : nodes) {
        tree2.Insert(node);
    }

    EXPECT_FALSE(tree.ContainsSubtree(tree2));
}

TEST(BinaryTreeTest, ContainsSubtreeEmpty1) {
    BinaryTree<int> tree;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    BinaryTree<int> tree2;

    EXPECT_TRUE(tree.ContainsSubtree(tree2));
}

TEST(BinaryTreeTest, ContainsSubtreeEmpty2) {
    BinaryTree<int> tree2;

    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree2.Insert(node);
    }

    BinaryTree<int> tree;

    EXPECT_FALSE(tree.ContainsSubtree(tree2));
}

TEST(BinaryTreeTest, ContainsSubtreeEmpty3) {
    BinaryTree<int> tree;
    BinaryTree<int> tree2;

    EXPECT_TRUE(tree.ContainsSubtree(tree2));
}

TEST(BinaryTreeTest, ContainsSubtreeNotFound) {
    BinaryTree<int> tree;
    
    std::vector<int> nodes = {50, 30, 70, 20, 40, 60, 80};
    for (auto node : nodes) {
        tree.Insert(node);
    }

    nodes = {100, 90, 110};

    BinaryTree<int> tree2;
    for (auto node : nodes) {
        tree2.Insert(node);
    }

    EXPECT_FALSE(tree.ContainsSubtree(tree2));
}

TEST(BinaryTreeTest, ContainsSubtreeSameValuesDifferentStructure) {
    BinaryTree<int> tree;
    BinaryTree<int> tree2;

    std::vector<int> nodes = {30, 20, 40, 10, 50};

    for (auto node : nodes) {
        tree.Insert(node);
    }

    nodes = {30, 10, 50, 20, 40};

    for (auto node : nodes) {
        tree2.Insert(node);
    }

    EXPECT_FALSE(tree.ContainsSubtree(tree2));
    EXPECT_FALSE(tree2.ContainsSubtree(tree));
}