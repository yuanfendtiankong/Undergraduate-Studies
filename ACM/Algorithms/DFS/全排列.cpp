#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;

int n;
bool st[20];
int path[20];
void dfs(int u)
{
    if (u > n)
    {
        for (int i = 1; i <= n; i++)
            cout << path[i] << ' ';
        cout << endl;
    }

    for (int i = 1; i <= n; i++)
    {
        if (!st[i])
        {
            path[u] = i;
            st[i] = true;
            dfs(u + 1);
            st[i] = false;
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    dfs(1);
    return 0;
}
