#include <iostream>
#include </home/george/Documents/Course_work/rbtree.h>

using namespace std;

template <typename T>
void print_tree(RBTree<T> tree);

int main()
{
    RBTree<int> tree;
    tree.add(10);
    cout << "Succ" <<endl;
    tree.add(3);
    cout << "Succ" <<endl;
    tree.add(12);
    cout << "Succ" <<endl;
    tree.add(56);
    cout << "Succ" <<endl;
    tree.add(5);
    cout << "Succ" <<endl;
    tree.add(110); //***
    cout << "Succ" <<endl;
    tree.add(-20);
    cout << "Succ" <<endl;
    tree.add(25);
    cout << "Succ" <<endl;
    tree.add(39);
    cout << "Succ" <<endl;
    tree.add(-32);
    cout << "Succ" <<endl;
    tree.add(-2);
    cout << "Succ" <<endl;
    tree.print();

    cout << endl;

  

    return 0;
}