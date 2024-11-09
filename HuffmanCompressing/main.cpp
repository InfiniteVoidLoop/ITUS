#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <map>
#define fi first
#define se second
#define pb push_back
using namespace std;

struct Node{
    char ch;
    Node* l = nullptr;
    Node* r = nullptr;
    int value = 0;
};

struct HeapSort{
    vector<Node*> *heap;
    int n;
    HeapSort(vector<Node*> &_heap){
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
};

struct HuffmanCompressing{
    Node* root = nullptr;
    int charFreq[256] = {0};
    vector<string>line;
    vector<Node*> lst;
    map <char, string> compressData;
    map <string, char> decompressData;
    char* fileNameIn = nullptr;
    char* fileNameOut = nullptr;

    HuffmanCompressing(char* _fileNameIn, char* _fileNameOut){
        fileNameIn = _fileNameIn;
        fileNameOut = _fileNameOut;
    }

    void readTextFile(char* fileName){
        fstream fileIn(fileName, ios::in);
        if (!fileIn.is_open()){
            cout << "Can't open file " << fileName << endl;
            return;
        }
        string buffer;
        while(getline(fileIn, buffer)){
            line.push_back(buffer);
        }   
        fileIn.close();
    }

    void getFrequency(void){
        for (int i = 0; i < line.size(); i++){
            for (int j = 0; j < line[i].size(); j++){
                charFreq[(int)line[i][j]]++;
            }
        }
        for (int i = 0; i < 256; i++){
            if (charFreq[i] > 0){
                Node* node = new Node();
                node->ch = (char)i;
                node->value = charFreq[i];
                lst.push_back(node);
            }
        }
    }
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
    void printMask(void){
        for (auto it = compressData.begin(); it != compressData.end(); it++){
            cout << it->first << " " << it->second << endl;
        }
    }
    
    int convertStringToBinary(string s){
        int res = 0;
        for (int i = 0; i < s.size(); i++){
            bool bit = s[i] - '0';
            res = (res << 1) | bit;
        }
        return res;
    }

    string convertBinaryToString(int num, int bitSize){
        string res = "";
        while (num){
            res = (char)(num % 2 + '0') + res;
            num = num >> 1;
        }
        bitSize -= res.size();
        while(bitSize--){
            res = '0' + res;
        }
        return res;
    }
    
    void writeCompressionBinaryFile(void){  // compress data
        fstream fileOut(fileNameOut, ios::out | ios::binary);
        if (!fileOut.is_open()){
            cout << "Can't open file " << fileNameOut << endl;
            return;
        }
        // Write table for decoding data
        int table_size = compressData.size();
        fileOut.write((char*)&table_size, 1);

        for (auto it = compressData.begin(); it != compressData.end(); it++){
            int bitSize = it->second.size();
            int compressBit = convertStringToBinary(it->second);
            fileOut.write((char*)&it->first, 1);
            fileOut.write((char*)&bitSize, 1);
            fileOut.write((char*)&compressBit, 1);
        }

        // Compress Data
        int byte = 0;
        int numBit = 0;
        for (int i = 0; i < line.size(); i++){
            for (int j = 0; j < line[i].size(); j++){
                char ch = line[i][j];
                string code = compressData[ch];
                int convertBit = convertStringToBinary(code);
                if (numBit + code.size() <= 8){
                    numBit += code.size();
                    byte = (byte << code.size()) | convertBit;
                }
                else{
                    int remainBit = 8 - numBit;
                    byte = (byte << remainBit) | (convertBit >> (code.size() - remainBit));
                    fileOut.write((char*)&byte, 1);
                    byte = 0;
                    numBit = code.size() - remainBit;
                    byte = (byte << numBit) | (convertBit & ((1 << (numBit + 1)) - 1));
                }
            }
        }
        int padding = 0;
        if (byte){
            padding = 8 - numBit;
            byte = byte << padding;
            fileOut.write((char*)&byte, 1);
        }
        // cout << "Padding: " << padding << endl;
        fileOut.write((char*)&padding, 1);
        cout << "Compressing successfully" << endl;
        fileOut.close();
    }   

    void writeTextFileDecode(void){         // decode data
        fstream fileIn(fileNameIn, ios::in | ios::binary);
        fstream fileOut(fileNameOut, ios::out);
        if (!fileIn.is_open()){
            cout << "Can't open file " << fileNameIn << endl;
            return;
        }
        if (!fileOut.is_open()){
            cout << "Can't open file " << fileNameOut << endl;
            return;
        }
        // Read table for decoding data
        int table_size;
        char buffer;
        fileIn.read(&buffer, 1);
        table_size = (int)buffer;
        for (int i = 0; i < table_size; i++){
            char ch = 0;
            int bitSize = 0;
            int compressBit = 0;
            fileIn.read(&ch, 1);
            fileIn.read(&buffer, 1);
            bitSize = (int)buffer;
            fileIn.read(&buffer, 1);
            compressBit = (int)buffer;
            decompressData[convertBinaryToString(compressBit, bitSize)] = ch;
        }
        int curPos = fileIn.tellg();
        fileIn.seekg(0, ios::end);
        int padding;
        fileIn.seekg(-1, ios::end);
        fileIn.read(&buffer, 1);
        padding = (int)buffer;
        fileIn.seekg(curPos, ios::beg);

        // Read compress data
        int byte;
        int numBit = 0;
        string code = "";
        curPos = fileIn.tellg();
        fileIn.seekg(-1, ios::end);
        int lastByte = fileIn.tellg();
        fileIn.seekg(curPos, ios::beg);

        while (fileIn.tellg() != lastByte - 1){
            fileIn.read(&buffer, 1);
            byte = (int)buffer;
            for (int i = 7; i >=0; --i){
                bool bit = (byte >> i) & 1;
                code = code + (char)(bit + '0');
                if (decompressData.find(code) != decompressData.end()){
                    fileOut << decompressData[code];
                    code = "";
                }
            }
        }
        // Read the last byte of the binary file
        fileIn.read(&buffer, 1);
        byte = (int)buffer;
        for (int i = 7; i >= padding; --i){
            bool bit = (byte >> i) & 1;
            code = code + (char)(bit + '0');
            if (decompressData.find(code) != decompressData.end()){
                fileOut << decompressData[code];
                code = "";
            }
        }
        cout << "Decompressing successfully" << endl;
        fileIn.close();
        fileOut.close();
    }
};

int main(int argc, char* argv[]){
    int type = atoi(argv[1]);
    char* fileNameIn = argv[2];
    char* fileNameOut = argv[3];
    HuffmanCompressing huffmanCompressing(fileNameIn, fileNameOut);

    if (type == 1){     // Compressing
        huffmanCompressing.readTextFile(fileNameIn);
        huffmanCompressing.getFrequency();
        huffmanCompressing.buildHuffmanTree();
        // huffmanCompressing.printHuffmanTree(huffmanCompressing.root, "");
        huffmanCompressing.getMask(huffmanCompressing.root);
        // huffmanCompressing.printMask();
        huffmanCompressing.writeCompressionBinaryFile();
    }
    else if (type == 2){    // Decompressing
        huffmanCompressing.writeTextFileDecode();
        
    }
    return 0;
}  
