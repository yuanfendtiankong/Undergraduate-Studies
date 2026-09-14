#include <bits/stdc++.h>

using namespace std;
#define endl "\n"
const int N = 1e5 + 10, M = 1024;
typedef pair<int, int> pii;
typedef tuple<int, int, int> tiii;
int n, flag;
char g[M][M];
bool st[M][M];
int dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    if (str[0] == '<' && str[str.size() - 1] == '>')
    {
        for (int i = 1; i < str.size() - 1; i++)
        {
            if (str[i] != '=')
            {
                cout << "No" << endl;
                return 0;
            }
        }
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
        return 0;
    }

    return 0;
}