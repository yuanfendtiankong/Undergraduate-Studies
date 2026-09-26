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

题意：给我们一个长度为N的整数序列A = (A1, A2, ..., AN)，让我们去挑选出在序列A = (A1, A2, ..., Ak)取出第三大的整数

本质：维护一个长度为三的数组，这个数组始终满足单调递减即可。
但是为什么这去做是对的呢？

证明：

设当前数组为：

$$
B=(b_1,b_2,b_3)
$$

并且始终满足：

$$
b_1\ge b_2\ge b_3
$$

其中 (b1,b2,b3) 表示目前遇到的三个最大数。

当加入新数字 (x) 时，只需要将 (x) 插入到正确的位置，并删除最小的数。

为什么这样做是正确的？

因为原来没有被保存的数字都不大于 \(b_3\)。加入一个新数字后，新的前三大数字只可能来自：

$$
b_1,\ b_2,\ b_3,\ x
$$

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

### **E - Min-Max Swap**

题意：给我们一个长度为 `N` 的排列 `P`，以及 `M` 个区间 `[L_i,R_i]`。每次在当前排列的这个区间里，找到最小值和最大值，然后交换它们所在的位置。按顺序做完 `M` 次操作后，输出最终的排列。

### 1. 我是怎么想到线段树的？

如果每次都从头扫描 `[L_i,R_i]`，找最小值、最大值和它们的位置，一次最坏要 `O(N)`，`M` 次最坏就是 `O(NM)`。`N` 和 `M` 都可以到 `2×10^5`，这个做法太慢了。

关键是每次操作之后，排列会变化，下一次查询必须基于更新后的排列。因此我需要同时支持：

- 查询一个区间里的最小值、最大值，以及它们的位置；
- 交换后修改两个位置的值；
- 后续查询能立即看到修改后的值。

这就是“**区间查询 + 单点修改**”的场景。差分适合处理预先给定的区间加减，不能直接维护每次交换之后的区间最值；这里用线段树更合适。

### 2. 线段树的本质

线段树把数组下标递归地分成左右两段，每个节点负责一个区间，并保存这段区间的统计信息。

这题的统计信息是：

```text
区间最小值及其位置
区间最大值及其位置
```

如果一个区间被分成左右两段，而且能用左右两段的信息快速算出整段的信息，就可以把查询拆成若干个已经存好答案的小区间，再把它们合并。单点修改时，只需要沿着根节点到对应叶子的路径更新信息。

所以线段树的关键是先想清楚两件事：

1. 一个节点要保存什么信息？
2. 两个子区间的信息怎么合并？

### 3. `Node`：一个区间保存的信息

只保存最小值和最大值还不够，因为操作要交换的是它们**所在的位置**。所以每个节点保存两个数对：

```text
mn = {最小值, 最小值的位置}
mx = {最大值, 最大值的位置}
```

```cpp
struct Node
{
    pair<int, int> mn;
    pair<int, int> mx;
};
```

本题给的是排列，数值互不相同。`pair` 按“先比较值、再比较位置”的顺序比较，因此 `min` 能选出最小值对应的数对，`max` 能选出最大值对应的数对。

### 4. `merge` 和 `pushup`：合并左右区间

`mergeNode` 接收左右子区间的信息，返回合并后的信息：

```text
合并后的 mn = 左右两边中更小的 mn
合并后的 mx = 左右两边中更大的 mx
```

`pushup(u)` 则把合并结果写回当前节点 `u`。可以记成：

```text
mergeNode：算出父区间的信息
pushup：把算出的信息保存到 tr[u]
```

```cpp
Node mergeNode(const Node& left, const Node& right)
{
    Node res;
    res.mn = min(left.mn, right.mn);
    res.mx = max(left.mx, right.mx);
    return res;
}

void pushup(int u)
{
    tr[u] = mergeNode(tr[u * 2], tr[u * 2 + 1]);
}
```

### 5. `build`：根据初始排列建树

当 `l == r` 时，当前区间只有一个位置，所以它的最小值和最大值都是 `p[l]`。否则先建左右子树，再用 `pushup` 合并出当前节点的信息。

