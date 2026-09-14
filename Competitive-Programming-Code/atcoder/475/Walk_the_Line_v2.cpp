#include <bits/stdc++.h>

using namespace std;
#define ll long long
const int N = 1e4 + 5;

// O(nlogn) solution
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
        ll costL = qa[S] - qa[i];
        if (costL > L)
            continue;

        ll l = S, r = n, mid = 0, res = 1;
        while (l <= r)
        {
            mid = (l + r) / 2;
            ll costR = qa[mid] - qa[S];
            ll sum = costL + costR + min(costL, costR);
            if (sum <= L)
            {
                res = max(res, mid - i + 1);
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        ans = max(ans, res);
    }
    cout << ans << endl;

    return 0;
}
