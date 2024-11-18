#include <iostream> 
#include <fstream>
#include <sstream>
#include <vector>
#include "../inc/sort.h"

using namespace std;

void copyArr(int *src, int *&des, int n);
void addArray(int *&a, int &n, int val);
void outputArray(fstream& file, const string title, int *a, int n);

int main(){
    fstream inputFile("../test/input.txt", ios::in);
    fstream outputFile("../test/output.txt", ios::out);
    int n = 0, tmp;
    int *a = nullptr;
    while(inputFile >> tmp){
        addArray(a, n, tmp);
    }
    outputArray(outputFile, "Original array: ", a, n);
    
    int *b = nullptr;
    copyArr(a, b, n);
    selectionSort(b, n);
    outputArray(outputFile, "Selection sort: ", b, n);


    int *c = nullptr;
    copyArr(a, c, n);
    interchangeSort(c, n);
    outputArray(outputFile, "Interchange sort: ", c, n);

    int *d = nullptr;
    copyArr(a, d, n);
    quickSort(d, 0, n - 1);
    outputArray(outputFile, "Quick sort: ", d, n);

    int *e = nullptr;
    copyArr(a, e, n);
    bubbleSort(e, n);
    outputArray(outputFile, "Bubble sort: ", e, n);

    int *f = nullptr;
    copyArr(a, f, n);
    shakeSort(f, n);
    outputArray(outputFile, "Shake sort: ", f, n);

    int *g = nullptr;
    copyArr(a, g, n);
    mergeSort(g, 0, n - 1);
    outputArray(outputFile, "Merge sort: ", g, n);

    int *h = nullptr;
    copyArr(a, h, n);
    heapSort(h, n);
    outputArray(outputFile, "Heap sort: ", h, n);

    int *k = nullptr;
    copyArr(a, k, n);
    countingSort(k, n);
    outputArray(outputFile, "Counting sort: ", k, n);

    int *l = nullptr;
    copyArr(a, l, n);
    radixSort(l, n);
    outputArray(outputFile, "Radix sort: ", l, n);

    int *m = nullptr;
    copyArr(a, m, n);
    flashSort(m, n);
    outputArray(outputFile, "Flash sort: ", m, n);

    inputFile.close();
    outputFile.close();
    return 0;
}

//  Additional functions
void copyArr(int *src, int *&des, int n){
    des = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) des[i] = src[i];
}

void addArray(int *&a, int &n, int val){
    int *tmp = (int*)realloc(a, sizeof(int) * (n + 1));
    tmp[n] = val;
    a = tmp;
    n = n + 1;
}

void outputArray(fstream& file, string title, int *a, int n){
    file << title << '\n';
    for (int i = 0; i < n; i++){
        file << a[i] << " ";
    }
    file << "\n \n";
}



