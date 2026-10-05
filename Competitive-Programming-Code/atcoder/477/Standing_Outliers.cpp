#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
    int n, d, ans = 0;
    cin >> n >> d;
    vector<int> a(n + 1, 0), b;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
    {
        int flag = 0;
        for (int j = 1; j <= n; j++)
        {
            if (i != j && abs(a[i] - a[j]) < d)
                flag = 1;
        }
        if (flag == 0)
        {
            ans++;
            b.push_back(i);
        }
    }
    cout << ans << endl;
    for (auto x : b)
        cout << x << " ";

    return 0;
}