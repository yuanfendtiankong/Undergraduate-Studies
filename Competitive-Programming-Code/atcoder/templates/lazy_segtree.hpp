#pragma once
#include <bits/stdc++.h>

// 专用懒标记线段树：区间加 + 区间和。所有数值及中间结果必须能放进 long long。
class RangeAddSum
{
    int n;
    std::vector<long long> tree, lazy;

    void pull(int p) { tree[p] = tree[p * 2] + tree[p * 2 + 1]; }

    void apply(int p, int l, int r, long long delta)
    {
        tree[p] += delta * (r - l);
        lazy[p] += delta;
    }

    void push(int p, int l, int r)
    {
        if (lazy[p] == 0 || r - l == 1) return;
        int mid = l + (r - l) / 2;
        apply(p * 2, l, mid, lazy[p]);
        apply(p * 2 + 1, mid, r, lazy[p]);
        lazy[p] = 0;
    }

    void build(int p, int l, int r, const std::vector<long long>& a)
    {
        if (r - l == 1) { tree[p] = a[l]; return; }
        int mid = l + (r - l) / 2;
        build(p * 2, l, mid, a);
        build(p * 2 + 1, mid, r, a);
        pull(p);
    }

    void add_impl(int p, int l, int r, int ql, int qr, long long delta)
    {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) { apply(p, l, r, delta); return; }
        push(p, l, r);
        int mid = l + (r - l) / 2;
        add_impl(p * 2, l, mid, ql, qr, delta);
        add_impl(p * 2 + 1, mid, r, ql, qr, delta);
        pull(p);
    }

    long long sum_impl(int p, int l, int r, int ql, int qr)
    {
        if (qr <= l || r <= ql) return 0;
        if (ql <= l && r <= qr) return tree[p];
        push(p, l, r);
        int mid = l + (r - l) / 2;
        return sum_impl(p * 2, l, mid, ql, qr)
             + sum_impl(p * 2 + 1, mid, r, ql, qr);
    }

public:
    explicit RangeAddSum(int count)
        : n(count), tree(4 * std::max(1, n), 0), lazy(tree.size(), 0)
    {
        assert(n >= 0);
    }

    explicit RangeAddSum(const std::vector<long long>& a)
        : RangeAddSum(static_cast<int>(a.size()))
    {
        if (n > 0) build(1, 0, n, a);
    }

    void add(int l, int r, long long delta)
    {
        assert(0 <= l && l <= r && r <= n);
        if (l < r) add_impl(1, 0, n, l, r, delta);
    }

    long long sum(int l, int r)
    {
        assert(0 <= l && l <= r && r <= n);
        return l == r ? 0 : sum_impl(1, 0, n, l, r);
    }
};
