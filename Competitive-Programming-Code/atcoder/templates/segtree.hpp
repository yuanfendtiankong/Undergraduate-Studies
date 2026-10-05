#pragma once
#include <bits/stdc++.h>

// 单点赋值 + 区间合并。op 必须满足结合律，e() 必须是单位元。
// op 不必满足交换律；查询会保留元素顺序。
template <class S, S (*op)(S, S), S (*e)()>
class SegTree
{
    int n, base;
    std::vector<S> tree;

public:
    explicit SegTree(int count) : n(count), base(1)
    {
        assert(n >= 0);
        while (base < n) base *= 2;
        tree.assign(base * 2, e());
    }

    explicit SegTree(const std::vector<S>& a) : SegTree(static_cast<int>(a.size()))
    {
        for (int i = 0; i < n; ++i) tree[base + i] = a[i];
        for (int p = base - 1; p >= 1; --p)
            tree[p] = op(tree[p * 2], tree[p * 2 + 1]);
    }

    void set(int p, S value)
    {
        assert(0 <= p && p < n);
        p += base;
        tree[p] = value;
        while (p > 1)
        {
            p /= 2;
            tree[p] = op(tree[p * 2], tree[p * 2 + 1]);
        }
    }

    S get(int p) const
    {
        assert(0 <= p && p < n);
        return tree[base + p];
    }

    S prod(int l, int r) const
    {
        assert(0 <= l && l <= r && r <= n);
        S left = e(), right = e();
        for (l += base, r += base; l < r; l /= 2, r /= 2)
        {
            if (l & 1) left = op(left, tree[l++]);
            if (r & 1) right = op(tree[--r], right);
        }
        return op(left, right);
    }

    S all_prod() const { return tree[1]; }
};
