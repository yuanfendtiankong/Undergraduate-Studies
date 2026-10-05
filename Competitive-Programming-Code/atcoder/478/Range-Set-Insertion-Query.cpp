#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> ans(n + 1, 0);
    map<int, vector<pair<int, int>>> cnt;
    for (int i = 0; i < q; i++)
    {
        int l, r, x;
        cin >> l >> r >> x;
        cnt[x].push_back({l, r});
    }

    for (auto [a, b] : cnt)
    {
        sort(b.begin(), b.end());
        vector<pair<int, int>> tmp;
        for (auto c : b)
        {
            if (tmp.empty() || c.first > tmp.back().second)
                tmp.push_back({c.first, c.second});
            else
                tmp.back().second = max(tmp.back().second, c.second);
        }

        for (int i = 0; i < tmp.size(); i++)
        {
            ans[tmp[i].first]++;
            if (tmp[i].second + 1 <= n)
                ans[tmp[i].second + 1]--;
        }
    }

    for (int i = 1; i <= n; i++)
        ans[i] += ans[i - 1];
    for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";

    return 0;
}