#include <bits/stdc++.h>

using namespace std;
#define ll long long
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k, t;
    cin >> n >> k >> t;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        a[i] = {x, x + k};
    }

    sort(a.begin(), a.end());
    vector<pair<int, int>> tmp;
    for (auto it : a)
    {
        if (tmp.empty() || it.first > tmp.back().second)
            tmp.push_back({it.first, it.second});
        else
            tmp.back().second = max(tmp.back().second, it.second);
    }

    vector<pair<int, int>> res;
    int pos = 0;
    for (auto it : tmp)
    {
        if (min(it.first, t) > pos)
            res.push_back({pos, min(it.first, t)});
        pos = max(pos, min(it.second, t));
    }
    if (pos < t)
        res.push_back({pos, t});

    ll ans = 0;
    for (int i = 0; i < res.size(); i++)
        ans += (res[i].second - res[i].first + k - 1) / k;

    cout << ans << endl;
    return 0;
}