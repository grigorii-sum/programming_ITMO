#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template<typename T>

struct Node
{
    Node <T> *parent;
    Node <T> *leftChild;
    Node <T> *rightChild;
    T value;

    Node() : value(T()), leftChild(nullptr), rightChild(nullptr), parent(nullptr) {};

    ~Node()
    {
        delete leftChild;
        delete rightChild;
    }

    Node(const Node<T> &node) : value(node.value)
    {
        if (node.leftChild != nullptr)
        {
            leftChild = new Node<T>(*node.leftChild);
            leftChild->parent = this;
        }
        else
        {
            leftChild = nullptr;
        }

        if (node.rightChild != nullptr)
        {
            rightChild = new Node<T>(*node.rightChild);
            rightChild->parent = this;
        }
        else
        {
            rightChild = nullptr;
        }
    }

    Node& operator=(const Node<T> &node)
    {
        this->~Node();
        new (this)Node(m);
        return *this;
    }
};


template<typename T, class Compare = std::less<T> >

class BST
{
private:
    Node<T> *root;
    size_t s;

    bool checkExists(int val)
    {
        return search_method(val) != nullptr;
    }

    Node<T>* search_method(const T& val)
    {
        Node<T> *currentNode = root;
        while (currentNode != nullptr && val != currentNode->value)
        {
            if (val < currentNode->value)
            {
                currentNode = currentNode->leftChild;
            }
            else
            {
                currentNode = currentNode->rightChild;
            }
        }
        return currentNode;
    }

public:
    template<typename T>

    class Iter : public std::iterator<std::bidirectional_iterator_tag, Node<T>>
    {
        friend class BST<T>;
    public:
        Iter(Node<T> *node)
        {
            it = node;
        }

        Iter& operator ++()
        {
            if (it->rightChild == nullptr)
            {
                Node<T> *p;
                p = it->parent;
                while (p != nullptr && p->rightChild == it)
                {
                    it = p;
                    p = p->parent;
                }
                it = p;
            }
            else
            {
                it = it->rightChild;
                while (it->leftChild != nullptr)
                {
                    it = it->leftChild;
                }
            }
            return *this;
        }

        Iter& operator --()
        {
            if (it->leftChild == nullptr)
            {
                Node<T> *p;
                p = it->parent;
                while (p != nullptr && p->leftChild == it)
                {
                    it = p;
                    p = p->parent;
                }
                it = p;
            }
            else
            {
                it = it->leftChild;
                while (it->rightChild != nullptr)
                {
                    it = it->rightChild;
                }
            }
            return *this;
        }

        bool operator == (Iter& iter)
        {
            if (iter.it == it)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool operator != (Iter& iter)
        {
            return !(*this == iter);
        }

        typename Iter::reference operator*() const
        {
            return *it;
        }

    private:
        Node <T> *it;
    };

    typedef Iter<T> iterator;
    typedef Iter<T> const_iterator;

    BST() : root(new Node<T>), s(0)
    {
        root->value = T();
    };

    ~BST()
    {
        delete root;
    }

    BST(const BST &bst)
    {
        s = bst.s;
        root = new Node<T>(*bst.root);
    };

    BST& operator = (const BST &bst)
    {
        s = bst.s;
        root = new Node<T>(*bst.root);
        return *this;
    };

    template<class ​InputIt>

    void ​assign(​InputIt first, ​InputIt last)
    {
        while (first != last)
        {
            insert(*first);
            first++;
        }
    }

    Node<T>* beg()
    {
        Node<T> *n = root;
        while (n->leftChild != nullptr)
        {
            n = n->leftChild;
        }
        return n;
    }

    Node<T>* en()
    {
        Node<T> *n = root;
        while (n->rightChild != nullptr)
        {
            n = n->rightChild;
        }
        return n;
    }

    iterator begin()
    {
        return iterator(beg());
    }

    const_iterator cbegin()
    {
        return const_iterator(beg());
    }

    iterator end()
    {
        return iterator(en());
    }

    const_iterator cend()
    {
        return const_iterator(en());
    }

