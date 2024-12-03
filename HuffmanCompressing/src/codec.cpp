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
    table_size = (unsigned char)buffer;

    Node* root = new Node();
    Node* tmp = root;

    for (int i = 0; i < table_size; i++){
        char ch = 0;
        uint16_t bin = 0;
        int bitSize = 0;

        fileIn.read(&ch, 1);
        fileIn.read(&buffer, 1);
        bitSize = (unsigned char)buffer;
        fileIn.read(reinterpret_cast<char*>(&bin), sizeof(bin));
        
        root = tmp;
        for (int j = bitSize - 1; j >= 0; j--){
            bool bit = (bin >> j) & 1;
            if (bit == 0){
                if (root->l == nullptr){
                    Node* node = new Node();
                    root->l = node;
                }
                root = root->l;
            }
            else if(bit == 1){
                if (root->r == nullptr){
                    Node* node = new Node();
                    root->r = node;
                }
                root = root->r;
            }
        }
        // cout << ch << " " << bitSize << " " << bin << endl;
        root->ch = ch;
    }

    // Read padding
    int curPos = fileIn.tellg();
    fileIn.seekg(0, ios::end);
    int padding;
    fileIn.seekg(-1, ios::end);
    fileIn.read(&buffer, 1);
    padding = (unsigned char)buffer;
    fileIn.seekg(curPos, ios::beg);

    // Read compress data
    int byte, numBit = 0;
    fileIn.seekg(-1, ios::end);
    int lastByte = fileIn.tellg();
    fileIn.seekg(curPos, ios::beg);

    root = tmp;
    while (fileIn.tellg() != lastByte - 1)
    {
        fileIn.read(&buffer, 1);
        byte = (unsigned char)buffer;
        for (int i = 7; i >= 0; --i)
        {
            bool bit = (byte >> i) & 1;
            if (bit == 0) root = root->l;
            else root = root->r;
            if (root->l == nullptr && root->r == nullptr)
            {
                fileOut << root->ch;
                root = tmp;
            }
        }
    }
   
    // Read the last byte of the binary file
   
    fileIn.read(&buffer, 1);
    byte = (unsigned char)buffer;
    for (int i = 7; i >= padding; --i)
    {
        bool bit = (byte >> i) & 1;
        if (bit == 0) root = root->l;
        else root = root->r;
        if (root->l == nullptr && root->r == nullptr){
            fileOut << root->ch;
            root = tmp;
        }   
    }
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
        char ch = i;
        uint16_t bit = compressData[i].first;
        int bitSize = compressData[i].second;
        fileOut.write((char *)&ch, 1);
        fileOut.write((char *)&bitSize, 1);
        fileOut.write((char *)&bit, sizeof(bit));

        // cerr << ch << " " << bitSize << " " << bit << endl;
    }

    // Compress Data
    int byte = 0;
    int numBit = 0;
    int remainBit;
    for (int i = 0; i < line.size(); i++)
    {
        char ch = line[i];
        int convertBit = compressData[int(ch)].first;
        int bitSize = compressData[int(ch)].second;
        remainBit = 8 - numBit;
        if (remainBit >= bitSize){
            byte = (byte << bitSize) | convertBit;
            numBit += bitSize;
        }
        else{
            byte = (byte << remainBit) | (convertBit >> (bitSize - remainBit));
            fileOut.write((char *)&byte, 1);
            byte = 0;
            numBit = bitSize - remainBit;
            byte = (convertBit & ((1 << (numBit + 1)) - 1));
        }
    }
    remainBit = 8 - numBit;
    int padding = remainBit;
    byte = byte << padding;
    fileOut.write((char *)&byte, 1);
    fileOut.write((char *)&padding, 1);
    cout << "Compressing successfully" << endl;
    fileOut.close();
}
