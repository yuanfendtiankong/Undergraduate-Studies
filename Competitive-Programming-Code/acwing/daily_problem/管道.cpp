#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int N = 1e5 + 10;
ll L[N], S[N];
ll n, len;
bool check(ll mid)
{
    vector<pii> segs, res;
    for (int i = 0; i < n; i++)
        if (S[i] <= mid)
        {
            ll l = max((ll)1, L[i] - mid + S[i]);
            ll r = min(len, L[i] + mid - S[i]);
            segs.push_back({l, r});
        }

    sort(segs.begin(), segs.end());
    if (segs[0].first > 1)
        return false;

    int ed = segs[0].second;
    for (int i = 1; i < segs.size(); i++)
    {
        if (segs[i].first <= ed + 1)
            ed = max(ed, segs[i].second);
        else
            return false;
    }
    return ed == len;
}
int main()
{
    ios::sync_with_stdio(false), cin.tie(0);
    cout.tie(0);

    cin >> n >> len;
    for (int i = 0; i < n; i++)
        cin >> L[i] >> S[i];

    ll l = 0, r = 2e9 + 10;
    while (l < r)
    {
        ll mid = l + r >> 1;
        if (check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    cout << r << endl;

    return 0;
}