#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int n, k;
int main()
{
    cin >> n >> k;
    vector<ll> a(n + 1, 0), q(n + 1, 0);
    map<ll, int> cnt;
    cnt[0] = 1;
    //子序列的长度为0
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        q[i] = (q[i - 1] + a[i]) % k;
        cnt[q[i]]++;
    }

    ll ans = 0;
    for (auto x : cnt)
    {
        ans += ((x.second - 1) * x.second) / 2;
    }
    cout << ans << endl;

    return 0;
}