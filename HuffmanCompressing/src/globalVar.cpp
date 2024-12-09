#include "../include/globalVar.h"
#include "../include/node.h"
#include <cstring>
#include <vector>
#include <map>
using namespace std;

char* fileNameIn;
char* fileNameOut;
int charFreq[256] = {0};
string line;
vector<Node*> lst;  // list node in heap while building tree
pair <int, int> compressData[256];
