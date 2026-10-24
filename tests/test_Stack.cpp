#include "Stack.hpp"
#include <gtest/gtest.h>

TEST(StackTest, CreateStack) {
    Stack<int> stack;
    
    EXPECT_EQ(stack.GetSize(), 0u);
    EXPECT_THROW(stack.Get(), std::out_of_range);
    EXPECT_THROW(stack.Pop(), std::out_of_range);
}

TEST(StackTest, PushStack) {
    Stack<int> stack;

    for (size_t i = 0; i < 100; i++) {
        stack.Push(i);
        EXPECT_EQ(stack.Get(), i);
    }

    EXPECT_EQ(stack.GetSize(), 100u);
}

TEST(StackTest, PopStack) {
    Stack<int> stack;

    for (size_t i = 0; i < 100; i++) {
        stack.Push(i);
    }

    for (size_t i = 0; i < 100; i++) {
        EXPECT_EQ(stack.Get(), 100 - i - 1);
        stack.Pop();
    }

    EXPECT_EQ(stack.GetSize(), 0u);
    EXPECT_THROW(stack.Pop(), std::out_of_range);
    EXPECT_THROW(stack.Get(), std::out_of_range);
}   

TEST(StackTest, MergeOperationsStack) {
    Stack<int> stack;

    stack.Push(10);
    stack.Push(20);

    stack.Pop();

    stack.Push(30);

    EXPECT_EQ(stack.Get(), 30);
    EXPECT_EQ(stack.GetSize(), 2u);
}

