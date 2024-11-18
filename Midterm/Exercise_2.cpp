#include <iostream>
#include <fstream>
#include <vector>
#define pb push_back
#define fi first
#define se second
#define maxn 1003
#define pii pair<int, int>
using namespace std;

int n, k = 0;
pii p[maxn], lst[maxn];

bool cmp(pii u, pii v)
{
    if (u.fi < v.fi)
        return true;
    if (u.fi == v.fi && u.se > v.se)
        return true;
    return false;
}

void quickSort(pii p[], int l, int r)
{
    int i = l, j = r;
    pii x = p[(l + r) / 2];
    while (i <= j)
    {
        while (cmp(p[i], x))
            i++;
        while (cmp(x, p[j]))
            j--;
        if (i <= j)
        {
            swap(p[i], p[j]);
            i++;
            j--;
        }
    }
    if (l < j)
        quickSort(p, l, j);
    if (i < r)
        quickSort(p, i, r);
}

void process(void)
{
    quickSort(p, 1, n);
    int preVal = p[1].fi;
    int curVal = p[1].se;
    for (int i = 2; i <= n; i++)
    {
        if (curVal >= p[i].fi)
        {
            if (curVal < p[i].se)
                curVal = p[i].se;
        }
        else
        {
            ++k;
            lst[k].fi = preVal;
            lst[k].se = curVal;
            preVal = p[i].fi;
            curVal = p[i].se;
        }
    }
    ++k;
    lst[k].fi = preVal;
    lst[k].se = curVal;
}

int main()
{
    fstream fileIn("input.txt", ios::in);
    fstream fileOut("output.txt", ios::out);

    fileIn >> n;
    for (int i = 1; i <= n; i++)
        fileIn >> p[i].fi >> p[i].se;
    process();
    quickSort(lst, 1, k);
    for (int i = 1; i <= k; i++)
    {
        fileOut << lst[i].fi << " " << lst[i].se << '\n';
    }
    fileIn.close();
    fileOut.close();
    return 0;
}
