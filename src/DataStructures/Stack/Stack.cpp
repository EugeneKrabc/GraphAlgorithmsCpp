#include "Stack.h"

namespace s21 {

Stack::Stack() { stack_ = std::stack<int>(); }

Stack Stack::init() { return Stack(); }

void Stack::push(const int value) { stack_.push(value); }

int Stack::pop() {
  int ret = stack_.top();
  stack_.pop();
  return ret;
}

int Stack::peek() const { return stack_.top(); }

} // namespace s21