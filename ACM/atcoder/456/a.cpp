#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int, int>
const int N = 1e5 + 10;
void solve()
{
    int x;
    cin >> x;
    for (int i = 1; i < 3; i++)
    {
        for (int j = 1; j <= 6; j++)
        {
            for (int k = 1; k <= 6; k++)
            {
                for (int m = 1; m <= 6; m++)
                {
                    if (k + j + m == x)
                    {
                        cout << "Yes" << endl;
                        return;
                    }
                }
            }
        }
    }
    cout << "No" << endl;
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