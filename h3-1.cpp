//利用泡沫排序、選擇排序、插入排序，排序鏈結串列內隨機生成的值(交換節點裡的值)
#include <iostream>
#include <cstdlib>  //rand()、srand()
#include <ctime>  //time()

#define SIZE 100

using namespace std;

class Node {
public:
    Node() {
        next = NULL;
        pre = NULL;
    }
    Node(int n) {
        data = n;
        next = NULL;
        pre = NULL;
    }
    int getData() { return data; }
    Node* getNext() { return next; }
    Node* getPre() { return pre; }
    void setData(int d) { data = d; }
    void setNext(Node* n) { next = n; }
    void setPre(Node* p) { pre = p; }

private:
    int data;
    Node* next, * pre;
};

class List {
public:
    List() { list = NULL; }
    List(int n) { generate(n); }

    void generate(int n) {
        int j;
        list = NULL;
        for (j = 0; j < n; j++)
            generate();
    }

    void generate() {
        Node* buf = new Node(rand());  //隨機生成buf的值
        buf->setNext(list);  //將buf接在原list(頭)前
        if (list != NULL)
            list->setPre(buf);
        list = buf;  //將list更新為頭
    }

    void bubbleSort() {  //從頭開始將大的往上浮(由尾開始排到小)
        if (list == NULL)
            return;

        bool swapped;
        Node* ptr1; //當前的引索
        Node* lptr = NULL; //最後一組的下一個

        do {
            swapped = false;
            ptr1 = list;

            while (ptr1->getNext() != lptr) {
                if (ptr1->getData() > ptr1->getNext()->getData()) {
                    int temp = ptr1->getData();
                    ptr1->setData(ptr1->getNext()->getData()); 
                    ptr1->getNext()->setData(temp);
                    swapped = true;
                }
                ptr1 = ptr1->getNext();
            }
            lptr = ptr1;  //已經是最大就不用再比所以lptr往前一節
        } while (swapped);  //只剩一組數據，swapped為false終止迴圈
    }

    void selectionSort() {  //引索min追蹤當前最小的值，最後再跟第一個交換(由頭開始排到大)
        if (list == NULL)
            return;

        Node* temp = list;

        while (temp != NULL) {
            Node* min = temp;
            Node* r = temp->getNext();

            while (r != NULL) {
                if (r->getData() < min->getData())
                    min = r;
                r = r->getNext();
            }

            if (min != temp) {   //交換
                int tempData = temp->getData();
                temp->setData(min->getData());
                min->setData(tempData);
            }

            temp = temp->getNext();  
        }
    }

    void insertionSort() {
        if (list == NULL)
            return;

        Node* sorted = NULL;  //連接已排序數列的新的鏈結
        Node* current = list;

        while (current != NULL) {
            Node* next = current->getNext();   //因為會改變current，所以先儲存current的next

            if (sorted == NULL || sorted->getData() >= current->getData()) {  //判斷是否加數據到sorted前
                current->setNext(sorted);
                if (sorted != NULL)
                    sorted->setPre(current);
                sorted = current;
                sorted->setPre(NULL);
            } else {
                Node* temp = sorted;
                while (temp->getNext() != NULL && temp->getNext()->getData() < current->getData()) { //判斷數據應該插在哪
                    temp = temp->getNext();
                }

                current->setNext(temp->getNext());   //插進去
                if (temp->getNext() != NULL)
                    temp->getNext()->setPre(current);
                temp->setNext(current);
                current->setPre(temp);
            }

            current = next;  
        }

        list = sorted;   //將list改為新鏈結的頭
    }

    void print() {
        Node* cur = list;
        while (cur != NULL) {
            cout << cur->getData() << " ";
            cur = cur->getNext();
        }
        cout << endl;
    }

    // 釋放所有節點的記憶體
    void freeList() {
        Node* current = list;
        while (current != NULL) {
            Node* next = current->getNext();
            delete current;  // 釋放當前節點的記憶體
            current = next;  // 移動到下一個節點
        }
        list = NULL;  // 將鏈表設為空，防止再次呼叫到freeList
    }

private:
    Node* list;   //list會一直指向頭
};

int main() {
    srand(time(NULL));

    List* l = new List(10);
    l->print();
    l->bubbleSort();
    l->print();
    l->freeList();  // 釋放鏈表記憶體
    delete l;  // 釋放 List 類別的記憶體

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
}