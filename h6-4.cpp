#include <iostream>
#include <vector>
#include <stdexcept>
#include <time.h>

using namespace std;

template<class T>
class MinMaxHeap {
public:
    MinMaxHeap() {}

    void insert(int value) {       //先插在最後的位置再開始判斷可不可以往上浮
        heap.push_back(value);
        bubbleUp(heap.size() - 1);
    }

    T getMin() const {       //root一定最小
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }

    T getMax() const {        //最大值一定在前3個節點中
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        if (heap.size() == 1) {
            return heap[0];
        }
        if (heap.size() == 2) {
            return heap[1];
        }
        return max(heap[1], heap[2]);
    }

    void deleteMin() {        //把最後一個元素跟root交換，再把交換後的最後一個元素(原root)刪掉，再利用trickleDown去把新root排好
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        swap(heap[0], heap.back());
        heap.pop_back();
        trickleDown(0);
    }

    void deleteMax() {     //跟deleteMin差不多
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        int maxIdx;
        if (heap.size() == 1) {
            maxIdx = 0;  // 當只有一個元素時，最大值就是根節點
        } else {
            maxIdx = (heap.size() == 2 || heap[1] > heap[2]) ? 1 : 2;  //如果超過2層那最大值一定在第2層
        }
        swap(heap[maxIdx], heap.back());
        heap.pop_back();
        trickleDown(maxIdx);
    }

private:
    vector<T> heap;

    bool isMinLevel(int index) const {  //判斷是否為min層
        int level = 0;
        while (index > 0) {
            index = (index - 1) / 2;
            ++level;
        }
        return (level % 2 == 0);     //如果是偶數層就是min層
    }

    void bubbleUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if (isMinLevel(index)) {
            if (heap[index] > heap[parent]) {     //判斷是否能上浮
                swap(heap[index], heap[parent]);
                bubbleUpMax(parent);
            } else {
                bubbleUpMin(index);
            }
        } else {                                //如果是是max層的情形
            if (heap[index] < heap[parent]) {
                swap(heap[index], heap[parent]);
                bubbleUpMin(parent);
            } else {
                bubbleUpMax(index);
            }
        }
    }

    void bubbleUpMin(int index) {     //判斷min層的節點有沒有比他上面的min層的節點小
        if (index <= 2) return;
        int grandparent = (index - 3) / 4;
        if (heap[index] < heap[grandparent]) {
            swap(heap[index], heap[grandparent]);
            bubbleUpMin(grandparent);
        }
    }

    void bubbleUpMax(int index) {   //判斷max層的節點有沒有比他上面的max層的節點大
        if (index <= 2) return;    //前2層的節點沒有祖輩
        int grandparent = (index - 3) / 4;
        if (heap[index] > heap[grandparent]) {
            swap(heap[index], heap[grandparent]);  //有就交換
            bubbleUpMax(grandparent);    //再往他的更上層去檢查
        }
    }

    void trickleDown(int index) {    //呼叫trickleDownMin或trickleDownMax
        if (isMinLevel(index)) {
            trickleDownMin(index);
        } else {
            trickleDownMax(index);
        }
    }

    void trickleDownMin(int index) {   //判斷是否要跟下層(max)或下下一層(min)交換
        int m = minIndex(index);
        if (m >= heap.size()) return;

        if (m >= 4 * index + 3) {         //下面有2層以上的情況
            if (heap[m] < heap[index]) {
                swap(heap[m], heap[index]);
                int parent = (m - 1) / 2;
                if (heap[m] > heap[parent]) {    //判斷是否比下下一層大又比下一層大
                    swap(heap[m], heap[parent]);
                }
                trickleDownMin(m);     //繼續往下判斷
            }
        } else if (heap[m] < heap[index]) {   //如果下面只有一層的情況
            swap(heap[m], heap[index]);
        }
    }

    void trickleDownMax(int index) {  //判斷是否要跟下層(min)或下下一層(max)交換
        int m = maxIndex(index);
        if (m >= heap.size()) return;

        if (m >= 4 * index + 3) {
            if (heap[m] > heap[index]) {
                swap(heap[m], heap[index]);
                int parent = (m - 1) / 2;
                if (heap[m] < heap[parent]) {
                    swap(heap[m], heap[parent]);
                }
                trickleDownMax(m);
            }
        } else if (heap[m] > heap[index]) {
            swap(heap[m], heap[index]);
        }
    }

    int minIndex(int index) const {      //判斷我的下面2層內哪個index是最小的(ps:要比自己小，不然就不變)
        //先跟下一層(max層)去比，(主要在處理下一層是最後一層的情況)
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int minIndex = index;

        if (leftChild < heap.size() && heap[leftChild] < heap[minIndex]) {
            minIndex = leftChild;
        }
        if (rightChild < heap.size() && heap[rightChild] < heap[minIndex]) {
            minIndex = rightChild;
        }
        //再來跟下下一層(min層)比
        int grandChildStart = 4 * index + 3;
        for (int i = 0; i < 4; ++i) {
            int grandChild = grandChildStart + i;
            if (grandChild < heap.size() && heap[grandChild] < heap[minIndex]) {
                minIndex = grandChild;
            }
        }
        return minIndex;
    }

    int maxIndex(int index) const {      //判斷我的下面2層內哪個index是最大的(ps:要比自己大)
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int maxIndex = index;

        if (leftChild < heap.size() && heap[leftChild] > heap[maxIndex]) {
            maxIndex = leftChild;
        }
        if (rightChild < heap.size() && heap[rightChild] > heap[maxIndex]) {
            maxIndex = rightChild;
        }

        int grandChildStart = 4 * index + 3;
        for (int i = 0; i < 4; ++i) {
            int grandChild = grandChildStart + i;
            if (grandChild < heap.size() && heap[grandChild] > heap[maxIndex]) {
                maxIndex = grandChild;
            }
        }
        return maxIndex;
    }
};

int main() {
    MinMaxHeap<int> mmHeap;
    int j;
    srand(time(NULL));
    for (j = 0; j < 10; j++)
        mmHeap.insert(rand() % 100);

    cout << "Minimum elements in order: ";
    while (true) {
        try {
            cout << mmHeap.getMin() << " ";
            mmHeap.deleteMin();
        }
        catch (const std::exception&) {
            break;
        }
    }
    cout << endl;

    for (j = 0; j < 10; j++)
        mmHeap.insert(rand() % 100);

    cout << "Maximum elements in order: ";
    while (true) {
        try {
            cout << mmHeap.getMax() << " ";
            mmHeap.deleteMax();
        }
        catch (const std::exception&) {
            break;
        }
    }

    return 0;
}