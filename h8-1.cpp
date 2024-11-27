//用動態記憶體設立一個連續空間的2維陣列(C語言)
#include<stdio.h>
#include<stdlib.h>

void allocArray(int *** p, int m, int n){

    *p = (int**)malloc(m * sizeof(int*)); //分配記憶體給一個指標陣列array去儲存每一行的指標

    int * data = (int*)malloc(m * n * sizeof(int));  //分配一個連續的記憶體存放所有元素

    for(int i = 0; i < m; i++){
        (*p)[i] = data + i * n;
    }
}

int main(){
    int **array;
    int j, k;

    allocArray(&array, 5, 10);

    for(j = 0; j < 5; j++){
        for(k = 0; k < 10; k++){
            array[j][k] = j * 10 + k;
        }
    }
    for(j = 0; j < 5; j++){
        for(k = 0; k < 10; k++){
            printf("%d ", array[j][k]);
        }
        printf("\n");
    }

    free(array[0]);
    free(array);

    return 0;
}