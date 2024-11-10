#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <cstring>
using namespace std;

string getExtension(char*);
void readTextFile(char*);
void getFrequency(void);
int convertStringToBinary(string);
string convertBinaryToString(int num, int bitSize);
void compressBytesInfo(char*, char*);
bool checkingFilesAreTheSame(char*, char*);

#endif

