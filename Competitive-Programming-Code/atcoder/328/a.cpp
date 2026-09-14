#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
const int N = 1e5 + 10, mod = 1e9 + 7;
typedef long long ll;
typedef pair<ll, ll> pii;

void solve()
{
    int n, x, sum = 0;
    cin >> n >> x;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        if (a <= x)
        {
            sum += a;
        }
    }
    cout << sum << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
