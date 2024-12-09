#include <iostream>
#include <cstring>
#include <vector>
#define fo(i, a, b) for (int i = a; i <= b; i++)
using namespace std;
const int p = 31;
const int m = 1e9 + 9;

struct hashTable{
    struct hashNode{
        string key;
        int value;
        hashNode* next;
    };
    int capacity;
    vector <hashNode*> table;

    void init(unsigned int hashSize){
        capacity = hashSize;
        table.resize(capacity);
        fo(i, 0, capacity - 1) table[i] = nullptr;
    }

    void release(void){
        fo(i, 0, capacity - 1){
            if  (table[i] != nullptr) free(table[i]);
        }
        table.clear();
    }

    unsigned int hashFunction(string key){
        unsigned int hash = 0, power = 31;
        fo(i, 0, key.size() - 1){
            hash = (hash + int(key[i]) * power) % m;
            power = (power * p) % m;
        }
        return hash;
    }
    
    void add(string key, int value){
        unsigned int id = hashFunction(key) % capacity;
        hashNode* newNode = (hashNode*)malloc(sizeof(hashNode));
        newNode->key = key;
        newNode->value = value;
        newNode->next = nullptr;
        if (table[id] == nullptr) table[id] = newNode;
        else{
            hashNode* tmpNode = table[id];
            while (tmpNode->next != nullptr) tmpNode = tmpNode->next;
            tmpNode->next = newNode;
        }
    }

    int* searchValue(string key){
        unsigned int id = hashFunction(key) % capacity;
        while (table[id] != nullptr && table[id]->key != key){
            table[id] = table[id]->next;
        }
        if (table[id] == nullptr) return nullptr;
        return &table[id]->value;
    }

    void removeKey(string key){
        unsigned int id = hashFunction(key) % capacity;
        hashNode* tmpNode = table[id];
        if (tmpNode == nullptr) return;
        if (tmpNode->key == key){
            table[id] = tmpNode->next;
            free(tmpNode);
            return;
        }
        while (tmpNode->next != nullptr && tmpNode->next->key != key){
            tmpNode = tmpNode->next;
        }
        if (tmpNode->next == nullptr) return;
        hashNode* delNode = tmpNode->next;
        tmpNode->next = delNode->next;
        free(delNode);
    }
};

int main(){
    
}
