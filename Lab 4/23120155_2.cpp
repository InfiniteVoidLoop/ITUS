#include <iostream>
#include <queue>

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

// Exercise 2 functions
bool isFull(Node* root);
bool isComplete(Node* root);
bool isPerfect(Node* root);
int findCommonAncestor(Node* root, int x, int y);
void printSpecialNode(Node* root);

// Adding functions 
Node* leftRotation(Node* root);
Node* rightRotation(Node* root);
int balanceNumber(Node* root);
int getHeight(Node* root);
Node* findMin(Node* root);

bool isFull(Node* root){
    if (root == NULL) return true;
    if (root->left == NULL && root->right == NULL)  return true;
    if (root->left != NULL && root->right != NULL) return isFull(root->left) && isFull(root->right);
    return false;
}

bool isComplete(Node* root){
    if (root == NULL) return true;
    queue <Node*>q;
    q.push(root);
    bool flag = false;
    while(!q.empty()){
        Node* u = q.front();
        q.pop();
        
        if (u == NULL) flag = true;
        else{
            if (flag) return false;
        }
        if (u != NULL){
            q.push(u->left);
            q.push(u->right);
        }
    }
}

bool isPerfect(Node* root){
    int h = getHeight(root);
    return isComplete(root) && isFull(root);
}

int findCommonAncestor(Node* root, int x, int y){
    if (root == NULL) return -1;
    if (root->key == x || root->key == y) return root->key;
    int leftLCA = findCommonAncestor(root->left, x, y);
    int rightLCA = findCommonAncestor(root->right, x, y);
    if (leftLCA != -1 && rightLCA != -1) return root->key;
    if (leftLCA != -1) return leftLCA;
    return rightLCA;
}

void printSpecialNode(Node* root){
    if (root == NULL) return;
    if (root->left != NULL && root->right != NULL && root->right->key % root->left->key == 0){
        printSpecialNode(root->left);
        cout << root->key << " ";
        printSpecialNode(root->right);
    }
    else{
        printSpecialNode(root->left);
        printSpecialNode(root->right);
    }
}

Node* findMin(Node* root){
    if (root == NULL) 
        return NULL;
    if (root->left == NULL) 
        return root;
    return findMin(root->left);
}

int getHeight(Node* root){
    if (root == NULL) return 0;
    return root->height;
}

Node* leftRotation(Node* root){
    Node* tmp = root->right;
    root->right = tmp->left;
    tmp->left = root;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    tmp->height = 1 + max(getHeight(tmp->left), getHeight(tmp->right));
    return tmp;
}

Node* rightRotation(Node* root){
    Node* tmp = root->left;
    root->left = tmp->right;
    tmp->right = root;
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    tmp->height = 1 + max(getHeight(tmp->left), getHeight(tmp->right));
    return tmp;
}

int balanceNumber(Node* root){
    return getHeight(root->left) - getHeight(root->right);
}

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
    
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = balanceNumber(root);
    
    if (balance > 1 && data < root->left->key)      // Left Left Case
        return rightRotation(root);
    
    if (balance < -1 && data > root->right->key)    // Right Right Case
        return leftRotation(root);

    if (balance > 1 && data > root->left->key){     // Left Right Case
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    
    if (balance < -1 && data < root->right->key){   // Right Left Case
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    return root;
}

Node* searchNode(Node* root, int data){
    if (root == NULL)
        return NULL;
    
    if (root->key == data)
        return root;
    
    if (root->key > data) 
        return searchNode(root->left, data);
    if (root->key < data)
        return searchNode(root->right, data);
}

Node* deleteNode(Node* root, int data){
  if (root == NULL) 
        return NULL;
    else if (data < root->key)
        root->left = deleteNode(root->left, data);
    else if (data > root->key)
        root->right = deleteNode(root->right, data);
    else{
         if (root->left != NULL && root->right != NULL){
            Node* tmp = findMin(root->right);
            root->key = tmp->key;
            root->right = deleteNode(root->right, root->key);
        }
        else{
            Node* tmp = root;
            if (root->left == NULL) 
                root = root->right;
            else if (root->right == NULL)
                root = root->left;
            delete tmp;
        }
    }
    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = balanceNumber(root);
    
    if (balance > 1 && data < root->left->key)      // Left Left Case
        return rightRotation(root);
    
    if (balance < -1 && data > root->right->key)    // Right Right Case
        return leftRotation(root);

    if (balance > 1 && data > root->left->key){     // Left Right Case
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    
    if (balance < -1 && data < root->right->key){   // Right Left Case
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    return root;
}

void NLR(Node* root){
    if (root == NULL) 
        return; 
    cout << root->key << " ";
    NLR(root->left);
    NLR(root->right);
}

void LNR(Node* root){
    if (root == NULL)
        return;
    LNR(root->left);
    cout << root->key << " ";
    LNR(root->right);
}

void LRN(Node* root){
    if (root == NULL)
        return;
    LRN(root->left);
    LRN(root->right);
    cout << root->key << " ";
}

void LevelOrder(Node* root){
    if (root == NULL)
        return;
    queue <Node*> myQueue;
    myQueue.push(root);
    
    while(!myQueue.empty()){
        Node* u = myQueue.front();
        myQueue.pop();
        cout << u->key << " ";
        if (u->left != NULL) 
            myQueue.push(u->left);
        if (u->right != NULL)
            myQueue.push(u->right);
    }
}

int main(){
    Node* root = NULL;
    vector <int> lst = {1,2,3,4,5,6,7,8,9,10};
    for (int i = 0; i < lst.size(); i++)
        root = insertNode(root, lst[i]);

    cout << "NLR: ";
    NLR(root);
    cout << '\n';
    cout << "LNR: ";
    LNR(root);
    cout << '\n';
    cout << "LRN: ";
    LRN(root);
    cout << '\n';
    deleteNode(root, 8);
    cout << "Level Order: ";
    LevelOrder(root);
    cout << '\n';
    if (isFull(root))
        cout << "The tree is full\n";
    else
        cout << "The tree is not full\n";

    if (isComplete(root))
        cout << "The tree is complete\n";
    else
        cout << "The tree is not complete\n";
    if (isPerfect(root))
        cout << "The tree is perfect\n";
    else
        cout << "The tree is not perfect\n";

    cout << "Common ancestor of 5 and 9: " << findCommonAncestor(root, 5, 9) << '\n';
    cout << "Special Nodes: ";
    printSpecialNode(root);
    return 0;
}