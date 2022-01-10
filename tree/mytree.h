#ifndef MYTREE_H
#define MYTREE_H

#include <vector>

struct Node
{
    Node(int value = 0) : value_(value), next_(nullptr),
        parent_(nullptr), firstChildren_(nullptr) {}

    int value_;
    Node	*next_;
    Node	*parent_;
    Node	*firstChildren_;
};

class MyTree
{
public:
    MyTree();

    Node* DeleteNodes(Node *temp);

    void pushRoot(int value);
    void pushChildrenNode(int value, Node *parent);
    void popChildrenNode(Node *parent);
    Node *searh(int value, Node *temp);

    Node *root() const;

private:
    Node *root_ = nullptr; //корень дерева
    void pushBrother(Node *temp, Node *parent);
};

#endif // MYTREE_H
