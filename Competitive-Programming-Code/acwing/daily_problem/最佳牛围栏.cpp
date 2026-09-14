#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
typedef pair<int, int> pii;
int n, f;
int a[N];
double q[N];
bool check(double mid)
{
    memset(q, 0, sizeof q);
    for (int i = 1; i <= n; i++)
        q[i] = q[i - 1] + a[i] - mid;

    double minn = 0;
    for (int i = 0, j = f; j <= n; j++, i++)
    {
        minn = min(minn, q[i]);
        if (q[j] - minn > 0)
            return true;
    }
    return false;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> f;
    double l = 0, r = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        r = max(r, (double)a[i]);
    }
    while (r - l >= 1e-6)
    {
        double mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }
    printf("%d", (int)(r * 1000));
    return 0;
}