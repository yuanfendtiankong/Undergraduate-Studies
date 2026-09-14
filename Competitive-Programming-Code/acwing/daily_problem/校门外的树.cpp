#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
typedef pair<int, int> pii;
void merge(vector<pii> &segs)
{
    vector<pii> res;
    sort(segs.begin(), segs.end());

    int st = -2e9, ed = -2e9;
    for (auto seg : segs)
    {
        if (ed < seg.first)
        {
            if (st != -2e9)
                res.push_back({st, ed});
            st = seg.first, ed = seg.second;
        }
        else
            ed = max(ed, seg.second);
    }

    if (st != -2e9)
        res.push_back({st, ed});

    segs = res;
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    int l, m;
    cin >> l >> m;
    vector<pii> segs;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        segs.push_back({a, b});
    }
    merge(segs);

    int sum = 0;
    for (int i = 0; i < segs.size(); i++)
    {
        sum += (segs[i].second - segs[i].first + 1);
    }
    cout << l - sum + 1 << endl;

    return 0;
}