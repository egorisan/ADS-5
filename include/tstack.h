// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

#include <array>
#include <stdexcept>

template <typename T, int size>
class TStack {
 private:
  static_assert(size > 0, "stack size must be positive");
  static constexpr int kStackSize = size;

  std::array<T, kStackSize> data_;
  int top_index_;

 public:
  TStack() : top_index_(-1) {}

  void push(const T& value) {
    if (full()) throw std::overflow_error("stack overflow");
    data_[++top_index_] = value;
  }

  void pop() {
    if (empty()) throw std::underflow_error("stack underflow");
    --top_index_;
  }

  T& top() {
    if (empty()) throw std::underflow_error("stack is empty");
    return data_[top_index_];
  }

  const T& top() const {
    if (empty()) throw std::underflow_error("stack is empty");
    return data_[top_index_];
  }

  int count() const { return top_index_ + 1; }
  bool empty() const { return top_index_ < 0; }
  bool full() const { return top_index_ == kStackSize - 1; }
};

#endif  // INCLUDE_TSTACK_H_

