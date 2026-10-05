#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, v;
    cin >> n >> v;
    vector<int> w(n + 1);

    for (int i = 1; i <= n; i++)
        cin >> w[i];

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            for (int k = j + 1; k <= n; k++)
            {
                if (i + j + k <= v)
                    ans = max(ans, w[i] + w[j] + w[k]);
            }
        }
    }
    cout << ans << endl;

    return 0;
}