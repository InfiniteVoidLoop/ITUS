#include <iostream>
using namespace std;

void init(int **&a, int &m, int &n){
    cin >> m >> n;
    a = (int**)malloc((m) * sizeof(int*));
    for (int i = 0; i < m; i++)
        a[i] = (int*)malloc((n) * sizeof(int));
    
    for (int i = 0; i < m; i++) 
        for (int j = 0; j < n; ++j) 
            cin >> a[i][j];
}

void interchangeSort(int *a, int n){
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j]) swap(a[i], a[j]);
}

void process(int** &a, int m, int n){
    int* b = (int*)malloc(m * n * sizeof(int));
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; ++j)
            b[i * n + j] = a[i][j];
    }
    interchangeSort(b, m * n);
    int cur = 0;
    for (int d = 0; d < (1 + min(m, n)) / 2; ++d){
        for (int j = d; j < n - d; ++j)
            if (cur < m * n) a[d][j] = b[cur++];
        
        for (int i = d + 1; i < m - d; i++)
            if (cur < m * n) a[i][n - d - 1] = b[cur++];
    
        for (int j = n - d - 2; j >= d; --j)
            if (cur < m * n) a[m - d - 1][j] = b[cur++];
        
        for (int i = m - d - 2; i >= d + 1; --i)
            if (cur < m * n) a[i][d] = b[cur++];
        
    }
    free(b);
}

void output2DArray(int **a, int m, int n){
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; ++j){
            cout << a[i][j] << " ";
        }
        cout << '\n';
    }
}

void free2DArray(int **&a, int m, int n){
    for (int i = 0; i < m; i++) free(a[i]);
    free(a);
}

int main(){
    int m, n;
    int **a;
    init(a, m, n);
    process(a, m, n);
    output2DArray(a, m, n);
    free2DArray(a, m, n);
    
    return 0;
}
