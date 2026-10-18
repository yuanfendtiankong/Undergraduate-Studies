
#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define endl '\n'

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<ll> a(n + 1, 0), qa(n + 1, 0), sum(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        qa[i] = qa[i - 1] + a[i];
        sum[i] = sum[i - 1] + qa[i];
    }
    vector<ll> st(n + 1, 0);
    for (int i = 1; i <= n; i++)
        st[i] = st[i - 1] + i;

    while (q--)
    {
        ll l, r;
        cin >> l >> r;

        int L = lower_bound(st.begin() + 1, st.end(), l) - st.begin();
        int R = lower_bound(st.begin() + 1, st.end(), r) - st.begin();

        ll ans1 = sum[L - 1] + qa[l - 1 - st[L - 1]];
        ll ans2 = sum[R - 1] + qa[r - st[R - 1]];

        cout << ans2 - ans1 << endl;
    }

    return 0;
}