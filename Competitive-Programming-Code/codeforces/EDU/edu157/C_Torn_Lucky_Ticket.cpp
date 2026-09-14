#include <bits/stdc++.h>

using namespace std;
#define int long long
typedef pair<int, int> pii;
const int N = 2e5 + 10;

int n, ans;
int mp[6][60];
string s[N];
void solve()
{

    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> s[i];
    sort(s + 1, s + n + 1, [&](string a, string b)
         { return a.size() < b.size(); });

    for (int i = 1; i <= n; i++)
    {
        int sum = 0;
        int m = s[i].size();
        for (auto x : s[i])
            sum += (x - '0');

        int res = 0;
        for (int j = 0, l = 1; j < s[i].size(); j++, l++)
        {
            res += (s[i][j] - '0');
            for (int len = 1; len <= 5; len++)
                if (l + len == m - l)
                    ans += mp[len][sum - res * 2];
        }

        res = 0;
        for (int j = m - 1, l = 1; j >= 0; j--, l++)
        {
            res += (s[i][j] - '0');
            for (int len = 1; len <= 5; len++)
                if (l + len == m - l)
                    ans += mp[len][sum - res * 2];
        }
        ans += mp[m][sum] * 2;
        ans++;

        mp[m][sum]++;
    }

    cout << ans << "\n";
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    int t;
    t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}