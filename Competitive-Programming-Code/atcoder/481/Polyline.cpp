#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> tmp;

    int be, x;
    cin >> be;
    for (int i = 1; i < n; i++)
    {
        cin >> x;
        tmp.push_back({be, x});
        be = x;
    }

    int ans = 0, pos = 0;
    for (auto [a, b] : tmp)
        if (a <= k && b > k || a >= k && b < k)
            ans++;
    if (tmp.back().second == k)
        ans++;
    cout << ans << endl;
    return 0;
}