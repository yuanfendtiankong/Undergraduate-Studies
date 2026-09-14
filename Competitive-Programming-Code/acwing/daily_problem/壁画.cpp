#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
const int N = 1e5 + 10;
typedef pair<int, int> pii;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int ca;
    cin >> ca;
    for (int i = 1; i <= ca; i++)
    {
        int n;
        cin >> n;
        string str;
        cin >> str;
        str = " " + str;
        vector<int> q(n + 1, 0);
        for (int i = 1; i <= n; i++)
            q[i] = q[i - 1] + (str[i] - '0');

        int ans = 0, m = (n + 1) / 2;
        for (int i = m; i <= n; i++)
        {
            ans = max(ans, q[i] - q[i - m]);
        }
        cout << "Case #" << i << ": " << ans << endl;
        // printf("Case #%d: %d\n", i, ans);
    }

    return 0;
}