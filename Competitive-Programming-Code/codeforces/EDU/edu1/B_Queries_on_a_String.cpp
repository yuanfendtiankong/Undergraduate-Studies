#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define endl '\n'
void solve()
{
    string str1, str2;
    cin >> str1;
    str2 = str1;

    int n;
    cin >> n;
    while (n--)
    {
        int l, r, k, len;
        cin >> l >> r >> k;
        len = r - l + 1;
        k = k % len;
        l--, r--;
        string ans = str1.substr(l, len);
        for (int i = l; i <= r; i++)
        {
            int pos = (i + k) > r ? i + k - r + l - 1 : i + k;
            str1[pos] = str2[i];
        }
        str2 = str1;
    }
    cout << str1 << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}