// #include <bits/stdc++.h>

// using namespace std;
// const int N = 1e5 + 10, M = 520;
// int n, m, k;
// int a[M][M], q[M][M];
// int main()
// {
//     ios::sync_with_stdio(false), cin.tie(0);
//     cout.tie(0);

//     cin >> n >> m >> k;
//     for (int i = 1; i <= n; i++)
//         for (int j = 1; j <= m; j++)
//             cin >> a[i][j];

//     for (int i = 1; i <= n; i++)
//         for (int j = 1; j <= m; j++)
//         {
//             q[i][j] = q[i - 1][j] + q[i][j - 1] + a[i][j] - q[i - 1][j - 1];
//             //cout << q[i][j] << " \n"[j == m];
//         }
//     ll ans = 0;
//     for (int i = 1; i <= n; i++)
//     {
//         for (int j = 1; j <= m; j++)
//         {
//             for (int x = i; x <= n; x++)
//             {
//                 for (int y = j; y <= m; y++)
//                 {
//                     if (q[x][y] - q[x][j - 1] - q[i - 1][y] + q[i - 1][j - 1] <= k)
//                         ans++;
//                 }
//             }
//         }
//     }
//     cout << ans << endl;

//     return 0;
// }

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int n, m, k;
int a[520][520];
int main()
{

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
        {
            cin >> a[i][j];
            a[i][j] += a[i - 1][j];
        }

    ll res = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
        {
            for (int l = 1, r = 1, sum = 0; r <= m; r++)
            {
                sum += a[j][r] - a[i - 1][r];
                while (sum > k)
                {
                    sum -= a[j][l] - a[i - 1][l];
                    l++;
                }
                res += (r - l + 1);
            }
        }
    cout << res << endl;
    return 0;
}