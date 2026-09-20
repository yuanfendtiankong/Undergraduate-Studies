#include <bits/stdc++.h>

using namespace std;
#define ll long long
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, m, k, x, y, ans = 0;
    cin >> n >> m >> k >> x >> y;

    vector<ll> a(n + 1, 0), qa(n + 1, 0);
    vector<ll> b(m + 1, 0), qb1(m + 1, 0), qb2(m + 1, 0);
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    for (ll i = 1; i <= m; i++)
        cin >> b[i];

    sort(a.begin() + 1, a.end());
    sort(b.begin() + 1, b.end());
    for (int i = 1; i <= n; i++)
        qa[i] = qa[i - 1] + a[i];
    for (int i = 1; i <= m; i++)
    {
        qb1[i] = qb1[i - 1] + b[i];
        qb2[i] = qb2[i - 1] + ((b[i] - 1) / k + 1);
    }
    for (ll i = 0; i <= m; i++)
    {
        if (y < qb2[i])
            break;
        ll ny = y - qb2[i];
        ll nx = qb2[i] * k - qb1[i] + x;
        ll nsum = ny * k + nx;

        ll ans2 = i, ans1 = 0;

        auto pos = upper_bound(qa.begin(), qa.end(), nsum);
        ans1 = pos - qa.begin() - 1;
        ans = max(ans, ans1 + ans2);
    }

    cout << ans << endl;

    return 0;
}