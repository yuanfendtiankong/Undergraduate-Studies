#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
void solve()
{
    int n;
    cin >> n;
    vector<int> arr(n + 10);
    int t = 1e9 + 10;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        t = min(t, arr[i]);
    }

    int l = 1;
    while (arr[l % n + 1] - l > 0)
        l++;
    cout << l % n + 1 << endl;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin>>t;
    while (t--)
    {
        solve();
    }
    return 0;
}
