#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define endl '\n'
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<ll> x(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> x[i];

    for (int i = 1; i <= n; i++)
    {
        if (i == 1 || i == n)
        {
            cout << (x[n] - x[1]) / 2 << endl;
            continue;
        }

        ll L = x[i] - x[1];
        ll R = x[n] - x[i];

        ll dl = x[i] - x[i - 1];
        ll dr = x[i + 1] - x[i];

        cout << min(max(L, R + dl) / 2, max(R, L + dr) / 2) << endl;
    }

    return 0;
}