#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    string str;
    cin >> str;
    int cnt = 0;
    for (auto x : str)
        if (x == 'o')
            cnt++;
    if (cnt % 2)
        cout << "odd" << endl;
    else
        cout << "even" << endl;
    return 0;
}