#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    for (int i = 1; i <= n; i++)
        cin >> b[i];

    int l = 1, r = n;
    while (l <= n && a[l] == b[l])
        l++;
    while (r >= 1 && a[r] == b[r])
        r--;

    //cout << l << " " << r << endl;

    if (l > n)
    {
        cout << "Yes" << endl;
        return 0;
    }

    // a[r]=b[l] a[i]=b[i+1]
    bool flag = false;
    if (a[r] == b[l])
    {
        bool ans = true;
        for (int i = l; i < r; i++)
            if (a[i] != b[i + 1])
                ans = false;
        if (ans)
            flag = true;
    }
    // a[l]= b[r] a[i+1] = b[i]
    if (a[l] == b[r])
    {
        bool ans = true;
        for (int i = l + 1; i <= r; i++)
            if (a[i] != b[i - 1])
                ans = false;
        if (ans)
            flag = true;
    }

    cout << (flag ? "Yes" : "No") << '\n';

    return 0;
}
