#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 10;
#define pii pair<int, int>
int d[N];
bool st[N];
int n, m, s, t;
vector<vector<pii>> g;
int dijkstra(int be, int ed)
{
    memset(d, 0x3f, sizeof d);
    d[be] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, be});

    while (q.size())
    {
        auto t = q.top();
        q.pop();

        int node = t.second, dis = t.first;
        if (st[node])
            continue;
        st[node] = true;

        for (int i = 0; i < g[node].size(); i++)
        {
            int now = g[node][i].first, nd = g[node][i].second;
            if (d[now] > d[node] + nd)
            {
                d[now] = d[node] + nd;
                q.push({d[now], now});
            }
        }
    }
    if (d[ed] == 0x3f3f3f3f)
        return -1;
    return d[ed];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> s >> t;
    g.resize(n + 1);
    vector<int> mn(n + 1, 1000000);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, 1});
        mn[a] = min(mn[a], b);
    }
    for (int i = 1; i <= n; i++)
    {
        if (g[i].size() == 0)
            continue;
        for (int j = 0; j < g[i].size(); j++)
            if (g[i][j].first == mn[i])
                g[i][j].second = 0;
    }

    cout << dijkstra(s, t) << endl;

    return 0;
}