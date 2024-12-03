#include "../include/utils.h"
#include "../include/globalVar.h"
#include <fstream>
#include <iostream>
#include <cstring>
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

    char ch;
    while(fileIn.get(ch)){
         line = line + ch;
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
