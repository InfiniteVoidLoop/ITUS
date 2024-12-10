#include <iostream>
#include <queue>

using namespace std;

struct Node{
    int key;
    Node* left;
    Node* right;
};

// Exercise 1 functions 
Node* newNode(int data);
Node* insert(Node* root, int data);
Node* search(Node* root, int data);
Node* deleted(Node* root, int data);
void NLR(Node* root);
void LNR(Node* root);
void LRN(Node* root);
void LevelOrder(Node* root);


// Added functions 
Node* findMin(Node* root);

Node* findMin(Node* root){
    if (root == NULL) 
        return NULL;
    if (root->left == NULL) 
        return root;
    return findMin(root->left);
}

// Exercise 2 functions
int height(Node* root);
int countNode(Node* root);
int countInternal(Node* root);
int sumNode(Node* root);
int countLeaf(Node* root);
int countLess(Node* root, int x);
int countGreater(Node* root, int x);

Node* newNode(int data){
    Node* newNode = new Node;
    newNode->key = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data){
    if (root == NULL){
        root = newNode(data);
    }
    else if (data < root->key){
        root->left = insert(root->left, data);
    }
    else if (data > root->key){
        root->right = insert(root->right, data);
    }
    return root;
}

Node* search(Node* root, int data){
    if (root == NULL)
        return NULL;
    else if (root->key == data)
        return root;
    else if (data < root->key) 
        return search(root->left, data);
    return search(root->right, data);
}

Node* deleted(Node* root, int data){
    if (root == NULL) 
        return NULL;
    else if (data < root->key)
        root->left = deleted(root->left, data);
    else if (data > root->key)
        root->right = deleted(root->right, data);
    
    if (root->left != NULL && root->right != NULL){
        Node* tmp = findMin(root->right);
        root->key = tmp->key;
        root->right = deleted(root->right, root->key);
    }
    else{
        Node* tmp = root;
        if (root->left == NULL) 
            root = root->right;
        else if (root->right == NULL)
            root = root->left;
        delete tmp;
    }
    return root;
}

void NLR(Node* root){
    if (root == NULL) return;
    cout << root->key << " ";
    NLR(root->left);
    NLR(root->right);
}

void LNR(Node* root){
    if (root == NULL) return;
    LNR(root->left);
    cout << root->key << " ";
    LNR(root->right);
}

void LRN(Node* root){
    if (root == NULL) return;
    LRN(root->left);
    LRN(root->right);
    cout << root->key << " ";
}

void LevelOrder(Node* root){
    queue <Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* u = q.front();
        q.pop();
        cout << u->key << " ";
        if (u->left != NULL) 
            q.push(u->left);

        if (u->right != NULL) 
            q.push(u->right);
    }
}

int height(Node* root){
    if (root == NULL) return -1;
    int maxLeftHeight = height(root->left);
    int maxRightHeight = height(root->right);
    return max(maxLeftHeight, maxRightHeight) + 1;
}

int countNode(Node* root){
    if (root == NULL) return 0;
    return 1 + countNode(root->left) + countNode(root->right);
}

int countInternal(Node* root){
    if (root == NULL) return 0;
    bool notLeaf = (root->left || root->right);
    return notLeaf + countInternal(root->left) + countInternal(root->right);
}

int sumNode(Node* root){
    if (root == NULL) return 0;
    return root->key + sumNode(root->left) + sumNode(root->right);
}

int countLeaf(Node* root){
    if (root == NULL) return 0;
    bool isLeaf = (root->left == NULL && root->right == NULL);
    return isLeaf + countLeaf(root->left) + countLeaf(root->right);
}

int countLess(Node* root, int x){
    if (root == NULL) return 0;
    bool isLess = root->key < x;
    return isLess + countLess(root->left, x) + countLess(root->right, x);
}

int countGreater(Node* root, int x){
    if (root == NULL) return 0;
    bool isGreater = root->key > x;
    return isGreater + countGreater(root->left, x) + countGreater(root->right, x);
}

int main(){
    Node* root = NULL;
    root = insert(root, 8);
    root = insert(root, 6);
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 9);
    root = insert(root, 10);  
    NLR(root);
    cout << '\n';
    LNR(root);
    cout << '\n';
    LRN(root);
    cout << '\n';
    deleted(root, 8);
    LevelOrder(root);
    cout << '\n';
    cout << "Height: " << height(root) << '\n';
    cout << "Count node: " << countNode(root) << '\n';
    cout << "Count internal" << countInternal(root) << '\n';
    cout << "Sum node: " << sumNode(root) << '\n';
    cout << "Count leaf: " << countLeaf(root) << '\n';
    cout << "Count less: " << countLess(root, 7) << '\n';
    cout << "Count greater: " << countGreater(root, 7);
    return 0;
}