#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
int n, m;
ll R[N], d[N], s[N], t[N], q[N];
bool check(int mid)
{
    memset(q, 0, sizeof q);
    for (int i = 1; i <= mid; i++)
    {
        q[s[i]] += d[i];
        q[t[i] + 1] -= d[i];
    }

    ll sum = 0;
    for (int i = 1; i <= n; i++)
    {
        sum += q[i];
        if (sum > R[i])
            return false;
    }
    return true;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> R[i];
    for (int i = 1; i <= m; i++)
        cin >> d[i] >> s[i] >> t[i];

    int l = 0, r = m;
    while (l < r)
    {
        int mid = l + r + 1 >> 1;
        if (check(mid))
            l = mid;
        else
            r = mid - 1;
    }
    if (r == m)
        cout << 0 << endl;
    else
    {
        cout << -1 << endl;
        cout << r + 1 << endl;
    }

    return 0;
}