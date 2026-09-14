#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
const int N = 1e5 + 10;
typedef long long ll;
typedef pair<int, int> pii;

void solve()
{
    int n, l = 1e9, r = -1;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        if (a[i] == 1)
        {
            l = min(l, i);
            r = max(r, i);
        }
    }

    int ans = 0;
    for (int i = l; i <= r; i++)
    {
        if (a[i] == 0)
            ans++;
    }
    cout << ans << endl;
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