#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

struct Queue{
    Node* front;
};

Node* createNode(int data){
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enqueue(Queue &q, int data){
    Node* newNode = createNode(data);
    if (q.front == NULL){
        q.front = newNode;
    }
    else{
        Node* ptr = q.front;
        for(;ptr->next != NULL; ptr = ptr->next);
        ptr->next = newNode;
    }
}

void dequeue(Queue &q){
    if(q.front == NULL) return;
    else if (q.front->next == NULL){
        delete q.front;
        q.front = NULL;
    }
    else{
        Node* ptr = q.front->next;
        delete q.front;
        q.front = ptr;
    }
}

int getFront(Queue &q){
    return q.front->data;
}

void destroyQueue(Queue &q){
    while (q.front != NULL) dequeue(q);
}

void menu(void){
    cout << "-------------------" << '\n';
    cout << "       Menu        " << '\n';
    cout << "-------------------" << '\n';
    cout << "Press 1: Enqueue function \n";
    cout << "Press 2: Dequeue function  \n";
    cout << "Press 3: Get front function \n";
    cout << "Press 0: Stop running \n";
    cout << "-------------------------------- \n";
}

int main(){
    Queue q;
    q.front = NULL;
    menu();
    int choice = 1;
    while (choice){
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1){
            cout << "Enter the value: ";
            int val;
            cin >> val;
            enqueue(q, val);
        }
        else if (choice == 2){
            dequeue(q);
        }
        else if (choice == 3){
            if (q.front == NULL){
                cout << "Empty queue !!! \n";
            }
            else{
                cout << "The front value of the queue: ";
                cout << getFront(q) << '\n';
            }
        }
    }
    destroyQueue(q);
    return 0;
}