#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
typedef long long ll;
vector<int> a[N];

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    int ans = 0;
    for (int i = 0; i < str.size() - 1; i++)
    {
        char a = str[i], b = str[i + 1];
        if (a == b || a == '?' || b == '?')
            ans++, i++;
    }
    cout << ans << endl;

    return 0;
}