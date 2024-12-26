#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#define maxn 10005

using namespace std;
 
struct Data{
    int u, v, cost;
    Data(int _u, int _v, int _cost){
        u = _u; 
        v = _v;
        cost = _cost;
    }
};
int n;
vector <Data> edge;

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
            if (cost) edge.push_back(Data(i, j, cost));
        }
    }
}

int dist[maxn], trace[maxn];
void bellman_ford(int source){
    for (int i = 0; i < n; i++) dist[i] = 1000000009;
    dist[source] = 0;
    for (int i = 0; i < n; i++){
        for (auto [u, v, w]: edge){
            if (dist[v] > dist[u] + w){
                if (i == n - 1){
                    cout << "Detect negative cycle !!! \n";
                    return;
                }
                dist[v] = dist[u] + w;
                trace[v] = u;
            }
        }
    }
}

void trace_back(int source, int v){
    stack <int> st;
    cout << "The shortest path from " << source << " to " << v << ": ";
    while (v != source){
        st.push(v);
        v = trace[v];
    }
    st.push(v);
    while(!st.empty()){
        if (st.size() > 1) 
            cout << st.top() << " -> ";
        else 
            cout << st.top() << ". \n";
        st.pop();
    }
    
}

int main(){
    readFile();
    int source;
    cout << "Enter source vertex: ";
    cin >> source;
    bellman_ford(source);
    for (int i = 0; i < n; i++){
        if (i == source) continue;
        trace_back(source, i);
    }
    return 0;
}