#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;
const int N = 1e2 + 10, M = 170;
const double eps = 1e-8;
int n, m;
char g[N][N];
pii p[M];
double hash_val[32];
int top, cnt;
void bfs(int a, int b)
{
    queue<pii> q;
    q.push({a, b});
    p[top++] = {a, b};
    g[a][b] = '0';

    while (q.size())
    {
        auto t = q.front();
        q.pop();

        for (int i = t.first - 1; i <= t.first + 1; i++)
        {
            for (int j = t.second - 1; j <= t.second + 1; j++)
            {
                if (i >= 0 && i < n && j < m && j >= 0 && g[i][j] == '1')
                {
                    g[a][b] = '0';
                    q.push({i, j});
                    p[top++] = {i, j};
                }
            }
        }
    }
}
double get_dis(pii &a, pii &b)
{
    double x = a.first - b.first, y = a.second - b.second;
    return sqrt(x * x + y * y);
}
double get_hash()
{
    double sum = 0;
    for (int i = 0; i < top; i++)
    {
        for (int j = 0; j < i; j++)
        {
            sum += get_dis(p[i], p[j]);
        }
    }

    return sum;
}
char get_id()
{
    double val = get_hash();
    for (int i = 0; i < cnt; i++)
    {
        if (abs(hash_val[i] - val) < eps)
            return 'a' + i;
    }

    hash_val[cnt++] = val;
    return 'a' + cnt - 1;
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    cin >> m >> n;

    for (int i = 0; i < n; i++)
        cin >> g[i];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (g[i][j] == '1')
            {
                top = 0;
                bfs(i, j);
                char id = get_id();
                for (int k = 0; k < top; k++)
                {
                    g[p[k].first][p[k].second] = id;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
        cout << g[i] << endl;

    return 0;
}