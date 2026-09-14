#include <bits/stdc++.h>

using namespace std;
const int mod = 1e9 + 7;
typedef long long ll;
typedef pair<int, int> pii;
#define endl '\n'
ll qmi(ll a, ll b, ll k)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = (res * a) % k;
        a = (a * a) % k;
        b >>= 1;
    }
    return res;
}
void solve()
{
    int n, k;
    cin >> n >> k;
    vector<ll> a(n + 1, 0), q(n + 1, 0);
    ll maxx = 0, sum = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum = (sum + a[i]) % mod;
        q[i] = max(q[i - 1] + a[i], a[i]);
        maxx = max(maxx, q[i]);
    }
    maxx %= mod;

    ll ans = sum, tmp = 0;
    for (int i = 1; i <= k; i++)
    {
        tmp = (maxx * qmi(2, i - 1, mod)) % mod;
        ans = (ans + tmp) % mod;
    }

    cout << (ans + mod) % mod << endl;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}