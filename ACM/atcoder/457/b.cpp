#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int, int>
const int N = 1e5 + 10;
void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int l;
        cin >> l;
        for (int j = 1; j <= l; j++)
        {
            int x;
            cin >> x;
            a[i].push_back(x);
        }
    }

    int x, y;
    cin >> x >> y;
    cout << a[x][y - 1] << endl;
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