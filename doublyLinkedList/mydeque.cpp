#include "mydeque.h"
#include <iostream>

Node* myDeque::searh(int value)
{
    Node* node = head_;
    while (node != nullptr && node->value_ != value)
        node = node->next_;
    return node;
}

void myDeque::push(Node* node)
{
   node->next_ = head_;
   if (head_ != nullptr)
       head_->previous_ = node;
   head_ = node;
   node->previous_ = nullptr;
}

void myDeque::pop(Node* node)
{
    if(node->previous_ != nullptr)
        node->previous_->next_ = node->next_;
    else
        head_ = node->next_;
    if (node->next_ != nullptr)
        node->next_->previous_ = node->previous_;
}

void myDeque::print()
{
    Node *temp = head_;
    while(temp != nullptr)
    {
        std::cout << temp->value_ << " ";
        temp = temp->next_;
    }
    std::cout << std::endl;
}
