#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
const int N = 1e5 + 10, mod = 1e9 + 7;
typedef long long ll;
typedef pair<ll, ll> pii;

void solve()
{
    int n, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        vector<int> vi;
        int nn = i;
        while (nn)
        {
            vi.push_back(nn % 10);
            nn /= 10;
        }
        for (int j = 1; j <= a; j++)
        {
            vector<int> num;
            int now = j, f = 1;
            while (now)
            {
                num.push_back(now % 10);
                now /= 10;
            }
            for (int k = 0; k < num.size(); k++)
            {
                for (int m = 0; m < vi.size(); m++)
                {
                    if (num[k] != vi[m])
                    {
                        f = 0;
                        break;
                    }
                }
            }
            if (f)
                ans++;
        }
    }
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
