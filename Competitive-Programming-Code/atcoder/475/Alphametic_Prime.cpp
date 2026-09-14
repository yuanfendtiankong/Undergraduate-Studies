#include <bits/stdc++.h>

using namespace std;
const int N = 1e7 + 10;
string str, s;
int num, ans;
bool st[10], prime[N];
map<char, int> mp;
void isprime()
{
    prime[0] = true;
    prime[1] = true;
    for (int i = 2; i < N; i++)
        if (!prime[i])
            for (int j = i + i; j < N; j += i)
                prime[j] = true;
}
void dfs(int pos)
{
    if (pos == num)
    {
        int ans = 0;
        if (mp[str[0]] == 0)
            return;
        for (auto x : str)
            ans = ans * 10 + mp[x];

        if (!prime[ans])
        {
            cout << ans << endl;
            exit(0);
        }
        return;
    }

    for (int i = 0; i < 10; i++)
    {
        if (st[i])
            continue;

        st[i] = true;
        mp[s[pos]] = i;
        dfs(pos + 1);
        mp[s[pos]] = -1;
        st[i] = false;
    }
}
int main()
{
    isprime();
    cin >> str;
    set<char> kind;
    for (auto x : str)
        kind.insert(x);
    num = kind.size();
    for (auto x : kind)
        s += x, mp[x] = -1;

    dfs(0);

    cout << -1 << endl;

    return 0;
}