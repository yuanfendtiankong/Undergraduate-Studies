#include <bits/stdc++.h>
#include "segtree.hpp"
using namespace std;

// 完整示例：每次把输入闭区间 [L, R] 内的最小值和最大值交换。
// 本地可 include；提交时把 segtree.hpp 的模板粘贴进来，移除该本地 include。
struct Info
{
    pair<int, int> mn, mx; // {值, 0 起始下标}；相同值用下标打破平局。
};
Info op(Info a, Info b) { return {min(a.mn, b.mn), max(a.mx, b.mx)}; }
Info e() { return {{INT_MAX, INT_MAX}, {INT_MIN, INT_MIN}}; }

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    if (!(cin >> n >> q)) return 0;
    vector<int> a(n);
    vector<Info> initial(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        initial[i] = {{a[i], i}, {a[i], i}};
    }
    SegTree<Info, op, e> seg(initial);
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        --l; // 题目的 1 起始闭区间 [L, R] 变成 [L - 1, R)。
        Info info = seg.prod(l, r);
        int u = info.mn.second, v = info.mx.second;
        swap(a[u], a[v]);
        seg.set(u, {{a[u], u}, {a[u], u}});
        seg.set(v, {{a[v], v}, {a[v], v}});
    }
    for (int i = 0; i < n; ++i) cout << a[i] << (i + 1 == n ? '\n' : ' ');
}
