# AtCoder Beginner Contest 480

### **A - ADjacent**

题意：给我们一个`2x2`的方格，方格里面有`A,B,C,D`四个字母，并且每个方格里面的字母都不相同，如果我们的A和D是相邻的，那么我们就输出`Yes`，否者的话我们就输出`No`

思路：今天的第一题其实我感觉还挺麻烦的，我第一想法是直接写if，else,也是就是判断我们的A和D是否在一条边上，好像判断四种情况就行，但是我感觉有点麻烦，我就多想了一下，发现其实只有我们的A和D处于两条对角线，也就是他俩的曼哈顿距离为2的时候输出No其余情况都是输出Yes，其实这样写，代码也没有变短，但是时间确实被浪费了。

```c++
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
```

### **B - Invalid Vote**

题意：有N个候选人参加选举，每个候选人的名字都是由小写的英文字母组成，并且每个人的名字都是不一样的，第`i`个候选人的名字是`S[i]`,现在我们有`M`张选票，每张选票上都是一个字符串`T[i]`，如果有一个候选人的名字和`T[i]`完全一致，那么这个人就或者一票，否者的话，如果只有**一位**候选人的名字可以通过修改`T[i]`中的一个字符来得到,那么这个人就获得一票，否则这个选票无效。问题让我们计算每个候选人最后获得的投票数。

思路：有一说一我每一遇到这种字符串的题目都很头痛，这次也不例外，这个题目帧的好麻烦呀，为了处理那个可以修改一个字符匹配+只允许一个人可以修改这个要求，直接把我的代码写的像狗屎一样了。这个题第一步肯定是先拿map统计一下每个字符串出现过的次数，然后在统计我们选票的时候，我们先去判断这个选票的名字是否出现过，出现过直接++，否则的话我们再去寻找是或否有和我们字符串只相差一位的候选人，并且统计只差一位的候选人数量，只有当候选人数量为1时，我们才回去判断这张选票有效，否者都是无效的。

```c++
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    map<string, int> cnt;
    vector<string> s(n + 1);
    for (int i = 1; i <= n; i++)
    {
        string str;
        cin >> str;
        s[i] = str;
        cnt[str] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        string str;
        cin >> str;
        if (cnt.find(str) != cnt.end())
            cnt[str]++;
        else
        {
            vector<string> ss;
            for (int j = 1; j <= n; j++)
            {
                int cnt2 = 0;
                if (str.size() == s[j].size())
                {
                    for (int t = 0; t < str.size(); t++)
                    {
                        if (str[t] != s[j][t])
                            cnt2++;
                    }
                    if (cnt2 == 1)
                        ss.push_back(s[j]);
                }
            }
            if (ss.size() == 1)
                cnt[ss.front()]++;
        }
    }
    for (int i = 1; i <= n; i++)
        cout << cnt[s[i]] << endl;

    return 0;
}
```

### **C - Self-Stopping Shower**

题意：依旧是我们熟悉的高桥先生，他去公共澡堂洗澡，这个淋浴间有一个按钮。如果在时间 *t* 按下按钮，从时间` t` 到时间 `t+K` 的 `K` 秒内会有热水流出。即使在出热水时再次按下按钮，从上次按下按钮的时间算起，也会有 *K* 秒的热水流出。现在有N个人在澡堂洗澡，第`i`个人会在`A[i]`按下按钮，问如果我们的高桥先生想要在`[0,T]`的时间内最少需要按多少次按钮才可以使我们的热水一直流出？

思路：把每个人按下按钮后出热水的时间看成一个区间，问题就变成了：**已有的区间覆盖了哪些时间，还需要按几次按钮才能补齐剩下的空档？**

1. **合并已有的出水区间。** 在 `A[i]` 时刻按下按钮，可以让热水持续到 `A[i] + K`。将这些区间按左端点排序，再把重叠或首尾相接的区间合并，就能得到几段连续出热水的时间。
2. **找出 `[0, T]` 内没有热水的空档。** 用 `pos` 记录已经检查到的位置，初始为 `0`。遍历合并后的区间 `[l, r]`，如果 `min(l, T) > pos`，说明中间有一段空档 `[pos, min(l, T)]`；随后更新 `pos = max(pos, min(r, T))`。遍历结束后，如果 `pos < T`，还要补上最后一段空档 `[pos, T]`。这里用 `min(..., T)`，是因为我们只关心 `T` 之前的时间。
3. **分别计算每段空档需要按几次。** 对于长度为 `len` 的空档，每次按按钮最多覆盖 `K` 秒，因此至少需要向上取整 `len / K` 次，也就是代码中的 `(len + K - 1) / K`。从空档起点开始，每隔 `K` 秒按一次，就能达到这个次数；最后一次出水超过空档右端点也没关系。

不同空档之间隔着一段长度至少为 `K` 的已有出水区间，因此一次额外按按钮无法同时覆盖两个空档，可以把各段所需次数直接相加。

例如 `K = 3，T = 12`，其他人在 `2、4、9` 时刻按按钮。已有区间合并后为 `[2, 7]、[9, 12]`，剩下两段空档 `[0, 2]、[7, 9]`，各需要按一次，所以答案是 `2`。

时间复杂度为 `O(N log N)`，主要用于排序；空间复杂度为 `O(N)`。

