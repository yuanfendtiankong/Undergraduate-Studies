#include <iostream>

using namespace std;
char ch[3] = {'B', 'Y', 'R'};
int main()
{
    char a;
    cin >> a;
    for (int i = 0; i < 3; i++)
    {
        if (a == ch[i])
        {
            cout << ch[(i + 1) % 3] << endl;
            return 0;
        }
    }
    return 0;
}