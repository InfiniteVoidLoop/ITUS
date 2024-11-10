#ifndef NODE_H
#define NODE_H

typedef struct Node{
    char ch;
    Node* l = nullptr;
    Node* r = nullptr;
    int value = 0;
}
Node;

#endif