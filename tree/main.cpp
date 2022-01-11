#include <QCoreApplication>

#include <iostream>
#include <functional>

#include <mytree.h>

//1. oigul
//* разобраться с удалением (рекурсивно, попробовать объединить с рутом)
//2. Если несколько раз пойду в глубь при наличии братьев, то информация о прошлом дяде потеряется? - в поиске, в принте и в удалении
//Например запомнить в лист дядь, чтобы потом вернуться
//3. Node *print(Node* temp, bool first); - посм можно ли ничего не возвращать
//4. посмотреть что надо убрать в private в MyTree
//отдельное присваивание для root, потому что у него зануляется next
//посм. освобождение памяти

Node *print(Node* temp, bool first);
void printChildren(Node* temp);
void printBrother(Node* temp);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTree myTree = MyTree();
    myTree.pushRoot(1);

    myTree.pushChildrenNode(2, myTree.root());
    myTree.pushChildrenNode(3, myTree.root());
//    myTree.pushChildrenNode(5, myTree.root());

    myTree.pushChildrenNode(4,  myTree.root()->firstChildren_);
    myTree.pushChildrenNode(5,  myTree.root()->firstChildren_);
    myTree.pushChildrenNode(6,  myTree.root()->firstChildren_);

//    myTree.pushChildrenNode(4, myTree.root()->firstChildren_);
//    myTree.pushChildrenNode(8,  myTree.root()->firstChildren_->next_);
//    myTree.pushChildrenNode(9, myTree.root()->firstChildren_->next_);
//    myTree.pushChildrenNode(1, myTree.root()->firstChildren_->next_);

    print(myTree.root(), true);


    Node* forDelete = myTree.root()->firstChildren_;
//    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
//    myTree.popChildrenNode(forDelete);
//    print(myTree.root(), true);

//    forDelete = myTree.root()->firstChildren_->firstChildren_/*->next_*/;
//    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
//    myTree.popChildrenNode(forDelete);
//    print(myTree.root(), true);

//    if(myTree.searh(8, myTree.root()))
//        std::cout << "true" << std::endl;
//    else
//        std::cout << std::endl << "\n8 false" << std::endl;

//    if(myTree.searh(2, myTree.root()))
//        std::cout << "true" << std::endl;
//    else
//        std::cout << std::endl << "9 false" << std::endl;

//    if(myTree.searh(3, myTree.root()))
//        std::cout << "3 true" << std::endl;
//    else
//        std::cout << std::endl << "3 false" << std::endl;

//    forDelete = myTree.root();
//    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
//    myTree.popChildrenNode(forDelete);
//    print(myTree.root(), true);

    forDelete = myTree.root()->firstChildren_;
    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
    myTree.popChildrenNode(forDelete);
    print(myTree.root(), true);

    forDelete = myTree.root();
    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
    myTree.popChildrenNode(forDelete);
    print(myTree.root(), true);


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

    auto  text
    {
        [](Node *temp)
        {
            return ((temp != nullptr) ? QString::number(temp->value_):QString::fromStdString( "-"));
        }
    };

    std::cout << temp->value_
              << " p " << text(temp->parent_).toStdString()
              << " n " << text(temp->next_).toStdString()
              << " fch " << text(temp->firstChildren_).toStdString() << std::endl;
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
