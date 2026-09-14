#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    int n, x, f = 0;
    cin >> n >> x;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    sort(arr.begin(), arr.end());

    auto i = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
    auto j = upper_bound(arr.begin(), arr.end(), x) - arr.begin() - 1;

    int ans = 0;

    if (i == n)
    {
        ans = 1;
        j = i;
        n++;
    }

    int m = (n - 1) / 2;
    if (i > m)
        ans += (i * 2 - n + 1);
    else if (j < m)
        ans += n - 2 * j - 2;
    cout << ans << endl;

    return 0;
}