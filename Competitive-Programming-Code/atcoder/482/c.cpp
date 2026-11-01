#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int h, w, n, q;
    cin >> h >> w >> n >> q;

    vector<int> a, b;
    for (int i = 0; i < n; i++)
    {
        int r, c;
        cin >> r >> c;
        a.push_back(r);
        b.push_back(c);
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    for (int i = 0; i < q; i++)
    {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 1)
        {
            int L = lower_bound(a.begin(), a.end(), l) - a.begin();
            int R = upper_bound(a.begin(), a.end(), r) - a.begin();
            cout << R - L << endl;
        }
        else
        {
            int L = lower_bound(b.begin(), b.end(), l) - b.begin();
            int R = upper_bound(b.begin(), b.end(), r) - b.begin();
            cout << R - L << endl;
        }
    }
    return 0;
}