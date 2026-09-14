#include <bits/stdc++.h>

using namespace std;

int main()
{
    string str;
    cin >> str;

    set<string> cnt;
    for (int i = 0; i < str.size(); i++)
    {
        for (int j = 1; j + i <= str.size(); j++)
        {
            cnt.insert(str.substr(i, j));
        }
    }

    cout << cnt.size() << endl;
    return 0;
}