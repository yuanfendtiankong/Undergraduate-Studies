#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10, mod = 99999997;
typedef long long ll;
#define endl '\n'
int a[N], p[N];

ll n, res = 0;

void merge(int l, int r)
{
    if (l >= r)
        return;
    int mid = l + r >> 1;
    merge(l, mid), merge(mid + 1, r);
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
    {
        if (a[i] <= a[j])
            p[k++] = a[i++];
        else
        {
            res = res + mid - i + 1;
            p[k++] = a[j++];
        }
    }

    while (i <= mid)
        p[k++] = a[i++];
    while (j <= r)
        p[k++] = a[j++];

    for (int i = l, j = 0; i <= r; i++, j++)
        a[i] = p[j];
}
int main()

{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> n, n)
        {for (int i = 1; i <= n; i++)
            cin >> a[i];

    merge(1, n);
    cout << res << endl;

    return 0;
}

/*
7 5 3
7 6 1 3 2 5 4
3 1 5 4 2 6 7
7 6 5 4 3 2 1

YES
NO
NO
*/
