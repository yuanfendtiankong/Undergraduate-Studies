#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define endl '\n'
void solve()
{
    ll n;
    cin >> n;
    ll sub = 1, sum = 0;
    while (sub <= n)
    {
        sum += sub;
        sub *= 2;
    }

    cout << (1 + n) * n / 2 - 2 * sum << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}