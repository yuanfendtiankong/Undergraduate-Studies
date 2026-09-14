#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
#define endl "\n"
const int N = 1e5 + 10;
typedef pair<int, int> pii;
ll n, k;
ll a[N], b[N];
bool check(ll mid)
{
    ll sub = k;
    for (int i = 0; i < n; i++)
    {
        if (b[i] >= a[i] * mid)
            continue;
        if (b[i] + sub < a[i] * mid)
            return false;
        if (sub >= a[i] * mid - b[i])
            sub -= (a[i] * mid - b[i]);
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];

    ll l = 0, r = 1e10 + 10;
    while (l < r)
    {
        ll mid = (l + r + 1) >> 1;
        if (check(mid))
            l = mid;
        else
            r = mid - 1;
    }
    cout << r << endl;

    return 0;
}