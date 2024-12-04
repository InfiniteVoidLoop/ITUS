#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H
#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <bitset>
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

    void deleteTree(Node* root){
        if (root == nullptr) return;
        deleteTree(root->l);
        deleteTree(root->r);
        delete root;
    }
};

struct CanonicalHuffmanTree{
    Node* root = nullptr;
    
    void buildCode(void){
        bitset <256> curBit;
        bool isFirst = true;
        int curLength = 0;
        for (int i = 0; i < lstCanonical.size(); i++){
            int bitLength = lstCanonical[i].fi;
            char ch = lstCanonical[i].se;
            if (isFirst == false) addOne(curBit);
            isFirst = false;
            curBit = curBit << (bitLength - curLength);
            curLength = bitLength;
            // cout << ch << " " << bitLength << " " <<curBit << endl;
            codeBook[ch] = curBit;
        }
    }
    void printCodeBook(void){
        for (int i = 0; i < lstCanonical.size(); i++){
            cout << lstCanonical[i].se << " " << codeBook[lstCanonical[i].se] << endl;
        }
    }
    void buildTree(Node* root, char ch, bitset <256> code, int bitLength){
        if (bitLength == 0){
            root->ch = ch;
            return;
        }
        int bit = code[bitLength - 1];
        if (bit == 0){
            if (root->l == nullptr){
                root->l = new Node();
            }
            buildTree(root->l, ch, code, bitLength - 1);
        }
        else{
            if (root->r == nullptr){
                root->r = new Node();
            }
            buildTree(root->r, ch, code, bitLength - 1);
        }
    }
    void buildCanonicalHuffmanTree(void){
        root = new Node();
        for (int i = 0; i < lstCanonical.size(); i++){
            char ch = lstCanonical[i].se;
            bitset <256> code = codeBook[ch];
            int bitLength = lstCanonical[i].fi;
            buildTree(root, ch, code, bitLength);
        }
    }
    void deleteTree(Node* root){
        if (root == nullptr) return;
        deleteTree(root->l);
        deleteTree(root->r);
        delete root;
    }
};

#endif