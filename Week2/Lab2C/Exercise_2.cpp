#include <iostream>
#include <vector>
#include <ctime> 

using namespace std;

void generateRandomArray(int *&a, int &n){
    int from = 1000000, to = 2000000;   // Please config the range of the array if you want =))
    n = from + rand() % (to - from + 1);
    a = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        a[i] = 10000000 + rand() % 1000000;
    }
}

void copyArray(int *a, int n, int *&b){
    b = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        b[i] = a[i];
    }
}

void mergeSort(int *a, int n){
    if (n <= 1) return;
    int mid = (n - 1) / 2, nleft = mid + 1, nright = n - nleft;

    int *leftArray = (int*)malloc(nleft * sizeof(int));
    int *rightArray = (int*)malloc(nright * sizeof(int));
    
    for (int i = 0; i < nleft; i++){
        leftArray[i] = a[i];
    }
    for (int i = 0; i < nright; i++){
        rightArray[i] = a[mid + i + 1];
    }

    mergeSort(leftArray, nleft);
    mergeSort(rightArray, nright);
    
    int i = 0, j = 0, k = 0;
    while (i < nleft && j < nright){
       if (leftArray[i] < rightArray[j])
            a[k++] = leftArray[i++];
        else 
            a[k++] = rightArray[j++];
    }
    while (i < nleft){
        a[k++] = leftArray[i++];
    }
    while (j < nright){
        a[k++] = rightArray[j++];
    }
    free(leftArray);
    free(rightArray);
}

void countingSort(int *a, int n){
    int maxValue = a[0];
    for (int i = 0; i < n; i++) maxValue = max(maxValue, a[i]);
    int *count = (int*)calloc(maxValue + 1, sizeof(int));
    for (int i = 0; i < n; i++) count[a[i]]++;
    for (int i = 1; i <= maxValue; i++) count[i] += count[i - 1];

    int *tmp = (int*)malloc(n * sizeof(int));
    for (int i = n - 1; i >=0; --i){
        tmp[--count[a[i]]] = a[i];
    }
    for (int i = 0; i < n; i++){
        a[i] = tmp[i];
    }
    free(tmp);
    free(count);
}

void radixSort(int *a, int n){
    vector <int> lot[10];
    int maxVal = a[0];
    for (int i = 0; i < n; i++) maxVal = max(maxVal, a[i]);
    
    int d = 1;
    while (maxVal / d){
        for (int i = 0; i < n; i++){
            int digit = (a[i] / d) % 10;
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

void printTheFastest(double mergeTime, double countingTime, double radixTime, double flashTime){
    if (mergeTime < countingTime && mergeTime < radixTime && mergeTime < flashTime){
        cout << "The fastest algorithm: Merge Sort" << endl;
    }
    else if (countingTime < mergeTime && countingTime < radixTime && countingTime < flashTime){
        cout << "The fastest algorithm: Counting Sort" << endl;
    }
    else if (radixTime < mergeTime && radixTime < countingTime && radixTime < flashTime){
        cout << "The fastest algorithm: Radix Sort" << endl;
    }
    else{
        cout << "The fastest algorithm: Flash Sort" << endl;
    }
}

void printTheSlowest(double mergeTime, double countingTime, double radixTime, double flashTime){
    if (mergeTime > countingTime && mergeTime > radixTime && mergeTime > flashTime){
        cout << "The slowest algorithm: Merge Sort" << endl;
    }
    else if (countingTime > mergeTime && countingTime > radixTime && countingTime > flashTime){
        cout << "The slowest algorithm: Counting Sort" << endl;
    }
    else if (radixTime > mergeTime && radixTime > countingTime && radixTime > flashTime){
        cout << "The slowest algorithm: Radix Sort" << endl;
    }
    else{
        cout << "The slowest algorithm: Flash Sort" << endl;
    }
}

// check if the array is sorted
// bool checkSortedArray(int *a, int n){
//     for (int i = 0; i < n - 1; i++){
//         if (a[i] > a[i + 1]) return false;
//     }
//     return true;
// }

int main(){
    srand(time(NULL));
    int *a, n;
    generateRandomArray(a, n);
    int *b;
    copyArray(a, n, b);
    int *c;
    copyArray(a, n, c);
    int *d;
    copyArray(a, n, d);
    
    clock_t start = clock();
    mergeSort(a, n);
    clock_t end = clock();
    double mergeTime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Merge sort: " << mergeTime << endl;

    start = clock();
    countingSort(b, n);
    end = clock();
    double countingTime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Counting sort: " << countingTime << endl;

    start = clock();
    radixSort(c, n);
    end = clock();
    double radixTime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Radix sort: " << radixTime << endl;

    start = clock();
    flashSort(d, n);
    end = clock();
    double flashTime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Flash sort: " << flashTime << endl;

    printTheFastest(mergeTime, countingTime, radixTime, flashTime);
    printTheSlowest(mergeTime, countingTime, radixTime, flashTime);
    
    // Check if the array is sorted
    // cout << "Check mergeSort: " << (checkSortedArray(a, n) ? "Sorted" : "Unsorted") << endl;
    // cout << "Check countingSort: " << (checkSortedArray(b, n) ? "Sorted" : "Unsorted") << endl;
    // cout << "Check radixSort: " << (checkSortedArray(c, n) ? "Sorted" : "Unsorted") << endl;
    // cout << "Check flashSort: " << (checkSortedArray(d, n) ? "Sorted" : "Unsorted") << endl;
    
    free(a);
    free(b);
    free(c);
    free(d);
    return 0;
}