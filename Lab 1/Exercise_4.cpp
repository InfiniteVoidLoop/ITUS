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

void removeNode(List &L, Node* delNode){
    if (delNode == L.head) removeHead(L);
    else if (delNode->next == NULL){
        removeTail(L);
    }
    else{
        Node* ptr;
        for (ptr = L.head; ptr->next != delNode; ptr = ptr->next);
        ptr->next = delNode->next;
        delete delNode;
    }
}

void removeDuplicate(List &L){
    for (Node* ptr1 = L.head; ptr1 != NULL; ptr1 = ptr1->next){
        for (Node* ptr2 = L.head; ptr2 != ptr1; ptr2 = ptr2->next){
            if (ptr1->data == ptr2->data){
                removeNode(L, ptr2);
                break;
            }
        }
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

void displayMenu(void){
    cout << "-------------------" << '\n';
    cout << "       Menu        " << '\n';
    cout << "-------------------" << '\n';
    cout << "Press 1: Traversal nodes \n";
    cout << "Press 2: Count nodes \n";
    cout << "Press 3: Add head \n";
    cout << "Press 4: Add tail \n";
    cout << "Press 5: Remove head \n";
    cout << "Press 6: Remove tail \n";
    cout << "Press 7: Remove duplicate \n";
    cout << "Press 0: Stop running \n";
    cout << "-------------------------------- \n";
}

int main(){
    displayMenu();
    List L;
    L.head = NULL;
    int type = 1;
    
    while(type){
        cout << "Enter your choice: ";
        cin >> type;

        if (type == 0) break;
        else if (type == 1){
            cout << "The linked list: \n";
            printList(L);
        }
        else if (type  == 2){
            cout << "Number of nodes: " << countNode(L) << '\n';
        }
        else if (type == 3){
            cout << "Enter the data (addHead): ";
            int val;
            cin >> val;
            addHead(L, val);
        }
        else if (type == 4){
            cout << "Enter the data (addTail): ";
            int val;
            cin >> val;
            addTail(L, val);
        }
        else if (type == 5){
            removeHead(L);
        }
        else if (type == 6){
            removeTail(L);
        }
        else if (type == 7){
            removeDuplicate(L);
        }
    }
    removeList(L);
    return 0;
}