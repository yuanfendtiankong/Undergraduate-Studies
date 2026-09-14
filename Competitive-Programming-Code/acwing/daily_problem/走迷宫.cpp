#include <bits/stdc++.h>

using namespace std;
const int N = 1e2 + 10;
typedef pair<int, int> pii;
int n, m;
int g[N][N], dis[N][N];
int dx[] = {0, -1, 0, 1}, dy[] = {-1, 0, 1, 0};
void bfs(int x, int y)
{
    queue<pii> q;
    q.push({x, y});
    dis[x][y] = 0;

    while (q.size())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int a = t.first + dx[i], b = t.second + dy[i];
            if (a < 0 || a >= n || b < 0 || b >= m)
                continue;
            if (dis[a][b] != -1 || g[a][b] == 1)
                continue;

            dis[a][b] = dis[t.first][t.second] + 1;
            q.push({a, b});
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    memset(dis, -1, sizeof dis);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> g[i][j];

    bfs(0, 0);
    cout << dis[n - 1][m - 1] << endl;

    return 0;
}