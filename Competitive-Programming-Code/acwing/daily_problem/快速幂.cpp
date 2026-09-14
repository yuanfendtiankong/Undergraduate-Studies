#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll qmi(ll a, ll b, ll p)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = (res * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    while (t--)
    {
        ll a, b, p;
        cin >> a >> b >> p;
        cout << qmi(a, b, p) << endl;
    }

    return 0;
}