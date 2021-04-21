#include </home/george/Documents/Course_work/tree_node.h>
#include </home/george/Documents/Course_work/rb_color.h>

class TreeIterator
{
    private:
        Node* current;
        Node* root;
    public:
        TreeIterator(Node* first) { current = first; }

        Node* operator++()
        {
            if(current == get_max())
            {
                current = NULL;
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

        Node* operator++(int)
        {
            Node* temp = current;
            ++current;
            return temp;
        }

        Node* operator+(int n)
        {
            for(int i = 0; i < n; i++, current++){}
            return current;
        }

        Node* operator--()
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

        Node* operator--(int)
        {
            Node* temp = current;
            --current;
            return temp;
        }

        Node* operator-(int n)
        {
            for(int i = 0; i < n; i++, current--){}
            return current;
        }

        bool operator==(Iterator it) { return current == it.current; }
        bool operator!=(Iterator it) { return current != it.current; }

        T operator*() { return current->value; }
};

class Iterator
    {
        private:
            Node* current;
        public:
            Iterator(Node* node) { current = node; }

            Node* operator++()
            {

            }

            Node* operator--()
            {
                
            }
    }

    Iterator begin() { return get_min(); }
    Iterator end() { return get_max(); }