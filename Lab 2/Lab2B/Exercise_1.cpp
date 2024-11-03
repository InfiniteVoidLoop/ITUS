#include <iostream>
#include <ctime>
using namespace std;

void insertionSort(int *a, int n){
    for (int i = 1; i < n; i++){
        int val = a[i], j = i - 1;
        while(j >= 0 && a[j] > val){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = val;
    }
}

void selectionSort(int *a, int n){
    for (int i = 0; i < n - 1; i++){
        int minID = i;
        for (int j = i + 1; j < n; j++){
            if (a[j] < a[minID]) minID = j;
        }
        if (minID != i){
            int tmp = a[i];
            a[i] = a[minID];
            a[minID] = tmp;
        }
    }
}

void interchangeSort(int *a, int n){
    for (int i = 0; i < n - 1; i++){
        for (int j = i + 1; j < n; j++){
            if (a[i] > a[j]){
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

void generateRandomArray(int *&a, int &n){
    int from = 10000, to = 20000;     // Please config the range of the array if you want =))
    n = from + rand() % (to - from + 1);
    a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        a[i] = rand() % 1000;
    }
}

void copyArray(int *a, int n, int *&b){
    b = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        b[i] = a[i];
    }
}

void printTheFastest(double insertTime, double selectTime, double interchangeTime){
    if (insertTime < selectTime && insertTime < interchangeTime){
        cout << "The fastest algorithm: Insertion Sort" << endl;
    }
    else if (selectTime < insertTime && selectTime < interchangeTime){
        cout << "The fastest algorithm: Selection Sort" << endl;
    }
    else{
        cout << "The fastest algorithm: Interchange Sort" << endl;
    }
}

void printTheSlowest(double insertTime, double selectTime, double interchangeTime){
    if (insertTime > selectTime && insertTime > interchangeTime){
        cout << "The slowest algorithm: Insertion Sort" << endl;
    }
    else if (selectTime > insertTime && selectTime > interchangeTime){
        cout << "The slowest algorithm: Selection Sort" << endl;
    }
    else{
        cout << "The slowest algorithm: Interchange Sort" << endl;
    }
}


int main(){
    srand(time(0));
    int *arr, *a, *b, *c, n;
    generateRandomArray(arr, n);
    copyArray(arr, n, a);   // "a" array for insertion sort
    copyArray(arr, n, b);   // "b" array for selection sort
    copyArray(arr, n, c);   // "c" array for interchange sort

    cout << "The number of elements in the array: " << n << endl;

    clock_t start, end;
    double insertTime, selectTime, interchangeTime;
    
    start = clock();
    insertionSort(a, n);
    end = clock();
    insertTime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Time for insertion sort: " << insertTime << " seconds" << endl;

    start = clock();
    selectionSort(b, n);
    end = clock();
    selectTime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Time for selection sort: " << selectTime << " seconds" << endl;

    start = clock();
    interchangeSort(c, n);
    end = clock();
    interchangeTime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Time for interchange sort: " << interchangeTime << " seconds" << endl;

    printTheFastest(insertTime, selectTime, interchangeTime);
    printTheSlowest(insertTime, selectTime, interchangeTime);
    
    free(arr);
    free(a);
    free(b);
    free(c);
    return 0;
}
