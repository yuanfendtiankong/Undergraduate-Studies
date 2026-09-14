#include <bits/stdc++.h>

using namespace std;
const int N = 70;
#define endl '\n'

int n;
bool st[N];
int w[N];
int sum, len;
bool dfs(int u, int cur, int start)
{
    if (u * len == sum)
        return true;
    if (cur == len)
        return dfs(u + 1, 0, 0);

    for (int i = start; i < n; i++)
    {
        if (st[i])
            continue;

        if (cur + w[i] <= len)
        {
            st[i] = true;
            if (dfs(u, cur + w[i], i + 1))
                return true;
            st[i] = false;
        }

        if (!cur || cur + w[i] == len)
            return false;

        int j = i + 1;
        while (j < n && w[i] == w[j])
            j++;
        i = j - 1;
    }

    return false;
}
int main()
{

    while (true)
    {
        cin >> n;
        if (n == 0)
            break;
        len = sum = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> w[i];
            sum += w[i];
            len = max(len, w[i]);
        }

        sort(w, w + n, greater<int>());

        memset(st, 0, sizeof st);
        while (true)
        {
            if (sum % len == 0 && dfs(0, 0, 0))
            {
                cout << len << endl;
                break;
            }
            len++;
        }
    }
    return 0;
}
