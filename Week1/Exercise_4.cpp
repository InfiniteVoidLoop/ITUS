#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

struct List{
    Node* head;
};

Node* createNode(int data){
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = NULL;
    
    return newNode;
}

void printList(List L){
    for (Node* ptr = L.head; ptr != NULL; ptr = ptr->next) cout << ptr->data << " ";
    cout << '\n';
}

int countNode(List L){
    int cnt = 0;
    for (Node* ptr = L.head; ptr != NULL; ptr = ptr->next) cnt++;
    return cnt;
}

void addHead(List &L, int data){
    Node* newNode = createNode(data);
    if (L.head == NULL) L.head = newNode;
    else{
        newNode->next = L.head;
        L.head = newNode;
    }
}

void addTail(List &L, int data){
    Node* newNode = createNode(data);
    if (L.head == NULL) L.head = newNode;
    else{
        Node* ptr = L.head;
        for (; ptr->next != NULL; ptr = ptr->next);
        ptr->next = newNode;
    }
}

void removeHead(List &L){
    if(L.head == NULL) return;
    Node* tmpNode = L.head;
    L.head = L.head->next;
    delete tmpNode;
}

void removeTail(List &L){
    if (L.head == NULL) return;
    if (L.head->next == NULL){
        delete L.head;
        L.head = NULL;
        return;
    }
    Node* preNode = L.head;
    Node* tmpNode = L.head->next;
    for (; tmpNode->next != NULL; tmpNode = tmpNode->next, preNode = preNode->next);
    preNode->next = NULL;
    delete tmpNode;
}

void removeNode(List &L, int val){
    bool flag = true;
    while(flag){
        bool check = false;
        Node* delNode = NULL;
        for (Node* ptr = L.head; ptr != NULL; ptr = ptr->next){
            if (ptr->data == val){
                check = true;
                delNode = ptr;
                break;
            }
        }
        flag &= check;
        if (flag){
            if (delNode == L.head) removeHead(L);
            else if (delNode->next == NULL){
                Node* ptr = L.head;
                for (; ptr->next != delNode; ptr = ptr->next);
                ptr->next = NULL;
                delete delNode;
            }
            else{
                 Node* tmp = delNode->next;
                *delNode = *tmp;
                delete tmp;
            }
        }
    }
}

void removeDuplicate(List &L){
    bool flag = true;
    while(flag){
        bool check = false;
        int duplicateValue;
        for (Node* ptr1 = L.head; ptr1 != NULL; ptr1 = ptr1->next){
            if (check) break;
            for (Node* ptr2 = ptr1->next; ptr2 != NULL; ptr2 = ptr2->next){
                if (ptr1->data == ptr2->data){
                    check = true;
                    duplicateValue = ptr1->data;
                    break;
                }
            }
        }
        flag &= check;
        if (flag) removeNode(L, duplicateValue);
    }
}

void removeList(List &L){
    Node* ptr = L.head;
    while(L.head){
        ptr = L.head;
        L.head = L.head->next;
        delete ptr;
    }
}

int main(){
    List L;
    L.head = NULL;
    int type = 1;
    while(type){
        cin >> type;
        if (type == 0) break;
        else if (type == 1){
            int num;
            cin >> num;
            addTail(L, num);
        }
        else if (type  == 2){
            int num;
            cin >> num;
            addHead(L, num);
        }
        else if (type == 3){
            cout << countNode(L) << '\n';
        }
        else if (type == 4){
            removeHead(L);
        }
        else if (type == 5){
            removeTail(L);
        }
        else if (type == 6){
            printList(L);
        }
        else if (type == 7){
            removeDuplicate(L);
        }
    }
    removeList(L);
    printList(L);
}