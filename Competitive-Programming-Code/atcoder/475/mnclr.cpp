#include <bits/stdc++.h>

using namespace std;

int main()
{
    string s, ans;
    cin >> s;

    int num = s.size();
    for (int i = 0; i < num; i++)
    {
        if (i != 0)
            cout << "o";
        cout << s[i];
    }

    return 0;
}