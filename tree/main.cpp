#include <QCoreApplication>

#include <iostream>

#include <mytree.h>

//1. oigul
//2. Освобождение памяти
//3. Если несколько раз пойду в глубь при наличии братьев, то информация о прошлом дяде потеряется?
//4. Node *print(Node* temp, bool first); - можно ли ничего не возвращать
//5. посмотреть что надо убрать в private в MyTree

Node *print(Node* temp, bool first);
void printChildren(Node* temp);
void printBrother(Node* temp);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTree myTree = MyTree();
    myTree.pushRoot(5);

    myTree.pushChildrenNode(1, myTree.root());
    myTree.pushChildrenNode(2, myTree.root());

    myTree.pushChildrenNode(8,  myTree.root()->firstChildren_);
    myTree.pushChildrenNode(7, myTree.root()->firstChildren_);

    myTree.pushChildrenNode(6,  myTree.root()->firstChildren_->next_);
    myTree.pushChildrenNode(9, myTree.root()->firstChildren_->next_);
    myTree.pushChildrenNode(1, myTree.root()->firstChildren_->next_);

    print(myTree.root(), true);


    std::cout << std::endl;
    myTree.popChildrenNode(myTree.root()->firstChildren_);
    print(myTree.root(), true);

    std::cout << std::endl;
    myTree.popChildrenNode(myTree.root()->firstChildren_->firstChildren_->next_);
    print(myTree.root(), true);

    if(myTree.searh(8, myTree.root()))
        std::cout << "true" << std::endl;
    else
        std::cout << std::endl << "\n8 false" << std::endl;

    if(myTree.searh(2, myTree.root()))
        std::cout << "true" << std::endl;
    else
        std::cout << std::endl << "9 false" << std::endl;

    if(myTree.searh(3, myTree.root()))
        std::cout << "3 true" << std::endl;
    else
        std::cout << std::endl << "3 false" << std::endl;

    myTree.~MyTree();
    std::cout << std::endl << "~MyTree";

    return a.exec();
}

Node* print(Node *temp, bool first)
{
    static Node* nodeUncle = nullptr;
    static bool nodeUncleTrue = false;

    //for new printing
    if(first)
    {
        nodeUncleTrue = false;
        first = false;
    }

    std::cout << temp->value_ << " ";
    if (temp->firstChildren_ && temp->next_)
    {
        nodeUncleTrue = true;
        nodeUncle = temp->next_;
        return print(temp->firstChildren_, false);
    }
    if (temp->firstChildren_)
        return print(temp->firstChildren_, false);
    if (temp->next_)
        return print(temp->next_, false);
    if (nodeUncleTrue)
    {
        nodeUncleTrue = false;
        return print(nodeUncle, false);
    }
}
