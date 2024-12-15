#include <iostream>
#include <queue>

using namespace std;

struct AVLTree {
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
    };
    Node* root;
    AVLTree() {
        root = NULL;
    }
private:
    Node* newNode(int data) {
        Node* temp = new Node;
        temp->key = data;
        temp->left = temp->right = NULL;
        temp->height = 1;
        return temp;
    }
    int height(Node* root) {
        if (root == NULL) return 0;
        return root->height;
    }
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));
        return x;
    }
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }

public:
    Node* insertNode(Node* root, int data) {
        if (root == NULL) return newNode(data);
        if (data < root->key) root->left = insertNode(root->left, data);
        else if (data > root->key) root->right = insertNode(root->right, data);
        else return root;
        root->height = 1 + max(height(root->left), height(root->right));
        int balance = height(root->left) - height(root->right);
        if (balance > 1 && data < root->left->key) return rightRotate(root);
        if (balance < -1 && data > root->right->key) return leftRotate(root);
        if (balance > 1 && data > root->left->key) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && data < root->right->key) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }
    Node* searchNode(Node* root, int data) {
        if (root == NULL || root->key == data) return root;
        if (root->key < data) return searchNode(root->right, data);
        return searchNode(root->left, data);
    }   
    Node* deleteNode(Node* root, int data) {
        if (root == NULL) return root;
        if (data < root->key) root->left = deleteNode(root->left, data);
        else if (data > root->key) root->right = deleteNode(root->right, data);
        else {
            if (root->left == NULL || root->right == NULL) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                }
                else *root = *temp;
                delete temp;
            }
            else {
                Node* temp = root->right;
                while (temp->left != NULL) temp = temp->left;
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }
        if (root == NULL) return root;
        root->height = 1 + max(height(root->left), height(root->right));
        int balance = height(root->left) - height(root->right);
        if (balance > 1 && height(root->left->left) - height(root->left->right) >= 0) return rightRotate(root);
        if (balance > 1 && height(root->left->left) - height(root->left->right) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && height(root->right->left) - height(root->right->right) <= 0) return leftRotate(root);
        if (balance < -1 && height(root->right->left) - height(root->right->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }
    void NLR(Node* root) {
        if (root != NULL) {
            cout << root->key << " ";
            NLR(root->left);
            NLR(root->right);
        }
    }
    void LNR(Node* root) {
        if (root != NULL) {
            LNR(root->left);
            cout << root->key << " ";
            LNR(root->right);
        }
    }
    void LRN(Node* root) {
        if (root != NULL) {
            LRN(root->left);
            LRN(root->right);
            cout << root->key << " ";
        }
    }
    void LevelOrder(Node* root) {
        if (root == NULL) return;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* temp = q.front();
            cout << temp->key << " ";
            q.pop();
            if (temp->left != NULL) q.push(temp->left);
            if (temp->right != NULL) q.push(temp->right);
        }
    }
    bool isFull(Node* root) {
        if (root == NULL) return true;
        if (root->left == NULL && root->right == NULL) return true;
        if (root->left != NULL && root->right != NULL) return isFull(root->left) && isFull(root->right);
        return false;
    }
    bool isComplete(Node* root, int index, int numberNodes) {
        if (root == NULL) return true;
        if (index >= numberNodes) return false;
        return isComplete(root->left, 2 * index + 1, numberNodes) && isComplete(root->right, 2 * index + 2, numberNodes);
    }
    bool isPerfect(Node* root) {
        int h = height(root);
        return isComplete(root, 0, 1 << h) && isFull(root);
    }
    int findCommonAncestor(Node* root, int x, int y) {
        if (root == NULL) return -1;
        if (root->key == x || root->key == y) return root->key;
        int left = findCommonAncestor(root->left, x, y);
        int right = findCommonAncestor(root->right, x, y);
        if (left != -1 && right != -1) return root->key;
        return left != -1 ? left : right;
    }
    void printSpecialNodes(Node* root) {
        if (root == NULL) return;
        if (root->left != NULL && root->right != NULL && root->right->key % root->left->key == 0) {
            printSpecialNodes(root->left);
            cout << root->key << " ";
            printSpecialNodes(root->right);
        }
        else {
            printSpecialNodes(root->left);
            printSpecialNodes(root->right);
        }
    }
};

int main() {
    AVLTree tree;
    vector<int> a = {1, 2, 3,4,5,6,7,8,9,10};
    for (int i = 0; i < (int) a.size(); i++) {
        tree.root = tree.insertNode(tree.root, a[i]);
    }
    cout << "Pre-order: ";
    tree.NLR(tree.root);
    cout << '\n';
    cout << "In-order: ";
    tree.LNR(tree.root);
    cout << '\n';
    cout << "Post-order: ";
    tree.LRN(tree.root);
    cout << '\n';
    tree.deleteNode(tree.root, 5);
    cout << "Level-order: ";
    tree.LevelOrder(tree.root);
    cout << '\n';
    cout << "Is full: " << tree.isFull(tree.root) << '\n';
    cout << "Is complete: " << tree.isComplete(tree.root, 0, 15) << '\n';
    cout << "Is perfect: " << tree.isPerfect(tree.root) << '\n';
    cout << "Common ancestor of 2 and 4: " << tree.findCommonAncestor(tree.root, 2, 4) << '\n';
    cout << "Special nodes: ";
    tree.printSpecialNodes(tree.root);
    return 0;
}