#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
const int N = 1e5 + 10, M = 1024;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
int n, f;
char g[M][M];
bool st[M][M];
int dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0};
int dfs(int x, int y)
{
    if (g[x - 1][y] == '#' && g[x][y - 1] == '#' && g[x + 1][y] == '#' && g[x][y + 1] == '#')
    {
        f = 1;
        // cout << x << " " << y << endl;
    }

    for (int i = 0; i < 4; i++)
    {
        int a = x + dx[i], b = y + dy[i];
        if (a < 0 || a >= n || b < 0 || b >= n || st[a][b])
            continue;
        if (g[a][b] == '.')
            continue;

        st[a][b] = true;
        dfs(a, b);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> g[i];

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (g[i][j] == '#' && !st[i][j])
            {
                st[i][j] = true;
                f = 0;
                dfs(i, j);
                if (f == 0)
                    ans++;
            }
        }
    }

    cout << ans << endl;
    return 0;
}