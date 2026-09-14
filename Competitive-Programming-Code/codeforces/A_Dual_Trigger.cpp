#include <bits/stdc++.h>

using namespace std;
void solve()
{
    int n;
    cin >> n;
    string str;
    cin >> str;
    if (n == 2 && str == "11")
    {
        cout << "NO" << endl;
        return;
    }
    int cnt = 0;
    for (auto x : str)
        if (x == '1')
            cnt++;
    if (cnt == 2)
    {
        for (int i = 0; i < n - 1; i++)
            if (str[i] == '1' && str[i + 1] == '1')
            {
                cout << "NO" << endl;
                return;
            }
        cout << "YES" << endl;
    }
    else
        cout << (cnt & 1 ? "NO" : "YES") << endl;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }

    return 0;
}