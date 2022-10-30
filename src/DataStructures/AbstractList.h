

#ifndef A2_SIMPLENAVIGATOR_V1_0_0_MASTER_ABSTRACTLIST_H
#define A2_SIMPLENAVIGATOR_V1_0_0_MASTER_ABSTRACTLIST_H


namespace s21 {
class AbstractList {

 public:
    virtual ~AbstractList() {}
    virtual void push(int value) = 0;
    virtual int pop() = 0;
    virtual int peek() const = 0;
    virtual bool empty() const = 0;

};
}



#endif //A2_SIMPLENAVIGATOR_V1_0_0_MASTER_ABSTRACTLIST_H
