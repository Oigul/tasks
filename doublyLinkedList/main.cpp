#include <QCoreApplication>
#include <mydeque.h>
#include <iostream>

void print(myDeque deque);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    myDeque deque;
    Node node1 = Node(5);
    Node node2 = Node(2);
    deque.push(&node1);
    deque.push(&node2);
    deque.print();

    deque.pop(&node1);
    Node node3 = Node(452);
    deque.push(&node3);
    deque.print();

    std::cout << deque.searh(2) << std::endl;
    std::cout << deque.searh(5) << std::endl;
    std::cout << deque.searh(546) << std::endl;

    return a.exec();
}
