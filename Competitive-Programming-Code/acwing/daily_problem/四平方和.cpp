#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
const int N = 5000010, M = 1024;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
int n;
bool st[N];
pii cnt[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i * i <= n; i++)
        for (int j = i; j * j + i * i <= n; j++)
        {
            if (st[i * i + j * j])
            {
                st[i * i + j * j] = true;
                cnt[i * i + j * j] = {i, j};
            }
        }

    for (int i = 0; i * i <= n; i++)
    {
        for (int j = 0; i * i + j * j <= n; j++)
        {
            int val = i * i + j * j;
            if (st[n - val])
            {
                cout << i << " " << j << " " << cnt[n - val].first << " " << cnt[n - val].second << endl;
                return 0;
            }
        }
    }

    return 0;
}