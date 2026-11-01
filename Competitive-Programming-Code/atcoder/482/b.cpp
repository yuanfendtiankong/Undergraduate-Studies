#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    char mp[6][6];

    for (int i = 1; i <= 5; i++)
        for (int j = 1; j <= 5; j++)
            cin >> mp[i][j];

    int mx = 0;
    for (int i = 1; i <= 5; i++)
    {
        int cnt = 0;
        for (int j = 1; j <= 5; j++)
            if (mp[i][j] == 'o')
                cnt++;
        mx = max(mx, cnt);
    }

    for (int i = 1; i <= 5; i++)
    {
        int cnt = 0;
        for (int j = 1; j <= 5; j++)
            if (mp[j][i] == 'o')
                cnt++;
        mx = max(mx, cnt);
    }

    int cnt = 0;
    for (int i = 1; i <= 5; i++)
        if (mp[i][i] == 'o')
            cnt++;
    mx = max(mx, cnt);
    // cout << cnt << endl;

    cnt = 0;
    for (int i = 1; i <= 5; i++)
        if (mp[i][6 - i] == 'o')
            cnt++;
    mx = max(mx, cnt);

    cout << 5 - mx << endl;

    return 0;
}