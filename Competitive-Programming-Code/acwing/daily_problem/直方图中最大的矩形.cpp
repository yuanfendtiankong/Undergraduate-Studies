#include <iostream>
#include <vector>
#include <stack>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int h[N], l[N], r[N];
int main()
{
    int n;
    while (cin >> n, n)
    {
        for (int i = 1; i <= n; i++)
            cin >> h[i];
        h[0] = h[n + 1] = -1;
        stack<int> st;
        st.push(0);
        for (int i = 1; i <= n; i++)
        {
            while (h[st.top()] >= h[i])
                st.pop();
            l[i] = st.top();
            st.push(i);
        }

        while (st.size())
            st.pop();
        st.push(n + 1);
        for (int i = n; i; i--)
        {
            while (h[st.top()] >= h[i])
                st.pop();
            r[i] = st.top();
            st.push(i);
        }

        ll ans = 0;
        for (int i = 1; i <= n; i++)
        {
            ans = max(ans, ((ll)h[i] * (r[i] - l[i] - 1)));
        }
        cout << ans << endl;
    }
    return 0;
}
