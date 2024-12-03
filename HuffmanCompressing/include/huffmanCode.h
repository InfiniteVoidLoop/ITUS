#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <map>
#include "node.h"
#include "heapSort.h"
#include "globalVar.h"
#include "utils.h"

#define fi first
#define se second
#define pb push_back
using namespace std;

struct HuffmanCompressing{
    Node* root = nullptr;
    
    void buildHuffmanTree(void){
        int n = lst.size();
        HeapSort heapSort(lst);
        heapSort.buildHeap(lst.size());
        while(n > 1){
            Node* l = heapSort.getTop(n);
            Node* r = heapSort.getTop(n);
            Node* node = new Node();
            node->value = l->value + r->value;
            // cout << l->value << " " << r->value << " " << node->value << endl;
            node->l = l;
            node->r = r;
            heapSort.pushHeap(n, node);
        }
        root = heapSort.getTop(n);
    }
    
    void getMask(Node* root, int code, int bitSize){
        if (root->l == nullptr && root->r == nullptr){
            compressData[root->ch] = make_pair(code, bitSize);
            if (code == 0 && bitSize == 0) compressData[root->ch] = make_pair(0, 1); 
            return;    // Speacial case for single character
        }
        getMask(root->l, code << 1, bitSize + 1);
        getMask(root->r, (code << 1) | 1, bitSize + 1);
    }
    void getMask(void){
        getMask(root, 0, 0);
    }
};
#endif