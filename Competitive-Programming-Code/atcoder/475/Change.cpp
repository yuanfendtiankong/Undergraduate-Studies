#include <bits/stdc++.h>

using namespace std;

int main()
{

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        a[i] %= 1000;
    }
    int num1 = 0, num2 = 0, num3 = 0;

    for (int i = 0; i < n; i++)
    {
        if (a[i] == 0)
            continue;
        int now = 1000 - a[i];
        num1 = num1 + now / 100;
        num2 = num2 + (now % 100) / 10;
        num3 = num3 + now % 10;
    }
    cout << num3 << " " << num2 << " " << num1 << endl;

    return 0;
}