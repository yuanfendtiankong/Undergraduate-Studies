#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int h[N], w[N];
int n, k;
bool check(int mid)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += (h[i] / mid) * (w[i] / mid);
    }

    if (sum >= k)
        return true;
    else
        return false;
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> h[i] >> w[i];
    }

    int l = 1, r = 1e5 + 10;
    while (l < r)
    {
        int mid = l + r + 1 >> 1;
        if (check(mid))
            l = mid;
        else
            r = mid - 1;
    }

    cout << l << endl;

    return 0;
}