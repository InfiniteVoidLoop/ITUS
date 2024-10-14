#include<iostream>
using namespace std;

double power(double x, int n){
    if (n == 0) return 1;
    return power(x, n - 1) * x;
}

int main(){
    double x;
    int n;
    cin >> x >> n;
    cout << power(x, n);

    return 0;
}