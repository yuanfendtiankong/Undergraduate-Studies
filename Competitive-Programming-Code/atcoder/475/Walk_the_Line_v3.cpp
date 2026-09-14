#include <bits/stdc++.h>

using namespace std;
#define ll long long
const int N = 1e4 + 5;

// O(n) solution
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, S, L, ans = 1;
    cin >> n >> S >> L;
    vector<ll> a(n + 1), qa(n + 2, 0);

    for (int i = 2; i <= n; i++)
    {
        cin >> a[i];
        qa[i] = qa[i - 1] + a[i];
    }

    ll j = S;
    for (ll i = 1; i <= S; i++)
    {
        ll costL = qa[S] - qa[i];
        ll costR = qa[j] - qa[S];
        ll sum = costL + costR + min(costL, costR);
        if (sum > L)
            continue;

        while (j <= n && costL + qa[j] - qa[S] + min(costL, qa[j] - qa[S]) <= L)
            j++;
        ans = max(ans, j - i);
    }
    cout << ans << endl;

    return 0;
}
