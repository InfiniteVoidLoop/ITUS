#include <iostream>
#include <vector>
#include <cmath>
#define fi first
#define se second
#define pb push_back
#define pii pair<int, int>
#define fo(i, a, b) for (int i = a; i <= b; i++)
using namespace std;
vector <int> a;
int n;

struct Data{
    int max, min, gcd;    
};
vector<vector<Data>> st;
vector <Data> tmp;

int GCD(int a, int b){
    if (b == 0) return a;
    return GCD(b, a % b);
}

void preCal(void){
    int log = log2(n) + 1;
    fo(i, 0, log - 1) tmp.pb({-1000000000, 1000000000, 0});
    fo(i, 0, n - 1){
        st.pb(tmp);
        st[i][0].max = a[i];
        st[i][0].min = a[i];
        st[i][0].gcd = a[i];
    }
    for (int i = 1; i <= log2(n); i++){
        for (int j = 0; j < n; j++){
            if (j + (1 << i) - 1 > n - 1) break;
            st[j][i].max = max(st[j][i - 1].max, st[j + (1<<(i - 1))][i - 1].max);
            st[j][i].min = min(st[j][i - 1].min, st[j + (1<<(i - 1))][i - 1].min);
            st[j][i].gcd = GCD(st[j][i - 1].gcd, st[j + (1<<(i - 1))][i - 1].gcd);            
        }
    }
}

void cal(int l, int r){
    int len = r - l + 1;
    int k = log2(len);
    int maxVal = max(st[l][k].max, st[r - (1<<k) + 1][k].max);
    int minVal = min(st[l][k].min, st[r - (1<<k) + 1][k].min);
    int gcdVal = GCD(st[l][k].gcd, st[r - (1<<k) + 1][k].gcd);
    cout << maxVal << " " <<  minVal << " " << gcdVal << '\n'; 
}

int main(){
    cin >> n;
    fo(i, 0, n - 1){
        int x;
        cin >> x;
        a.push_back(x);
    }
    preCal();
    int l, r;
    while(cin >> l >> r){
        if (l == -1 && r == -1) break;  // END OF INPUT
        else{
            cal(l, r);
        }
    }
    return 0;
}