```text
build(u, l, r)
├── l == r：初始化叶子节点
└── 否则：建左右子树，再 pushup(u)
```

### 6. `query`：查询 `[L,R]` 的最值和位置

这里要区分两组下标：

```text
[l,r]：当前线段树节点负责的区间
[L,R]：这次要查询的区间
```

查询时分三种情况：

1. 当前节点的区间完全落在查询范围内：直接返回 `tr[u]`；
2. 查询范围完全在左边或右边：只递归对应的子树；
3. 查询范围跨过 `mid`：左右都查，再用 `mergeNode` 合并。

完整覆盖时直接返回已经保存的信息，不必继续访问区间中的每个位置，这正是区间查询能快起来的原因。

### 7. `update`：单点修改

`update` 的参数含义是：

```text
u       当前线段树节点编号
[l,r]   当前节点负责的区间
pos     要修改的数组下标
value   这个位置的新值
```

递归找到 `pos` 对应的叶子并更新它，然后沿途调用 `pushup`，重新计算祖先节点的区间最值。

### 8. 主流程

每次操作按这个顺序做：

1. `build(1, 1, n)`，根据初始排列建树；
2. `query(1, 1, n, L, R)`，得到当前区间的最小值位置和最大值位置；
3. 在原数组 `p` 中交换这两个位置；
4. 对这两个位置分别调用 `update`，让线段树同步到最新排列；
5. 所有操作完成后，输出 `p`。

注意：只交换数组 `p` 不够，线段树里还存着旧信息；所以交换后必须更新这两个位置。

### 9. 复杂度

- 建树：`O(N)`
- 每次区间查询：`O(log N)`
- 每次操作有两次单点更新：`O(log N)`
- 总时间复杂度：`O(N + M log N)`
- 空间复杂度：`O(N)`（线段树数组开约 `4N` 个节点）

### 完整代码

```cpp
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

struct Node
{
    pair<int, int> mn;
    pair<int, int> mx;
};

Node tr[N * 4];
int p[N];

Node mergeNode(const Node& left, const Node& right)
{
    Node res;
    res.mn = min(left.mn, right.mn);
    res.mx = max(left.mx, right.mx);
    return res;
}

void pushup(int u)
{
    tr[u] = mergeNode(tr[u * 2], tr[u * 2 + 1]);
}

void build(int u, int l, int r)
{
    if (l == r)
    {
        tr[u].mn = {p[l], l};
        tr[u].mx = {p[l], l};
        return;
    }

    int mid = (l + r) / 2;
    build(u * 2, l, mid);
    build(u * 2 + 1, mid + 1, r);
    pushup(u);
}

Node query(int u, int l, int r, int L, int R)
{
    if (L <= l && r <= R)
        return tr[u];

    int mid = (l + r) / 2;

    if (R <= mid)
        return query(u * 2, l, mid, L, R);

    if (L > mid)
        return query(u * 2 + 1, mid + 1, r, L, R);

    Node left = query(u * 2, l, mid, L, R);
    Node right = query(u * 2 + 1, mid + 1, r, L, R);
    return mergeNode(left, right);
}

void update(int u, int l, int r, int pos, int value)
{
    if (l == r)
    {
        tr[u].mn = {value, pos};
        tr[u].mx = {value, pos};
        return;
    }

    int mid = (l + r) / 2;
    if (pos <= mid)
        update(u * 2, l, mid, pos, value);
    else
        update(u * 2 + 1, mid + 1, r, pos, value);

    pushup(u);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        cin >> p[i];

    build(1, 1, n);

    for (int i = 1; i <= m; i++)
    {
        int L, R;
        cin >> L >> R;

        Node res = query(1, 1, n, L, R);
        int mnp = res.mn.second;
        int mxp = res.mx.second;

        swap(p[mnp], p[mxp]);

        update(1, 1, n, mnp, p[mnp]);
        update(1, 1, n, mxp, p[mxp]);
    }

    for (int i = 1; i <= n; i++)
        cout << p[i] << (i == n ? '\n' : ' ');

    return 0;
}
```