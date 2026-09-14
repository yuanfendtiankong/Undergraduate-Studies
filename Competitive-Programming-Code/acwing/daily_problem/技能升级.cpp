#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
typedef pair<int, int> pii;
int n, m;
priority_queue<pii> heap;
int a[N], b[N];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i] >> b[i];
        heap.push({a[i], i});
    }

    ll ans = 0;
    for (int i = 1; i <= m; i++)
    {
        ans += heap.top().first;
        int pos = heap.top().second;
        heap.pop();
        a[pos] -= b[pos];
        heap.push({a[pos], pos});
    }
    cout << ans << endl;
    return 0;
}