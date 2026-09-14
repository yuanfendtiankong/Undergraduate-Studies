#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
const int N = 1e5 + 10, mod = 1e9 + 7;
typedef long long ll;
typedef pair<ll, ll> pii;

void solve()
{
    int n, m, cnt = 0;
    cin >> n >> m;
    string str;
    cin >> str;
    str = " " + str;
    vector<int> pos, q(str.size() + 1, 0);
    for (int i = 1; i <= n - 1; i++)
    {
        if (str[i] == str[i + 1])
        {
            pos.push_back(i);
        }
        q[i] = pos.size();
    }
    while (m--)
    {
        int l, r;
        cin >> l >> r;
        cout << q[r - 1] - q[l - 1] << endl;
    }
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
