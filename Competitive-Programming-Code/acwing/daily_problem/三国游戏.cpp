#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
int n;
ll a[N], b[N], c[N], d[N];
ll solve(ll x[], ll y[], ll z[])
{
    vector<ll> q(n + 1, 0);
    for (int i = 1; i <= n; i++)
        q[i] = z[i] - y[i] - x[i];
    sort(q.begin() + 1, q.end(), greater<ll>());

    if (q[1] < 0)
        return -1;
    ll sum = 0, ans = 0;
    for (ll i = 1; i <= n; i++)
    {
        sum += q[i];
        if (sum > 0)
            ans = max(ans, i);
    }

    return ans;
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = 1; i <= n; i++)
        cin >> c[i];

    ll ans = max(solve(a, b, c), max(solve(a, c, b), solve(b, c, a)));
    cout << ans << endl;
    return 0;
}