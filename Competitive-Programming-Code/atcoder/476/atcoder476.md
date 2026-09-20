# AtCoder Beginner Contest 476

### **A - Appender**

*水题，题意说的是如果我们的单词以e结尾则在后面+r，否则则在最后面+er*

```c++
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
```

### **B - Wild Card**

*水题：题意说的给你两个长度一致的字符串S和T，其中字符串T种有‘*’*，这个*可以被替换成任意的字母，问你是否可以通过有限次的替换把T变成S，可以的话输出Yes，否则输出No。其实就是看S和T在相同的位置上是否匹配就可以了。

```c++
#include <iostream>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    for (int i = 0; i < n; i++)
    {
        if (t[i] != s[i] && t[i] != '*')
        {
            cout << "No" << endl;
            exit(0);
        }
    }
    cout << "Yes" << endl;
    return 0;
}
```

### **C - Third Largest Number**

题意：给我们一个长度为N的整数序列\(A=(A_1,A_2,\ldots,A_N)\)，让我们去挑选出在序列\(A=(A_1,A_2,\ldots,A_k)\) 取出第三大的整数

本质：维护一个长度为三的数组，这个数组始终满足单调递减即可。
但是为什么这去做是对的呢？

证明：

设当前数组为：

\[
B=(b_1,b_2,b_3)
\]

并且始终满足：

\[
b_1\ge b_2\ge b_3
\]

其中 \(b_1,b_2,b_3\) 表示目前遇到的三个最大数。

当加入新数字 \(x\) 时，只需要将 \(x\) 插入到正确的位置，并删除最小的数。

为什么这样做是正确的？

因为原来没有被保存的数字都不大于 \(b_3\)。加入一个新数字后，新的前三大数字只可能来自：

\[
b_1,\ b_2,\ b_3,\ x
\]

所以只要在这四个数字中保留最大的三个，就能得到新的前三大数字。

不断处理所有数字后，数组中的第三个数字 \(b_3\) 就是整个序列中的第三大数字。

因此，我们只需要维护最大的三个数和每次新进来的那个数就可以

```
#include <bits/stdc++.h>

using namespace std;
#define endl '\n'
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int x = a[0], y = a[1], z = a[2];
    cout << min({x, y, z}) << endl;

    for (int i = 3; i < n; i++)
    {
        int nn = a[i];
        int num[4] = {x, y, z, nn};

        sort(num, num + 4, greater<int>());

        x = num[0], y = num[1], z = num[2];
        cout << z << endl;
    }
    return 0;
}
```



### **D - Automat**

哎依旧差一点第四题，我的二分学的和够死一样

题意：在我们的Atcoder公司里面有两种售卖机，一种卖甜点，一种卖饮料，每个公司的员工只有一元和K元的货币，而我们的饮料售卖机只收K元货币，甜点两种货币都收，问我们如何花钱我们可以得到数量最多的甜品+饮料数量？

思考：刚开始我看样例，我想到了肯定和这个饮料怎么去买有关系，我第一种想法是饮料和甜点都排序，然后按照最便宜的去一次购买，然后很容易我就想到了反例。第二种想法，两个分别排序，然后先去购买甜点剩下的钱去购买饮料，后面我自己也想到了反例，自己pass了。然后我就开始陷入了长时间的思考，最后我灵光乍现，想到了我们先去枚举卖多少个饮料，然后剩下的钱去全买甜点。但是至于为什么这个思路对，我自己也不是很会证明，因此一下的证明借助chatgpt

***为什么这样做可以保证最优？***

核心思想：**枚举全局决策 + 局部贪心**。

假设最优方案购买了 (d) 个饮料。

1. **固定饮料数量 (d)**

如果要买 (d) 个饮料，那么一定可以选择**最便宜的 (d) 个饮料**。

因为如果方案中买了一个更贵的饮料，却没买更便宜的饮料，那么将其替换后：

- 消耗的 (K) 元钞票不会更多；
- 得到的 1 元找零不会更少。

因此方案不会变差。

2. **甜品同理**

买完这 (d) 个饮料后，如果还能买 (c) 个甜品，那么这 (c) 个甜品也一定可以选择**最便宜的 (c) 个**。

所以将甜品排序并维护前缀和，就可以求出当前剩余金额下最多能买多少个甜品。

3. **为什么不会漏掉最优解？**

   真正的最优方案一定对应某个饮料数量 `d*`。

   我们枚举所有可能的饮料数量：

   ```
   d = 0, 1, 2, ..., M
   ```

   因此一定会枚举到：

   ```
   d = d*
   ```

   对于固定的 `d*`：

   - 选择最便宜的 `d*` 个饮料，不会比原方案更差；
   - 再用剩余的钱购买尽可能多的最便宜甜品，也不会比原方案更差。

   因此，对所有 `d` 的情况取最大值，就一定能够得到全局最优解。

   > **核心：枚举最优解中的饮料数量，再对固定数量下的商品选择进行贪心。**

```c++
#include <bits/stdc++.h>

using namespace std;
#define ll long long
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, m, k, x, y, ans = 0;
    cin >> n >> m >> k >> x >> y;

    vector<ll> a(n + 1, 0), qa(n + 1, 0);
    vector<ll> b(m + 1, 0), qb1(m + 1, 0), qb2(m + 1, 0);
    for (ll i = 1; i <= n; i++)
        cin >> a[i];
    for (ll i = 1; i <= m; i++)
        cin >> b[i];

    sort(a.begin() + 1, a.end());
    sort(b.begin() + 1, b.end());
    for (int i = 1; i <= n; i++)
        qa[i] = qa[i - 1] + a[i];
    for (int i = 1; i <= m; i++)
    {
        qb1[i] = qb1[i - 1] + b[i];
        qb2[i] = qb2[i - 1] + ((b[i] - 1) / k + 1);
    }
    for (ll i = 0; i <= m; i++)
    {
        if (y < qb2[i])
            break;
        ll ny = y - qb2[i];
        ll nx = qb2[i] * k - qb1[i] + x;
        ll nsum = ny * k + nx;

        ll ans2 = i, ans1 = 0;

        auto pos = upper_bound(qa.begin(), qa.end(), nsum);
        ans1 = pos - qa.begin() - 1;
        ans = max(ans, ans1 + ans2);
    }

    cout << ans << endl;

    return 0;
}
```

