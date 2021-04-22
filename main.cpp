#include <iostream>
#include </home/george/Documents/Course_work/rbtree.h>

using namespace std;

template <typename T>
void print_tree(RBTree<T> tree);

int main()
{
    RBTree<int> tree;
    tree.print();

    cout << "\n\n\n";

    tree.add(10);
    tree.add(3);
    tree.add(12);
    tree.add(56);
    tree.add(5);
    tree.add(110);
    tree.add(-20);
    tree.add(25);
    tree.add(39);
    tree.add(-32);
    tree.add(-2);
    tree.print();

    cout << "\n\n\n";

    tree.remove(-2);
    tree.remove(10);
    tree.remove(5);
    tree.print();

    cout << "\n\n\n";

    tree.delete_tree();
    tree.print();

    cout << "\n\n\n";

    tree.add(-17);
    tree.add(55);
    tree.add(83);
    tree.add(-23);
    tree.add(0);
    tree.add(11);
    tree.add(24);
    tree.print();
    Node<int> *n = tree.find(-2);

    return 0;
}