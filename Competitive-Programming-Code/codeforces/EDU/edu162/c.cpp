#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
const int N = 1e5 + 10;
typedef long long ll;
typedef pair<int, int> pii;

void solve()
{
    int n, Q;
    cin >> n >> Q;
    vector<ll> c(n + 1, 0), q(n + 10, 0), cnt(n + 10, 0);
    for (int i = 0; i < n; i++)
    {
        cin >> c[i];
        q[i + 1] = q[i] + c[i];
        cnt[i + 1] = cnt[i] + (c[i] == 1 ? 1 : 0);
    }
    while (Q--)
    {
        int l, r;
        cin >> l >> r;
        l--;
        ll a = q[r] - q[l];
        ll b = cnt[r] - cnt[l];
        if (r - l <= a - b && r - l > 1)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
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