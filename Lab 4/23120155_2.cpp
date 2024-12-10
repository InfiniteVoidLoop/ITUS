#include <bits/stdc++.h>
using namespace std;

struct Node{
    int key;
    Node* left;
    Node* right;
    int height;
    Node(int _key, Node* _left, Node* _right, int _height){
        key = _key;
        left = _left;
        right = _right;
        height = _height;
    }
};
// Exercise 1 functions 
Node* newNode(int data);
Node* insertNode(Node* root, int data);
Node* searchNode(Node* root, int data);
Node* deleteNode(Node* root, int data);
void NLR(Node* root);
void LNR(Node* root);
void LRN(Node* root);
void LevelOrder(Node* root);

// Adding functions 
Node* leftRotation(Node* root);
Node* rightRotation(Node* root);
int balanceNumber(Node* root);

Node* newNode(int data){
    Node* newNode = new Node(data, NULL, NULL, 0);
    return newNode;
}

Node* insertNode(Node* root, int data){
    if (root == NULL)
        return newNode(data);
    if (data < root->key)
        root->left = insertNode(root->left, data);
    else if (data > root->key)
        root->right = insertNode(root->right, data);
    else
        return root;
}