```c++
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, k, t;
    cin >> n >> k >> t;
    vector<pair<int, int>> a;
    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        a.push_back({x, x + k});
    }

    sort(a.begin(), a.end());
    vector<pair<int, int>> tmp;
    for (auto c : a)
    {
        if (tmp.empty() || c.first > tmp.back().second)
            tmp.push_back({c.first, c.second});
        else
            tmp.back().second = max(tmp.back().second, c.second);
    }
    vector<pair<int, int>> res;
    int pos = 0;
    for (auto [l, r] : tmp)
    {
        if (min(l, t) > pos)
            res.push_back({pos, min(l, t)});

        pos = max(pos, min(r, t));
    }
    if (pos < t)
        res.push_back({pos, t});

    long long ans = 0;
    for (auto [l, r] : res)
    {
        int len = r - l;
        ans += (len + k - 1) / k;
    }
    cout << ans << endl;

    return 0;
}
```

### **D - Concatenation of Prefixes**

题意：

给定一个长度为 N 的整数序列 A = (A₁, A₂, …, Aₙ)。

按照以下步骤，构造一个长度为 N(N+1)/2 的序列 B：

- 初始时，B 是一个空序列。
- 依次遍历 i = 1, 2, …, N，每次将 A 的前 i 项追加到 B 的末尾。

也就是说，依次拼接以下序列：

- 第 1 次追加：(A₁)
- 第 2 次追加：(A₁, A₂)
- 第 3 次追加：(A₁, A₂, A₃)
- ……
- 第 N 次追加：(A₁, A₂, …, Aₙ)

给定 Q 次询问，每次询问给出两个整数 L 和 R，求序列 B 中第 L 项到第 R 项（包含两端）的元素之和。

思路：区间求和可以转化为两个前缀和相减。设 `F(x)` 表示序列 `B` 的前 `x` 项之和，那么每次询问的答案就是 `F(R) - F(L - 1)`。关键在于：**不真正构造很长的 `B`，而是利用它的拼接规律计算 `F(x)`。**

**1. 预处理每一段的和，以及前几段的总和。**

把追加的 `(A₁, A₂, …, Aᵢ)` 称为第 `i` 段，这一段长度为 `i`，元素和就是 `A` 的前 `i` 项之和。因此预处理两个数组：

- `p[i] = p[i - 1] + A[i]`：`A` 的前 `i` 项之和，也是第 `i` 段的和。
- `sum[i] = sum[i - 1] + p[i]`：`B` 中前 `i` 个完整段的总和。

其中 `p[0] = sum[0] = 0`。这样，只要知道包含了几个完整段，就可以直接算出它们的总和。

**2. 利用每段的结束位置，找到第 `x` 项属于哪一段。**

前 `i` 段一共有 `1 + 2 + … + i` 个元素，所以令：

`st[i] = i × (i + 1) / 2`，并令 `st[0] = 0`。

`st[i]` 记录的是第 `i` 段在 `B` 中的结束位置，依次为 `1、3、6、10、…`。这些数叫作三角数，和杨辉三角不同。

对于 `x > 0`，用 `lower_bound` 找到第一个满足 `st[i] >= x` 的段号 `i`。此时有 `st[i - 1] < x <= st[i]`，说明前 `i - 1` 段已经完整包含，第 `i` 段取了前 `x - st[i - 1]` 项。

**3. 把“完整段”和“当前段取到的部分”相加。**

第 `i` 段本来就是 `A` 的前缀，所以它的前 `x - st[i - 1]` 项之和可以直接查 `p`，得到：

`F(x) = sum[i - 1] + p[x - st[i - 1]]`

另外单独规定 `F(0) = 0`，用于处理 `L = 1` 的情况。

例如 `A = [2, 4, 6]`，拼接后 `B = [2 | 2, 4 | 2, 4, 6]`。计算 `F(5)` 时，由于 `st[2] = 3 < 5 <= st[3] = 6`，前两段完整包含，第三段取前 `2` 项，因此 `F(5) = sum[2] + p[2] = 8 + 6 = 14`。

最后，对每次询问分别计算 `F(R)` 和 `F(L - 1)`，相减即可。预处理为 `O(N)`，每次询问二分两次，为 `O(log N)`，总时间复杂度为 `O(N + Q log N)`，空间复杂度为 `O(N)`。位置、前缀和及答案都用 `long long` 存储。

```c++

#include <bits/stdc++.h>

using namespace std;
#define ll long long
#define endl '\n'

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    vector<ll> st(n + 1, 0);
    for (int i = 1; i <= n; i++)
        st[i] = st[i - 1] + i;

    vector<ll> p(n + 1, 0);
    for (int i = 1; i <= n; i++)
        p[i] = p[i - 1] + a[i];
    vector<ll> sum(n + 1, 0);
    for (int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + p[i];

    for (int i = 0; i < q; i++)
    {
        ll l, r;
        cin >> l >> r;
        int R = lower_bound(st.begin() + 1, st.end(), r) - st.begin();
        ll ans1 = sum[R - 1] + p[r - st[R - 1]], ans2 = 0;

        if (l > 1)
        {
            int L = lower_bound(st.begin() + 1, st.end(), l - 1) - st.begin();
            ans2 = sum[L - 1] + p[l - 1 - st[L - 1]];
        }

        cout << ans1 - ans2 << endl;
    }

    return 0;
}
```

