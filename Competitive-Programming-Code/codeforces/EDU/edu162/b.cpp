#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
const int N = 1e5 + 10;
typedef long long ll;
typedef pair<int, int> pii;

void solve()
{
    int n, k;
    cin >> n >> k;
    vector<ll> a(n), b(n), c(n + 1);

    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0, x; i < n; i++)
        cin >> b[i];
    for (int i = 0; i < n; i++)
        c[abs(b[i])] += a[i];

    ll le = 0;
    for (int i = 1; i <= n; i++)
    {
        le += k;
        if (le < c[i])
        {
            cout << "No" << endl;
            return;
        }
        le -= c[i];
    }
    cout << "Yes" << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int _ = 0;
    cin >> _;
    while (_--)
    {
        solve();
    }

    return 0;
}