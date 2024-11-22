#include <iostream>
#include <vector>
#define fi first
#define se second
#define pii pair<int, int>
#define fo(i, a, b) for (int i = a; i <= b; i++)
using namespace std;
vector<pii>lst;
vector <int> a;
int n;

void process(void){
    // sparse table
    vector<vector<int>> st(n, vector<int>(n, 0));
    cout << st[0].size() << endl;
}

int main(){
    cin >> n;
    fo(i, 0, n - 1){
        int x;
        cin >> x;
        a.push_back(x);
    }
    int l, r;
    while(cin >> l >> r){
        if (l == -1 && r == -1) break;  // END OF INPUT
        else{
            lst.push_back({l, r});
        }
    }
    process();
}