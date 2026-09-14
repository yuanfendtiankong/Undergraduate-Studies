#include <bits/stdc++.h>

using namespace std;
const int N = 4e4 + 10;
typedef pair<int, int> pii;
int tr[N], level[N];
int lowbit(int x)
{
    return x & -x;
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
    for (int i = x; i < N; i += lowbit(i))
        tr[i] += v;
}
void solve()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        x++;

        int t = query(x);
        level[t]++;
        add(x, 1);
    }
    for (int i = 0; i < n; i++)
        cout << level[i] << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}