#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;
int a[N], n, x;
int main()
{

    // lower_bound
    int L = 0, R = n - 1;

    while (L <= R)
    {
        int mid = L + (R - L) / 2;

        if (a[mid] >= x) // 如果改成>号会变成求解upper_bound
        {
            // mid 合法，但左边可能还有更早的合法位置
            R = mid - 1;
        }
        else
        {
            // mid 不合法，往右找
            L = mid + 1;
        }
    }

    // L = 第一个满足 a[i] >= x 的位置
    // R = 最后一个满足 a[i] < x 的位置

    return 0;
}