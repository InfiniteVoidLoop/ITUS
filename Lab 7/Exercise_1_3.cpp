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
        table.resize(capacity, nullptr);
    }

    void release(void){
        fo(i, 0, capacity - 1){
            if  (table[i] != nullptr) delete table[i];
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
        hashNode* newNode = new hashNode{key, value, nullptr};

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
            delete tmpNode;
            return;
        }
        while (tmpNode->next != nullptr && tmpNode->next->key != key){
            tmpNode = tmpNode->next;
        }
        if (tmpNode->next == nullptr) return;
        hashNode* delNode = tmpNode->next;
        tmpNode->next = delNode->next;
        delete delNode;
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