#include <iostream> 
#include <fstream> 
#include <vector>
#define fi first
#define se second
#define maxn 100005
using namespace std;

struct Data{
    int u, v, cost;
    Data(int _u, int _v, int _cost){
        u = _u;
        v = _v;
        cost = _cost;
    }
};

struct HEAP_SORT{
    vector <Data> arr;
    void heapify(int idx){
        int n = arr.size() - 1;
        int left = idx * 2 + 1;
        int right = idx * 2 + 2;
        int minID = idx;
        if (left < n && arr[minID].cost > arr[left].cost){
            minID = left;
        }
        if (right < n && arr[minID].cost > arr[right].cost){
            minID = right;
        }
        if (minID != idx){
            swap(arr[minID], arr[idx]);
            heapify(minID);
        }
    }

    void push(Data newNode){
        arr.push_back(newNode);
        int i = arr.size() - 1;
        while (i > 0 && arr[i].cost < arr[(i - 1) / 2].cost){
            swap(arr[(i - 1) / 2], arr[i]);
            i = (i - 1) / 2;
        }
    }
    
    Data top(void){
        Data res = arr[0];
        arr[0] = arr.back();
        arr.pop_back();
        heapify(0);
        return res;
    }
};

int n;
bool visited[maxn];
vector <pair<int, int>> adj[maxn];

void prim(void){
    cout << "Edge" << "\t" << "Weight" << '\n';
    HEAP_SORT heap;
    for (int i = 0; i < n; i++) visited[i] = false;
    heap.push(Data(0, 0, 0));

    while (heap.arr.size() != 0){
        Data tmp = heap.top();
        if (visited[tmp.v]) continue;
        visited[tmp.v] = true;
        
        if (tmp.u != tmp.v)
            cout << tmp.u << " - " << tmp.v << '\t' << tmp.cost << '\n';

        for (pair <int, int> v: adj[tmp.v]){
            if (!visited[v.fi])
                heap.push(Data(tmp.v, v.fi, v.se));
        }  
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
            if (cost) adj[i].push_back(make_pair(j, cost));
        }
    }
    fileIn.close();
}

int main(){
    readFile();
    prim();
    return 0;
}