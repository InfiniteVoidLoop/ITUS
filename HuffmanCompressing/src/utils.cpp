#include "../include/utils.h"
#include "../include/globalVar.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <bitset>

using namespace std;

string getExtension(char* fileName){
    string res ="";
    for (int i = strlen(fileName) - 1; i >= 0; i--){
        if (fileName[i] == '.'){
            break;
        }
        res = fileName[i] + res;
    }
    return res;
}

void readTextFile(char* fileName){
    fstream fileIn(fileName, ios::in);
    if (!fileIn.is_open()){
        cout << "Can't open file " << fileName << endl;
        return;
    }
    string temp;
    bool check = false;
    while (!fileIn.eof()){
        getline(fileIn, temp);
        line += temp + "\n";
        check = true;
    }
    if (check) {
        line.pop_back();
    }
    fileIn.close();
}

 void getFrequency(void){
    for (int i = 0; i < line.size(); i++){
        charFreq[(int)line[i]]++;
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

void compressBytesInfo(char* fileNameIn, char* fileNameOut){
    fstream fileIn(fileNameIn, ios::in);
    fstream fileOut(fileNameOut, ios::in | ios::binary);
    // Count bytes from fileIn
    int cntBytes = 0;
    while (fileIn.get() != EOF){
        cntBytes++;
    }
    fileIn.close();
    // Count bytes from fileOut
    int cntBytesOut = 0;
    while (fileOut.get() != EOF){
        cntBytesOut++;
    }
    fileOut.close();
    cout << "Compress from " << cntBytes << " bytes to " << cntBytesOut << " bytes" << endl;
}

void addOne(bitset <256> &a){   
    bool carry = 1;
    for (int i = 0; i < 256; i++){
        if (a[i] == 0){
            if (carry == 1){
                a[i] = 1;
                carry = 0;
            }
            else if (carry == 0){
                a[i] = 0;
            }
        }
        else if (a[i] == 1){
            if (carry == 1){
                a[i] = 0;
            }
            else if (carry == 0){
                a[i] = 1;
                carry = 0;
            }
        }
    }
}

void ORBIT(bitset <8>&a, bitset <256>&b){
    for (int i = 0; i < 8; i++){
        if (a[i] == 1 || b[i] == 1){
            a[i] = 1;
        }
    }
}