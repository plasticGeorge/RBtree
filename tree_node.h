#include </home/george/Documents/Course_work/rb_color.h>

template<typename T>
class Node
{
    public:
        T value;
        NodeColor color; //true => red; false => black;
        Node* left;
        Node* right;
        Node* parent;

        Node(T value, NodeColor color, Node* left, Node* right, Node* parent)
        {
            this->value = value;
            this->color = color;
            this->left = left;
            this->right = right;
            this->parent = parent;
        }
};