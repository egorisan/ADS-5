// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int size>
private:
    T data[size];
    int topIndex;

public:
    TStack() : topIndex(-1) {}

    bool IsEmpty() const {
        return topIndex == -1;
    }

    bool IsFull() const {
        return topIndex == size - 1;
    }

    void Push(const T& value) {
        if (IsFull()) {
            throw std::overflow_error("Stack overflow");
        }
        data[++topIndex] = value;
    }

    T Pop() {
        if (IsEmpty()) {
            throw std::underflow_error("Stack underflow");
        }
        return data[topIndex--];
    }

    T Top() const {
        if (IsEmpty()) {
            throw std::underflow_error("Stack is empty");
        }
        return data[topIndex];
    }
};

#endif  // INCLUDE_TSTACK_H_
