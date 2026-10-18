#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    map<string, int> cnt;
    vector<string> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        string str;
        cin >> str;
        s[i] = str;
        cnt[str] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        string str;
        cin >> str;
        if (cnt.find(str) != cnt.end())
        {
            cnt[str]++;
        }
        else
        {
            vector<string> ss;
            for (int j = 1; j <= n; j++)
            {
                int cnt2 = 0;
                if (str.size() == s[j].size())
                {
                    for (int t = 0; t < str.size(); t++)
                    {
                        if (str[t] != s[j][t])
                            cnt2++;
                    }
                    if (cnt2 == 1)
                    {
                        ss.push_back(s[j]);
                    }
                }
            }
            if (ss.size() == 1)
                cnt[ss.front()]++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << cnt[s[i]] << endl;
    }

    return 0;
}