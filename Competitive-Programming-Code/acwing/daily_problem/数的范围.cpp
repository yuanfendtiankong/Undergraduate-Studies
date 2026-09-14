#include <bits/stdc++.h>

using namespace std;
const int N = 3e2 + 10;
typedef pair<int, int> pii;
int n, ans;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    while (q--)
    {
        int tar;
        cin >> tar;
        int l = 1, r = n;
        while (l < r)
        {
            int mid = l + r >> 1;
            if (a[mid] >= tar)
                r = mid;
            else
                l = mid + 1;
        }

        if (a[l] != tar)
            cout << -1 << " " << -1 << endl;
        else
        {
            cout << l - 1 << " ";
            l = 1, r = n;
            while (l < r)
            {
                int mid = l + r + 1 >> 1;
                if (a[mid] <= tar)
                    l = mid;
                else
                    r = mid - 1;
            }
            cout << r - 1 << endl;
        }
    }

    return 0;
}