#include <bits/stdc++.h>

using namespace std;
#define ll long long
const int N = 1e4 + 5;

// O(n^2) solution
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, S, L, ans = 1;
    cin >> n >> S >> L;
    vector<ll> a(n + 1), qa(n + 1, 0);

    for (int i = 2; i <= n; i++)
    {
        cin >> a[i];
        qa[i] = qa[i - 1] + a[i];
    }

    for (ll i = 1; i <= S; i++)
    {
        for (ll j = S; j <= n; j++)
        {
            ll x = qa[S] - qa[i];
            ll y = qa[j] - qa[S];
            ll sum = x + y + min(x, y);
            if (sum <= L)
                ans = max(ans, j - i + 1);
        }
    }
    cout << ans << endl;

    return 0;
}
