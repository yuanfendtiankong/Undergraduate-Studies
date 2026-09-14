#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
const int N = 2e5 + 10;
ll n, m, k, ans = 1e18;
bool st[10];
vector<pii> edg[10];
void dfs(ll x, ll val)
{
    if (x == n)
    {
        ans = min(val, ans);
        return;
    }

    for (int i = 1; i <= n; i++)
    {
        if (st[i])
        {
            for (int j = 0; j < edg[i].size(); j++)
            {
                ll u = edg[i][j].first;
                if (!st[u])
                {
                    st[u] = 1;
                    dfs(x + 1, (val + edg[i][j].second) % k);
                    st[u] = 0;
                }
            }
        }
    }
}
int main()
{
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++)
    {
        ll a, b, w;
        cin >> a >> b >> w;
        edg[a].push_back({b, w});
        edg[b].push_back({a, w});
    }
    st[1] = 1;
    dfs(1, 0);
    cout << ans << endl;

    return 0;
}