#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int, int>
const ll N = 1e5 + 10, mod = 998244353;
void solve()
{
    string str;
    cin >> str;
    ll n = str.size();

    vector<ll> st;
    ll ans = n;
    for (int i = 0; i < n; i++)
    {
        int j = i;
        while (j < n - 1 && str[j] != str[j + 1])
            j++;
        // printf("i:%d  j:%d\n", i, j);
        st.push_back(j - i + 1);
        i = j;
    }
    for (auto x : st)
        ans = (ans + x * (x - 1) / 2 % mod) % mod;
    cout << ans << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int _ = 1;
    // cin >> _;
    while (_--)
    {
        solve();
    }

    return 0;
}