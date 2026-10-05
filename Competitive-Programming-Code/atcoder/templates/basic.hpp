#pragma once
#include <bits/stdc++.h>

// 以下数组下标从 0 开始，区间统一为 [l, r)。
template <class T = long long>
class PrefixSum
{
    std::vector<T> pre;

public:
    explicit PrefixSum(const std::vector<T>& a) : pre(a.size() + 1, T{})
    {
        for (int i = 0; i < static_cast<int>(a.size()); ++i)
            pre[i + 1] = pre[i] + a[i];
    }

    T sum(int l, int r) const
    {
        assert(0 <= l && l <= r && r < static_cast<int>(pre.size()));
        return pre[r] - pre[l];
    }
};

template <class T = long long>
class PrefixSum2D
{
    int h, w;
    std::vector<std::vector<T>> pre;

public:
    explicit PrefixSum2D(const std::vector<std::vector<T>>& a)
        : h(static_cast<int>(a.size())),
          w(h == 0 ? 0 : static_cast<int>(a[0].size())),
          pre(h + 1, std::vector<T>(w + 1, T{}))
    {
        for (int i = 0; i < h; ++i)
        {
            assert(static_cast<int>(a[i].size()) == w);
            for (int j = 0; j < w; ++j)
                pre[i + 1][j + 1] = pre[i][j + 1] + pre[i + 1][j]
                                    - pre[i][j] + a[i][j];
        }
    }

    // 行 [r1, r2)，列 [c1, c2)。
    T sum(int r1, int c1, int r2, int c2) const
    {
        assert(0 <= r1 && r1 <= r2 && r2 <= h);
        assert(0 <= c1 && c1 <= c2 && c2 <= w);
        return pre[r2][c2] - pre[r1][c2] - pre[r2][c1] + pre[r1][c1];
    }
};

// 先批量区间加，最后一次性还原；初始数组全为 0。
template <class T = long long>
class Difference
{
    std::vector<T> diff;

public:
    explicit Difference(int n) : diff(n + 1, T{}) { assert(n >= 0); }

    void add(int l, int r, T delta)
    {
        assert(0 <= l && l <= r && r < static_cast<int>(diff.size()));
        diff[l] += delta;
        diff[r] -= delta;
    }

    std::vector<T> values() const
    {
        std::vector<T> a(diff.size() - 1);
        T current{};
        for (int i = 0; i < static_cast<int>(a.size()); ++i)
            a[i] = (current += diff[i]);
        return a;
    }
};

template <class T>
class Compressor
{
    std::vector<T> xs;

public:
    explicit Compressor(std::vector<T> a) : xs(std::move(a))
    {
        std::sort(xs.begin(), xs.end());
        xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    }

    int size() const { return static_cast<int>(xs.size()); }

    // 小于 x 的不同值数量；x 不必出现过。
    int lower_bound(const T& x) const
    {
        return static_cast<int>(std::lower_bound(xs.begin(), xs.end(), x) - xs.begin());
    }

    // x 必须在构造时传入的数组中出现过。
    int index(const T& x) const
    {
        int p = lower_bound(x);
        assert(p < size() && xs[p] == x);
        return p;
    }

    T value(int p) const
    {
        assert(0 <= p && p < size());
        return xs[p];
    }
};

// 在非负整数区间 [l, r) 找第一个使 check(x) 为真的 x，无解返回原来的 r。
// check 必须先 false 后 true；不会调用 check(r)。
template <class Predicate>
long long first_true(long long l, long long r, Predicate check)
{
    assert(0 <= l && l <= r);
    while (l < r)
    {
        long long mid = l + (r - l) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}
