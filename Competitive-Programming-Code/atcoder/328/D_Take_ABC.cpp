#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
const int N = 1e5 + 10, mod = 1e9 + 7;
typedef long long ll;
typedef pair<ll, ll> pii;

void solve()
{
    string S, ans;
    cin >> S;

    for (auto x : S)
    {
        ans += x;
        if (ans.size() >= 3 && ans.substr(ans.size() - 3) == "ABC")
            ans.erase(ans.end() - 3, ans.end());
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
