#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e5 + 10;
void solve()
{
    int a, b;
    cin >> a >> b;
    vector<pii> ones;
    string str;
    cin >> str;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '1')
        {
            int j = i + 1;
            while (j < str.size() && str[j] == '1')
                j++;
            ones.push_back({i, j});
            i = j - 1;
        }
    }
    // cout << ones.size() << endl;
    if (ones.size() == 1)
    {
        cout << a << endl;
    }
    else if (ones.size() == 0)
    {
        cout << 0 << endl;
    }
    else
    {
        int ans = a;
        for (int i = 0; i < ones.size() - 1; i++)
        {
            int val = (ones[i + 1].first - ones[i].second) * b;
            if (val < a)
                ans += val;
            else
                ans += a;
        }
        cout << ans << endl;
    }
}
void solve2()
{
    int a, b;
    cin >> a >> b;
    string str;
    cin >> str;
    vector<int> pos;
    int pre = -99999, ans = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '1')
        {
            ans += min((i - pre - 1) * b, a);
            pre = i;
        }
    }
    cout << ans << endl;
}
int main()
{

    int t = 1;
    cin >> t;
    while (t--)
    {
        solve2();
    }

    return 0;
}
