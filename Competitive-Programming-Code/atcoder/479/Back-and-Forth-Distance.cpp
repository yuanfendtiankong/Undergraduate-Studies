#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, Q;
    cin >> n >> Q;
    vector<int> l(n + 1), r(n + 1);
    for (int i = 2; i <= n; i++)
        cin >> l[i];
    for (int j = 1; j <= n - 1; j++)
        cin >> r[j];

    vector<int> R(n + 10, 1e9 + 10), L(n + 10, 1e9 + 10);
    for (int i = 1; i < n; i++)
        R[i] = min(R[i - 1], r[i]);
    for (int i = n; i >= 2; i--)
        L[i] = min(L[i + 1], l[i]);

    for (int i = 0; i < Q; i++)
    {
        int s, t, ans;
        cin >> s >> t;
        if (s < t)
            ans = min(r[s], l[s] + R[s - 1]);
        else
            ans = min(l[s], r[s] + L[s + 1]);
        cout << ans << endl;
    }

    return 0;
}