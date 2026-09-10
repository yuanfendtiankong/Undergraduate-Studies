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
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<pii> num;
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;
        num.push_back({l, r});
    }
    merge(num);

    cout << num.size() << endl;

    return 0;
}