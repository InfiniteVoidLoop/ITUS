#include "../include/globalVar.h"
#include "../include/node.h"
#include <cstring>
#include <vector>
#include <map>
#include <bitset>
using namespace std;

char* fileNameIn;
char* fileNameOut;
int charFreq[256] = {0};
string line;
vector<Node*> lst;  // list node in heap while building tree
int compressData[256];  // code values and bit length of huffman tree

bitset <256> codeBook[256];  // code of canonical form
vector <pair <int,char >> lstCanonical;     // list for building canonical huffman code


