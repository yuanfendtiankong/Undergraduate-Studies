#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 10;
struct Node
{
    pair<int, int> mn;
    pair<int, int> mx;
};
Node tr[N * 4];
int p[N];
void pushup(int u)
{
    int lc = u * 2;
    int rc = u * 2 + 1;

    tr[u].mn = min(tr[lc].mn, tr[rc].mn);
    tr[u].mx = max(tr[lc].mx, tr[rc].mx);
}

void build(int u, int l, int r)
{
    if (l == r)
    {
        tr[u].mn = {p[l], l};
        tr[u].mx = {p[l], l};
        return;
    }

    int mid = (l + r) / 2;

    build(u * 2, l, mid);
    build(u * 2 + 1, mid + 1, r);

    pushup(u);
}
Node query(int u, int l, int r, int L, int R)
{

    int mid = (l + r) / 2;
    if (L <= l && r <= R)
        return tr[u];
    else if (R <= mid)
        return query(u * 2, l, mid, L, R);
    else if (L > mid)
        return query(u * 2 + 1, mid + 1, r, L, R);
    else
    {
        Node left = query(u * 2, l, mid, L, R);
        Node right = query(u * 2 + 1, mid + 1, r, L, R);

        Node res;
        res.mn = min(left.mn, right.mn);
        res.mx = max(left.mx, right.mx);
        return res;
    }
}
void update(int u, int l, int r, int pos, int value)
{
    int mid = (l + r) / 2;
    if (l == r)
    {
        tr[u].mn = {value, pos};
        tr[u].mx = {value, pos};
        return;
    }

    if (pos <= mid)
        update(u * 2, l, mid, pos, value);
    else
        update(u * 2 + 1, mid + 1, r, pos, value);

    pushup(u);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> p[i];

    build(1, 1, n);

    for (int i = 1; i <= m; i++)
    {
        int L, R;
        cin >> L >> R;

        Node res = query(1, 1, n, L, R);

        int mnpos = res.mn.second;
        int mxpos = res.mx.second;

        swap(p[mnpos], p[mxpos]);

        update(1, 1, n, mnpos, p[mnpos]);
        update(1, 1, n, mxpos, p[mxpos]);
    }

    for (int i = 1; i <= n; i++)
        cout << p[i] << " ";

    return 0;
}