    iterator insert(const T& val)
    {
        if (checkExists(val))
        {
            return find(val);
        }
        s++;
        Node<T> *buffNode = new Node<T>();
        buffNode->parent = buffNode->leftChild = buffNode->rightChild = nullptr;
        buffNode->value = val;
        Node<T> *currentPosition = root;
        while (currentPosition != nullptr)
        {
            buffNode->parent = currentPosition;
            if (!(buffNode->value < currentPosition->value))
            {
                currentPosition = currentPosition->rightChild;
            }
            else
            {
                currentPosition = currentPosition->leftChild;
            }
        }
        if (buffNode->parent == nullptr)
        {
            root = buffNode;
        }
        else if (buffNode->value < buffNode->parent->value)
            {
                buffNode->parent->leftChild = buffNode;
            }
            else
            {
                buffNode->parent->rightChild = buffNode;
            }
        return iterator(buffNode);
    }

    void remove(const T& val)
    {
        Node<T>* nodeForDelete = &*find(val);

        if (nodeForDelete == nullptr)
        {
            return;
        }

        Node<T> *buff1, *buff2;

        if (nodeForDelete->leftChild == nullptr || nodeForDelete->rightChild == nullptr)
        {
            buff1 = nodeForDelete;
        }
        else
        {
            buff1 = &*(++find(val));
        }

        if (buff1->leftChild != nullptr)
        {
            buff2 = buff1->leftChild;
        }
        else
        {
            buff2 = buff1->rightChild;
        }

        if (buff2 != nullptr)
        {
            buff2->parent = buff1->parent;
        }

        if (buff1->parent == nullptr)
        {
            root = buff2;
        }
        else if (buff1 == buff1->parent->leftChild)
            {
                buff1->parent->leftChild = buff2;
            }
            else
            {
                buff1->parent->rightChild = buff2;
            }

        if (buff1 != nodeForDelete)
        {
            nodeForDelete->value = buff1->value;
        }
        s--;
        delete buff1;
    }

    iterator find(const T& val)
    {
        return iterator(search_method(val));
    }

    const_iterator cfind(const T& val)
    {
        return const_iterator(search_method(val));
    }

    bool empty() const
    {
        return s == 0;
    };

    size_t size() const
    {
        return s;
    };
};

template<typename T>

void print_tree(BST<T> bst_test_1)
{
    BST<int>::iterator s1 = bst_test_1.begin();
    BST<int>::iterator f1 = bst_test_1.end();
    while (s1 != f1)
    {
        ++s1;
        cout << (*s1).value << " ";
    }
    cout << (*s1).value << " ";
    cout << endl;
}

template<typename T>

void find_prev_and_next_in_tree(BST<T> bst_test_1, T val)
{
    BST<int>::iterator f = bst_test_1.find(val);
    ++f;
    cout << "++f = " << (*f).value << endl;
    --(--f);
    cout << "--f = " << (*f).value << endl;
}

template<typename T>

void check(BST<T> bst_test_1, T arg0, T arg1, T arg2, T arg3)
{
    print_tree(bst_test_1);
    find_prev_and_next_in_tree(bst_test_1, arg0);
    cout << "size = " << bst_test_1.size() << endl;
    bst_test_1.remove(arg1);
    print_tree(bst_test_1);
    bst_test_1.remove(arg2);
    print_tree(bst_test_1);
    bst_test_1.remove(arg3);
    print_tree(bst_test_1);
    cout << "size = " << bst_test_1.size() << endl;
    if (bst_test_1.empty())
    {
        cout << "empty" << endl;
    }
    else
    {
        cout << "non empty" << endl;
    }
}

int main()
{
    BST<int> bst_test_1;
    BST<int> bst_test_2;
    vector<int> vec = { 50, 25, 75, 65, 85, 60, 30, 20, 70 };

    bst_test_1.insert(50);
    bst_test_1.insert(25);
    bst_test_1.insert(75);
    bst_test_1.insert(65);
    bst_test_1.insert(85);
    bst_test_1.insert(60);
    bst_test_1.insert(30);
    bst_test_1.insert(20);
    bst_test_1.insert(70);

    bst_test_2.​assign(vec.begin(), vec.end());

    check(bst_test_1, 50, 30, 31, 50);
    cout << endl << endl;
    check(bst_test_2, 50, 30, 31, 50);

    return 0;
}
