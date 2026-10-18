#include <bits/stdc++.h>

using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, w;
    cin >> n >> w;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i] >> b[i];

    ll ans = 0;
    for (int i = 0; i < 1 << n; i++)
    {
        ll val = 0, v = 0;
        for (int j = 0; j < n; j++)
            if (i >> j & 1)
            {
                val += a[j];
                v += b[j];
            }
        if (v <= w)
            ans = max(ans, val);
    }
    cout << ans << endl;
    return 0;
}