#include <bits/stdc++.h>

using namespace std;
#define ll long long
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--)
    {
        int n, ans = -1, x;
        cin >> n;
        vector<int> a(n + 1, 0);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        cin >> x;

        for (int i = 0; i < n; i++)
        {
            if (a[i] < x)
            {
                ans = a[i];
                break;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
