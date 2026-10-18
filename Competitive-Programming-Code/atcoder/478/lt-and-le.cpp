#include <bits/stdc++.h>

using namespace std;

struct Edge
{
    int v; // 终点
    int w; // 0 表示 <=，1 表示 <
};

vector<vector<Edge>> g;

// Tarjan 相关
vector<int> dfn;     // DFS 访问时间
vector<int> low;     // 最早能回到的时间点
vector<int> stk;     // Tarjan 栈
vector<bool> in_stk; // 是否在栈中
vector<int> bel;     // 属于哪个 SCC

int timer = 0;   // DFS 时间戳
int top = 0;     // 栈顶
int scc_cnt = 0; // SCC 数量

void tarjan(int u)
{
    dfn[u] = ++timer;
    low[u] = dfn[u];
    stk[++top] = u;
    in_stk[u] = true;

    for (auto &e : g[u])
    {
        int v = e.v;
        if (dfn[v] == 0)
        {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (in_stk[v])
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (dfn[u] == low[u])
    {
        scc_cnt++;
        while (1)
        {
            int x = stk[top--];

            in_stk[x] = false;
            bel[x] = scc_cnt;

            if (x == u)
                break;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    g.resize(n + 1);

    dfn.resize(n + 1);
    low.resize(n + 1);
    stk.resize(n + 1);
    in_stk.resize(n + 1);
    bel.resize(n + 1);

    // 建原图
    for (int i = 0; i < m; i++)
    {
        int t, u, v;
        cin >> t >> u >> v;

        g[u].push_back({v, t});
    }

    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
            tarjan(i);
    }

    bool ok = true;
    for (int u = 1; u <= n; u++)
    {
        for (auto e : g[u])
        {
            if (e.w == 1 && bel[u] == bel[e.v])
            {
                ok = false;
            }
        }
    }
    if (!ok)
    {
        cout << "No" << endl;
        return 0;
    }
    vector<vector<Edge>> dag(scc_cnt + 1);
    vector<int> indeg(scc_cnt + 1, 0);

    for (int u = 1; u <= n; u++)
    {
        for (auto &e : g[u])
        {
            int v = e.v;
            if (bel[u] != bel[v])
            {
                dag[bel[u]].push_back({bel[v], e.w});
                indeg[bel[v]]++;
            }
        }
    }

    queue<int> q;
    for (int i = 1; i <= scc_cnt; i++)
    {
        if (indeg[i] == 0)
            q.push(i);
    }
    vector<int> val(scc_cnt + 1, 1);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (auto &e : dag[u])
        {
            int v = e.v;

            val[v] = max(val[v], val[u] + e.w);
            indeg[v]--;
            if (indeg[v] == 0)
                q.push(v);
        }
    }

    cout << "Yes" << endl;
    for (int i = 1; i <= n; i++)
        cout << val[bel[i]] << " ";

    return 0;
}