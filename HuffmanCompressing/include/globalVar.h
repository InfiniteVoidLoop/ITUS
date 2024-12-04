#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H
#include "../include/node.h"
#include <cstring>
#include <vector>
#include <map>
#include <bitset>
using namespace std;

extern char* fileNameIn;
extern char* fileNameOut;
extern int charFreq[256];
extern string line;
extern vector<Node*> lst;  // list node in heap while building tree
extern pair <int, int> compressData[256];

extern bitset <256> codeBook[256];  // code of canonical form
extern vector <pair<int, char>> lstCanonical;     // list for building canonical huffman code
#endif