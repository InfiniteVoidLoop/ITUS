#include <iostream>
#define pii pair <int, int>
#define fi first
#define se second
using namespace std;


struct Node{
	pii key;	// value and number of occurences
    int count;
	int lcount;
	int subTree;
	Node* left;
	Node* right;
	Node(pii _key, int _lcount, int _count, int subTree, Node* _left, Node* _right){
		key = _key;
        count = _count;
		lcount = _lcount;
		left = _left;
		right = _right;
	}
};

struct BINARY_SEARCH_TREE{
	Node* newNode(pii key){
		Node* res = new Node(key, 1, 1, nullptr, nullptr);
		return res;
	}

	Node* insert(Node* root, pii key){
		if (root == NULL)
			root = newNode(key);
		else if (key < root->key)
			root->left = insert(root->left, key);
		else if (key > root->key)
			root->right = insert(root->right, key);
        
        root->lcount = 1;
        root->subTree = 1;
        root->count = 0;
        if (root->left){
            root->lcount += root->left->subTree;
            root->subTree += root->left->subTree;
        }
        if (root->right){
            root->subTree += root->right->subTree;
        }

		return root;
	}

	void update(Node* root, Node* tmp){
		if (root == tmp){
			tmp->key.se = tmp->key.se + 1;
			return;
		}
		if (root->key.fi > tmp->key.fi)
			update(root->left, tmp);
		else 
			update(root->right, tmp);
        
        if (root->left)
            root->key.se = root->left->key.se;
        if (root->right)
            root->key.se += root->left->key.se;

	}

	void insertNode(Node* root, int key){
		Node* tmp = searchNode(root, key);
		if (tmp != NULL){
			update(root, tmp);
		}
		else{
			root = insert(root, make_pair(key, 1));
        }
	}

	Node* findMin(Node* root){
		if (root == NULL) 
			return root;
		if (root->left == NULL)
			return root;
		else 
			return findMin(root->left);
	}

	Node* remove(Node* root, int value){
		if (root == NULL) 
			return NULL;
		else if (value < root->key.fi)
			root->left = remove(root->left, value);
		else if (value > root->key.fi)
			root->right = remove(root->right, value);
		else{
			if (root->key.se > 1)
				root->key.se--;
			else{
				if (root->left != NULL && root->right != NULL){
					Node* minNode = findMin(root->right);
					root->key = minNode->key;
					root->right = remove(root->right, root->key.fi);
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
		}
        root->key.se = 0;
		if (root->left){
            root->key.se = root->left->key.se;
            root->subTree = root->left->subTree;
            root->lcount = 1 + root->left->subTree;
        }
        if (root->right){
            root->key.se += root->right->key.se;
            root->subTree += root->right->subTree;
        }
		return root;
 	}

 	Node* searchNode(Node* root, int value){
 		if (root == NULL)
 			return NULL;
 		if (root->key.fi == value) 
 			return root;
 		else if (root->key.fi > value)
 			return searchNode(root->left, value);
 		else if (root->key.fi < value)
 			return searchNode(root->right, value);
 	}

 	int kSmallest(Node* root, int k){
 		if (root == nullptr) return -1;

 		if (k < root->lcount + 1)
 			return kSmallest(root->left, k);
 		else if (k == root->lcount + 1)
 			return root->key.fi;
 		else{
 			k = k - root->lcount - 1;
 			return kSmallest(root->right, k);
 		}
 	}
};

int main(){
	freopen("practice.inp", "r", stdin);
	freopen("practice.out", "w", stdout);
	Node* root = NULL;
	int N, M;
	BINARY_SEARCH_TREE bst;
	int lastAns, x, v;
	char c;
	cin >> N >> M;

	for (int i = 0; i < N; i++){
		int value;
		cin >> value;
		bst.insertNode(root, value);
	}

	while (M--){
		cin >> c >> x;
		v = x ^ lastAns;
		if (c == 'I'){
			bst.insertNode(root, v);
			lastAns = 0;
		}
		else if (c == 'R'){
			bst.remove(root, v);
			lastAns = 0;
		}
		else if (c == 'S'){
			lastAns = bst.kSmallest(root, v);
			cout << lastAns;
			cout << '\n';
		}
		else{
			Node* tmp = bst.searchNode(root, v);
			if (tmp == NULL)
				cout << -1;
			else 
				cout << tmp->right->key.se + 1;

			lastAns = tmp->right->key.se + 1;
			cout << '\n';
		}
	}
	return 0;
}
