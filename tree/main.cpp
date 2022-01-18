#include <QCoreApplication>

#include <mytree.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyTree myTree = MyTree();
    myTree.pushRoot(1);

    myTree.pushNode(2, myTree.root());
    myTree.pushNode(3, myTree.root());
    myTree.pushNode(4, myTree.root());

    myTree.pushNode(5,  myTree.root()->firstChildren_);
    myTree.pushNode(6,  myTree.root()->firstChildren_);
    myTree.pushNode(7,  myTree.root()->firstChildren_);

    myTree.pushNode(8, myTree.root()->firstChildren_->firstChildren_);
    myTree.pushNode(9,  myTree.root()->firstChildren_->firstChildren_);
    myTree.pushNode(10, myTree.root()->firstChildren_->firstChildren_);
    myTree.pushNode(11, myTree.root()->firstChildren_->next_);

    myTree.print();

    Node* forDelete = myTree.root()->firstChildren_;
    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
    myTree.popChildrenNode(forDelete);
    myTree.print();

    forDelete = myTree.root()->firstChildren_->firstChildren_/*->next_*/;
    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
    myTree.popChildrenNode(forDelete);
    myTree.print();

    if(myTree.searh(8, myTree.root()))
        std::cout << "true" << std::endl;
    else
        std::cout << std::endl << "\n8 false" << std::endl;

    if(myTree.searh(2, myTree.root()))
        std::cout << "true" << std::endl;
    else
        std::cout << std::endl << "2 false" << std::endl;

    if(myTree.searh(3, myTree.root()))
        std::cout << " true" << std::endl;
    else
        std::cout << std::endl << "3 false" << std::endl;

    forDelete = myTree.root();
    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
    myTree.popChildrenNode(forDelete);
    myTree.print();

    forDelete = myTree.root()->firstChildren_;
    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
    myTree.popChildrenNode(forDelete);
    myTree.print();

    forDelete = myTree.root();
    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
    myTree.popChildrenNode(forDelete);
    if (myTree.root())
    {
        myTree.print();
    }

    if(myTree.searh(4, myTree.root()))
        std::cout << "true\n" << std::endl;
    else
        std::cout << std::endl << "4 false" << std::endl;

    myTree.~MyTree();
    std::cout << std::endl << "~MyTree\n";

    return a.exec();
}
