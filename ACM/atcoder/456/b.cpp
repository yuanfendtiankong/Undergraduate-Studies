#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int, int>
const int N = 1e5 + 10;
int a[3][6];
void solve()
{
    vector<tuple<int, int, int>> ans;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 6; j++)
            cin >> a[i][j];

    for (int j = 0; j < 6; j++)
    {
        tuple<int, int, int> tmp;
        for (int k = 0; k < 6; k++)
            for (int m = 0; m < 6; m++)
            {
                tmp = {a[0][j], a[1][k], a[2][m]};
                ans.push_back(tmp);
            }
    }

    int res = 0;
    for (auto x : ans)
    {
        // cout << get<0>(x) << " " << get<1>(x) << " " << get<2>(x) << endl;
        if (get<0>(x) * get<1>(x) * get<2>(x) == 120)
            res++;
    }
    // cout << res << endl;
    cout << 1.0 * res / 216 << endl;
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