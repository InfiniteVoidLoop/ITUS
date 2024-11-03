#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

const int BUFF_SIZE = 2000;
const char* dictFileName = "..\\Lab 2 - Data\\English-Vietnamese Dictionary.txt";

struct Word{
    char* word = nullptr;
    char* definition = nullptr;
};

void addChar(char* &ch, char a){    
    int n = (ch == nullptr ? 0 : strlen(ch));
    ch = (char*)realloc(ch, (n + 2) * sizeof(char));
    ch[n] = a;
    ch[n + 1] = '\0';
}

void addTomyDict(Word** &myDict, int &sz, char* buff){   
    myDict = (Word**)realloc(myDict, (sz + 1) * sizeof(Word*));   
    myDict[sz] = (Word*)malloc(sizeof(Word));
    myDict[sz]->word = nullptr;
    myDict[sz]->definition = nullptr;

    int i = 0;
    while(buff[i] != ':') addChar(myDict[sz]->word, buff[i++]);
    while(buff[i] != '\0') addChar(myDict[sz]->definition, buff[i++]);
    // cout << myDict[sz]->word << " " << myDict[sz]->definition << '\n';
    sz++;
}

void getDict(const char* dictFileName, Word** &myDict, int &sz){    
    fstream dictFile(dictFileName, ios::in);
    if (!dictFile.is_open()){
        cout << "Can not open !!!";
        return;
    }
    char buff[BUFF_SIZE];

    while(dictFile.getline(buff, BUFF_SIZE)){
        addTomyDict(myDict, sz, buff);
    }
    dictFile.close();
}

void quickSortDict(Word** &myDict, int l, int r){
    if (l >= r) return;
    int i = l, j = r;
    char* pivot = myDict[(l + r) / 2]->word;
    while (i <= j){
        while (strcmp(myDict[i]->word, pivot) < 0) i++;
        while (strcmp(myDict[j]->word, pivot) > 0) j--;
        if (i <= j){
            Word* tmp = myDict[i];
            myDict[i] = myDict[j];
            myDict[j] = tmp;
            i++;
            j--;
        }
    }
    quickSortDict(myDict, l, j);
    quickSortDict(myDict, i, r);
}

int findDict(Word** myDict, int sz, char* word){
    int l = 0, r = sz - 1;
    while (l <= r){
        int m = (l + r) / 2;
        if (strcmp(myDict[m]->word, word) == 0) return m;
        else if (strcmp(myDict[m]->word, word) < 0) l = m + 1;
        else r = m - 1;
    }
    return -1;
}


void freeMyDict(Word** &myDict, int &sz){
    for (int i = 0; i < sz; i++){
        free(myDict[i]->word);
        free(myDict[i]->definition);
        free(myDict[i]);
    }
    free(myDict);
}

int main(int argc, char* argv[]){   
    Word** myDict = nullptr;
    int sz = 0;
    
    getDict(dictFileName, myDict, sz);
    quickSortDict(myDict, 0, sz - 1);
    
    fstream fileOut(argv[argc - 1], ios::out);
    if (!fileOut.is_open()){
        cout << "Can not open file " << argv[argc - 1] << "\n";
        return 0;
    }

    for (int i = 1; i <= argc - 2; i++){
        int posInDict = findDict(myDict, sz, argv[i]);
        if (posInDict == -1)
            fileOut << argv[i] << " --> not in the dictionary\n";
        else 
            fileOut << argv[i] << myDict[posInDict]->definition << '\n';
    }
    freeMyDict(myDict, sz);
    fileOut.close();

    return 0;
}