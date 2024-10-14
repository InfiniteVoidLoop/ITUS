#include <iostream>
using namespace std;

void inputArray(int *&arr, int n)
{
    arr = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
}

void printArray(int *&arr, int n)
{
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";

    cout << '\n';
}

int findMax(int *&arr, int n)
{
    int maxx = arr[0];
    for (int i = 0; i < n; ++i)
    {
        maxx = max(maxx, arr[i]);
    }
    return maxx;
}

int sumArray(int *&arr, int n)
{
    int sum = 0;
    for (int i = 0; i < n; ++i)
        sum += arr[i];
    return sum;
}

void concatArrays(int *a, int na, int *b, int nb, int *&res, int &nres)
{
    nres = na + nb;
    res = (int *)calloc(na + nb, sizeof(int));
    for (int i = 0; i < na; i++)
        res[i] = a[i];
    for (int i = 0; i < nb; i++)
        res[na + i] = b[i];
}

void findLongestAscendingSubarray(int *arr, int n, int *&res, int &nres)
{
    int *f = (int *)calloc(n, sizeof(int));
    f[0] = 1;
    int maxpos = 0;
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] >= arr[i - 1])
            f[i] = f[i - 1] + 1;
        else
            f[i] = 1;
        if (f[maxpos] < f[i])
            maxpos = i;
    }

    nres = f[maxpos];
    res = (int *)calloc(nres, sizeof(int));

    int pos = 0;
    for (int i = maxpos - f[maxpos] + 1; i <= maxpos; i++)
        res[pos++] = arr[i];
}

int main()
{
    int *a, na;
    cin >> na;
    inputArray(a, na);

    int *b, nb;
    cin >> nb;
    inputArray(b, nb);

    int *c, nc;
    concatArrays(a, na, b, nb, c, nc);
    printArray(c, nc);
    cout << findMax(c, nc) << '\n';
    cout << sumArray(c, nc) << '\n';

    int *res, nres;
    findLongestAscendingSubarray(c, nc, res, nres);

    printArray(res, nres);

    free(a);
    free(b);
    free(c);
    free(res);

    return 0;
}
