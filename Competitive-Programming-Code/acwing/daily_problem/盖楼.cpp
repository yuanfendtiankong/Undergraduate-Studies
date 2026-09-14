#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll n, m, x, y;
ll gcd(ll a, ll b) // 欧几里得算法
{
    return b ? gcd(b, a % b) : a;
}
bool check(ll mid)
{
    ll a = mid / x;
    ll b = mid / y;
    ll c = mid / (x * y / gcd(x, y));

    int f1 = 0, f2 = 0, sa = n, sb = m;
    if (b - c >= n)
        f1 = 1, sa = 0;
    else
        sa -= (b - c);
    if (a - c >= m)
        f2 = 1, sb = 0;
    else
        sb -= (a - c);

    if (f1 && f2)
        return true;
    else if (mid - a - b + c >= sa + sb)
        return true;
    else
        return false;
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> x >> y;

    ll l = 0, r = 1e18;
    while (l < r)
    {
        ll mid = l + r >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    cout << l << endl;

    return 0;
}