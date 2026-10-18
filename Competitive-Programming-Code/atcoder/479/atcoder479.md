# AtCoder Beginner Contest 479

### **A - Odd Index Sum**

题意：水题，给你一个长度为N的数值序列，找到下标为奇数的项，并计算他们的和。

```c++
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, sum = 0;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        if (i % 2)
            sum += a[i];
    }
    cout << sum << endl;
    return 0;
}
```

### **B - Longest Rainy Streak**

题意：Takahashi记录了连续`N`天的天气，记录的每一天都包括两种情况“Sunny”或者“Rainy”。他把他的记录以字符串的格式给我们，长度为`N`的字符串`S`，其中字符串中`S`中的字符”S“表示Sunny，字符”R“表示Rainy，问题是让我们找到Takahashi记录的串中，Rainy最多连续多少天？

思路：因为我们题目的范围是1-100所以我们直接暴力枚举，从每一次雨天开始往后枚举，有多少天是连续的雨天，最后把结果max一下即可，时间复杂度***O(N)***

```c++
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n, ans = 0;
    cin >> n;
    string str;
    cin >> str;
    for (int i = 0; i < n; i++)
    {
        if (str[i] == 'R')
        {
            int st = i;
            while (i < n && str[i] == 'R')
                i++;
            ans = max(ans, i - st);
        }
    }
    cout << ans << endl;
    return 0;
}
```

### C - Bento Packing

题意：餐馆里面有`N`道菜肴，每一道菜肴都会有他自己的美味程度`A[i]`和体积`B[i]`,你是一名顾客，你将会在这N道菜肴里面选择若干道菜放到你的午餐盒里面去，请问你在不超过午餐盒体积`W`的情况下，你能吃到的最大的***美味程度之和***是多少？

思路：因为我们的`N`范围只有1-20，所以我们购买所有菜肴的总方案最多也就是`2^20`，因此对于这道题目来说方法就会很多了，我使用的是dfs枚举每道菜选不选，最后比较一下那种方案的美味程度最大，时间复杂度：
$$
O(2^N)
$$
除了我自己做的这种方法之外，我看答案上给我们的哪种方案也是很长的优雅，他是使用了位运算的方法来解决这道问题，直接枚举`2^20`这些方案之后，根据二进制上每一位是***0***还是***1***来判断每道菜肴选还是不选，然后计算一下所有选择菜肴的美味值之和，复杂度是
$$
O(N2^N)
$$
注意我们的`A`和`B`数组的范围是**1e9**，所以说还是得开一下**longlong**，以防数据溢出.

```C++
#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll mx = 0, n, w;
vector<int> a, b;
void dfs(int u, ll sum, ll val)
{
    if (sum > w)
        return;

    if (u > n)
    {
        mx = max(mx, val);
        return;
    }

    dfs(u + 1, sum, val);
    dfs(u + 1, sum + b[u], val + a[u]);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> w;
    a.resize(n + 1, 0);
    b.resize(n + 1, 0);
    for (int i = 1; i <= n; i++)
        cin >> a[i] >> b[i];

    dfs(1, 0, 0);

    cout << mx << endl;

    return 0;
}
```

```c++
#include <bits/stdc++.h>

using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, w;
    cin >> n >> w;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i] >> b[i];

    ll ans = 0;
    for (int i = 0; i < 1 << n; i++)
    {
        ll val = 0, v = 0;
        for (int j = 0; j < n; j++)
            if (i >> j & 1)
            {
                val += a[j];
                v += b[j];
            }
        if (v <= w)
            ans = max(ans, val);
    }
    cout << ans << endl;
    return 0;
}
```

### **D - Back and Forth Distance**

题意：有`N`个方格从左到右排列成一行，当你在方格`i`的时候你有两种移动方法，向左移动到任意一个（不包括自己）花费代价`L[i]`,或者向右移动到任意一格，花费代价`R[i]`，接下来给你`q`次询问给你`s`和`t`问你每次询问下的从s到t的最下代价。

思路：通过分析题意和样例，我们可以发现，从起点 (S) 移动到终点 (T)，只需要考虑两种情况：

1. **直接移动**：从起点 (S) 沿着目标方向（向左或向右）移动，直到到达终点 (T)。
2. **先反向移动，再前往终点**：先从起点 (S) 向目标的相反方向移动，找到能够使总代价最小的折返点，然后改变方向，移动到终点 (T)。

因此，我们只需要分别计算这两种方案的最小代价，再取其中的较小值，即可得到最终答案。

但是在这个实现的过程中你会发现我们需要去维护当前方格的一个最小前缀，以及一个最小的后缀，这东西如果有积累还是比较容易想到如何去实现的，如果是这里卡住了，看过代码之后你应该会豁然开朗。我的代码中`R[i]`表示的就是1-s中向右移动花费的最小代价，同理`L[i]`表示的就是我们N->s中向左移动花费的最小代价

```c++
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, Q;
    cin >> n >> Q;
    vector<int> l(n + 1), r(n + 1);
    for (int i = 2; i <= n; i++)
        cin >> l[i];
    for (int j = 1; j <= n - 1; j++)
        cin >> r[j];

    vector<int> R(n + 10, 1e9 + 10), L(n + 10, 1e9 + 10);
    for (int i = 1; i < n; i++)
        R[i] = min(R[i - 1], r[i]);
    for (int i = n; i >= 2; i--)
        L[i] = min(L[i + 1], l[i]);

    for (int i = 0; i < Q; i++)
    {
        int s, t, ans;
        cin >> s >> t;
        if (s < t)
            ans = min(r[s], l[s] + R[s - 1]);
        else
            ans = min(l[s], r[s] + L[s + 1]);
        cout << ans << endl;
    }

    return 0;
}
```



