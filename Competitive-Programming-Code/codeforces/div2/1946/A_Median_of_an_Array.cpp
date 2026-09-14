#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
#define endl '\n'
void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 2, 0);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    sort(a.begin() + 1, a.end() - 1);

    int ans = 1, mid = (n + 1) / 2;
    // cout << mid << endl;
    // cout << a[mid] << endl;
    for (int i = mid; i <= n; i++)
    {
        if (a[mid] == a[i + 1])
        {
            ans++;
            //cout << i << endl;
        }
    }
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}