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

void pop(Stack &st){
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

void destroyStack(Stack &st){
    while(st.top != NULL) pop(st);
}

void menu(void){
    cout << "-------------------" << '\n';
    cout << "       Menu        " << '\n';
    cout << "-------------------" << '\n';
    cout << "Press 1: Push function \n";
    cout << "Press 2: Pop function  \n";
    cout << "Press 3: Top function \n";
    cout << "Press 0: Stop running \n";
    cout << "-------------------------------- \n";
}

int main(){
    Stack st;
    st.top = NULL;
    menu();
    int choice = 1;
    while(choice){
        cout << "Enter your choice: ";
        cin >> choice;
        
        if (choice == 1){
            cout << "Enter the value: ";
            int val;
            cin >> val;
            push(st, val);
        }
        else if (choice == 2){
            pop(st);
        }
        else if (choice == 3){
            if (st.top == NULL){
                cout << "Empty list !!! \n";
            }
            else{
                cout << "Top value of the stack: ";
                cout << getTop(st) << '\n';              
            }
       }
    }
    destroyStack(st);
    return 0;
}