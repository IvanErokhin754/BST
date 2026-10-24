#ifndef STACK_HPP
#define STACK_HPP

#include "DynamicArray.hpp"

template<typename T> 
class Stack {
private:
    DynamicArray<T> data;

public:
    Stack() : data() {}

    void Push(const T& value) {
        data.PushBack(value);
    }

    void Pop() {
        if (data.GetSize() == 0)
            throw std::out_of_range("Stack is empty");
        data.PopBack();
    }
    
    const T& Get() const {
        if (data.GetSize() == 0)
            throw std::out_of_range("Stack is empty");
        return data[data.GetSize() - 1];
    }

    size_t GetSize() const {
        return data.GetSize();
    }

    bool IsEmpty() const {
        return data.GetSize() == 0;
    }
};

#endif /* STACK_HPP */
