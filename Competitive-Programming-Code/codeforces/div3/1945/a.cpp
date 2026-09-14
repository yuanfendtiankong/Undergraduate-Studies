#include <bits/stdc++.h>

using namespace std;
#define INF 0x3f3f3f3f
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;

void solve()
{
    ll a, b, c, ans = 0;
    cin >> a >> b >> c;
    ans += a;
    if (b % 3 == 0)
    {
        ans += b / 3;
        ans += (c == 0 ? 0 : (c - 1) / 3 + 1);
    }
    else
    {
        if (b % 3 + c < 3)
            ans = -1;
        else
            ans += (b + c - 1) / 3 + 1;
    }
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
