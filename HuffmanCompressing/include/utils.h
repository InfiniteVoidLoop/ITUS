#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <cstring>
#include <bitset>
using namespace std;

string getExtension(char*);
void readTextFile(char*);
void getFrequency(void);
void compressBytesInfo(char*, char*);
void addOne(bitset <256>&);
void ORBIT(bitset <8>&, bitset <256>&);
#endif

