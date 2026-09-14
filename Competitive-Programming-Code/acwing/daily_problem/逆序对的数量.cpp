#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
ll a[N], ans, tmp[N];
ll merge(int l, int r)
{
    if (l >= r)
        return 0;

    int mid = l + r >> 1;
    ans = merge(l, mid) + merge(mid + 1, r);

    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
    {
        if (a[i] <= a[j])
            tmp[k++] = a[i++];
        else
        {
            tmp[k++] = a[j++];
            ans += (mid - i + 1);
        }
    }

    while (i <= mid)
        tmp[k++] = a[i++];
    while (j <= r)
        tmp[k++] = a[j++];
    for (int i = l, j = 0; i <= r; j++, i++)
        a[i] = tmp[j];
    return ans;
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << merge(0, n - 1) << endl;

    return 0;
}