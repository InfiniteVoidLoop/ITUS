#include <iostream>
#include <queue>
using namespace std;

const int MAX = 3;

struct Node {
    int key[MAX];
    Node* children[MAX + 1];
    int numKeys;
    bool isLeaf;
};

// Exercise 2 main functions
Node* newNode(bool isLeaf);
Node* insert(Node* root, int data);
Node* search(Node* root, int data);
Node* deleteNode(Node* root, int data);
void NLR(Node* root);
void LNR(Node* root);
void LRN(Node* root);
void LevelOrder(Node* root);

// Additional functions
void splitChildNode(Node* parent, int i);
void insertInNonFull(Node* node, int data);
void mergeChildNodes(Node* root, int idx);
void deleteFromLeaf(Node* root, int idx);
void deleteFromInternalNode(Node* root, int idx);
int findPredecessor(Node* root, int idx);
int findSuccessor(Node* root, int idx);
void borrowFromLeftSibling(Node* root, int idx);
void borrowFromRightSibling(Node* root, int idx);
void displayNode(Node* node);

Node* newNode(bool isLeaf) {
    Node* node = new Node;
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    for (int i = 0; i < MAX + 1; ++i)
        node->children[i] = nullptr;
    return node;
}

Node* search(Node* root, int data) {
    if (!root) return nullptr;

    int i = 0;
    while (i < root->numKeys && data > root->key[i])
        i++;

    if (i < root->numKeys && root->key[i] == data)
        return root;

    if (root->isLeaf)
        return nullptr;

    return search(root->children[i], data);
}

void splitChildNode(Node* parent, int i) {
    Node* child = parent->children[i];
    Node* sibling = newNode(child->isLeaf);

    sibling->numKeys = MAX / 2;

    for (int j = 0; j < MAX / 2; ++j)
        sibling->key[j] = child->key[j + MAX / 2 + 1];

    if (!child->isLeaf) {
        for (int j = 0; j <= MAX / 2; ++j)
            sibling->children[j] = child->children[j + MAX / 2 + 1];
    }

    child->numKeys = MAX / 2;

    for (int j = parent->numKeys; j >= i + 1; --j)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = sibling;

    for (int j = parent->numKeys - 1; j >= i; --j)
        parent->key[j + 1] = parent->key[j];

    parent->key[i] = child->key[MAX / 2];
    parent->numKeys++;
}

void insertInNonFull(Node* node, int data) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        while (i >= 0 && data < node->key[i]) {
            node->key[i + 1] = node->key[i];
            i--;
        }
        node->key[i + 1] = data;
        node->numKeys++;
    } else {
        while (i >= 0 && data < node->key[i])
            i--;
        i++;

        if (node->children[i]->numKeys == MAX) {
            splitChildNode(node, i);
            if (data > node->key[i])
                i++;
        }
        insertInNonFull(node->children[i], data);
    }
}

Node* insert(Node* root, int data) {
    if (!root) {
        root = newNode(true);
        root->key[0] = data;
        root->numKeys = 1;
        return root;
    }

    if (root->numKeys == MAX) {
        Node* newRoot = newNode(false);
        newRoot->children[0] = root;
        splitChildNode(newRoot, 0);

        int i = (data > newRoot->key[0]) ? 1 : 0;
        insertInNonFull(newRoot->children[i], data);

        return newRoot;
    }

    insertInNonFull(root, data);
    return root;
}

void mergeChildNodes(Node* root, int idx) {
    Node* child = root->children[idx];
    Node* sibling = root->children[idx + 1];

    child->key[MAX / 2] = root->key[idx];

    for (int i = 0; i < sibling->numKeys; ++i)
        child->key[i + MAX / 2 + 1] = sibling->key[i];

    if (!child->isLeaf) {
        for (int i = 0; i <= sibling->numKeys; ++i)
            child->children[i + MAX / 2 + 1] = sibling->children[i];
    }

    for (int i = idx + 1; i < root->numKeys; ++i)
        root->key[i - 1] = root->key[i];

    for (int i = idx + 2; i <= root->numKeys; ++i)
        root->children[i - 1] = root->children[i];

    child->numKeys += sibling->numKeys + 1;
    root->numKeys--;

    delete sibling;
}

void deleteFromLeaf(Node* root, int idx) {
    for (int i = idx + 1; i < root->numKeys; ++i)
        root->key[i - 1] = root->key[i];

    root->numKeys--;
}

void deleteFromInternalNode(Node* root, int idx) {
    int k = root->key[idx];

    if (root->children[idx]->numKeys >= MAX / 2) {
        int pred = findPredecessor(root, idx);
        root->key[idx] = pred;
        root->children[idx] = deleteNode(root->children[idx], pred);
    } else if (root->children[idx + 1]->numKeys >= MAX / 2) {
        int succ = findSuccessor(root, idx);
        root->key[idx] = succ;
        root->children[idx + 1] = deleteNode(root->children[idx + 1], succ);
    } else {
        mergeChildNodes(root, idx);
        root->children[idx] = deleteNode(root->children[idx], k);
    }
}

int findPredecessor(Node* root, int idx) {
    Node* current = root->children[idx];
    while (!current->isLeaf)
        current = current->children[current->numKeys];
    return current->key[current->numKeys - 1];
}

