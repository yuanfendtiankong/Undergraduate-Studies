#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int tr[N];
int n, m;
int lowbit(int x)
{
    return x & (-x);
}
int query(int x)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i))
        res += tr[i];
    return res;
}
void add(int x, int v)
{
    for (int i = x; i <= n; i += lowbit(i))
        tr[i] += v;
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        add(i, x);
    }

    while (m--)
    {
        int k, a, b;
        cin >> k >> a >> b;
        if (k == 0)
            cout << query(b) - query(a - 1) << endl;
        else
            add(a, b);
    }

    return 0;
}