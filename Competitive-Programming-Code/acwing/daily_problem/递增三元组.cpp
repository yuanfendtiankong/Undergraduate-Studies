#include <bits/stdc++.h>

using namespace std;
int n;
const int N = 1e5 + 10;
int a[N], b[N], c[N];
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    for (int i = 0; i < n; i++)
        cin >> c[i];
    sort(a, a + n);
    sort(b, b + n);
    sort(c, c + n);

    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        long long l = lower_bound(a, a + n, b[i]) - a;
        long long r = upper_bound(c, c + n, b[i]) - c;
        ans += (l) * (n - r);
    }
    cout << ans << endl;
    return 0;
}