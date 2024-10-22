#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

const int BUFF_SIZE = 2000;
const char* dictFileName = "D:\\ITUS\\Week2\\Lab 2 - Data\\English-Vietnamese Dictionary.txt";

bool checkValid(char*);     // check if the word is valid
void addChar(char*&, char);     // add single character to string
void addTomyDict(char** &, int &, char*);   // add a word to my dictinary 
void getDict(const char*, char** &, int&);  // add a line from dictionary file to my dictionary array
void freemyDict(char** &, int &sz);     // free dictionary mem

struct Word{
    char* word = nullptr;
    char* definition = nullptr;
};

struct WordList{
    struct Node{ 
        Node* child[53];
        char* definition;    
        Node(){
            for (int i = 0; i <= 52; i++) child[i] = nullptr;
            definition = nullptr;
        }
    };
    int cur = 0;
    Node* root = new Node ();
    
    void buildList(Word** myDict, int sz){  // build trie 
        for (int i = 0; i < sz; i++) addWord(myDict[i]);
    }

    void addWord(Word* dictWord){   // add single word to trie 
        if (checkValid(dictWord->word) == false) return;    
        Node* ptr = root;

        for (int i = 0; i < strlen(dictWord->word); i++){
            int c;
            char ch = dictWord->word[i];
            if (ch >= 'a' && ch <= 'z') c = ch - 'a';
            else if (ch >= 'A' && ch <='Z') c = ch - 'A'+26;
            else if (ch == '-') ch = 52;
            if (ptr->child[c] == nullptr) ptr->child[c] = new Node();
            ptr = ptr->child[c];
        }
        ptr->definition = dictWord->definition;
    }

    char* getWordDefinition(char* word){    // get a word from trie
        Node* ptr = root;
        for (int i = 0; i < strlen(word); i++){
            int c;
            char ch = word[i];
            if (ch >= 'a' && ch <= 'z') c = ch - 'a';
            else if (ch >= 'A' && ch <='Z') c = ch - 'A'+26;
            else if (ch == '-') ch = 52;
            if (ptr->child[c] == nullptr) return nullptr;
            ptr = ptr->child[c];
        }
        return ptr->definition;
    }

    void freeTrie(Node* p){
        Node* ptr = p;
        for (int i = 0; i <= 52; i++){
            if (ptr->child[i] != nullptr) freeTrie(ptr->child[i]);
        }
        free(p);
    }

    void freeTrie(void) {freeTrie(root);}
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

bool checkValid(char* word){
    for (int i = 0; i < strlen(word); i++){
        if (word[i] == '-') continue;
        if ((word[i] < 'a' || word[i] > 'z') && (word[i] < 'A' && word[i] > 'Z')) return false; 
    }
    return true;
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
    WordList Trie;

    getDict(dictFileName, myDict, sz);
    Trie.buildList(myDict, sz);
    
    fstream fileOut(argv[argc - 1], ios::out);

    for (int i = 1; i <= argc - 2; i++){

        if (checkValid(argv[i]) == false) continue;
        char* definition = Trie.getWordDefinition(argv[i]);

        if (definition == nullptr)
            fileOut << argv[i] <<" -> Not in dictionary !!! \n"; 
        else fileOut << argv[i]<< definition << '\n';
    }
    freeMyDict(myDict, sz);
    Trie.freeTrie();
    fileOut.close();

    return 0;
}