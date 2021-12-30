#ifndef MYDEQUE_H
#define MYDEQUE_H

//структура узла
struct Node
{
    Node(int value = 0) : value_(value), next_(nullptr), previous_(nullptr) {}

    int value_;
    Node* next_;
    Node* previous_;
};

class myDeque
{
public:
    myDeque() : head_(nullptr) {}

    Node* searh(int value);
    void push(Node* node);
    void pop(Node* node);
    void print();
private:
    Node *head_;
};

#endif // MYDEQUE_H
