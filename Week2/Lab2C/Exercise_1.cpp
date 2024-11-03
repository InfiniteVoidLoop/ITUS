#include <iostream>
#include <ctime>

using namespace std;

void generateRandomArray(int *&a, int &n){
    int from = 1000000, to = 2000000;   // Please config the range of the array if you want =))
    n = from + rand() % (to - from + 1);
    a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        a[i] = rand() % 1000000;
    }
}

void copyArray(int *a, int n, int *&b){
    b = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        b[i] = a[i];
    }
}

void heapify(int *a, int n, int i){
    int idmax = i, left = 2 * i + 1, right = 2 * i + 2;

    if (left < n && a[left] > a[idmax]) idmax = left;
    if (right < n && a[right] > a[idmax]) idmax = right;

    if (idmax != i){
        swap(a[i], a[idmax]);
        heapify(a, n, idmax);
    }
}

void heapSort(int*a, int n){
    for (int i = n / 2 - 1; i >= 0; i--){
        heapify(a, n, i);
    }

    for (int i = n - 1; i > 0; i--){
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

void quickSort(int *a, int n){
    if (n <= 1) return;
    int i = 0, j = n - 1;
    int pivot = a[n / 2];
    while (i <= j){
        while(a[i] < pivot) i++;
        while(a[j] > pivot) j--;
        if (i <= j){
            swap(a[i], a[j]);
            i++, j--;
        }
    }
    quickSort(a, j + 1);
    quickSort(a + i, n - i);
}

void printTheFastest(double heapTime, double quickTime){
    if (heapTime < quickTime){
        cout << "The fastest algorithm: Heap Sort" << endl;
    }
    else{
        cout << "The fastest algorithm: Quick Sort" << endl;
    }
}

void printTheSlowest(double heapTime, double quickTime){
    if (heapTime > quickTime){
        cout << "The slowest algorithm: Heap Sort" << endl;
    }
    else{
        cout << "The slowest algorithm: Quick Sort" << endl;
    }
}

int main(){
    int *a = NULL, *b = NULL, n;
    generateRandomArray(a, n);
    copyArray(a, n, b);
    clock_t start = clock();
    heapSort(a, n);
    clock_t end = clock();
    double heapTime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Heap Sort: " << heapTime << " seconds" << endl;

    start = clock();
    quickSort(b, n);
    end = clock();
    double quickTime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Quick Sort: " << quickTime << " seconds" << endl;

    printTheFastest(heapTime, quickTime);
    printTheSlowest(heapTime, quickTime);
    
    free(a);
    free(b);
    return 0;
}

