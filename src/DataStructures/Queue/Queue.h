//
// Created by Curran Carr on 10/28/22.
//

#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_QUEUE_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_QUEUE_H

#include "queue"  // TEMPORARY

namespace s21 {

class Queue {
 public:
    static Queue init();
    void push(int value);
    int pop();
    int peek() const;

 private:
    Queue();
    std::queue<int> queue_;  // TEMPORARY
};

}


#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_QUEUE_H
