#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <sstream>
#include <string>
using namespace std;
struct nNode;

struct Node{
    int indeg;
    int task; 
    Node* next;
    nNode* adj;
};

struct nNode{
    Node* node;
    nNode* next;
};
vector<int>ans; 

Node* findNode(Node* &head, int u){
    Node* curr = head;
    if (curr == NULL){
        head = new Node;
        head->task = u;
        head->next = NULL;
        head->adj = NULL;
        head->indeg = 0;
        return head;
    }
    while (curr->next != NULL){
        if (curr->task == u){
            return curr;
        }
        curr = curr->next;
    }
    if (curr->task == u){
        return curr;
    }
    curr->next = new Node;
    curr->next->task = u;
    curr->next->next = NULL;
    curr->next->adj = NULL;
    curr->next->indeg = 0;
    return curr->next;
}

void add(Node*& u, Node*& v){
    nNode* head = u->adj;
    if (head == NULL){
        u->adj = new nNode;
        u->adj->node = v;
        u->adj->next = NULL;
        return;
    }
    while (head->next != NULL){
        head = head->next;
    }
    head->next = new nNode;
    head->next->node = v;
    head->next->next = NULL;
}

void connect(Node* &head, int u, int v){
    Node* uNode = findNode(head, u);
    Node* vNode = findNode(head, v);
    add(uNode, vNode);
    vNode->indeg = vNode->indeg + 1;
}

void clear(Node* &head){
    Node* curr = head;
    while (curr != NULL){
        nNode* currAdj = curr->adj;
        while (currAdj != NULL){
            nNode* temp = currAdj;
            currAdj = currAdj->next;
            delete temp;
        }
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

void topoSort(Node* &head){
    Node* curr = head;
    queue <Node*> q;
    vector  <int> ans;
    int tmp = 0;
    while(curr){
        tmp++;
        curr = curr->next;
    }
    curr = head;
    while(curr){
        if (curr->indeg == 0){
            q.push(curr);
        }
        curr = curr->next;
    }

    while (!q.empty()){
        Node* u = q.front();
        q.pop();
        ans.push_back(u->task);
        nNode* curr = u->adj;
        while(curr != NULL){
            curr->node->indeg = curr->node->indeg - 1;
            if (curr->node->indeg == 0){
                q.push(curr->node);
            }
            curr = curr->next;
        }
    }
    fstream fileOut("output.txt", ios::out);
    if (!fileOut){
        cout << "File not found" << endl;
        return;
    }
    if (ans.size() == tmp){
        for (int i = 0; i < ans.size(); i++){
            fileOut << ans[i] << " ";
        }
    }
    else{
        fileOut << -1;
    }

}

int main(){
    fstream fileIn("input.txt", ios::in);
    if (!fileIn){
        cout << "File not found" << endl;
        return 0;
    }
    string line;
    getline(fileIn, line);
    stringstream iss(line);
    Node* head = NULL;
    char c;
    while (iss >> c){
        int u, v;
        iss >> u >> c >> v >> c;
        connect(head, u, v);
    }
    topoSort(head);
    clear(head);

    fileIn.close();
    return 0;

}