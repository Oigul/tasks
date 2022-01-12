#include <QCoreApplication>

#include <mytree.h>

Node *print(Node* temp);

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

    print(myTree.root());


    Node* forDelete = myTree.root()->firstChildren_;
    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
    myTree.popChildrenNode(forDelete);
    print(myTree.root());

    forDelete = myTree.root()->firstChildren_->firstChildren_/*->next_*/;
    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
    myTree.popChildrenNode(forDelete);
    print(myTree.root());

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
    print(myTree.root());

    forDelete = myTree.root()->firstChildren_;
    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
    myTree.popChildrenNode(forDelete);
    print(myTree.root());

    forDelete = myTree.root();
    std::cout << std::endl << "delete " << forDelete->value_<<std::endl;
    myTree.popChildrenNode(forDelete);
    if (myTree.root())
    {
        print(myTree.root());
    }

    if(myTree.searh(4, myTree.root()))
        std::cout << "true\n" << std::endl;
    else
        std::cout << std::endl << "4 false" << std::endl;

    myTree.~MyTree();
    std::cout << std::endl << "~MyTree\n";

    return a.exec();
}

Node* print(Node *temp)
{
    static std::vector<Node*> nodesUncle;

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
        nodesUncle.push_back(temp->next_);
        return print(temp->firstChildren_);
    }
    if (temp->firstChildren_)
        return print(temp->firstChildren_);
    if (temp->next_)
        return print(temp->next_);
    if (nodesUncle.size() > 0)
    {
        temp = nodesUncle[nodesUncle.size()-1];
        nodesUncle.pop_back();
        return print(temp);
    }
}
