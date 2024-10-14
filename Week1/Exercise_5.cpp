#include <iostream>
using namespace std;

struct Node{
    int data;
    Node* next;
};

struct Stack{
    Node* top;
};

Node* createNode(int data){
    Node* newNode =  new Node;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(Stack &st, int data){
    Node* newNode = createNode(data);
    if (st.top == NULL) st.top = newNode;
    else{
        newNode->next = st.top;
        st.top = newNode;
    }
}

void pop(Stack &st, int data){
    if (st.top == NULL) return;
    else if (st.top->next == NULL){
        delete st.top;
        st.top = NULL;
    }
    else{
        Node* tmp = st.top->next;
        delete st.top;
        st.top = tmp;
    }
}

int getTop(Stack st){
    return st.top->data;
}

int main(){

}