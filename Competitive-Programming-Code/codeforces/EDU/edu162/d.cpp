#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
const ll N = 1e5 + 10, INF = 1e18;
void solve()
{
    ll n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i += 1)
        cin >> a[i];

    vector<ll> l(n), r(n), lf(n), rf(n);
    // r前缀和，lf第一个不与左边相等的数的位置
    for (int i = 0; i < n; i += 1)
    {
        r[i] = (i == 0 ? 0 : r[i - 1]) + a[i];
        if (i == 0)
            lf[i] = -1;
        else
            lf[i] = (a[i] == a[i - 1] ? lf[i - 1] : i - 1);
    }

    // l后缀和，rf第一个不与右边相等的数的位置
    for (int i = n - 1; i >= 0; i -= 1)
    {
        l[i] = (i == n - 1 ? 0 : l[i + 1]) + a[i];
        if (i == n - 1)
            rf[i] = n;
        else
            rf[i] = (a[i] == a[i + 1] ? rf[i + 1] : i + 1);
    }

    vector<ll> ans(n, -1);
    for (int i = 0; i < n; i += 1)
    {
        if ((i != 0 && a[i] < a[i - 1]) || (i != n - 1 && a[i] < a[i + 1])) // 直接被吃
        {
            ans[i] = 1;
            continue;
        }

        ll fa = (i == 0 ? -1 : lf[i - 1]);
        auto it = upper_bound(l.rbegin() + (n - 1) - fa, l.rend(), l[i] + a[i]);
        if (it != l.rend())
        {
            if (ans[i] == -1)
            {
                ans[i] = i - ((n - 1) - (it - l.rbegin()));
            }
        }
        fa = (i == n - 1 ? n : rf[i + 1]);
        auto it2 = upper_bound(r.begin() + fa, r.end(), r[i] + a[i]);
        if (it2 != r.end())
        {
            if (ans[i] == -1)
            {
                ans[i] = it2 - r.begin() - i;
            }
            else
                ans[i] = min(ans[i], ll(it2 - r.begin() - i));
        }
    }
    for (int i = 0; i < n; i += 1)
    {
        cout << ans[i] << ' ';
    }
    cout << endl;
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