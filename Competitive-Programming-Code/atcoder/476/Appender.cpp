#include <iostream>

using namespace std;

int main()
{

    ios::sync_with_stdio(false);
    cin.tie(0);

    string str;
    cin >> str;
    if (*(str.end() - 1) == 'e')
        cout << str << "r" << endl;
    else
        cout << str << "er" << endl;

    return 0;
}