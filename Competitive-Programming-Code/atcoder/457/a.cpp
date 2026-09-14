#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
#define ll long long
#define pii pair<int, int>
const int N = 1e5 + 10;
int a[N];
void solve()
{
    int n, x;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    cin >> x;
    cout << a[x] << endl;
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