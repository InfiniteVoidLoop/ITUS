#include <iostream>
#include <fstream>
#include "../include/codec.h"
#include "../include/utils.h"
#include "../include/globalVar.h"

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
    for (int i = 0; i < table_size; i++)
    {
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

    while (fileIn.tellg() != lastByte - 1)
    {
        fileIn.read(&buffer, 1);
        byte = (int)buffer;
        for (int i = 7; i >= 0; --i)
        {
            bool bit = (byte >> i) & 1;
            code = code + (char)(bit + '0');
            if (decompressData.find(code) != decompressData.end())
            {
                fileOut << decompressData[code];
                code = "";
            }
        }
    }
    // Read the last byte of the binary file
    fileIn.read(&buffer, 1);
    byte = (int)buffer;
    for (int i = 7; i >= padding; --i)
    {
        bool bit = (byte >> i) & 1;
        code = code + (char)(bit + '0');
        if (decompressData.find(code) != decompressData.end())
        {
            fileOut << decompressData[code];
            code = "";
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
    int table_size = compressData.size();
    fileOut.write((char *)&table_size, 1);

    for (auto it = compressData.begin(); it != compressData.end(); it++)
    {
        int bitSize = it->second.size();
        int compressBit = convertStringToBinary(it->second);
        fileOut.write((char *)&it->first, 1);
        fileOut.write((char *)&bitSize, 1);
        fileOut.write((char *)&compressBit, 1);
    }

    // Compress Data
    int byte = 0;
    int numBit = 0;
    for (int i = 0; i < line.size(); i++)
    {
        for (int j = 0; j < line[i].size(); j++)
        {
            char ch = line[i][j];
            string code = compressData[ch];
            int convertBit = convertStringToBinary(code);
            if (numBit + code.size() <= 8)
            {
                numBit += code.size();
                byte = (byte << code.size()) | convertBit;
            }
            else
            {
                int remainBit = 8 - numBit;
                byte = (byte << remainBit) | (convertBit >> (code.size() - remainBit));
                fileOut.write((char *)&byte, 1);
                byte = 0;
                numBit = code.size() - remainBit;
                byte = (byte << numBit) | (convertBit & ((1 << (numBit + 1)) - 1));
            }
        }
    }
    int padding = 0;
    if (byte)
    {
        padding = 8 - numBit;
        byte = byte << padding;
        fileOut.write((char *)&byte, 1);
    }
    // cout << "Padding: " << padding << endl;
    fileOut.write((char *)&padding, 1);
    cout << "Compressing successfully" << endl;
    fileOut.close();
}
