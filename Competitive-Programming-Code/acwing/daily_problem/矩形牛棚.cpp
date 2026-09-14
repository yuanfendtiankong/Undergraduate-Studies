#include <iostream>
#include <vector>
#include <stack>
using namespace std;
typedef long long ll;
const int N = 3e3 + 10;
int n, m, p, top;
int h[N][N], l[N], r[N], d[N][N], st[N];
int solve(int h[])
{
    h[0] = h[m + 1] = -1;
    top = 0;
    st[++top] = 0;
    for (int i = 1; i <= m; i++)
    {
        while (h[st[top]] >= h[i])
            top--;
        l[i] = st[top];
        st[++top] = i;
    }

    top = 0;
    st[++top] = m + 1;
    for (int i = m; i; i--)
    {
        while (h[st[top]] >= h[i])
            top--;
        r[i] = st[top];
        st[++top] = i;
    }

    int ans = 0;
    for (int i = 1; i <= m; i++)
        ans = max(ans, (r[i] - l[i] - 1) * (h[i]));
    return ans;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);

    cin >> n >> m >> p;

    for (int i = 0; i < p; i++)
    {
        int x, y;
        cin >> x >> y;
        d[x][y] = 1;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (!d[i][j])
                h[i][j] = h[i - 1][j] + 1;

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans = max(ans, solve(h[i]));
    }
    cout << ans << endl;

    return 0;
}
