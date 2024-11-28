#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <ctime>
#include <algorithm>
using namespace std;

template<class T>
class Node
{
public:
    Node()
    {
        data = new T;
    }
    Node(T d)
    {
        data = new T;
        (*data) = d;
    }
    Node &operator=(T d)
    {
        (*data) = d;
        return *this;
    }
    friend ostream &operator<<(ostream &out, Node n)
    {
        out << *(n.data);
        return out;
    }
    friend ostream &operator<<(ostream &out, Node *n)
    {
        out << *(n->data);
        return out;
    }
    void setData(T d)
    {
        *data = d;
    }
    T &getData() const
    {
        return *data;
    }
protected:
    T *data;
};

template<class T>
class BinaryTreeNode : public Node<T>
{
public:
    BinaryTreeNode() : Node<T>(), left(NULL), right(NULL), height(1) {}
    BinaryTreeNode(T d) : Node<T>(d), left(NULL), right(NULL), height(1) {}
    BinaryTreeNode(BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(), left(l), right(r), height(1) {}
    BinaryTreeNode(T d, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : Node<T>(d), left(l), right(r), height(1) {}

    void setLeft(BinaryTreeNode<T> *l)
    {
        left = l;
    }
    void setRight(BinaryTreeNode<T> *r)
    {
        right = r;
    }
    BinaryTreeNode<T> *&getLeft()
    {
        return left;
    }
    BinaryTreeNode<T> *&getRight()
    {
        return right;
    }
    int getHeight()
    {
        return height;
    }
    void setHeight(int h)
    {
        height = h;
    }

private:
    BinaryTreeNode<T> *left, *right;
    int height;
};

template<class T>
class AVLTree
{
private:
    BinaryTreeNode<T> *root;

    int height(BinaryTreeNode<T> *node)
    {
        return node ? node->getHeight() : 0;
    }

    //平衡因子=左子樹高度−右子樹高度
    int getBalanceFactor(BinaryTreeNode<T> *node)
    {
        return node ? height(node->getLeft()) - height(node->getRight()) : 0;
    }

    BinaryTreeNode<T> *rotateRight(BinaryTreeNode<T> *y)
    {
        BinaryTreeNode<T> *x = y->getLeft();
        BinaryTreeNode<T> *T2 = x->getRight();

        x->setRight(y);
        y->setLeft(T2);

        y->setHeight(1 + max(height(y->getLeft()), height(y->getRight())));
        x->setHeight(1 + max(height(x->getLeft()), height(x->getRight())));

        return x;
    }

    BinaryTreeNode<T> *rotateLeft(BinaryTreeNode<T> *x)
    {
        BinaryTreeNode<T> *y = x->getRight();
        BinaryTreeNode<T> *T2 = y->getLeft();

        y->setLeft(x);
        x->setRight(T2);

        x->setHeight(1 + max(height(x->getLeft()), height(x->getRight())));
        y->setHeight(1 + max(height(y->getLeft()), height(y->getRight())));

        return y;
    }

    BinaryTreeNode<T> *insert(BinaryTreeNode<T> *node, T key)
    {
        if (!node)
            return new BinaryTreeNode<T>(key);

        if (key < node->getData())
            node->setLeft(insert(node->getLeft(), key));
        else if (key > node->getData())
            node->setRight(insert(node->getRight(), key));
        else
            return node;

        node->setHeight(1 + max(height(node->getLeft()), height(node->getRight())));

        int balance = getBalanceFactor(node);

        /* LL Case 左子樹高度過高，且插入於左子樹的左子樹
                X    
               /
              X
             /
            X        
        */
        if (balance > 1 && key < node->getLeft()->getData())
            return rotateRight(node); //右旋

        /* RR Case 右子樹高度過高，且插入於右子樹的右子樹
            X    
             \  
              X
               \
                X
        */
        if (balance < -1 && key > node->getRight()->getData())
            return rotateLeft(node); //左旋

        /* LR Case 左子樹高度過高，且插入於左子樹的右子樹             
              X    
             /
            1 
             \
              2
        */
        if (balance > 1 && key > node->getLeft()->getData())
        { //先對左子樹進行左旋，再對當前節點右旋
            node->setLeft(rotateLeft(node->getLeft()));
            return rotateRight(node);
        }

        /* RL Case 右子樹高度過高，且插入於右子樹的左子樹
            X
             \
              1
             /
            2 
        */
        if (balance < -1 && key < node->getRight()->getData())
        {//先對右子樹進行右旋，再對當前節點左旋
            node->setRight(rotateRight(node->getRight()));
            return rotateLeft(node);
        }

        return node;
    }

    void inorder(BinaryTreeNode<T> *cur, int depth)
    {
        if (cur == NULL)
            return;
        inorder(cur->getRight(), depth + 1);
        for (int i = 0; i < depth; ++i)
            cout << "  ";
        cout << cur << endl;
        inorder(cur->getLeft(), depth + 1);
    }

    void deleteNodes(BinaryTreeNode<T> *node) {
        if (!node)
            return;
        deleteNodes(node->getLeft());
        deleteNodes(node->getRight());
        delete node;
    }

public:
    AVLTree() : root(NULL) {}

    ~AVLTree() {
        deleteNodes(root);
    }

    void insert(T d)
    {
        root = insert(root, d);
    }

    void inorder()
    {
        inorder(root, 0);
    }
};

int main()
{
    AVLTree<int> *tree = new AVLTree<int>();
    srand(0);
    for (int j = 0; j < 20; j++)
    {
        tree->insert(rand() % 100);
        tree->inorder();
        cout << "###############" << endl;
    }
    delete tree;
}