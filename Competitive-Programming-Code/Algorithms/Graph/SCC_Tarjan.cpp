#include <bits/stdc++.h>
using namespace std;

// 有向图 Tarjan SCC，顶点编号 1..n。
// 整理自 atcoder/478/lt-and-le.cpp；只负责求强连通分量。
// 递归深度最坏为 n，大规模长链应考虑显式栈实现。
struct SCC
{
    int n, timer = 0, scc_cnt = 0;
    vector<vector<int>> g;
    vector<int> dfn, low, stk, bel;
    vector<bool> in_stk;

    explicit SCC(int n) : n(n), g(n + 1), dfn(n + 1), low(n + 1),
                          bel(n + 1), in_stk(n + 1, false) {}

    void add_edge(int u, int v)
    {
        g[u].push_back(v);
    }

    void tarjan(int u)
    {
        dfn[u] = low[u] = ++timer;
        stk.push_back(u);
        in_stk[u] = true;

        for (int v : g[u])
        {
            if (!dfn[v])
            {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            }
            else if (in_stk[v])
            {
                // 已访问、尚未归入完成的 SCC：用 dfn[v] 更新。
                low[u] = min(low[u], dfn[v]);
            }
        }

        if (dfn[u] == low[u])
        {
            ++scc_cnt;
            while (true)
            {
                int x = stk.back();
                stk.pop_back();
                in_stk[x] = false;
                bel[x] = scc_cnt;
                if (x == u)
                    break;
            }
        }
    }

    int run()
    {
        // 清空上次计算状态，保留图；再次调用会重新计算。
        timer = scc_cnt = 0;
        fill(dfn.begin(), dfn.end(), 0);
        fill(low.begin(), low.end(), 0);
        fill(bel.begin(), bel.end(), 0);
        fill(in_stk.begin(), in_stk.end(), false);
        stk.clear();
        for (int u = 1; u <= n; ++u)
            if (!dfn[u])
                tarjan(u);
        return scc_cnt;
    }

    vector<vector<int>> condensation() const
    {
        // run() 后调用。保留跨分量重边，拓扑排序时入度也逐边统计。
        vector<vector<int>> dag(scc_cnt + 1);
        for (int u = 1; u <= n; ++u)
            for (int v : g[u])
                if (bel[u] != bel[v])
                    dag[bel[u]].push_back(bel[v]);
        return dag;
    }
};

#ifndef SCC_TEMPLATE_NO_MAIN
// 输入：n m，接着 m 行有向边 u v。
// 输出：SCC 数量；每个顶点所属分量编号。
// 编号由搜索与弹栈顺序决定，不是题目顶点编号。
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m))
        return 0;
    SCC scc(n);
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        scc.add_edge(u, v);
    }
    cout << scc.run() << '\n';
    for (int u = 1; u <= n; ++u)
        cout << scc.bel[u] << (u == n ? '\n' : ' ');
    return 0;
}
#endif
