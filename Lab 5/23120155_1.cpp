#include <iostream>
#include <queue>

using namespace std;

enum Color{
    RED,
    BLACK
};

struct Node{
    int key;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
    Node (int data) {
        key = data;
        color = RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

// Exercise 1 main functions 
Node* newNode(int data);
Node* insert(Node* root, int data);
Node* search(Node* root, int data);
Node* deleteNode(Node* root, int data);
void LevelOrder(Node* root);

// Additional functions
void rotateLeft(Node*& root, Node* node);
void rotateRight(Node*& root, Node* node);
void fixViolation(Node*& root, Node* node);
void fixDoubleBlack(Node*& root, Node* node);

Node* newNode(int data) {
    Node* node = new Node (data);
    return node;
}

void rotateLeft(Node*& root, Node* node) {
    Node* rightChild = node->right;
    node->right = rightChild->left;
    
    if (node->right != nullptr)
        node->right->parent = node;
        
    rightChild->parent = node->parent;
    
    if (node->parent == nullptr)
        root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;
        
    rightChild->left = node;
    node->parent = rightChild;
}

void rotateRight(Node*& root, Node* node) {
    Node* leftChild = node->left;
    node->left = leftChild->right;
    
    if (node->left != nullptr)
        node->left->parent = node;
        
    leftChild->parent = node->parent;
    
    if (node->parent == nullptr)
        root = leftChild;
    else if (node == node->parent->left)
        node->parent->left = leftChild;
    else
        node->parent->right = leftChild;
        
    leftChild->right = node;
    node->parent = leftChild;
}

void fixViolation(Node*& root, Node* node) {
    Node* parent = nullptr;
    Node* grandparent = nullptr;
    
    while ((node != root) && (node->color != BLACK) && (node->parent->color == RED)) {
        parent = node->parent;
        grandparent = node->parent->parent;
        
        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;
            
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } 
            else {
                if (node == parent->right) {
                    rotateLeft(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(root, grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        } 
        else {
            Node* uncle = grandparent->left;
            
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } 
            else {
                if (node == parent->left) {
                    rotateRight(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(root, grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

Node* insert(Node* root, int data) {
    Node* node = newNode(data);
    
    if (root == nullptr) {
        node->color = BLACK;
        return node;
    }
    
    Node* parent = nullptr;
    Node* current = root;
    
    while (current != nullptr) {
        parent = current;
        if (node->key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    
    node->parent = parent;
    
    if (node->key < parent->key)
        parent->left = node;
    else
        parent->right = node;
        
    fixViolation(root, node);
    return root;
}

Node* search(Node* root, int data) {
    if (root == nullptr || root->key == data)
        return root;
        
    if (data < root->key)
        return search(root->left, data);
        
    return search(root->right, data);
}

Node* minimum(Node* node) {
    Node* current = node;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

void fixDoubleBlack(Node*& root, Node* node) {
    if (node == root)
        return;
        
    Node* sibling = nullptr;
    Node* parent = node->parent;
    
    if (parent->left == node)
        sibling = parent->right;
    else
        sibling = parent->left;
        
    if (sibling == nullptr)
        fixDoubleBlack(root, parent);
    else {
        if (sibling->color == RED) {
            parent->color = RED;
            sibling->color = BLACK;
            if (parent->left == sibling) rotateRight(root, parent);
            else rotateLeft(root, parent);

            fixDoubleBlack(root, node);
        } 
        else {
            if ((sibling->left != nullptr && sibling->left->color == RED) || (sibling->right != nullptr && sibling->right->color == RED)) {
                
                if (sibling->left != nullptr && sibling->left->color == RED) {
                    if (parent->left == sibling) {
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        rotateRight(root, parent);
                    } 
                    else {
                        sibling->left->color = parent->color;
                        rotateRight(root, sibling);
                        rotateLeft(root, parent);
                    }
                } 
                else {
                    if (parent->left == sibling) {
                        sibling->right->color = parent->color;
                        rotateLeft(root, sibling);
                        rotateRight(root, parent);
                    } 
                    else {
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        rotateLeft(root, parent);
                    }
                }
                parent->color = BLACK;
            } 
            else {
                sibling->color = RED;
                if (parent->color == BLACK)
                    fixDoubleBlack(root, parent);
                else
                    parent->color = BLACK;
            }
        }
    }
}

Node* deleteNode(Node* root, int data) {
    Node* node = search(root, data);
    if (node == nullptr)
        return root;
        
    Node* u;
    Node* v = nullptr;
    
    if (node->left == nullptr || node->right == nullptr)
        u = node;
    else
        u = minimum(node->right);
        
    if (u->left != nullptr)
        v = u->left;
    else
        v = u->right;
        
    bool uvBlack = ((u == nullptr || u->color == BLACK) && (v == nullptr || v->color == BLACK));
    
    Node* parent = u->parent;
    
    if (v != nullptr)
        v->parent = parent;
        
    if (parent == nullptr)
        root = v;
    else {
        if (u == parent->left)
            parent->left = v;
        else
            parent->right = v;
    }
    
    if (uvBlack) {
        if (v != nullptr)
            fixDoubleBlack(root, v);
        else if (parent != nullptr)
            fixDoubleBlack(root, parent);
    } 
    else {
        if (v != nullptr)
            v->color = BLACK;
    }
    
    if (u != node) {
        node->key = u->key;
    }
    
    delete u;
    return root;
}

void LevelOrder(Node* root) {
    if (root == nullptr)
        return;
        
    queue<Node*> q;
    q.push(root);
    
    while (!q.empty()) {
        Node* current = q.front();
        cout << current->key << " ";
        q.pop();
        
        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
}

int main() {
    Node* root = nullptr;
    int choice, value;
    
    do {
        cout << "\n=== Red-Black Tree Options ===\n";
        cout << "1. Insert a number\n";
        cout << "2. Delete a number\n";
        cout << "3. Search a number\n";
        cout << "4. Level-order\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter number to insert: ";
                cin >> value;
                root = insert(root, value);
                cout << "Inserted " << value << " successfully!\n";
                break;
            }
            case 2: {
                cout << "Enter number to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                cout << "Deleted " << value << " successfully!\n";
                cout << endl;
                break;
            }
            case 3: {
                cout << "Enter number to search: ";
                cin >> value;
                Node* result = search(root, value);
                if (result != nullptr)
                    cout << value << " found in the tree!\n";
                else
                    cout << value << " not found!\n";
                break;
            }
            case 4: {
                cout << "Level-order: ";
                LevelOrder(root);
                cout << endl;
                break;
            }
            case 5:
                cout << "Exiting program\n";
                break;
            default:
                cout << "Invalid choice !!!\n";
        }
    } while (choice != 5);

    return 0;
}

