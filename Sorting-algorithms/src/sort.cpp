#include "../inc/sort.h"
#include <vector>
#include <iostream>
using namespace std;

// Sorting functions
void selectionSort(int *a, int n){
    for (int i = 0; i < n - 1; i++){
        int minID = i;
        for (int j = i + 1; j < n; j++){
            if (a[j] < a[minID]) minID = j;
        }
        if (i != minID){
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

void insertionSort(int *a, int n){
    for (int i = 1; i < n; i++){
        int key = a[i];
        int j = i - 1;
        while(j >= 0 && a[j] > key){
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

void quickSort(int *a, int l, int r){
    if (l >= r) return;
    int pivot = a[(l + r) / 2];
    int i = l, j = r;
    while (i <= j){
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;
        if (i <= j){
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    }
    quickSort(a, l, j);
    quickSort(a, i, r);
}

void bubbleSort(int *a, int n){
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (a[j] > a[j + 1]){
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

void shakeSort(int *a, int n){
    int l = 0, r = n - 1;
    while (l < r){
        for (int i = l; i < r; i++){
            if (a[i] > a[i + 1]){
                int tmp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = tmp;
            }
        }
        r--;
        for (int i = r; i > l; i--){
            if (a[i] < a[i - 1]){
                int tmp = a[i];
                a[i] = a[i - 1];
                a[i - 1] = tmp;
            }
        }
        l++;
    }
}

void mergeSort(int a[], int l, int r){
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m+1, r);
    int i = l, j = m + 1, k = 0;
    int *tmp = new int[r - l + 1];
    while (i <= m && j <= r){
        if (a[i] < a[j]){
            tmp[k++] = a[i++];
        }
        else{
            tmp[k++] = a[j++];
        }
    }
    while (i <= m){
        tmp[k++] = a[i++];
    }
    while (j <= r){
        tmp[k++] = a[j++];
    }
    for (int i = l; i <= r; i++){
        a[i] = tmp[i - l];
    }
    delete[] tmp;
}

void heapify(int *a, int n, int id){
    int largest = id, l = 2 * id + 1, r = 2 * id + 2;
    if (l < n && a[l] > a[largest]) largest = l;
    if (r < n && a[r] > a[largest]) largest = r;
    if (largest != id){
        int tmp = a[id];
        a[id] = a[largest];
        a[largest] = tmp;
        heapify(a, n, largest);
    }
}

void heapSort(int *a, int n){
    for (int i = n/2 - 1; i >= 0; --i){
        heapify(a, n, i);
    }
    for (int i = n - 1; i > 0; --i){
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}

void countingSort(int *a, int n){
    int max = a[0];
    for (int i = 1; i < n; i++){
        if (a[i] > max) max = a[i];
    }
    int *count = new int[max + 1];
    for (int i = 0; i <= max; i++){
        count[i] = 0;
    }
    for (int i = 0; i < n; i++){
        count[a[i]]++;
    }
    int k = 0;
    for (int i = 0; i <= max; i++){
        while(count[i] > 0){
            a[k++] = i;
            count[i]--;
        }
    }
    delete[] count;
}

void radixSort(int *a, int n){
    vector <int> lot[10];
    int maxVal = a[0];
    for (int i = 0; i < n; i++) maxVal = max(maxVal, a[i]);
    
    int d = 1;
    while(maxVal / d){
        for (int i = 0; i < n; i++){
            int digit = (a[i]/d) % 10;
            lot[digit].push_back(a[i]);
        }
        int cur = 0;
        for (int digit = 0; digit < 10; digit++){
            for (int i = 0; i < lot[digit].size(); i++){
                a[cur++] = lot[digit][i];
            }
            lot[digit].clear();
        }
        d = d * 10;
    }
}

void flashSort(int *a, int n){
    int m = n * 0.43;   // number of buckets
    int *bucket = (int*)calloc(m, sizeof(int));
    int minVal = a[0], maxID = 0;
    for(int i = 1; i < n; i++){
        minVal = min(minVal, a[i]);
        if (a[i] > a[maxID]) maxID = i;
    }
    double c1 = (double)(m - 1) / (a[maxID] - minVal);
    // Number of elements in each bucket
    for (int i = 0; i < n; i++){
        int bucketIndex = (int)(c1 * (a[i] - minVal));
        bucket[bucketIndex]++;
    }
    // Last index of each bucket
    for (int i = 1; i < m; i++){
        bucket[i] += bucket[i - 1];
    }

    // Move elements to the right bucket
    int *tmp = (int*)malloc(n * sizeof(int));
    for (int i = n - 1; i >= 0; i--){
        int bucketIndex = (int)(c1 * (a[i] - minVal));
        tmp[--bucket[bucketIndex]] = a[i];
    }
    for (int i = 0; i < n; i++){
        a[i] = tmp[i];
    }
    free(tmp);
    free(bucket);

    // Apply insertion sort
    for (int i = 1; i < n; i++){
        int hold = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > hold){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = hold;
    }
}