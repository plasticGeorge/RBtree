#include </home/george/Documents/Course_work/tree_node.h>

using namespace std;

template <typename T>
class RBTree
{
    private:
        #define NIL &sentinel
        static Node<T> sentinel;

        Node<T>* root = NIL;
        int size = 0;

        //helper func section
        void _rotate_left(Node<T>* pivot)
        {
            Node<T>* new_root = pivot->right;
            if(new_root == NIL)
                return;
            pivot->right = new_root->left;
            new_root->left = pivot;
            new_root->parent = pivot->parent;
            if(new_root->parent)
            {
                if(pivot == new_root->parent->right)
                    new_root->parent->right = new_root;
                else
                    new_root->parent->left = new_root;
            }
            pivot->parent = new_root;
        }

        void _rotate_right(Node<T>* pivot)
        {
            Node<T>* new_root = pivot->left;
            if(new_root == NIL)
                return;
            pivot->left = new_root->right;
            new_root->right = pivot;
            new_root->parent = pivot->parent;
            if(new_root->parent)
            {
                if(pivot == new_root->parent->left)
                    new_root->parent->left = new_root;
                else
                    new_root->parent->right = new_root;
            }
            pivot->parent = new_root;
        }

        void _balance_after_add(Node<T>* pivot)
        {
            while(pivot != root && pivot->parent->color == RED)
            {
                if(pivot->parent == pivot->parent->parent->left)
                {
                    Node<T>* uncle = pivot->parent->parent->right;
                    if(uncle->color == RED)
                    {
                        uncle->color = BLACK;
                        pivot->parent->color = BLACK;
                        pivot->parent->parent->color = RED;
                        pivot = pivot->parent->parent;
                    }
                    else
                    {
                        if (pivot == pivot->parent->right)
                        {
                            pivot = pivot->parent;
                            _rotate_left(pivot);
                        }
                    pivot->parent->color = BLACK;
                    pivot->parent->parent->color = RED;
                    _rotate_right(pivot->parent->parent);
                    }
                }
                else
                {
                    Node<T>* uncle = pivot->parent->parent->left;
                    if (uncle->color == RED)
                    {
                        uncle->color = BLACK;
                        pivot->parent->color = BLACK;
                        pivot->parent->parent->color = RED;
                        pivot = pivot->parent->parent;
                    } 
                    else
                    {
                        if (pivot == pivot->parent->left)
                        {
                            pivot = pivot->parent;
                            _rotate_right(pivot);
                        }
                        pivot->parent->color = BLACK;
                        pivot->parent->parent->color = RED;
                        _rotate_left(pivot->parent->parent);
                    }
                }
            }
            root->color = BLACK;
        }
        
        void _balance_after_remove(Node<T>* pivot)
        {
            while (pivot != root && pivot->color == BLACK)
            {
                if (pivot == pivot->parent->left)
                {
                    Node<T>* brother = pivot->parent->right;
                    if (brother->color == RED)
                    {
                        brother->color = BLACK;
                        pivot->parent->color = RED;
                        _rotate_left (pivot->parent);
                        brother = pivot->parent->right;
                    }
                    if (brother->left->color == BLACK && brother->right->color == BLACK)
                    {
                        brother->color = RED;
                        pivot = pivot->parent;
                    }
                    else
                    {
                        if (brother->right->color == BLACK)
                        {
                            brother->color = RED;
                            brother->left->color = BLACK;
                            _rotate_right (brother);
                            brother = pivot->parent->right;
                        }
                        brother->color = pivot->parent->color;
                        brother->right->color = BLACK;
                        pivot->parent->color = BLACK;
                        _rotate_left (pivot->parent);
                        pivot = root;
                    }
                }
                else
                {
                    Node<T>* brother = pivot->parent->left;
                    if (brother->color == RED)
                    {
                        brother->color = BLACK;
                        pivot->parent->color = RED;
                        _rotate_right (pivot->parent);
                        brother = pivot->parent->left;
                    }
                    if (brother->right->color == BLACK && brother->left->color == BLACK)
                    {
                        brother->color = RED;
                        pivot = pivot->parent;
                    } 
                    else
                    {
                        if (brother->left->color == BLACK)
                        {
                            brother->color = RED;
                            brother->right->color = BLACK;
                            _rotate_left (brother);
                            brother = pivot->parent->left;
                        }
                        brother->color = pivot->parent->color;
                        brother->left->color = BLACK;
                        pivot->parent->color = BLACK;
                        _rotate_right (pivot->parent);
                        pivot = root;
                    }
                }
            }
            pivot->color = BLACK;
        }