int findSuccessor(Node* root, int idx) {
    Node* current = root->children[idx + 1];
    while (!current->isLeaf)
        current = current->children[0];
    return current->key[0];
}

void borrowFromLeftSibling(Node* root, int idx) {
    Node* child = root->children[idx];
    Node* sibling = root->children[idx - 1];

    for (int i = child->numKeys - 1; i >= 0; --i)
        child->key[i + 1] = child->key[i];

    if (!child->isLeaf) {
        for (int i = child->numKeys; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    child->key[0] = root->key[idx - 1];

    if (!root->isLeaf)
        child->children[0] = sibling->children[sibling->numKeys];

    root->key[idx - 1] = sibling->key[sibling->numKeys - 1];

    child->numKeys += 1;
    sibling->numKeys -= 1;
}

void borrowFromRightSibling(Node* root, int idx) {
    Node* child = root->children[idx];
    Node* sibling = root->children[idx + 1];

    child->key[child->numKeys] = root->key[idx];

    if (!child->isLeaf)
        child->children[child->numKeys + 1] = sibling->children[0];

    root->key[idx] = sibling->key[0];

    for (int i = 1; i < sibling->numKeys; ++i)
        sibling->key[i - 1] = sibling->key[i];

    if (!sibling->isLeaf) {
        for (int i = 1; i <= sibling->numKeys; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->numKeys += 1;
    sibling->numKeys -= 1;
}

Node* deleteNode(Node* root, int data) {
    int idx = 0;
    while (idx < root->numKeys && root->key[idx] < data)
        ++idx;

    if (idx < root->numKeys && root->key[idx] == data) {
        if (root->isLeaf)
            deleteFromLeaf(root, idx);
        else
            deleteFromInternalNode(root, idx);
    } else {
        if (root->isLeaf)
            return root;

        bool isLastChild = (idx == root->numKeys);

        if (root->children[idx]->numKeys < MAX / 2) {
            if (idx != 0 && root->children[idx - 1]->numKeys >= MAX / 2)
                borrowFromLeftSibling(root, idx);
            else if (idx != root->numKeys && root->children[idx + 1]->numKeys >= MAX / 2)
                borrowFromRightSibling(root, idx);
            else {
                if (idx != root->numKeys)
                    mergeChildNodes(root, idx);
                else
                    mergeChildNodes(root, idx - 1);
            }
        }

        if (isLastChild && idx > root->numKeys)
            root->children[idx - 1] = deleteNode(root->children[idx - 1], data);
        else
            root->children[idx] = deleteNode(root->children[idx], data);
    }

    if (root->numKeys == 0) {
        Node* temp = root;
        if (root->isLeaf)
            root = nullptr;
        else
            root = root->children[0];

        delete temp;
    }
    return root;
}

void displayNode(Node* node) {
    if (!node) return;
    cout << "[";
    for (int i = 0; i < node->numKeys; ++i) {
        cout << node->key[i];
        if (i < node->numKeys - 1) cout << ", ";
    }
    cout << "] ";
}

void NLR(Node* root) {
    if (!root) return;

    displayNode(root);
    for (int i = 0; i <= root->numKeys; ++i)
        NLR(root->children[i]);
}

void LNR(Node* root) {
    if (!root) return;

    for (int i = 0; i < root->numKeys; ++i) {
        LNR(root->children[i]);
        displayNode(root);
    }
    LNR(root->children[root->numKeys]);
}

void LRN(Node* root) {
    if (!root) return;

    for (int i = 0; i <= root->numKeys; ++i)
        LRN(root->children[i]);
    displayNode(root);
}

void LevelOrder(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();

        displayNode(node);

        for (int i = 0; i <= node->numKeys; ++i) {
            if (node->children[i])
                q.push(node->children[i]);
        }
    }
}

int main() {    
    Node* root = nullptr;
    int choice, value;

    do{
        cout << "\n=== B-Tree Options===\n";
        cout << "1. Insert a number\n";
        cout << "2. Search a number\n";
        cout << "3. Delete a number\n";
        cout << "4. Pre-order Traversal\n";
        cout << "5. In-order Traversal\n";
        cout << "6. Post-order Traversal\n";
        cout << "7. Level-order Traversal\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter a number to insert: ";
                cin >> value;
                root = insert(root, value);
                break;
            case 2:
                cout << "Enter a number to search: ";
                cin >> value;
                if (search(root, value))
                    cout << value << " is found\n";
                else
                    cout << value << " is not found\n";
                break;
            case 3:
                cout << "Enter a number to delete: ";
                cin >> value;
                root = deleteNode(root, value);
                cout << "Deleted " << value << " successfully!\n";
                break;
            case 4:
                cout << "Pre-order Traversal: ";
                NLR(root);
                cout << "\n";
                break;
            case 5:
                cout << "In-order Traversal: ";
                LNR(root);
                cout << "\n";
                break;
            case 6:
                cout << "Post-order Traversal: ";
                LRN(root);
                cout << "\n";
                break;
            case 7:
                cout << "Level-order Traversal: ";
                LevelOrder(root);
                cout << "\n";
                break;
            case 8:
                cout << "Exiting program \n";
                break;
            default:
                cout << "Invalid choice !!! \n";
        }
    } while(choice != 8);
    
    return 0;
}
