#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e5 + 10;
int n, h, w;
int a[10], b[10];
int g[10][10];
bool st[10];
void dfs(int x, int y)
{
    if (x == h)
    {
        cout << "Yes" << endl;
        exit(0);
    }
    if (y == w)
    {
        dfs(x + 1, 0);
    }
    if (g[x][y])
    {
        dfs(x, y + 1);
    }

    for (int i = 0; i < n; i++)
    {
        if (!st[i])
        {
            st[i] = true;
            for (int j = 0; j < 2; j++)
            {
                if (x + a[i] <= h && y + b[i] <= w)
                {
                    int ok = 1;
                    for (int u = 0; u < a[i]; u++)
                        for (int v = 0; v < b[i]; v++)
                            if (g[x + u][y + v])
                                ok = 0;

                    if (ok)
                    {
                        for (int u = 0; u < a[i]; u++)
                            for (int v = 0; v < b[i]; v++)
                                g[x + u][y + v] = 1;

                        dfs(x, y + 1);

                        for (int u = 0; u < a[i]; u++)
                            for (int v = 0; v < b[i]; v++)
                                g[x + u][y + v] = 0;
                    }
                }
                swap(a[i], b[i]);
            }
            st[i] = false;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> h >> w;
    for (int i = 0; i < n; i++)
        cin >> a[i] >> b[i];

    dfs(0, 0);

    cout << "No" << endl;

    return 0;
}
