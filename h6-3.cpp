#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template<class T>
class MaxHeap {
public:
    MaxHeap() : heapData() {}

    void insert(T value) {
        heapData.push_back(value);
        siftUp(heapData.size() - 1);
    }

    // 提取根節點（最大元素）並移除它
    T extract() {
        if (heapData.empty()) {
            throw out_of_range("Heap is empty");
        }
        T root = heapData[0];               // 根節點即為最大元素
        heapData[0] = heapData.back();      // 用尾端的元素取代根節點
        heapData.pop_back();                // 刪除尾端元素
        if (!heapData.empty()) {
            siftDown(0);                    // 使用 siftDown 調整，維持最大堆的特性
        }
        return root;
    }

    int count() const {       //回傳堆中元素的數量
        return heapData.size();
    }

private:
    vector<T> heapData;

    void siftUp(int index) {  //比較大就往上升
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (heapData[index] <= heapData[parentIndex])    
                break;
            swap(heapData[index], heapData[parentIndex]);    //如果後面有更大的([index] > [parentIndex])就把後面跟前面交換
            index = parentIndex;
        }
    }

    void siftDown(int index) {  //比較小就向下沉
        int size = heapData.size();
        while (index < size) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            if (leftChild < size && heapData[leftChild] > heapData[largest]) {
                largest = leftChild;
            }
            if (rightChild < size && heapData[rightChild] > heapData[largest]) {
                largest = rightChild;
            }
            if (largest == index) break;
            
            swap(heapData[index], heapData[largest]);
            index = largest;
        }
    }
};

int main() {    //test
    MaxHeap<int> heap;

    // 測試插入元素
    heap.insert(10);
    heap.insert(20);
    heap.insert(5);
    heap.insert(30);
    heap.insert(15);

    cout <<  heap.count() << endl;

    // 測試提取最大元素
    cout <<  heap.extract() << endl;  // 應該輸出 30
    cout <<  heap.count() << endl;

    // 再次提取最大元素
    cout <<  heap.extract() << endl;  // 應該輸出 20
    cout <<  heap.count() << endl;

    // 繼續提取
    cout <<heap.extract() << endl;  // 應該輸出 15
    cout <<  heap.extract() << endl;  // 應該輸出 10
    cout <<  heap.extract() << endl;  // 應該輸出 5

    // 嘗試在空堆中提取（應該拋出異常）
    try {
        heap.extract();
    } catch (const std::out_of_range& e) {
        cerr <<  e.what() << std::endl;
    }

    return 0;
}