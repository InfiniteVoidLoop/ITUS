#include <iostream>
#define int long long
using namespace std;


struct Node{
    int key, ltree, rtree;
    Node* left, *right;
    Node(int _key, int _ltree, int _rtree, Node* _left, Node* _right){
        key = _key, ltree = _ltree, rtree = _rtree;
        left = _left;
        right = _right;
    }
};

struct BINARY_SEARCH_TREE{
    Node* newNode(int key){
        return new Node(key, 0, 0, nullptr, nullptr);
    }

    void fixLeft(Node* root){
        if (root->left) root->ltree = root->left->ltree + root->left->rtree + 1;
        else root->ltree = 0;
    }

    void fixRight(Node* root){
        if (root->right) root->rtree = root->right->ltree + root->right->rtree + 1;
        else root->rtree = 0;
    }

    Node* insert(Node* root, int key){
        if (root == nullptr){
            root = newNode(key);
        }
        else if (root->key > key)
            root->left = insert(root->left, key);
        else if (root->key < key)
            root->right = insert(root->right, key);
        
        fixLeft(root);
        fixRight(root);
        return root;
    }
    
    int search(Node* root, int offset, int key){
        if (root == NULL) 
            return -1;
        if (root->key == key){
            return offset + root->rtree + 1;
        }
        else if (root->key > key){
            return search(root->left, offset + 1 + root->rtree, key);
        }
        else 
            return search(root->right, offset, key);
    }
    void LNR(Node* root){
        if (root == NULL)
            return;
        cout << root->key << " ";
        LNR(root->left);
        LNR(root->right);
    }
};

signed main(){
    // freopen("practice.inp", "r", stdin);
    // freopen("practice.out", "w", stdout);
    int  q;
    cin >> q;
    Node* root = nullptr;
    BINARY_SEARCH_TREE bst;
    while(q--){
        int type, val;
        cin >> type >> val;
        if (type == 1){
            root = bst.insert(root, val);
        }
        else{
            int res = bst.search(root, 0, val);
            if (res == -1)
                cout << "Data tidak ada \n";
            else    
                cout << res << '\n';
        }
    }
    // bst.LNR(root);
    return 0;
}