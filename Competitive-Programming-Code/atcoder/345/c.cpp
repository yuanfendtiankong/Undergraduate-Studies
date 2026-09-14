#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
const int N = 1e5 + 10, M = 1024;
typedef long long ll;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
int n, flag;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ll ans = 0;
    string s;
    cin >> s;
    vector<int> cnt(32, 0);
    for (auto x : s)
        cnt[x - 'a']++;

    for (int i = 0; i <= 26; i++)
        if (cnt[i] > 1)
            ans = 1;
    for (int i = 0; i < s.size(); i++)
    {
        ans += s.size() - i - 1;
        cnt[s[i] - 'a']--;
        ans -= cnt[s[i] - 'a'];
    }
    cout << ans << endl;

    return 0;
}
// #include <bits/stdc++.h>

// using namespace std;
// #define endl "\n"
// const int N = 1e5 + 10, M = 1024;
// typedef long long ll;
// typedef pair<int, int> pii;
// typedef tuple<int, int, int> tiii;
// int n, flag;

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     cout.tie(0);

//     ll ans = 0;

//     string str;
//     cin >> str;
//     set<char> st;
//     vector<vector<int>> cnt(str.size() + 1, vector<int>(32, 0));
//     cnt[0][str[0] - 'a']++;
//     for (int i = 1; i < str.size(); i++)
//     {
//         cnt[i] = cnt[i - 1];
//         cnt[i][str[i] - 'a']++;
//         st.insert({str[i]});
//     }
//     if (st.size() == 1)
//     {
//         cout << 1 << endl;
//         return 0;
//     }

//     for (int i = 0; i < 26; i++)
//         if (cnt[str.size() - 1][i] > 1)
//             ans = 1;

//     for (int i = 0; i < str.size(); i++)
//         for (int j = 0; j < 26; j++)
//             if (str[i] - 'a' != j)
//                 ans += (cnt[str.size() - 1][j] - cnt[i][j]);
//     cout << ans << endl;

//     return 0;
// }

