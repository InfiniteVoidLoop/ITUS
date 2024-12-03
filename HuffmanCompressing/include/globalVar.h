#ifndef GLOBAL_VAR_H
#define GLOBAL_VAR_H
#include "../include/node.h"
#include <cstring>
#include <vector>
#include <map>
using namespace std;

extern char* fileNameIn;
extern char* fileNameOut;
extern int charFreq[256];
extern vector<string>line;
extern vector<Node*> lst;  // list node in heap while building tree
extern pair <int, int> compressData[256];
#endif