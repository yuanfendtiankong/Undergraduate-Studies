#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
void solve()
{
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    sort(a.begin(), a.end());

    long long res = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] >= r)
            break;
        lpos = lower_bound(a.begin(), a.begin() + i, l - a[i]) - a.begin();
        rpos = upper_bound(a.begin(), a.begin() + i, r - a[i]) - a.begin();
        res += (rpos - lpos);
    }
    cout << res << endl;
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    int t = 0;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}