#include<iostream>
#include<vector>

using namespace std;

template<typename T>
class TreeInLinkedList{
private:
    class TreeNode{
    public:
        TreeNode* parent;   //一個指向父節點的指針
        T data;
        TreeNode(TreeNode* p, int d) : parent(p), data(d){}
    };

    vector<TreeNode*> *nodeList;

    void displayPreorderHelper(TreeNode* node){
        if(!node){
            return;
        }
        cout << node->data << " ";   //中間先輸出
        for(auto child : *nodeList){
            if(child->parent == node){
                displayPreorderHelper(child);
            }
        }
    }

    void displayPostorderHelper(TreeNode* node){
        if(!node){
            return;
        }
        for(auto child : *nodeList){
            if(child->parent == node){
                displayPostorderHelper(child);
            }
        }
        cout << node->data << " ";
    }

public:
    TreeInLinkedList(){
        nodeList = new vector<TreeNode*>();
    }

    ~TreeInLinkedList(){
        for(auto node : *nodeList){
            delete node;
        }
        delete nodeList;
    }

    void addElement(T data){    
        int size = nodeList->size();
        if(data == 1){    //第一個節點
            TreeNode* newNode = new TreeNode(nullptr, data);
            nodeList->push_back(newNode);
        }
        else{    //可以整除於vector裡的元素就加在他下面(同樣的值可以有很多父節點 ex:4分別在2和1下面)
            for(int i = 0; i < size; i++){
                if(data % (*nodeList)[i]->data == 0){
                    TreeNode* newNode = new TreeNode((*nodeList)[i], data);
                    nodeList->push_back(newNode);
                }
            }
        }
    }

    void displayPreorder(){
        if(!nodeList->empty()){
            displayPreorderHelper((*nodeList)[0]);
        }
    }

    void displayPostorder(){
        if(!nodeList->empty()){
            displayPostorderHelper((*nodeList)[0]);
        }
    }
};

int main()
{
  TreeInLinkedList<int> *tree = new TreeInLinkedList<int>();
  int j;
  int n;
  cin >> n;
  for(j = 1;j <= n;j ++)
    tree->addElement(j);
  tree->displayPreorder();
  cout << endl;
  tree->displayPostorder();
  cout << endl;

  delete tree;
  return 0;
}