#include <iostream>
#include <fstream>
#include <vector>
#define maxn 100005
using namespace std;

struct Data{
    int cost, u, v;
    Data(int _cost, int _u, int _v){
        cost = _cost;
        u = _u;
        v = _v;
    }
};

struct DSU{
    int root[maxn];
    
    void build(int n){
        for (int i = 0; i < n; i++) root[i] = -1;
    }  

    int find(int u){
        if (root[u] < 0) return u;
        return root[u] = find(root[u]);
    }

    void join(int u, int v){
        u = find(u);
        v = find(v);
        if (u == v) return;
        if (root[u] > root[v]) swap(u, v);
        root[u] += root[v];
        root[v] = u;
    }
};

int n;
vector <Data> edge;

void quickSort(int l, int r){
    if (l >= r) return;
    Data pivot = edge[(l + r) / 2];
    int i = l, j = r;
    while (i <= j){
        while (edge[i].cost < pivot.cost) i++;
        while (edge[j].cost > pivot.cost) j--;
        if (i <= j){
            swap(edge[i], edge[j]);
            i++;
            j--;
        }
    }
    quickSort(l, j);
    quickSort(i, r);
}
void kruskal(void){
    DSU dsu;
    dsu.build(n);
    quickSort(0, edge.size() - 1);
    cout << "Edge" << "\t" << "Weight" << '\n';
    for (int i = 0; i < edge.size(); i++){
        int cost = edge[i].cost;
        int u = edge[i].u;
        int v = edge[i].v;
        if (dsu.find(u) == dsu.find(v)) continue;
        dsu.join(u, v);
        cout << u << " - " << v << "\t" << cost << '\n';
        
    }
}

void readFile(void){
    fstream fileIn("graph.txt", ios::in);
    if (!fileIn.is_open()){
        cout << "Can not open file !!!";
        return;
    }
    fileIn >> n;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            int cost;
            fileIn >> cost;
            if (cost) edge.push_back(Data(cost, i, j));
        }
    }
}

int main(){
    readFile();
    kruskal();
    return 0;
}
