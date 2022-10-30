#include "Queue.h"

namespace s21 {

Queue::Queue() : AbstractList() { queue_ = std::queue<int>(); }

Queue* Queue::init() { return new Queue(); }

void Queue::push(int value) { queue_.push(value); }

int Queue::pop() {
  int ret = queue_.front();
  queue_.pop();
  return ret;
}

int Queue::peek() const { return queue_.front(); }

bool Queue::empty() const {
    return queue_.empty();
}

} // namespace s21