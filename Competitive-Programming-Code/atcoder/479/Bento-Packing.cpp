#include <bits/stdc++.h>

using namespace std;
#define ll long long
ll mx = 0, n, w;

vector<int> a, b;
void dfs(int u, ll sum, ll val)
{
    if (sum > w || u > n + 1)
        return;
    mx = max(mx, val);

    dfs(u + 1, sum, val);
    dfs(u + 1, sum + b[u], val + a[u]);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> w;
    a.resize(n + 2, 0);
    b.resize(n + 2, 0);
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i];

    dfs(1, 0, 0);

    cout << mx << endl;

    return 0;
}