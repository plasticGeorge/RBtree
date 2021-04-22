template <typename T>
class Iterator
{
    class RBTree;
    friend RBTree;
    private:
        Node<T>* current;
        Node<T>* root;

        Node<T>* _get_min(Node<T>* root)
        {
            Node<T>* current = root;
            Node<T>* res = NULL;
            while(current != NIL)
            {
                res = current;
                current = current->left;  
            }
            return res;
        }

        Node<T>* _get_max(Node<T>* root)
        {
            Node<T>* current = root;
            Node<T>* res = NULL;
            while(current != NIL)
            {
                res = current;
                current = current->right;
            }
            return res;
        }
    public:
        Iterator(Node<T>* first)
        {
            current = first;
            root = current;
            while(root->parent != NULL)
                root = root->parent;
        }

        Node<T>* operator++()
        {
            if(current == _get_max(root))
            {
                current = _get_max(root) + 1;
                return current;
            }
            if(current->right != NIL)
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

        Node<T>* operator++(int)
        {
            Node<T>* temp = current;
            if(current == _get_max(root))
            {
                current = _get_max(root) + 1;
                return temp;
            }
            if(current->right != NIL)
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
            return temp;
        }

        Node<T>* operator+(int n)
        {
            for(int i = 0; i < n; i++, current++){}
            return current;
        }

        Node<T>* operator--()
        {
            if(current == _get_min(root))
            {
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

        Node<T>* operator--(int)
        {
            Node<T>* temp = current;
            if(current == _get_min(root))
            {
                return temp;
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
            return temp;
        }

        Node<T>* operator-(int n)
        {
            for(int i = 0; i < n; i++, current--){}
            return current;
        }

        bool operator==(Iterator it)
        {
            
            return current == it.current;
        }

        bool operator!=(Iterator it)
        {
            return current != it.current;
        }

        T operator*() { return current->value; }
};