#include <iostream>
#include </home/george/Documents/Course_work/rbtree.h>

using namespace std;

template <typename T>
void print_tree(RBTree<T> tree);

int main()
{
    RBTree<int> tree;
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

    cout << endl;

  

    return 0;
}