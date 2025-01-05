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
            if  (table[i] != nullptr) delete table[i];
        }
        table.clear();
        capacity = 0;
    }

    unsigned int hashFunction(string key){
        unsigned int hash = 0, power = 31;
        for (int i = 0; i < key.size(); i++){
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
        if (table[id] != nullptr) delete table[id];
        table[id] = new hashNode{key, value};
    }

    int* searchValue(string key){
        unsigned int id = hashFunction(key) % capacity;
        unsigned int i = 1;
        while(table[id] != nullptr  && table[id]->key != key){
            id =  (id + i * i) % capacity;
            i++;
        }
        if (table[id] == nullptr) return nullptr;
        return &table[id]->value;
    }

    void removeKey(string key){
        unsigned int id = hashFunction(key) % capacity;
        unsigned int i = 1;
        while(table[id] != nullptr && table[id]->key != key){
            id = (id + i * i) % capacity;
            i++;
        }
        if (table[id] == nullptr) return;
        delete table[id];
        table[id] = nullptr;
    }
};

void menu(void){
    cout << "---------MENU---------\n";
    cout << "1. Add a key\n";
    cout << "2. Search a key\n";
    cout << "3. Remove a key\n";
    cout << "4. Exit\n";
}

int main(){
    hashTable table;
    table.init(1000000);
    while (true){
        menu();
        int choice;
        cout << "Enter your choice: ";

        cin >> choice;
        if (choice == 1){
            string key;
            int value;
            cout << "Enter key: ";
            cin >> key;
            cout << "Enter value: ";
            cin >> value;
            table.add(key, value);
        }
        else if (choice == 2){
            string key;
            cout << "Enter key: ";
            cin >> key;
            int* value = table.searchValue(key);
            if (value == nullptr) cout << "Key not found\n";
            else cout << "Value: " << *value << '\n';
        }
        else if (choice == 3){
            string key;
            cout << "Enter key: ";
            cin >> key;
            table.removeKey(key);
        }
        else if (choice == 4){
            table.release();
            break;
        }
    }
    return 0;    
}