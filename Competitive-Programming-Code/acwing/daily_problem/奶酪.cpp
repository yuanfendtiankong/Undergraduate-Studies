#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
const int N = 1e5 + 10, M = 1024;
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
int n, h, r;
int p[N];
struct point
{
    int x, y, z;
} q[N];
void init(int n)
{
    for (int i = 0; i <= n + 1; i++)
        p[i] = i;
}
int find(int x)
{
    if (x != p[x])
        p[x] = find(p[x]);
    return p[x];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> h >> r;

        init(n);
        for (int i = 1; i <= n; i++)
        {
            cin >> q[i].x >> q[i].y >> q[i].z;

            if (q[i].z - r <= 0)
                p[find(i)] = find(0);
            if (q[i].z + r >= h)
                p[find(i)] = find(n + 1);
        }

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j < i; j++)
            {
                ll dx = q[i].x - q[j].x;
                ll dy = q[i].y - q[j].y;
                ll dz = q[i].z - q[j].z;

                if (dx * dx + dy * dy + dz * dz <= 4 * r * r)
                    p[find(i)] = find(j);
            }
        }

        cout << (find(0) == find(n + 1) ? "Yes" : "No") << endl;
    }

    return 0;
}