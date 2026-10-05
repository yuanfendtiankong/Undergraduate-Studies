#pragma once
#include <bits/stdc++.h>

// 静态无权树：倍增 LCA。建树用迭代遍历，避免链状树递归爆栈。
class LCA
{
    int n, levels, edges = 0;
    bool ready = false;
    std::vector<std::vector<int>> adj, up;
    std::vector<int> depth;

public:
    explicit LCA(int count) : n(count), levels(1), adj(n), depth(n, -1)
    {
        assert(n >= 1);
        while ((1LL << levels) <= n) ++levels;
        up.assign(levels, std::vector<int>(n, 0));
    }

    void add_edge(int u, int v)
    {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back(v);
        adj[v].push_back(u);
        ++edges;
        ready = false;
    }

    // 必须先添加完整的一棵树，再 build，最后查询。
    void build(int root = 0)
    {
        assert(0 <= root && root < n && edges == n - 1);
        std::fill(depth.begin(), depth.end(), -1);
        std::vector<int> order{root};
        depth[root] = 0;
        up[0][root] = root;
        for (int i = 0; i < static_cast<int>(order.size()); ++i)
        {
            int u = order[i];
            for (int v : adj[u])
            {
                if (depth[v] != -1) continue;
                depth[v] = depth[u] + 1;
                up[0][v] = u;
                order.push_back(v);
            }
        }
        assert(static_cast<int>(order.size()) == n);
        for (int k = 1; k < levels; ++k)
            for (int v = 0; v < n; ++v)
                up[k][v] = up[k - 1][up[k - 1][v]];
        ready = true;
    }

    // 第 k 个祖先；k == 0 返回自身，越过根返回 -1。
    int jump(int v, int k) const
    {
        assert(ready && 0 <= v && v < n && k >= 0);
        if (k > depth[v]) return -1;
        for (int bit = 0; bit < levels; ++bit)
            if ((k >> bit) & 1) v = up[bit][v];
        return v;
    }

    int query(int u, int v) const
    {
        assert(ready && 0 <= u && u < n && 0 <= v && v < n);
        if (depth[u] < depth[v]) std::swap(u, v);
        u = jump(u, depth[u] - depth[v]);
        if (u == v) return u;
        for (int k = levels - 1; k >= 0; --k)
            if (up[k][u] != up[k][v]) { u = up[k][u]; v = up[k][v]; }
        return up[0][u];
    }

    int distance(int u, int v) const
    {
        int ancestor = query(u, v);
        return depth[u] + depth[v] - 2 * depth[ancestor];
    }
};
