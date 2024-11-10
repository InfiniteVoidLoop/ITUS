#ifndef HEAP_SORT_H
#define HEAP_SORT_H
#include <vector>
#include "node.h"
using namespace std;

typedef struct HeapSort{
    vector <Node*> *heap;
    int n;
    HeapSort(vector <Node*> &_heap){
        heap = &_heap;
        n = (*heap).size();
    }
    void swap(Node* &a, Node* &b){
        Node* tmp = a;
        a = b;
        b = tmp;
    }
    void heapify(int i, int n){
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int minID = i;
        if (l < n && (*heap)[minID]->value > (*heap)[l]->value){
            minID = l;
        }
        if (r < n && (*heap)[minID]->value > (*heap)[r]->value){
            minID = r;
        }
        if (minID != i){
            swap((*heap)[i], (*heap)[minID]);
            heapify(minID, n);
        }
    }
    void buildHeap(int n){
        for (int i = n / 2 - 1; i >= 0; i--){
            heapify(i, n);
        }
    } 
    void pushHeap(int &n, Node* node){
        (*heap).push_back(node);
        int i = n - 1;
        while (i > 0 && (*heap)[(i - 1) / 2]->value > (*heap)[i]->value){
            swap((*heap)[(i - 1) / 2], (*heap)[i]);
            i = (i - 1) / 2;
        }
        n = n + 1;
    }
    Node* getTop(int &n){
        Node* top = (*heap)[0];
        (*heap)[0] = (*heap)[n - 1];
        (*heap).pop_back();
        n = n - 1;
        heapify(0, n);
        return top;
    }
}
HeapSort;
#endif