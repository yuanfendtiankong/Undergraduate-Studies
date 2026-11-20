#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, flag = 0, ans = 1024;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (x == 9)
            flag = 1;
        ans = min(ans, x);
    }
    if (!flag)
        cout << -1 << endl;
    else
        cout << ans << endl;
    return 0;
}