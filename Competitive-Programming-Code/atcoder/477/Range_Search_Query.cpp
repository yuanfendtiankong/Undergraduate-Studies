#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int Q;
    string S, T;
    cin >> Q;
    cin >> S >> T;
    if (T.size() > S.size())
    {
        for (int i = 0; i < Q; i++)
        {
            int L, R;
            cin >> L >> R;
            cout << "No" << endl;
        }
    }
    else
    {
        vector<pair<int, int>> pos;
        for (int i = 0; i <= S.size() - T.size(); i++)
        {
            int flag = 0;
            for (int j = 0; j < T.size(); j++)
            {
                if (S[i + j] != T[j])
                    flag = 1;
            }
            if (flag == 0)
                pos.push_back({i + 1, i + (int)T.size()});
        }

        for (int i = 0; i < Q; i++)
        {
            int L, R, flag = 0;
            cin >> L >> R;
            pair<int, int> tmp = {L, -1};
            auto it = lower_bound(pos.begin(), pos.end(), tmp);

            if (it != pos.end() && it->second <= R)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
    }

    return 0;
}