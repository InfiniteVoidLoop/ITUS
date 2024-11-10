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

    void printHuffmanTree(Node* root, string code){
        if (root->l == nullptr && root->r == nullptr){
            cout << root->ch << " " << code << endl;
            return;
        }
        printHuffmanTree(root->l, code + "0");
        printHuffmanTree(root->r, code + "1");
    }
    
    void getMask(Node* root, string code = ""){
        if (root->l == nullptr && root->r == nullptr){
            compressData[root->ch] = code; 
            if (code == "") compressData[root->ch] = "0";       // Speacial case for single character
            return;
        }
        getMask(root->l, code + "0");
        getMask(root->r, code + "1");
    }
    
    void getMask(void){
        getMask(root);
    }
    void printMask(void){
        for (auto it = compressData.begin(); it != compressData.end(); it++){
            cout << it->first << " " << it->second << endl;
        }
    }
};
#endif