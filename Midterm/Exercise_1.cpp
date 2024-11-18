#include <iostream>
#define maxn 100005
using namespace std;
int n, a[maxn], val;

int find(int l, int r, int val)
{
    int res = 0;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (a[mid] == val)
        {
            res = mid;
            break;
        }
        if (a[l] <= a[mid])
        {
            if (a[l] <= val && val < a[mid])
                r = mid - 1;
            else
                l = mid + 1;
        }
        else
        {
            if (a[mid] < val && val <= a[r])
                l = mid + 1;
            else
                r = mid - 1;
        }
    }
    return res;
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cin >> val;
    cout << find(1, n, val);
    return 0;
}