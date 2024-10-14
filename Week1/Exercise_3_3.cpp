#include<iostream>
using namespace std;

int fibonacci(int i){
    if (i == 0 || i == 1) return i;
    return fibonacci(i - 1) + fibonacci(i - 2);
}

int main(){
    int n;
    cin >> n;
    cout << fibonacci(n);

    return 0;
}