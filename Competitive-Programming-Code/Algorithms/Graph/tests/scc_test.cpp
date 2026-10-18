#define SCC_TEMPLATE_NO_MAIN
#include "../SCC_Tarjan.cpp"

int cases_checked = 0;

void check(SCC &scc)
{
    const int n = scc.n;
    vector<vector<bool>> reach(n + 1, vector<bool>(n + 1, false));
    for (int u = 1; u <= n; ++u)
    {
        reach[u][u] = true;
        for (int v : scc.g[u])
            reach[u][v] = true;
    }
    // 独立基准：Floyd 计算可达性，互相可达才属于同一 SCC。
    for (int k = 1; k <= n; ++k)
        for (int u = 1; u <= n; ++u)
            for (int v = 1; v <= n; ++v)
                reach[u][v] = reach[u][v] || (reach[u][k] && reach[k][v]);

    int count = scc.run();
    set<int> ids;
    for (int u = 1; u <= n; ++u)
    {
        assert(1 <= scc.bel[u] && scc.bel[u] <= count);
        ids.insert(scc.bel[u]);
        for (int v = 1; v <= n; ++v)
            assert((scc.bel[u] == scc.bel[v]) == (reach[u][v] && reach[v][u]));
    }
    assert(int(ids.size()) == count);
    assert(scc.stk.empty());
    for (int u = 1; u <= n; ++u)
        assert(!scc.in_stk[u]);

    auto dag = scc.condensation();
    multiset<pair<int, int>> expected_edges, actual_edges;
    for (int u = 1; u <= n; ++u)
        for (int v : scc.g[u])
            if (scc.bel[u] != scc.bel[v])
                expected_edges.insert({scc.bel[u], scc.bel[v]});
    vector<int> indeg(count + 1, 0);
    for (int u = 1; u <= count; ++u)
        for (int v : dag[u])
        {
            assert(u != v);
            actual_edges.insert({u, v});
            ++indeg[v];
        }
    assert(expected_edges == actual_edges);
    queue<int> q;
    for (int u = 1; u <= count; ++u)
        if (!indeg[u])
            q.push(u);
    int visited = 0;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        ++visited;
        for (int v : dag[u])
            if (--indeg[v] == 0)
                q.push(v);
    }
    assert(visited == count);
    ++cases_checked;
}

int main()
{
    vector<pair<int, vector<pair<int, int>>>> fixed = {
        {0, {}}, {1, {}}, {1, {{1, 1}}},
        {4, {{1, 2}, {2, 3}, {3, 4}}},
        {3, {{1, 2}, {2, 3}, {3, 1}}},
        {3, {{1, 2}, {3, 2}}}, // 指向已经出栈的分量。
        {4, {{1, 2}, {1, 2}, {2, 1}, {2, 3}, {3, 3}}},
        {6, {{1, 2}, {2, 3}, {3, 1}, {3, 4}, {4, 5}, {5, 4}, {5, 6}}}
    };
    for (auto &[n, edges] : fixed)
    {
        SCC scc(n);
        for (auto [u, v] : edges)
            scc.add_edge(u, v);
        check(scc);
        check(scc); // 重复计算应正确重置状态。
    }

    mt19937 rng(20261017);
    for (int t = 0; t < 2000; ++t)
    {
        int n = int(rng() % 10);
        SCC scc(n);
        for (int u = 1; u <= n; ++u)
            for (int v = 1; v <= n; ++v)
                if (rng() % 4 == 0)
                {
                    scc.add_edge(u, v);
                    if (rng() % 5 == 0)
                        scc.add_edge(u, v);
                }
        check(scc);
        if (n)
            scc.add_edge(1, n); // 计算后加边，再次运行。
        check(scc);
    }
    cout << "PASS: " << cases_checked
         << " cases; reachability, reset, added edges and condensation; seed=20261017\n";
}
