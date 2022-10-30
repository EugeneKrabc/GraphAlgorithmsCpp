#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_QUEUE_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_QUEUE_H

#include "../AbstractList.h"

namespace s21 {

class Queue: public AbstractList {
 public:
    static Queue* init();
    void push(int value);
    int pop();
    int peek() const;
    bool empty() const;

 private:
    Queue();
};

}


#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_QUEUE_H
