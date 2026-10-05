#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<char> a(n + 1, 'a');
    vector<int> st(n + 1, 0), d(n + 1, 0);
    int cc = 0;
    char cur = 'a';

    for (int i = 0; i < q; i++)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x;
            cin >> x;
            if (!st[x])
            {
                if (cc > d[x])
                    a[x] = cur;

                st[x] = 1;
            }
            else
            {
                st[x] = 0;
                d[x] = cc;
            }
        }
        else
        {
            char b;
            cin >> b;
            cur = b;
            cc++;
        }
    }

    for (int i = 1; i < a.size(); i++)
    {
        if (st[i])
            cout << a[i];
        else
        {
            if (cc > d[i])
                cout << cur;
            else
                cout << a[i];
        }
    }

    return 0;
}