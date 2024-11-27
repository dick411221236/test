#include<iostream>
#include<cmath>      //pow(x, y) = x^y
#include<queue>
    
using namespace std;

template <typename T>
class BinaryTreeInArray{
public:
    BinaryTreeInArray() : array(nullptr), height(0), numOfElement(0){}

    ~BinaryTreeInArray(){
        delete[] array;
    }

    void addElementAsCompleteTree(T data){
        int cap = pow(2, height) - 1;     //pow(2, height) - 1 = 當前樹總共能容納的大小
        if(numOfElement + 1 > cap){
            resize((pow(2, height)) * 2 - 1);     //(pow(2, height)) * 2 - 1 = 再加一層後的總大小
        }
        array[numOfElement] = data;
        numOfElement++;
    }

    void displayInorder(){
        inorder(0);
    }

    void displayPreorder(){
        preorder(0);
    }

    void displayPostorder(){
        postorder(0);
    }

private:
    T* array;
    int height;  //表示樹的層數
    int numOfElement;   //表示當前樹中節點數量

    void resize(int size){    //新增一個更大的array再把原本array的節點利用temp拷貝進新array
        T* temp = new T[numOfElement];
        for(int i = 0; i < numOfElement; i++){
            temp[i] = array[i];
        }
        delete[] array;
        array = new T[size];
        for(int i = 0; i < numOfElement; i++){
            array[i] = temp[i];
        }
        height++;
        delete[] temp;
    }

    void inorder(int index){    //index表示當前位置
        if(index >= numOfElement){
            return;
        }
        inorder(index * 2 + 1);  //當前index的左下
        cout << array[index] << " ";
        inorder(index * 2 + 2);  //當前index的右下
    }

    void preorder(int index){
        if(index >= numOfElement){
            return;
        }
        cout << array[index] << " ";
        preorder(index *2 + 1);
        preorder(index * 2 + 2);
    }

    void postorder(int index){
        if(index >= numOfElement){
            return;
        }
        postorder(index * 2 + 1);
        postorder(index * 2 + 2);
        cout << array[index] << " ";
    }
};

template <typename T>
class BinaryTreeInLinkedList{
private:
    class TreeNode{
    public:
        TreeNode *left, *right;
        T data;
        TreeNode(T d) : data(d), left(nullptr), right(nullptr){}
    };
    TreeNode* root;   //永遠在最上層(第一個節點)
    int numOfElement;

    void inorder(TreeNode* node){
        if(!node){
            return;
        }
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(TreeNode* node){
        if(!node){
            return;
        }
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(TreeNode* node){
        if(!node){
            return;
        }
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

public:

    BinaryTreeInLinkedList() : root(nullptr), numOfElement(0) {}

    ~BinaryTreeInLinkedList(){
        clear(root);
    }

    void clear(TreeNode* node){
        if(!node){
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void addElementAsCompleteTree(T data){
        TreeNode* newNode = new TreeNode(data);
        if(!root){        //設置第一個節點
            root = newNode;
            numOfElement++;
            return;
        }

        queue<TreeNode*> q;
        q.push(root);      //每次都從root開始

        while(!q.empty()){
            TreeNode* current = q.front();
            q.pop();

            if(!(current->left)){      //判斷能不能插左下(是不是空)
                current->left = newNode;
                numOfElement++;
                return;
            }
            else{
                q.push(current->left);   //丟進queue往下延伸
            }

            if(!(current->right)){    //同理右邊
                current->right = newNode;
                numOfElement++;
                return;
            }
            else{
                q.push(current->right);
            }
        }
    }

    void displayInorder(){
        inorder(root);
    }

    void displayPreorder(){
        preorder(root);
    }

    void displayPostorder(){
        postorder(root);
    }
};

int main()
{
  BinaryTreeInArray<int> *b = new BinaryTreeInArray<int>;
  BinaryTreeInLinkedList<int> *tree = new BinaryTreeInLinkedList<int>;
  int j, n;
  cin >> n;
  for(j = 0;j < n;j ++) {
    b->addElementAsCompleteTree(j);
    tree->addElementAsCompleteTree(j);
  }
  b->displayInorder();
  cout << endl;
  tree->displayInorder();
  cout << endl;
  b->displayPreorder();
  cout << endl;
  tree->displayPreorder();
  cout << endl;
  b->displayPostorder();
  cout << endl;
  tree->displayPostorder();
  cout << endl;
  return 0;
}