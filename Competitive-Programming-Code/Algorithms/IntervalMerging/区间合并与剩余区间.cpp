#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

void merge(vector<pii> &segs)
{
    vector<pii> ans;
    sort(segs.begin(), segs.end());

    int st = -2e9, ed = -2e9;
    for (auto seg : segs)
    {
        if (ed < seg.first)
        {
            if (st != -2e9)
                ans.push_back({st, ed});
            st = seg.first, ed = seg.second;
        }
        else
        {
            ed = max(ed, seg.second);
        }
    }

    if (st != -2e9)
        ans.push_back({st, ed});

    segs = ans;
}

vector<pii> remain(vector<pii> segs, int t)
{
    merge(segs);
    vector<pii> res;
    int pos = 0;

    for (auto seg : segs)
    {
        if (seg.first >= t)
            break;
        if (seg.first > pos)
            res.push_back({pos, seg.first});
        if (seg.second >= t)
        {
            pos = t;
            break;
        }
        pos = max(pos, seg.second);
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
