#include <iostream>
#define int long long
using namespace std;

struct Node{
    int key, ltree, rtree;
    int height;
    Node* left, *right;
};

struct AVL_TREE{
    Node* newNode(int key){
        Node* tmp = new Node();
        tmp->key = key;
        tmp->ltree = 0;
        tmp->rtree = 0;
        tmp->height = 0;
        tmp->left = NULL;
        tmp->right = NULL;
        return tmp;
    }

    Node* search(Node* root, int key){
        if (root == NULL)
            return NULL;
        else if (root->key > key)
            return search(root->left, key);
        else if (root->key < key)
            return search(root->right, key);
        else 
            return root;
    }

    int getHeight(Node* root){
        if (root == NULL) return 0;
        return root->height;
    }

    int balanceFactor(Node* root){
        if (root == NULL) return 0;
        return getHeight(root->left) - getHeight(root->right);
    }
    
    void fixLeft(Node* root){
        if (root->left) 
            root->ltree = 1 + root->left->ltree + root->left->rtree;
        else
            root->ltree = 0;
    }

    void fixRight(Node* root){
        if (root->right)
            root->rtree = 1 + root->right->ltree + root->right->rtree;
        else 
            root->rtree = 0;
    }

    Node* leftRotation(Node* root){
        Node* tmp = root->right;
        root->right = tmp->left;
        tmp->left = root;

        tmp->height = 1 + max(getHeight(tmp->left), getHeight(tmp->right));
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        
        fixRight(root);
        fixLeft(tmp);
        return tmp;
    }
    
    Node* rightRotation(Node* root){
        Node* tmp = root->left;
        root->left = tmp->right;
        tmp->right = root;
        
        tmp->height = 1 + max(getHeight(tmp->left), getHeight(tmp->right));
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        fixLeft(root);
        fixRight(tmp);
        return tmp;
    }

    Node* findMin(Node* root){
        if (root == NULL)
            return NULL;
        if (root->left == NULL)
            return root;
        return findMin(root->left);
    }

    Node* insertNode(Node* root, int key){
        if (root == NULL){
            return newNode(key);
        }
        else if (root->key > key)
            root->left = insertNode(root->left, key);
        else if (root->key < key)
            root->right = insertNode(root->right, key);
    
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        int bf = balanceFactor(root);
        fixLeft(root);
        fixRight(root);
        if (bf > 1 && key < root->left->key){
            return rightRotation(root);
        }
        if (bf > 1 && key > root->left->key){
            root->right = leftRotation(root->right);
            return rightRotation(root);
        }
        if (bf < -1 && key > root->right->key){
            return leftRotation(root);
        }
        if (bf < -1 && key < root->right->key){
            root->left = rightRotation(root->left);
            return leftRotation(root);
        }
        return root;
        
    }

    Node* remove(Node* root, int key){
        if (root == NULL) 
            return NULL;
        else if (root->key > key)
            root->left = remove(root->left, key);
        else if (root->key < key)
            root->right = remove(root->right, key);
        else{
            if (root->left != nullptr && root->right != nullptr){
                Node* tmpMin = findMin(root->right);
                root->key = tmpMin->key;
                root->right = remove(root->right, root->key);
            }
            else{
                Node* tmp = root;
                if (root->left)
                    root = root->left;
                else if (root->right)
                    root = root->right;
                delete tmp;
            }
        }
        if (root == NULL)
            return root;

        fixLeft(root);
        fixRight(root);
        

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        int bf = balanceFactor(root);

        if (bf > 1 && key < root->left->key){
            root = rightRotation(root);
        }
        if (bf > 1 && key > root->left->key){
            root->right = leftRotation(root->right);
            root = rightRotation(root);
        }
        if (bf < -1 && key > root->right->key){
            root = leftRotation(root);
        }
        if (bf < -1 && key < root->right->key){
            root->left = rightRotation(root->left);
            root = leftRotation(root);
        }
        
       
        return root;
    }

    int kthSmallest(Node* root, int k){
        if (root == NULL) return -1;
        if (root->ltree + 1 == k) return root->key;
        if (root->ltree + 1 > k){
            return kthSmallest(root->left, k - 1);
        }
        else{
            k = k - root->ltree - 1;
            return kthSmallest(root->right, k);
        }
    }

    int countLess(Node* root, int x){
        if (root == NULL) return 0;
        int res = 0;
        if (root->key < x){
            res += root->ltree + 1;
            res += countLess(root->right, x);
        }
        else{
            res += countLess(root->left, x);
        }
        return res;
    }
    void LNR(Node* root){
        if (root == NULL) return;
        LNR(root->left);
        cout << root->key << " ";
        LNR(root->right);
    }
};

signed main(){
    freopen("practice.inp","r",stdin);
    freopen("practice.out","w",stdout);
    int Q;
    cin >> Q;
    Node* root = nullptr;
    AVL_TREE avl;
    while(Q--){
        char c;
        int x;
        cin >> c >> x;
        if (c == 'I'){
            Node* tmp = avl.search(root, x);
            if (!tmp) root = avl.insertNode(root, x);
        }
        else if (c == 'D'){
            Node* tmp = avl.search(root, x);
            if (tmp) root = avl.remove(root, x);
        }
        else if (c == 'C'){
            cout << avl.countLess(root, x) << "\n";
        }
        else if (c == 'K'){
            int res = avl.kthSmallest(root, x);
            if (res == -1){
                cout << "invalid\n";
            }
            else cout << res << '\n';
        }
    }
    // avl.LNR(root);
    return 0;
}