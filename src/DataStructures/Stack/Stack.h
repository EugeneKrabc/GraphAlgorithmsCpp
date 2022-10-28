#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_STACK_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_STACK_H

#include "stack"  // TEMPORARY

namespace s21 {

class Stack {
 public:
    static Stack init();
    void push(const int value);
    int pop();
    int peek() const;
    bool empty() const;

 private:
    Stack();
    std::stack<int> stack_;  // TEMPORARY

};

}  // namespace s21


#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_STACK_H