        void _delete_tree(Node<T>* current_node)
        {
            if(current_node != NIL)
            {
                _delete_tree(current_node->left);
                _delete_tree(current_node->right);
                delete current_node;
            }
            return;
        }

        void _print(Node<T>* current, int level)
        {      
            if (current->right != NIL) 
                _print(current->right, level + 1);
            for (int i = 0; i < level; i++)
                cout << "   ";
            if (current->parent)
            {
                if (current == current->parent->left)
                    cout << "\\";
                else
                    cout << "/";
            }
            cout << current->value << endl;
            if (current->left != NIL) 
                _print(current->left, level + 1);
        }

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
    RBTree(){}

    RBTree(T array_values[], int size)
    {
        for(int i = 0; i < size; i++)
            add(array_values[i]);
    }

    ~RBTree()
    {
        _delete_tree(root);
    }

    class Iterator
    {
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

    Iterator begin() { return get_min(); }

    Iterator end() { return get_max() + 1; }

    Node<T>* find(T value)
    {
        Node<T>* res = root;
        while(res != NIL)
        {
            if(value == res->value)
                return res;
            else
                res = value > res->value ? res->right : res->left;  
        }
        return NULL;
    }

    bool add(T value)
    {
        Node<T>* current = root;
        Node<T>* parent = NULL;
        while(current != NIL)
        {
            if(value == current->value)
                return false;
            parent = current;
            current = value < current->value ? current->left : current->right;  
        }
        Node<T>* new_node = new Node<T>(value, RED, NIL, NIL, parent);
        if(parent)
        {
            if(value < parent->value)
                parent->left = new_node;
            else
                parent->right = new_node;
        }
        else
            root = new_node;
        
        _balance_after_add(new_node);
        size++;
        return true;
    }

    bool remove(T value)
    {
        Node<T>* removed_node = find(value);
        if(removed_node == NULL)
            return false;
        
        Node<T>* temp = NULL;
        if (removed_node->left == NIL || removed_node->right == NIL)
            temp = removed_node;
        else
        {
            temp = removed_node->right;
            while (temp->left != NIL)
                temp = temp->left;
        }

        Node<T>* temp_child = NULL;
        if (temp->left != NIL)
            temp_child = temp->left;
        else
            temp_child = temp->right;
        temp_child->parent = temp->parent;
        if (temp->parent)
        {
            if (temp == temp->parent->left)
                temp->parent->left = temp_child;
            else
                temp->parent->right = temp_child;
        }
        else
            root = temp_child;
        if (temp != removed_node)
            removed_node->value = temp->value;
        
        if (temp->color == BLACK)
            _balance_after_remove(temp_child);
        delete temp;
        size--;
        return true;
    }

    void delete_tree()
    {
        _delete_tree(root);
        root = NIL;
        size = 0;
    }

    Node<T>* get_min()
    {
        return _get_min(root);
    }

    Node<T>* get_max()
    {
        return _get_max(root);
    }

    int get_size()
    {
        return size;
    }

    void print(){
        if(root != NIL)
            _print(root, 0);
        else
            cout << "Tree is empty..." << endl;
    }
};

template<typename T>
Node<T> RBTree<T>::sentinel = {T(), BLACK, NIL, NIL, NULL};