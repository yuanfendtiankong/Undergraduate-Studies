#include <iostream>

using namespace std;

int main()
{

    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    for (int i = 0; i < n; i++)
    {
        if (t[i] != s[i] && t[i] != '*')
        {
            cout << "No" << endl;
            exit(0);
        }
    }
    cout << "Yes" << endl;

    return 0;
}