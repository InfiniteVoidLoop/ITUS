#include <iostream>
#include <queue>
using namespace std;

struct BinarySearchTree {
    struct Node {
        int key;
        Node* left;
        Node* right;
    };
    Node* root;
    BinarySearchTree() {
        root = NULL;
    }
    Node* newNode(int data) {
        Node* temp = new Node;
        temp->key = data;
        temp->left = temp->right = NULL;
        return temp;
    }
    Node* insert(Node* root, int data) {
        if (root == NULL) return newNode(data);
        if (data < root->key) root->left = insert(root->left, data);
        else if (data > root->key) root->right = insert(root->right, data);
        return root;
    }
    void clear(Node* root) {
        if (root != NULL) {
            clear(root->left);
            clear(root->right);
            delete root;
        }
    }
#define delete del
    Node* delete(Node* root, int data) {
        if (root == NULL) return root;
        if (data < root->key) root->left = delete(root->left, data);
        else if (data > root->key) root->right = delete(root->right, data);
        else {
#undef delete
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
#define delete del
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = delete(root->right, temp->key);
        }
        return root;
    }
    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != NULL) current = current->left;
        return current;
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
    int height(Node* root) {
        if (root == NULL) return 0;
        else {
            int lHeight = height(root->left);
            int rHeight = height(root->right);
            if (lHeight > rHeight) return lHeight + 1;
            return rHeight + 1;
        }
    }
    int countNode(Node* root) {
        if (root == NULL) return 0;
        return 1 + countNode(root->left) + countNode(root->right);
    }
    int countInternal(Node* root) {
        if (root == NULL || (root->left == NULL && root->right == NULL)) return 0;
        return 1 + countInternal(root->left) + countInternal(root->right);
    }
    int sumNode(Node* root) {
        if (root == NULL) return 0;
        return root->key + sumNode(root->left) + sumNode(root->right);
    }
    int countLeaf(Node* root) {
        if (root == NULL) return 0;
        if (root->left == NULL && root->right == NULL) return 1;
        return countLeaf(root->left) + countLeaf(root->right);
    }
    int countLess(Node* root, int x) {
        if (root == NULL) return 0;
        if (root->key < x) return 1 + countLess(root->left, x) + countLess(root->right, x);
        return countLess(root->left, x);
    }
    int countGreater(Node* root, int x) {
        if (root == NULL) return 0;
        if (root->key > x) return 1 + countGreater(root->left, x) + countGreater(root->right, x);
        return countGreater(root->right, x);
    }
};

int main() {
    BinarySearchTree tree;
    vector<int> arr = {8, 6, 5, 7, 10, 9};
    for (int i = 0; i < arr.size(); i++) {
        tree.root = tree.insert(tree.root, arr[i]);
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
    tree.root = tree.delete(tree.root, 8);
    cout << "Level-order: ";
    tree.LevelOrder(tree.root);
    cout << '\n';
    cout << "Height: " << tree.height(tree.root) << '\n';
    cout << "Number of nodes: " << tree.countNode(tree.root) << '\n';
    cout << "Number of internal nodes: " << tree.countInternal(tree.root) << '\n';
    cout << "Sum of all nodes: " << tree.sumNode(tree.root) << '\n';
    cout << "Number of leaf nodes: " << tree.countLeaf(tree.root) << '\n';
    cout << "Number of nodes less than 7: " << tree.countLess(tree.root, 7) << '\n';
    cout << "Number of nodes greater than 7: " << tree.countGreater(tree.root, 7) << '\n';   
    tree.clear(tree.root);
// #undef delete
    return 0;
}