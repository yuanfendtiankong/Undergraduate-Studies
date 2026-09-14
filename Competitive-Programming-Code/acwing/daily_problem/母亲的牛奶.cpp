#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
const int N = 22, M = N * N * N;
typedef pair<int, int> pii;
int A, B, C;
bool st[N][N][N];

struct node
{
    int a, b, c;
};

void dfs(int a, int b, int c)
{
    int W[3] = {A, B, C};
    if (st[a][b][c])
        return;
    st[a][b][c] = true;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (i != j)
            {
                int w[3] = {a, b, c};
                int r = min(w[i], W[j] - w[j]);
                w[i] -= r, w[j] += r;
                if (!st[w[0]][w[1]][w[2]])
                {
                    dfs(w[0], w[1], w[2]);
                }
            }
}
void bfs()
{
    queue<node> q;
    q.push({0, 0, C});
    st[0][0][C] = true;

    int W[3] = {A, B, C};
    while (q.size())
    {
        auto t = q.front();
        q.pop();

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (i != j)
                {
                    int w[3] = {t.a, t.b, t.c};
                    int x = min(w[i], W[j] - w[j]);
                    w[i] -= x, w[j] += x;
                    if (!st[w[0]][w[1]][w[2]])
                    {
                        st[w[0]][w[1]][w[2]] = true;
                        q.push({w[0], w[1], w[2]});
                    }
                }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> A >> B >> C;

    // bfs();
    dfs(0, 0, C);
    for (int i = 0; i <= C; i++)
        for (int j = 0; j <= B; j++)
            if (st[0][j][i])
            {
                cout << i << " ";
                break;
            }

    return 0;
}