#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, pos = 1;
    cin >> n;
    map<string, int> cnt;
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        if (cnt.find(str) == cnt.end())
            cnt.insert({str, pos}), pos++;
        cout << cnt[str] << endl;
    }

    return 0;
}