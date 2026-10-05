#pragma once
#include <bits/stdc++.h>

class Graph
{
    int n;
    std::vector<std::vector<int>> adj;

public:
    explicit Graph(int count) : n(count), adj(n) { assert(n >= 0); }

    // 默认无向边；有向边必须显式传 true。
    void add_edge(int u, int v, bool directed = false)
    {
        assert(0 <= u && u < n && 0 <= v && v < n);
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    // 无权最短路；不可达为 -1。
    std::vector<int> bfs(int source) const
    {
        assert(0 <= source && source < n);
        std::vector<int> dist(n, -1);
        std::queue<int> q;
        dist[source] = 0;
        q.push(source);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : adj[u])
            {
                if (dist[v] != -1) continue;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        return dist;
    }

    // 用于有向图；返回长度不足 n 表示存在环。空图返回空序列，仍然是 DAG。
    std::vector<int> topological_sort() const
    {
        std::vector<int> indegree(n, 0), order;
        for (const auto& next : adj)
            for (int v : next) ++indegree[v];
        std::queue<int> q;
        for (int u = 0; u < n; ++u)
            if (indegree[u] == 0) q.push(u);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (int v : adj[u])
                if (--indegree[v] == 0) q.push(v);
        }
        return order;
    }
};

// 非负边权最短路；有用的最短距离必须严格小于 INF。
class Dijkstra
{
    int n;
    std::vector<std::vector<std::pair<int, long long>>> adj;

public:
    static constexpr long long INF = std::numeric_limits<long long>::max() / 4;
    explicit Dijkstra(int count) : n(count), adj(n) { assert(n >= 0); }

    void add_edge(int u, int v, long long weight, bool directed = false)
    {
        assert(0 <= u && u < n && 0 <= v && v < n);
        assert(0 <= weight && weight < INF);
        adj[u].push_back({v, weight});
        if (!directed) adj[v].push_back({u, weight});
    }

    std::vector<long long> run(int source) const
    {
        assert(0 <= source && source < n);
        using State = std::pair<long long, int>; // {距离, 点编号}
        std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
        std::vector<long long> dist(n, INF);
        dist[source] = 0;
        pq.push({0, source});
        while (!pq.empty())
        {
            auto [distance, u] = pq.top();
            pq.pop();
            if (distance != dist[u]) continue; // 跳过过期状态。
            for (auto [v, weight] : adj[u])
            {
                if (distance > INF - weight) continue;
                long long next = distance + weight;
                if (next >= dist[v]) continue;
                dist[v] = next;
                pq.push({next, v});
            }
        }
        return dist;
    }
};
