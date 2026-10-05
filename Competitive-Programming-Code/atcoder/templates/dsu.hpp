#pragma once
#include <bits/stdc++.h>

// 并查集：路径压缩 + 按大小合并。
class DSU
{
    // 根处保存 -集合大小；非根处保存父节点编号。
    std::vector<int> parent_or_size;
    int components;

public:
    explicit DSU(int n) : parent_or_size(n, -1), components(n) { assert(n >= 0); }

    int leader(int x)
    {
        assert(0 <= x && x < static_cast<int>(parent_or_size.size()));
        if (parent_or_size[x] < 0) return x;
        return parent_or_size[x] = leader(parent_or_size[x]);
    }

    // 真正合并了两个集合返回 true；本来就在同一集合返回 false。
    bool merge(int a, int b)
    {
        a = leader(a);
        b = leader(b);
        if (a == b) return false;
        if (-parent_or_size[a] < -parent_or_size[b]) std::swap(a, b);
        parent_or_size[a] += parent_or_size[b];
        parent_or_size[b] = a;
        --components;
        return true;
    }

    bool same(int a, int b) { return leader(a) == leader(b); }
    int size(int x) { return -parent_or_size[leader(x)]; }
    int count() const { return components; }
};
