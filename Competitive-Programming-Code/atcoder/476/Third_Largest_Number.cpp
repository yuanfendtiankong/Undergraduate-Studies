#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
int main()
{

    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int x = a[0], y = a[1], z = a[2];
    cout << min({x, y, z}) << endl;

    for (int i = 3; i < n; i++)
    {
        int nn = a[i];
        int num[4] = {x, y, z, nn};

        sort(num, num + 4, greater<int>());

        x = num[0], y = num[1], z = num[2];
        cout << z << endl;
    }
    return 0;
}