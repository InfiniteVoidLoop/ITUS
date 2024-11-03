#include <iostream>
using namespace std;
const int MAX = 10000;
int a[MAX], n;

void init(int a[], int &n){
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
}

void printArray(int a[], int n){
    for(int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

void sortArray(int a[], int n){
    for (int i = 0; i < n - 1; i++){
        int ID = i;
        if (a[i] % 2 == 0){
            for (int j = i + 1; j < n; j++)
                if (a[j] % 2 == 0 && a[j] < a[ID])
                    ID = j;
        }
        else{
            for (int j = i + 1; j < n; j++){
                if (a[j] % 2 != 0 && a[j] > a[ID])
                    ID = j;
            }
        }
        if (ID != i){
            int tmp = a[i];
            a[i] = a[ID];
            a[ID] = tmp;
        }
    }
}

int main(){
    init(a, n);
    cout << "Original array: \n";
    printArray(a, n);

    sortArray(a, n);
    cout << "Sorted array: \n";
    printArray(a, n);
    return 0;
}