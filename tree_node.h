template<typename T>
class Node
{
    private:
        nodeColor color; //true => red; false => black;
        Node* left;
        Node* right;
        Node* parent;

        Node(T value, nodeColor color, Node* left, Node* right, Node* parent)
        {
            this->value = value;
            this->color = color;
            this->left = left;
            this->right = right;
            this->parent = parent;
        }

        Node* _get_next()
        {
            if(current == get_max())
            {
                current = NULL;
                return current;
            }
            if(current->right != _get_nil())
                current = _get_min(current->right);
            else
            { 
                if(current->parent->left == current)
                    current = current->parent;
                else
                {
                    while(current->parent->right == current)
                        current = current->parent;
                    current = current->parent;
                }
            }
            return current;
        }

        Node* _get_prev()
        {
            if(current == get_min())
            {
                current = NULL;
                return current;
            }
            if(current->left != NIL)
                current = _get_max(current->left);
            else
            { 
                if(current->parent->right == current)
                    current = current->parent;
                else
                {
                    while(current->parent->left == current)
                        current = current->parent;
                    current = current->parent;
                }
            }
            return current;
        }
    public: 
        T value;
};