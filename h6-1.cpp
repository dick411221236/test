#include <iostream>
#include <string>
#include <queue>

using namespace std;

template<class T>
class BinarySearchTree {  //按照左<中<右的大小去存放node
private:
    struct Node {
        T data;
        Node *left, *right;
        Node(T d) : data(d), left(nullptr), right(nullptr) {}
    };

    Node *root;

    void inorder(Node* node) {
        if (!node) {
            return;
        }
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    bool find(Node* node, T d) {
        if (!node) {
            return false;
        }
        if (node->data == d) {
            return true;
        } else if (d < node->data) {
            return find(node->left, d);
        } else {
            return find(node->right, d);
        }
    }

    int calculateHeight(Node* node) {
        if (!node) {
            return 0;
        }
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        clear(root);
    }

    void clear(Node* node) {
        if (!node) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void insertElement(T d) {
        Node* newNode = new Node(d);
        if (!root) {
            root = newNode;
            return;
        }

        Node* current = root;
        while (true) {
            if (d < current->data) {
                if (!current->left) {
                    current->left = newNode;
                    return;
                }
                current = current->left;
            } else {
                if (!current->right) {
                    current->right = newNode;
                    return;
                }
                current = current->right;
            }
        }
    }

    void print() {
        inorder(root);
        cout << endl;
    }

    bool search(T d) {
        return find(root, d);
    }

    int height() {
        return calculateHeight(root);
    }
};

int main() {
    int data;
    string command;
    BinarySearchTree<int> *bst = new BinarySearchTree<int>();
    while (true) {
        cin >> command;
        if (command == "insert") {
            cin >> data;
            bst->insertElement(data);
        } else if (command == "search") {
            cin >> data;
            if (bst->search(data))
                cout << "true" << endl;
            else
                cout << "false" << endl;
        } else if (command == "height") {
            cout << bst->height() << endl;
        } else if (command == "print") {
            bst->print();
        } else if (command == "exit") {
            break;
        }
    }

    delete bst;
    return 0;
}