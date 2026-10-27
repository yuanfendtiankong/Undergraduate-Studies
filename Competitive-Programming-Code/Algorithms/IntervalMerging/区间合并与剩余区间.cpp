#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

void merge(vector<pii> &segs)
{
    sort(segs.begin(), segs.end());
    vector<pair<int, int>> tmp;
    for (auto it : segs)
    {
        if (tmp.empty() || it.first > tmp.back().second)
            tmp.push_back({it.first, it.second});
        else
            tmp.back().second = max(tmp.back().second, it.second);
    }

    segs = tmp;
}

vector<pii> remain(vector<pii> segs, int t)
{
    vector<pair<int, int>> res;
    int pos = 0;
    for (auto it : segs)
    {
        if (min(it.first, t) > pos)
            res.push_back({pos, min(it.first, t)});
        pos = max(pos, min(it.second, t));
    }
    if (pos < t)
        res.push_back({pos, t});

    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, t;
    cin >> n >> t;
    vector<pii> segs(n);
    for (int i = 0; i < n; i++)
        cin >> segs[i].first >> segs[i].second;

    vector<pii> merged = segs;
    merge(merged);
    for (auto seg : merged)
        cout << seg.first << ' ' << seg.second << '\n';

    vector<pii> res = remain(segs, t);
    for (auto seg : res)
        cout << seg.first << ' ' << seg.second << '\n';

    return 0;
}
