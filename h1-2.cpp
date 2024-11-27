//用動態記憶體設立一個連續空間的2維陣列(C++)
#include<iostream>

using namespace std;

template<class T>
class Memory{
public :
    static T ** allocArray(int m, int n){   
        
        T ** array = new T*[m];   //分配記憶體給array所指向的指標陣列(array[])
        T *data = new T[m * n];    //分配一個連續的記憶體存放所有元素

        for(int i = 0; i < m; i++){
            array[i] = data + i * n;  //將array所指向的指標陣列內的每個指標指向data陣列中對應的位置
        }

        return array;
    }

    static void freeArray(T ** array){
        delete[] array[0]; //先釋放所有array[]所指向的記憶體(data())
        delete[] array;   //後釋放array指向的所有記憶體(array[])
    }
};

int main(){
    
    int **array;
    int m = 5, n = 10;
    
    array = Memory<int>::allocArray(m, n);

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            array[i][j] = i * 10 + j;
        }
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cout << array[i][j] << " ";
        }
        cout << endl;
    }

    Memory<int>::freeArray(array);

    return 0;
}