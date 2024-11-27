//利用泡沫排序、選擇排序、插入排序，排序鏈結串列內隨機生成的值(交換指針)
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node{
public:
    Node(){
        next = NULL;
        pre = NULL;
    }
    
    Node(int n){
        next = NULL;
        pre = NULL;
        data = n;
    }
    
    int getData() {return data;}
    Node *getNext() {return next;}
    Node *getPre() {return pre;}
    void setData(int d) {data = d;}
    void setNext(Node *n) {next = n;}
    void setPre(Node *p) {pre = p;}

private:
    
    int data;
    Node *next, *pre;

};

class List{
public:
    List() {list = NULL;}
    List(int n) {generate(n);}

    void generate(int n){
        list = NULL;
        for(int i = 0;i < n;i++){
            generate();
        }
    }

    void generate(){
        Node *buf = new Node(rand() % 100);
        buf->setNext(list);
        if(list != NULL)
            list->setPre(buf);
        list = buf;
    }

    void swapNodes1(Node *a, Node *b){   //交換相鄰節點的函數swapNodes1
        if(a == NULL || b == NULL)
            return;
        if(a->getNext() != b)  //保證b是a的next
            return;
        
        Node *preA = a->getPre();
        Node *nextB = b->getNext();

        if (preA != NULL) preA->setNext(b);
        b->setPre(preA);
        b->setNext(a);
        a->setPre(b);
        a->setNext(nextB);
        if (nextB != NULL) nextB->setPre(a);

        if(a == list)     //如果原本a是頭，那就更新list指向b
            list = b;
    }

    void swapNodes2(Node *a, Node *b){
        if(a == NULL || b == NULL)
            return;
        if(a->getNext() == b)
            return;
        
        Node *preA = a->getPre();
        Node *nextA = a->getNext();
        Node *nextB = b->getNext(); 
        Node *preB = b->getPre();
        
        if (preA != NULL) preA->setNext(b);
        if(nextB != NULL) nextB->setPre(a);
        nextA->setPre(b);
        preB->setNext(a);        
        b->setPre(preA);
        b->setNext(nextA);
        a->setPre(preB);
        a->setNext(nextB);

        if(a == list)
            list = b;
    }

    void bubbleSort(){
        if(list == NULL)
            return;
        
        bool swapped;
        do{
            swapped = false;
            Node *cur = list;
            while(cur->getNext() != NULL){
                if(cur->getData() > cur->getNext()->getData()){
                    swapNodes1(cur, cur->getNext());
                    swapped = true;
                }
                else{
                    cur = cur->getNext();
                }
            }
        }while(swapped);
    }

    void selectionSort(){
        if(list == NULL)
            return;
        
        Node *temp = list;
        while(temp->getNext() != NULL){
            Node *min = temp;
            Node *next = temp->getNext();
            Node *scan = temp ->getNext();

            while(scan != NULL){
                if(min->getData() > scan->getData())
                    min = scan;
                scan = scan->getNext();
            }

            if(min != temp){
                if(min->getNext() == temp){
                    swapNodes1(temp, min);
                }
                else{
                    swapNodes2(temp, min);
                }
            }
            temp = next;
        }

    }
    void insertionSort(){
        if(list == NULL)
            return;
        
        Node *current = list;
        Node *sorted = NULL;

        while(current != NULL){
            Node *next = current->getNext();

            if(sorted == NULL || sorted->getData() >= current->getData()){
                current->setNext(sorted);
                if(sorted != NULL)
                    sorted->setPre(current);
                sorted = current;
                sorted->setPre(NULL);
            }
            else{
                Node *temp = sorted;
                while(temp->getNext() != NULL && temp->getNext()->getData() < current->getData()){
                    temp = temp->getNext();
                }

                current->setNext(temp->getNext());
                if(temp->getNext() != NULL)
                    temp->getNext()->setPre(current);
                temp->setNext(current);
                current->setPre(temp);
            }

            current = next;
        }

        list = sorted;
    }

    void print(){
        Node *cur = list;
        while(cur !=NULL){
            cout << cur->getData() << " ";
            cur = cur->getNext();
        }
        cout << endl;
    }

    void freeList(){
        Node *cur = list;
        while(cur != NULL){
            Node *next = cur->getNext();
            delete cur;
            cur = next;
        }
        list = NULL;
    }

private:

    Node *list;

};

int main()
{
    srand(time(NULL));

    List *l = new List(10);
    l->print();
    l->bubbleSort();
    l->print();
    l->freeList();
    delete l;

    l = new List(10);
    l->print();
    l->insertionSort();
    l->print();
    l->freeList();
    delete l;

    l = new List(10);
    l->print();
    l->selectionSort();
    l->print();
    l->freeList();
    delete l;

    return 0;
}