#include <iostream>
#include <fstream>

using namespace std;

int linearSearch(int*, int , int );
int sentinelLinearSearch(int *&, int &, int);
int binarySearch(int*, int , int );
int interpolationSearch(int *, int, int);

int linearSearch(int *a, int n, int val){
    int i = 0;
    while (i < n && a[i] != val) i++;
    return (i < n ? i : -1);
}

int sentinelLinearSearch(int *&a, int &n, int val){
    a = (int*)realloc(a, (n + 1) * sizeof(int));
    a[n] = val;
    int i = 0;
    while (a[i] != val) i++;
    return (i < n ? i : -1);
}

int binarySearch(int *a, int n, int val){
    int mid, l = 0, r = n - 1, res = -1;
    while(l <= r){
        mid = (l + r) >> 1;
        if (a[mid] == val){
            res = mid;
            r = mid - 1;
        }
        if (a[mid] < val) l = mid + 1;    
        else r = mid - 1;
    }
    return res;
}

int interpolationSearch(int *a, int n, int val){
    int l = 0, r = n - 1, res = -1;
    while(l <= r){
        int pos_val = l + (r - l)*(val - a[l])/(a[r] - a[l]);
        if (a[pos_val] == val){
            res = pos_val;
            r = pos_val - 1;
        }
        else if (a[pos_val] < val){
            l = pos_val + 1;
        }
        else r = pos_val - 1;
    }
    return res;
}

int main(int argc, char* argv[]){
    int algo = atoi(argv[1]);
    int val = atoi(argv[2]);
    char* fileInName = argv[3];
    char* fileOutName = argv[4];
    fstream inputFile(fileInName, ios::in);
    fstream outputFile(fileOutName, ios::out);

    //  Input array a with size n
    int *a = nullptr, n;
    inputFile >> n;
    a = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i) inputFile >> a[i];

    if (algo == 1)
        outputFile << linearSearch(a, n, val);
    else if (algo == 2)
        outputFile << sentinelLinearSearch(a, n, val);
    else if (algo == 3)
        outputFile << binarySearch(a, n, val);
    else if (algo == 4)
        outputFile << interpolationSearch(a, n, val);
    
    free(a);
    inputFile.close();
    outputFile.close();
    return 0;
}
