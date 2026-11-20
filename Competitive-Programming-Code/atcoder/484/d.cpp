#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define endl '\n'
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n + 1, 0);
    vector<int> cnt(n + 1, 0);

    ll ans = 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];

        if (a[i] != a[i - 1])
            ans += (i - 1 - cnt[a[i]]);
        cnt[a[i]]++;
    }
    cout << ans << endl;

    return 0;
}