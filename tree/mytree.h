#ifndef MYTREE_H
#define MYTREE_H

#include <iostream>
#include <vector>

struct Node
{
    Node(int value = 0) : value_(value), next_(nullptr),
                          parent_(nullptr), firstChildren_(nullptr) {}
    ~Node() {std::cout << "~Node " << value_<<std::endl;}

    int value_;
    Node* next_;
    Node* parent_;
    Node* firstChildren_;
};

class MyTree
{
public:
    MyTree();
    ~MyTree();

    Node* DeleteNodes(Node *temp);

    void pushRoot(int value);
    void pushNode(int value, Node *parent);
    void popChildrenNode(Node *parent);
    Node* searh(int value, Node *temp);
    void print();

    Node *root() const;

private:
    Node* root_ = nullptr;
    void pushBrother(Node *temp, Node *parent);
    void becomeParentForRoot(Node *firstChildren);
    void becomeParentForNode(Node *firstCh);
    Node *print(Node *temp);
};

#endif // MYTREE_H



