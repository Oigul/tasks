#include "mytree.h"
#include <iostream>
#include <vector>

MyTree::MyTree()
{
}

MyTree::~MyTree()
{
    DeleteNodes(root_);
}

Node* MyTree::DeleteNodes(Node *temp)
{
    static std::vector<Node*> nodesUncle;

    if (temp->firstChildren_ && temp->next_)
    {
        nodesUncle.push_back(temp->next_);
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
        Node* tempNext = temp->next_;
        delete temp;
        return DeleteNodes(tempNext);
    }
    if (nodesUncle.size() > 0)
    {
        Node* tempNext = nodesUncle[nodesUncle.size()-1];
        nodesUncle.pop_back();
        delete temp;
        return DeleteNodes(tempNext);
    }
    delete temp;
}

void MyTree::pushRoot(int value)
{
    Node *newNode = new Node(value);
    root_ = newNode;
}

void MyTree::pushNode(int value, Node *parent)
{
    Node *newNode = new Node(value);
    newNode->parent_ = parent;

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
    if(child == root_)
    {
        if(root_->firstChildren_)
        {
            Node* firstChild = root_->firstChildren_;
            firstChild->parent_ = nullptr;
            delete root_;
            //первый ребенок становится родителем, меняются братья и братья детей
            becomeParentForRoot(firstChild);
        }
        else
        {
            delete root_;
            root_ = nullptr;
        }
    }
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
                {
                    temp = temp->next_;
                }
                //находим участок, в котором надо затереть ребенка
                temp->next_ = child->next_;
            }
            delete child;
            return;
        }
        else //есть дети
        {
            becomeParentForNode(child->firstChildren_);
        }
    }
}

void MyTree::becomeParentForNode(Node *firstCh)
{
    //У РЕБЕНКА НЕТ ДЕТЕЙ
    //если нет дядь, нет братьев
    if(firstCh->parent_->next_ == nullptr && firstCh->next_ == nullptr
            && firstCh->firstChildren_ == nullptr)
    {
        Node* temp = firstCh->parent_;
        firstCh->parent_->parent_->firstChildren_ = firstCh;
        firstCh->parent_ = firstCh->parent_->parent_;
        delete temp;
        return;
    }
    //есть брат, нет дядь
    if(firstCh->parent_->next_ == nullptr && firstCh->next_
            && firstCh->firstChildren_ == nullptr)
    {
        Node* temp = firstCh->parent_;
        firstCh->parent_->parent_->firstChildren_ = firstCh;
        firstCh->parent_ = firstCh->parent_->parent_;
        delete temp;
        firstCh->firstChildren_ = firstCh->next_;
        //cтановится родителем братьям
        temp = firstCh->firstChildren_;
        while(temp != nullptr)
        {
            temp->parent_ = firstCh;
            temp = temp->next_;
        }
        firstCh->next_ = nullptr;
        return;
    }
    //есть брат и дяди
    if(firstCh->parent_->next_ && firstCh->next_ == nullptr
            && firstCh->firstChildren_ == nullptr)
    {
        Node* temp = firstCh->parent_;
        firstCh->parent_->parent_->firstChildren_ = firstCh;
        firstCh->parent_ = temp->parent_;
        firstCh->next_ = temp->next_;
        delete temp;
        return;
    }
    //есть братья и дяди
    if(firstCh->parent_->next_ && firstCh->next_
            && firstCh->firstChildren_ == nullptr)
    {
        Node* temp = firstCh->parent_;
        firstCh->parent_->parent_->firstChildren_ = firstCh;
        firstCh->parent_ = temp->parent_;
        firstCh->firstChildren_ = firstCh->next_;
        firstCh->next_ = temp->next_;
        delete temp;

        //cтановится родителем братьям
        temp = firstCh->firstChildren_;
        while(temp != nullptr)
        {
            temp->parent_ = firstCh;
            temp = temp->next_;
        }
        return;
    }
    //У РЕБЕНКА ЕСТЬ ДЕТИ
    //у ребенка есть дети, брат, нет дяди
    if(firstCh->parent_->next_ == nullptr && firstCh->next_
            && firstCh->firstChildren_)
    {
        Node* temp = firstCh->parent_;
        firstCh->parent_->parent_->firstChildren_ = firstCh;
        firstCh->parent_ = temp->parent_;
        delete temp;

        //брат становится братом последнего ребенка
        temp = firstCh->firstChildren_;
        while(temp->next_ != nullptr)
        {
            temp = temp->next_;
        }
        temp->next_ = firstCh->next_;

        //cтановится родителем братьям
        temp = firstCh->next_;
        while(temp != nullptr)
        {
            temp->parent_ = firstCh;
            temp = temp->next_;
        }
        firstCh->next_ = nullptr;
        return;
    }
    //у ребенка есть дети, братья, дяди
    if(firstCh->parent_->next_ && firstCh->next_
            && firstCh->firstChildren_)
    {
        Node* temp = firstCh->parent_;
        firstCh->parent_->parent_->firstChildren_ = firstCh;

        //брат становится братом последнего ребенка
        temp = firstCh->firstChildren_;
        while(temp->next_ != nullptr)
        {
            temp = temp->next_;
        }
        temp->next_ = firstCh->next_;

        //cтановится родителем братьям
        temp = firstCh->next_;
        while(temp != nullptr)
        {
            temp->parent_ = firstCh;
            temp = temp->next_;
        }

        firstCh->next_ = firstCh->parent_->next_;
        delete firstCh->parent_;
        firstCh->parent_ = firstCh->parent_->parent_;

        return;
    }
}

void MyTree::becomeParentForRoot(Node* firstChildren)
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
            if (firstChildren->firstChildren_ && firstChildren->firstChildren_->next_ && firstChildren->next_
                    && firstChildren->firstChildren_->firstChildren_ == nullptr)
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
            else
            {
                if (firstChildren->firstChildren_ && firstChildren->firstChildren_->next_ && firstChildren->next_
                        && firstChildren->firstChildren_->firstChildren_)
                {
                    root_ = firstChildren;

                    //брат становится братом последнего ребенка
                    Node* temp = root_->firstChildren_;
                    while(temp->next_ != nullptr)
                    {
                        temp = temp->next_;
                    }
                    temp->next_ = firstChildren->next_;

                    //cтановится родителем братьям
                    temp = firstChildren->next_;
                    while(temp != nullptr)
                    {
                        temp->parent_ = firstChildren;
                        temp = temp->next_;
                    }

                    firstChildren->next_ = nullptr;
                    firstChildren->parent_ = nullptr;
                }
            }
        }
    }
}

Node* MyTree::searh(int value, Node* temp)
{
    static std::vector<Node*> nodesUncle;

    if (temp->value_ == value)
    {
        std::cout << std::endl << std::endl << temp->value_ << " ";
        return temp;
    }

    if (temp->firstChildren_ && temp->next_)
    {
        nodesUncle.push_back(temp->next_);
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
    if (nodesUncle.size() > 0)
    {
        temp = nodesUncle[nodesUncle.size()-1];
        nodesUncle.pop_back();
        return searh(value, temp);
    }
    return nullptr;
}

Node *MyTree::root() const
{
    return root_;
}
