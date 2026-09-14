#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
vector<int> a[N];

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        a[x].push_back(y);
    }

    int cnt = n / 10;
    ll ans = 0;
    for (int i = 0; i < 10; i++)
    {
        sort(a[i].begin(), a[i].end());
        for (int j = 0; j < a[i].size(); j++)
        {
            if (a[i].size() - j <= cnt)
                break;
            else
                ans += a[i][j];
        }
    }
    cout << ans << endl;

    return 0;
}