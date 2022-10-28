//
// Created by Curran Carr on 10/28/22.
//

#include "Queue.h"


namespace s21 {

Queue::Queue() {
    queue_ = std::queue<int>();
}

Queue Queue::init() {
    return Queue();
}

void Queue::push(int value) {
    queue_.push(value);
}

int Queue::pop() {
    int ret = queue_.front();
    queue_.pop();
    return ret;
}

int Queue::peek() const {
    return queue_.front();
}


}  // namespace s21