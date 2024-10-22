#include <iostream>
using namespace std;

struct T1{
    int* t2;
};

T1** t1;

int main(){
    t1 = (T1**)realloc(t1, 2 * sizeof(T1*));
    t1[0] = (T1*)malloc(sizeof(T1));
    t1[0]->t2 = nullptr;
    free(t1[0]->t2);
    free(t1[0]);
    free(t1);
    cout << "check!!";
}