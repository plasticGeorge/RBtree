using namespace std;

template <typename T>
class RBTree
{
    private:
        enum NodeColor
        {
            BLACK,
            RED
        };

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

        Node* root = NULL;
        int size = 0;

        //helper func section
        void _rotate_left(Node* pivot)
        {
            Node* new_root = pivot->right;
            if(new_root == NULL)
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

        void _rotate_right(Node* pivot)
        {
            Node* new_root = pivot->left;
            if(new_root == NULL)
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

        void _balance_after_add(Node* pivot)
        {
            while(pivot != root && pivot->parent->color == RED)
            {
                if(pivot->parent == pivot->parent->parent->left)
                {
                    Node* uncle = pivot->parent->parent->right;
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
                    Node* uncle = pivot->parent->parent->left;
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
        
        void _balance_after_remove(Node* pivot)
        {
            while (pivot != root && pivot->color == BLACK)
            {
                if (pivot == pivot->parent->left)
                {
                    Node* brother = pivot->parent->right;
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
                    Node* brother = pivot->parent->left;
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

        void _delete_tree(Node* current_node)
        {
            if(current_node != NULL)
            {
                _delete_tree(current_node->left);
                _delete_tree(current_node->right);
                delete current_node;
            }
            return;
        }

        void _print(Node* current, int level)
        {      
            if (current->right != NULL) 
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
            if (current->left != NULL) 
                _print(current->left, level + 1);
        }

        Node* _get_min(Node* root)
        {
            Node* current = root;
            Node* res = NULL;
            while(current != NULL)
            {
                res = current;
                current = current->left;  
            }
            return res;
        }

        Node* _get_max(Node* root)
        {
            Node* current = root;
            Node* res = NULL;
            while(current != NULL)
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

    Node* find(T value)
    {
        Node* res = root;
        while(res != NULL)
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
        Node* current = root;
        Node* parent = NULL;
        while(current != NULL)
        {
            if(value == current->value)
                return false;
            parent = current;
            current = value > current->value ? current->right : current->left;  
        }
        Node* new_node = new Node(value, RED, NULL, NULL, parent);
        if(parent)
        {
            value > parent->value ? parent->right = new_node : parent->left = new_node;
        }
        else
            root = new_node;
        
        _balance_after_add(new_node);
        size++;
        return true;
    }

    bool remove(T value)
    {
        Node* removed_node = find(value);
        if(removed_node == NULL)
            return false;
        
        Node* temp = NULL;
        if (removed_node->left == NULL || removed_node->right == NULL)
            temp = removed_node;
        else
        {
            temp = removed_node->right;
            while (temp->left != NULL)
                temp = temp->left;
        }

        Node* temp_child = NULL;
        if (temp->left != NULL)
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
        root = NULL;
        size = 0;
    }

    Node* get_min()
    {
        return _get_min(root);
    }

    Node* get_max()
    {
        return _get_max(root);
    }

    int get_size()
    {
        return size;
    }

    void print(){
        if(root != NULL)
            _print(root, 0);
        else
            cout << "Tree is empty..." << endl;
    }
};