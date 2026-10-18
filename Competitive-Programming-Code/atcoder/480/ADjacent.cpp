#include <bits/stdc++.h>

using namespace std;

int main()
{

    pair<int, int> a, d;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
        {
            char ch;
            cin >> ch;
            if (ch == 'A')
                a = {i, j};
            if (ch == 'D')
                d = {i, j};
        }
    if (abs(a.first - d.first) + abs(d.second - a.second) < 2)
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    return 0;
}