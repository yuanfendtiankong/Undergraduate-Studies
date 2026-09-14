#include <bits/stdc++.h>

using namespace std;
const int N = 3e2 + 10;
typedef pair<int, int> pii;
int n, ans;
char g[N][N];
int cnt[N][N];
void dfs(int x, int y)
{
    int t = cnt[x][y];
    cnt[x][y] = -1;
    if (t)
        return;

    for (int i = x - 1; i <= x + 1; i++)
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i < 0 || i >= n || j < 0 || j >= n || cnt[i][j] == -1)
                continue;

            dfs(i, j);
        }
    }
}
int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    // cout.tie(0);

    int t;
    cin >> t;
    for (int k = 1; k <= t; k++)
    {
        ans = 0;

        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> g[i];

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (g[i][j] == '*')
                    cnt[i][j] = -1;
                else
                {
                    cnt[i][j] = 0;
                    for (int x = i - 1; x <= i + 1; x++)
                    {
                        for (int y = j - 1; y <= j + 1; y++)
                        {
                            if (x >= 0 && x < n && y >= 0 && y < n && g[x][y] == '*')
                                cnt[i][j]++;
                        }
                    }
                }
            }
        }

        // for (int i = 0; i < n; i++)
        //     for (int j = 0; j < n; j++)
        //         cout << cnt[i][j] << " \n"[j == n - 1];

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (!cnt[i][j])
                {
                    ans++;
                    dfs(i, j);
                }
            }
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (cnt[i][j] != -1)
                    ans++;

        printf("Case #%d: %d\n", k, ans);
    }

    return 0;
}