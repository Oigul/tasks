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
    //удаление root
    if(child == root_)
    {
        if(root_->firstChildren_)
        {
            Node* firstChild = root_->firstChildren_;
            firstChild->parent_ = nullptr;
            delete child;
            //первый ребенок становится родителем, меняются братья и братья детей
            becomeParentForRoot(firstChild);
        }
    }
    //end root
    else
    {
        //есди просто листок без детей и братьев
        if(child->firstChildren_ == nullptr && child->next_ == nullptr)
        {
            child->parent_->firstChildren_ = nullptr;
            delete child;
            return;
        }
        //удаление листочка без деток, но с братьями
        if(child->firstChildren_ == nullptr)
        {
            Node* temp = child->parent_->firstChildren_;
            if (temp == child)
            {
                //если это первый ребенок, то первым ребенком становится следующий брат
                child->parent_->firstChildren_ = child->next_;
            }
            else
            {
                while (temp->next_ != child)
                { // the node preceding child
                    temp = temp->next_;
                }
                //иначе находим участок, в котором надо затереть ребенка
                temp->next_ = child->next_;
            }
            delete child;
            return;
        }
        else //есть дети
        {
            //Первый ребенок становится родителем своим братьям и братом дядям
            //child->parent_->firstChildren_;
            becomeParentForNode(child->firstChildren_);
        }
        //        delete child;
    }
}

Node *MyTree::becomeParentForNode(Node *firstGS)
{
    //если нет дядь, нет братьев
    if(firstGS->parent_->next_ == nullptr && firstGS->next_ == nullptr)
    {
        Node* temp = firstGS->parent_;
        firstGS->parent_->parent_->firstChildren_ = firstGS;
        firstGS->parent_ = firstGS->parent_->parent_;
        delete temp;
        //oigul возвращать что-нибудь в это жизни или нет
        return firstGS;
    }
    //есть брат, нет дядь
    if(firstGS->parent_->next_ == nullptr && firstGS->next_)
    {
        Node* temp = firstGS->parent_;
        firstGS->parent_->parent_->firstChildren_ = firstGS;
        firstGS->parent_ = firstGS->parent_->parent_;
        delete temp;
        firstGS->firstChildren_ = firstGS->next_;
        //cтановится родителем братьям
        temp = firstGS->firstChildren_;
        while(temp != nullptr)
        {
            temp->parent_ = firstGS;
            temp = temp->next_;
        }
        firstGS->next_ = nullptr;
        //oigul возвращать что-нибудь в это жизни или нет
        return firstGS;
    }
    //есть 1 брат и дяди
    if(firstGS->parent_->next_ && firstGS->next_ == nullptr)
    {
        Node* temp = firstGS->parent_;
        firstGS->parent_->parent_->firstChildren_ = firstGS;
        firstGS->parent_ = temp->parent_;
        firstGS->next_ = temp->next_;
        delete temp;
        return firstGS;
    }
    //есть братья и дяди
    if(firstGS->parent_->next_ && firstGS->next_)
    {
        Node* temp = firstGS->parent_;
        firstGS->parent_->parent_->firstChildren_ = firstGS;
        firstGS->parent_ = temp->parent_;
        firstGS->firstChildren_ = firstGS->next_;
        firstGS->next_ = temp->next_;
        delete temp;

        //cтановится родителем братьям
        temp = firstGS->firstChildren_;
        while(temp != nullptr)
        {
            temp->parent_ = firstGS;
            temp = temp->next_;
        }

        return firstGS;
    }
}

Node* MyTree::becomeParentForRoot(Node* firstChildren)
{
    if(firstChildren->parent_ == nullptr)   //root
    {
        root_ = firstChildren;

        //если нет ребенка, но есть брат, то брат первого ребенка становится первым ребенком
        if (firstChildren->firstChildren_ == nullptr && firstChildren->next_)
        {
            firstChildren->firstChildren_ = firstChildren->next_;

            //новый отец у братьев
            Node* temp = firstChildren;
            while(temp->next_ != nullptr)
            {
                temp = temp->next_;
                temp->parent_ = firstChildren;
            }
            firstChildren->next_ = nullptr;
        }
        else
        {
            //есть брат и ребенок, но у ребенка нет братьев
            if (firstChildren->firstChildren_
                    && firstChildren->firstChildren_->next_ == nullptr
                    && firstChildren->next_)
            {
                firstChildren->firstChildren_->next_ = firstChildren->next_;
                //новый родитель у братьев
                Node* temp = firstChildren;
                while(temp->next_ != nullptr)
                {
                    temp = temp->next_;
                    temp->parent_ = firstChildren;
                }
                firstChildren->next_ = nullptr;
            }
            else
            //есть брат и ребенок с братьями,
            //ребенок становится братом брата (дядей), а брат ребенка становится первым ребенком ребенка
            {
                if (firstChildren->firstChildren_ && firstChildren->firstChildren_->next_ && firstChildren->next_)
                {

                    //первым ребенком ребенка становится брат ребенка ребенка
                    firstChildren->firstChildren_->firstChildren_ = firstChildren->firstChildren_->next_;
                    //первый ребенок становится дядей
                    firstChildren->firstChildren_->next_ = firstChildren->next_ ;

                    //новый родитель у братьев
                    Node* temp = firstChildren;
                    while(temp->next_ != nullptr)
                    {
                        temp = temp->next_;
                        temp->parent_ = firstChildren;
                    }
                    firstChildren->next_ = nullptr;

                    //новый родитель у внуков
                    temp = firstChildren->firstChildren_->firstChildren_;
                    while(temp != nullptr)
                    {
                        temp->parent_ = firstChildren->firstChildren_;
                        temp =  temp->next_;
                    }
                    firstChildren->next_ = nullptr;
                }
            }
            //end root children witn brothers
        }
        //end root children
    }
    //end root
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
