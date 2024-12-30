#include <iostream>
#define int long long
using namespace std;

struct Node{
    int key, ltree, rtree, height;
    Node* left, *right;
    Node(int _key, int _ltree,  int _rtree, int _height, Node* _left, Node* _right){
        key = _key, ltree = _ltree, rtree = _rtree, height = _height;
        left = _left, right = _right;
    }
};

struct AVL_TREE {
     Node* newNode(int key){
        return new Node(key, 0, 0, 0, nullptr, nullptr);
    }

    int getHeight(Node* root){
        if (root == NULL) return 0;
        return root->height;
    }
    
    int bf(Node* root){
        return getHeight(root->left) - getHeight(root->right);
    }

    Node* leftRotation(Node* root) {
        Node* tmp = root->right;
        root->right = tmp->left;
        tmp->left = root;

        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
        tmp->height = max(getHeight(tmp->left), getHeight(tmp->right)) + 1;

        fixLeft(root);
        fixRight(root);
        fixLeft(tmp);
        fixRight(tmp);

        return tmp;
    }

    Node* rightRotation(Node* root) {
        Node* tmp = root->left;
        root->left = tmp->right;
        tmp->right = root;

        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
        tmp->height = max(getHeight(tmp->left), getHeight(tmp->right)) + 1;

        fixLeft(root);
        fixRight(root);
        fixLeft(tmp);
        fixRight(tmp);

        return tmp;
    }

    void fixLeft(Node* root) {
        if (root->left)
            root->ltree = root->left->ltree + root->left->rtree + 1;
        else
            root->ltree = 0;
    }

    void fixRight(Node* root) {
        if (root->right)
            root->rtree = root->right->ltree + root->right->rtree + 1;
        else
            root->rtree = 0;
    }

    Node* insert(Node* root, int data) {
        if (!root) 
           root = newNode(data);
        else if (data < root->key)
            root->left = insert(root->left, data);
        else if (data > root->key)
            root->right = insert(root->right, data);

        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

        int balanceFactor = bf(root);

        if (balanceFactor > 1 && data < root->left->key)
            return rightRotation(root);

        if (balanceFactor > 1 && data > root->left->key) {
            root->left = leftRotation(root->left);
            root = rightRotation(root);
        }

        if (balanceFactor < -1 && data > root->right->key)
            return leftRotation(root);

        if (balanceFactor < -1 && data < root->right->key) {
            root->right = rightRotation(root->right);
            root = leftRotation(root);
        }

        fixLeft(root);
        fixRight(root);

        return root;
    }

    //   int search(Node* root, int offset, int data){
    //     if (root == NULL)
    //         return -1;
    //     if (root->key < data){
    //         return search(root->right, 1 + offset + root->ltree, data);
    //     }
    //     else if (root->key > data){
    //         return search(root->left, offset, data);
    //     }
    //     else{
    //         return offset + root->ltree + 1;
    //     }
    // }
      int search(Node* root, int offset, int data){
        if (root == NULL)
            return -1;
        if (root->key > data){
            return search(root->left, 1 + offset + root->rtree, data);
        }
        else if (root->key < data){
            return search(root->right, offset, data);
        }
        else{
            return offset + root->rtree + 1;
        }
    }
};

signed main() {
    // freopen("practice.inp","r",stdin);
    // freopen("practice.out","w",stdout);
    int q;
    cin >> q;

    Node* root = nullptr;
    AVL_TREE avl;

    while (q--) {
        int type, x;
        cin >> type >> x;

        if (type == 1) {
            root = avl.insert(root, x);
        } else {
            int res = avl.search(root, 0, x);
            if (res == -1) {
                cout << "Data tidak ada \n";
            } else {
                cout << res << '\n';
            }
        }
    }

    return 0;
}
