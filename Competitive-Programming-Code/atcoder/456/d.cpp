#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int, int>
const int N = 1e5 + 10;
void solve()
{
    string str;
    cin >> str;
    vector<ll> cnt(3, 0);
    for (auto x : str)
        cnt[x - 'a']++;
    
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