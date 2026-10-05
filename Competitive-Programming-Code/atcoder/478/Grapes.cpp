#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<int> ans(n + 1, 0);
    int i = 0;
    while (m)
    {
        ans[i % n]++;
        i++;
        m--;
    }
    for (int i = 0; i < n; i++)
        cout << ans[i] << endl;

    return 0;
}