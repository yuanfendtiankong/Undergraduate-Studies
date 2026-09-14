#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false), cin.tie();
    cout.tie(0);

    int n;
    cin >> n;
    stack<int> st;
    for (int i = 0, x; i < n; i++)
    {
        cin >> x;
        while (st.size() && st.top() >= x)
            st.pop();
        if (st.size())
            cout << st.top() << " ";
        else
            cout << -1 << ' ';
        st.push(x);
    }

    return 0;
}