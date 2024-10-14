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
        Node* ptr = q.front;
        for(; ptr->next->next != NULL; ptr = ptr->next);
        Node* prePtr = ptr;
        ptr = ptr->next;
        delete ptr;
        prePtr->next = NULL;
    }
}