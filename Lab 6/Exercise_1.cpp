#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#define maxn 100005
using namespace std;


struct Data{
    int node, cost;
    Data(int _node, int _cost){
        node = _node;
        cost = _cost;
    }    
};
vector <Data> adj[maxn];
int n;

struct HEAP_SORT{
    vector <Data> arr;
    void heapify(int idx){
        int l = idx * 2 + 1;
        int r = idx * 2 + 2;
        int minID = idx, sz = arr.size();

        if (l < sz && arr[l].cost < arr[minID].cost){
            minID = l;
        }
        if (r < sz && arr[r].cost < arr[minID].cost){
            minID = r;
        }
        if (minID != idx){
            swap(arr[minID], arr[idx]);
            heapify(minID);
        }
    }
    
    void push(Data newNode){
        arr.push_back(newNode);
        int i = arr.size() - 1;
        while (i > 0 && arr[(i - 1) / 2].cost > arr[i].cost){
            swap(arr[(i - 1) / 2], arr[i]);
            i = (i - 1) / 2;
        }
    }
    
    Data Top(){
        Data node = arr[0];
        arr[0] = arr.back();
        arr.pop_back();
        heapify(0);
        return node;
    }
};


struct DIJKSTRA{
    HEAP_SORT heap;
    int trace[maxn], dis[maxn];

    void dijkstra(int node){
        for (int i = 0; i < n; i++) dis[i] = 10000007;
        HEAP_SORT heap;
        dis[node] = 0; 
        heap.push({node, dis[node]});
        while(heap.arr.size() != 0){
            int u = heap.Top().node;

            for (Data v: adj[u]){
                if (dis[v.node] > dis[u] + v.cost){
                    dis[v.node] = dis[u] + v.cost;
                    trace[v.node] = u;
                    heap.push({v.node, dis[v.node]});
                }
            }
        }
    }

    void trace_back(int node, int v){        
        cout << "The shortest path from " << node << " to " << v << ": ";
        stack <int> st;
        while (v != node){
            st.push(v);
            v = trace[v];
        }
        st.push(v);
        while(!st.empty()){
            if (st.size() > 1)
                cout << st.top() << " -> ";
            else 
                cout << st.top() <<".\n"; 
            st.pop();
        }
    }
};

void readFile(void){
    ifstream fileIn("graph.txt");
    fileIn >> n;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            int cost;
            fileIn >> cost;
            if (cost != 0) adj[i].push_back(Data(j, cost));
        }
    }
    fileIn.close();
}

int main(){
    int source;
    cout << "Enter source vertex: ";
    cin >> source;
    
    readFile();
    
    DIJKSTRA dijkstra;
    dijkstra.dijkstra(source);

    for (int i = 0; i < n; i++){
        if (i == source) continue;
        dijkstra.trace_back(source, i);
    }
    return  0;
}