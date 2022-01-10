#include "mytree.h"
#include <iostream>

MyTree::MyTree()
{
}

Node* MyTree::DeleteNodes(Node *temp)
{
    static Node* nodeUncle = nullptr;
    static bool nodeUncleTrue = false;

    if (temp->firstChildren_ && temp->next_)
    {
        nodeUncleTrue = true;
        nodeUncle = temp->next_;
        Node* tempNext = temp->firstChildren_;
        delete temp;
        return DeleteNodes(tempNext);
    }
    if (temp->firstChildren_)
    {
        Node* tempNext = temp->firstChildren_;
        delete temp;
        return DeleteNodes(tempNext);
    }
    if (temp->next_)
    {
        Node* tempNext = temp->firstChildren_;
        delete temp;
        return DeleteNodes(tempNext);
    }
    if (nodeUncleTrue)
    {
        nodeUncleTrue = false;
        Node* tempNext = temp->firstChildren_;
        delete temp;
        return DeleteNodes(tempNext);
    }
}

void MyTree::pushRoot(int value)
{
    Node *newNode = new Node(value);
    root_ = newNode;
}

void MyTree::pushChildrenNode(int value, Node *parent)
{
    Node *newNode = new Node(value);
    newNode->parent_ = parent;

    //no children
    if (parent->firstChildren_ == nullptr)
    {
        parent->firstChildren_ = newNode;
    }
    else
        pushBrother(newNode, parent);
}

void MyTree::pushBrother(Node* newNode, Node* parent)
{
    Node *temp = parent->firstChildren_;
    while (temp->next_ != nullptr)
        temp = temp->next_;
    temp->next_ = newNode;
}

void MyTree::popChildrenNode(Node *child)
{
    //oigul подумать про удаление root
   Node* temp = child->parent_->firstChildren_;

    if (temp == child)
    {
        child->parent_->firstChildren_ = child->next_;
    }
    else
    {
        while (temp->next_ != child)
        { // the node preceding child
            temp = temp->next_;
        }

        temp->next_ = child->next_;
    }
    //oigul если есть дети? если есть ребенок, то первый ребенок становится родителем, например
    delete child;
}


Node* MyTree::searh(int value, Node* temp)
{
    static Node* nodeUncle = nullptr;
    static bool nodeUncleTrue = false;

    if (temp->value_ == value)
    {
        std::cout << std::endl << std::endl << temp->value_ << " ";
        return temp;
    }

    if(temp == root_)
    {
        //for a new search
        nodeUncleTrue = false;
    }
    if (temp->firstChildren_ && temp->next_)
    {
        nodeUncleTrue = true;
        nodeUncle = temp->next_;
        return searh(value, temp->firstChildren_);
    }
    if (temp->firstChildren_)
    {
        return searh(value, temp->firstChildren_);
    }
    if (temp->next_)
    {
        return searh(value, temp->next_);
    }
    if (nodeUncleTrue)
    {
        nodeUncleTrue = false;
        return searh(value, nodeUncle);
    }

    return nullptr;
}

Node *MyTree::root() const
{
    return root_;
}
