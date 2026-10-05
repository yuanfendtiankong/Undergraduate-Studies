#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b.begin() + 1, b.end());
    int mn = 1e8, mx = 0;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] != b[i])
        {
            mn = min(mn, i);
            mx = max(mx, i);
        }
    }
    // cout << mx << " " << mn << endl;
    int cnt = mx - mn + 1;
    if (cnt <= k)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}