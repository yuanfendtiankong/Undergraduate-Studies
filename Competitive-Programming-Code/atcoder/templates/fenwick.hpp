#pragma once
#include <bits/stdc++.h>

// 树状数组：外部下标从 0 开始，内部从 1 开始。
template <class T = long long>
class Fenwick
{
    int n;
    std::vector<T> bit;

public:
    explicit Fenwick(int count) : n(count), bit(n + 1, T{}) { assert(n >= 0); }

    // O(n) 建树。
    explicit Fenwick(const std::vector<T>& a) : Fenwick(static_cast<int>(a.size()))
    {
        for (int i = 1; i <= n; ++i)
        {
            bit[i] += a[i - 1];
            int parent = i + (i & -i);
            if (parent <= n) bit[parent] += bit[i];
        }
    }

    // a[p] += delta，不是赋值。
    void add(int p, T delta)
    {
        assert(0 <= p && p < n);
        for (++p; p <= n; p += p & -p) bit[p] += delta;
    }

    // a[0] + ... + a[r - 1]。
    T prefix(int r) const
    {
        assert(0 <= r && r <= n);
        T answer{};
        for (; r > 0; r -= r & -r) answer += bit[r];
        return answer;
    }

    T sum(int l, int r) const
    {
        assert(0 <= l && l <= r && r <= n);
        return prefix(r) - prefix(l);
    }
};
