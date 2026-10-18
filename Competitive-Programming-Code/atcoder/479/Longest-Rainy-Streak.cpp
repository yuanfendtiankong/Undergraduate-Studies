#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, ans = 0;
    cin >> n;
    string str;
    cin >> str;
    for (int i = 0; i < n; i++)
    {
        if (str[i] == 'R')
        {
            int st = i;
            while (i < n && str[i] == 'R')
                i++;
            ans = max(ans, i - st);
        }
    }
    cout << ans << endl;

    return 0;
}