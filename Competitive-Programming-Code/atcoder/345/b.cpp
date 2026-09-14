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

    ll x;
    cin >> x;
    if (x > 0)
    {
        cout << (x - 1) / 10 + 1 << endl;
    }
    else
    {
        cout << x / 10 << endl;
    }

    return 0;
}