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

    unsigned int secondHashFunction(string key){
        unsigned int hash = 0, power = 31;
        fo(i, 0, key.size() - 1){
            hash = (hash + int(key[i]) * power) % m;
            power = (power * p) % m;
        }
        return hash;
    }

    void add(string key, int value){
        unsigned int id = hashFunction(key) % capacity;
        unsigned int i = 1;
        while(table[id] != nullptr && table[id]->key != key){
            id = (id + i * i) % capacity;
            i++;
        }
        if (table[id] != nullptr) free(table[id]);
        table[id] = (hashNode*)malloc(sizeof(hashNode));
        table[id]->key = key;
        table[id]->value = value;
    }

    int* searchValue(string key){
        unsigned int id = hashFunction(key) % capacity;
        
        while(table[id] != nullptr  && table[id]->key != key){
            id =  (id + 1) % capacity;
        }
        if (table[id] == nullptr) return nullptr;
        return &table[id]->value;
    }

    void removeKey(string key){
        unsigned int id = hashFunction(key) % capacity;
        while(table[id] != nullptr && table[id]->key != key){
            id = (id + 1) % capacity;
        }
        if (table[id] == nullptr) return;
        free(table[id]);
        table[id] = nullptr;
    }

};

int main(){
    
}
