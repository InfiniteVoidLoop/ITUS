#include <iostream>
#include <fstream>
#include "../include/codec.h"
#include "../include/utils.h"
#include "../include/globalVar.h"
#include "../include/huffmanCode.h"

void decompressToTextFile(void)  // decode data
{ 
    fstream fileIn(fileNameIn, ios::in | ios::binary);
    fstream fileOut(fileNameOut, ios::out);
    if (!fileIn.is_open())
    {
        cout << "Can't open file " << fileNameIn << endl;
        return;
    }
    if (!fileOut.is_open())
    {
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
        int freq = 0;
        fileIn.read(&ch, 1);
        fileIn.read(&buffer, 1);
        charFreq[(int)ch] = (int)buffer;
        Node* node = new Node();
        node->ch = ch;
        node->value = charFreq[(int)ch];
        lst.push_back(node);
    }
    // Build Huffman Tree
    HuffmanCompressing huffmanCompressing;
    huffmanCompressing.buildHuffmanTree();
    
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
    Node* root = huffmanCompressing.root;

    while (fileIn.tellg() != lastByte - 1)
    {
        fileIn.read(&buffer, 1);
        byte = (int)buffer;
        for (int i = 7; i >= 0; --i)
        {
            bool bit = (byte >> i) & 1;
            if (bit == 0) root = root->l;
            else root = root->r;
            if (root->l == nullptr && root->r == nullptr)
            {
                fileOut << root->ch;
                root = huffmanCompressing.root;
            }
        }
    }
    // Read the last byte of the binary file
    fileIn.read(&buffer, 1);
    byte = (int)buffer;
    for (int i = 7; i >= padding; --i)
    {
        bool bit = (byte >> i) & 1;
        if (bit == 0) root = root->l;
        else root = root->r;
        if (root->l == nullptr && root->r == nullptr){
            fileOut << root->ch;
            root = huffmanCompressing.root;
        }   
    }
    if (root == huffmanCompressing.root) cout << "Decompressing successfully" << endl;
    else cout << "Decompressing failed" << endl;
    cout << "Decompressing successfully" << endl;
    fileIn.close();
    fileOut.close();
}

void compressToBinaryFile(void)   // compress data
{ 
    fstream fileOut(fileNameOut, ios::out | ios::binary);
    if (!fileOut.is_open())
    {
        cout << "Can't open file " << fileNameOut << endl;
        return;
    }
    // Write table for decoding data
    int table_size = 0;
    for (int i = 0; i < 256; i++){
        if (compressData[i].second != 0) table_size++;
    }
    fileOut.write((char *)&table_size, 1);

    for (int i = 0; i < 256; i++){
        if (charFreq[i] == 0) continue;
        char ch = char(i);
        int freq = charFreq[i];
        fileOut.write((char *)&ch, 1);
        fileOut.write((char *)&freq, 1);
    }
    // Compress Data
    int byte = 0;
    int numBit = 0;
    for (int i = 0; i < line.size(); i++)
    {
        for (int j = 0; j < line[i].size(); j++)
        {
            char ch = line[i][j];
            int convertBit = compressData[int(ch)].first;
            int bitSize = compressData[int(ch)].second;
            if (numBit + bitSize <= 8){
                numBit += bitSize;
                byte = (byte << bitSize) | convertBit;
            }
            else{
                int remainBit = 8 - numBit;
                byte = (byte << remainBit) | (convertBit >> (bitSize - remainBit));
                fileOut.write((char *)&byte, 1);
                byte = 0;
                numBit = bitSize - remainBit;
                byte = (byte << numBit) | (convertBit & ((1 << (numBit + 1)) - 1));
            }
        }
    }
    int padding = 0;
    if (byte){
        padding = 8 - numBit;
        byte = byte << padding;
        fileOut.write((char *)&byte, 1);
    }
    fileOut.write((char *)&padding, 1);
    cout << "Compressing successfully" << endl;
    fileOut.close();
}
