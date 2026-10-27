# AtCoder Beginner Contest 481

题目链接：[AtCoder Beginner Contest 481](https://atcoder.jp/contests/abc481/tasks)

### **A - Digits of A+B**

题意：给定两个整数 $A$ 和 $B$，求它们的和在十进制表示下有多少位。

思路：先计算 `n + m`，再用 `to_string` 把结果转换成字符串，字符串的长度就是答案。例如 $9+9=18$，转换后得到 `"18"`，长度为 2。

题目范围内的和可以用 `int` 保存。代码中的 `str.size()` 就是十进制位数；在本题给定的数据范围内，时间复杂度和空间复杂度均为 `O(1)`。

```c++
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;
    string str = to_string(n + m);
    cout << str.size() << endl;

    return 0;
}
```

### **B - Polyline**

题意：平面上有 $N$ 个点，第 $i$ 个点的坐标为 $(i,A_i)$。依次连接相邻的点得到一条折线，求折线上纵坐标等于 $K$ 的点有多少个，折线两端也要计算。题目保证相邻的 $A_i$ 不相等。

思路：我们只需要检查每一段折线是否与直线 $y=K$ 相交。不过，相邻线段共用一个端点，如果端点正好在 $y=K$ 上，就不能把它重复计算。

代码用 `tmp` 保存每一段的两个纵坐标 `a`、`b`，并采用**包含左端点、不包含右端点**的方式计数：

- 当 `a <= k && b > k` 时，这一段从 $K$ 或 $K$ 下方走到 $K$ 上方，交点计入答案。
- 当 `a >= k && b < k` 时，这一段从 $K$ 或 $K$ 上方走到 $K$ 下方，交点也计入答案。
- 如果 `b == k`，这一段暂时不计数。对于中间顶点，下一段会把它作为左端点计入；对于最后一个顶点，遍历完成后单独判断一次。

例如 $K=3$，纵坐标依次为 `1, 3, 1`。第一段的右端点是 3，暂时不计数；第二段从 3 出发，因此计数一次，最终答案为 1。

题目保证 $N\ge 2$，所以 `tmp.back()` 一定有效。共保存并遍历 $N-1$ 条线段，时间复杂度为 `O(N)`，空间复杂度为 `O(N)`。

```c++
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> tmp;

    int be, x;
    cin >> be;
    for (int i = 1; i < n; i++)
    {
        cin >> x;
        tmp.push_back({be, x});
        be = x;
    }

    int ans = 0, pos = 0;
    for (auto [a, b] : tmp)
        if (a <= k && b > k || a >= k && b < k)
            ans++;
    if (tmp.back().second == k)
        ans++;
    cout << ans << endl;
    return 0;
}
```

### **C - Bank Accounts**

题意：一开始银行没有账户，接下来依次给出 $Q$ 个名字。如果该名字已经有账户，就输出它的账户编号；否则创建一个账户，分配当前没有使用过的最小正整数作为编号，再输出这个编号。

思路：我们需要根据名字查找对应的编号，因此可以使用 `map<string, int>` 保存名字到编号的映射。

用 `pos` 表示下一个可用编号，初始为 1。每次读入名字时，先用 `find` 判断它是否已经出现过：如果是新名字，就把它和 `pos` 加入 `map`，然后让 `pos` 加一；如果名字已经存在，则不修改编号。最后输出 `cnt[str]`。

为什么 `pos` 一定是最小的未使用编号？因为账户不会被删除，新账户始终按 1、2、3……的顺序分配编号，所以已使用编号总是从 1 开始连续的一段。

例如依次输入 `alice, bob, alice`，输出的编号就是 `1, 2, 1`。设名字的最大长度为 $L$，`map` 的查找和插入需要 `O(log Q)` 次字符串比较，因此时间复杂度为 `O(Q L log Q)`，空间复杂度为 `O(Q L)`；本题 $L$ 最多为 10。

```c++
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, pos = 1;
    cin >> n;
    map<string, int> cnt;
    for (int i = 0; i < n; i++)
    {
        string str;
        cin >> str;
        if (cnt.find(str) == cnt.end())
            cnt.insert({str, pos}), pos++;
        cout << cnt[str] << endl;
    }

    return 0;
}
```

### **D - Autopilot**

题意：有 $N$ 个星球和 $M$ 条单向航路，飞船从星球 $S$ 出发，目标是到达星球 $T$。在当前星球，飞船可以免费前往所有直接可达星球中编号最小的一个；也可以消耗 1 单位燃料，前往任意一个直接可达的星球。求最少消耗多少燃料，如果无法到达则输出 `-1`。

思路：每次移动都会沿着一条有向边前进，而我们关心的是燃料消耗，所以可以把题目转换成**带权有向图上的最短路**。

对于星球 $u$ 的所有出边，先找出能够直接到达的最小编号 `mn[u]`：

- 通向 `mn[u]` 的边权设为 0，因为可以使用自动驾驶免费到达。
- 通向其他星球的边权设为 1，因为必须消耗 1 单位燃料。

即使也可以付费前往最小编号的星球，选择免费移动总是不更差，所以只需保留权值 0。没有出边的星球无法继续移动，跳过即可；航路是单向的，不能额外添加反向边。

建好图之后，从 $S$ 运行 Dijkstra。`d[v]` 表示从 $S$ 到达 $v$ 的最小燃料消耗，优先队列每次取出当前距离最小的点，再用它的出边尝试更新其他点。所有边权都是非负数，因此第一次确定某个点时，得到的就是它的最短距离。若 $T$ 的距离始终为初始无穷大，就说明无法到达。

例如从星球 2 可以到达 4 和 5，那么 $2\to4$ 的边权为 0，$2\to5$ 的边权为 1。接下来 Dijkstra 会综合考虑后续航路，找到总燃料最少的路线，而不是只看当前一步。

代码先遍历所有航路求每个点的最小出边终点，再遍历邻接表设置边权。堆优化 Dijkstra 的时间复杂度为 `O(N + M log(M + 1))`，空间复杂度为 `O(N + M)`。由于边权只有 0 和 1，这题也可以使用 0-1 BFS，时间复杂度为 `O(N + M)`。

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 2e5 + 10;
#define pii pair<int, int>
int d[N];
bool st[N];
int n, m, s, t;
vector<vector<pii>> g;
int dijkstra(int be, int ed)
{
    memset(d, 0x3f, sizeof d);
    d[be] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push({0, be});

    while (q.size())
    {
        auto t = q.top();
        q.pop();

        int node = t.second, dis = t.first;
        if (st[node])
            continue;
        st[node] = true;

        for (int i = 0; i < g[node].size(); i++)
        {
            int now = g[node][i].first, nd = g[node][i].second;
            if (d[now] > d[node] + nd)
            {
                d[now] = d[node] + nd;
                q.push({d[now], now});
            }
        }
    }
    if (d[ed] == 0x3f3f3f3f)
        return -1;
    return d[ed];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m >> s >> t;
    g.resize(n + 1);
    vector<int> mn(n + 1, 1000000);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, 1});
        mn[a] = min(mn[a], b);
    }
    for (int i = 1; i <= n; i++)
    {
        if (g[i].size() == 0)
            continue;
        for (int j = 0; j < g[i].size(); j++)
            if (g[i][j].first == mn[i])
                g[i][j].second = 0;
    }

    cout << dijkstra(s, t) << endl;

    return 0;
}
```

#### 拓展：0-1 BFS

上面的 Dijkstra 可以处理任意非负边权，但本题的边权只有 **0 和 1**。利用这个特点，我们可以用双端队列 `deque` 代替优先队列，得到更快的 0-1 BFS。

先回想普通 BFS：所有边权都为 1，所以新到达的点直接放到队尾，就能按照距离从小到大的顺序处理。但是本题还存在边权为 0 的边，如果把它的终点也直接放到队尾，就可能让距离较大的点先被处理。

假设当前取出的点是 `u`，它的最短距离为 `d[u]`。通过一条边到达 `v` 时，新的距离只可能有两种：

- 边权为 0：新距离是 `d[u]`，因此把 `v` 放到**队首**，优先处理。
- 边权为 1：新距离是 `d[u] + 1`，因此把 `v` 放到**队尾**。

例如队列中已经有距离为 1 的点，此时又通过一条权值为 0 的边发现了距离为 0 的点，就应当把新点放在队首；如果发现的是距离为 1 的点，就放到队尾。这样队列会按距离由小到大的顺序处理有效状态，作用和 Dijkstra 的优先队列类似。

这里仍然要进行**松弛操作**：只有当 `d[u] + w < d[v]` 时，才更新 `d[v]` 并把 `v` 加入队列。不能在第一次发现一个点时就认为它的距离已经确定，因为之后可能通过权值为 0 的边找到更短的路径。

下面的队列保存 `{距离, 顶点}`。同一个顶点可能因距离变小而多次入队，如果取出的距离已经不等于 `d[u]`，说明这是一个过期状态，直接跳过即可。严格变小才入队，也能避免在权值为 0 的环上反复加入相同距离。

建图方式与上面相同：先记录每个点能到达的最小编号，然后在遍历出边时判断边权。每个顶点和每条边只需处理常数次，时间复杂度为 `O(N + M)`，空间复杂度为 `O(N + M)`。

```c++
#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<vector<int>> g(n + 1);
    vector<int> mn(n + 1, n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        mn[a] = min(mn[a], b);
    }

    const int INF = 1e9;
    vector<int> d(n + 1, INF);
    deque<pair<int, int>> q; // {距离, 顶点}
    d[s] = 0;
    q.push_front({0, s});

    while (!q.empty())
    {
        auto [dis, u] = q.front();
        q.pop_front();

        if (dis != d[u])
            continue;

        for (int v : g[u])
        {
            int w = (v == mn[u] ? 0 : 1);
            if (d[v] > dis + w)
            {
                d[v] = dis + w;
                if (w == 0)
                    q.push_front({d[v], v});
                else
                    q.push_back({d[v], v});
            }
        }
    }

    if (d[t] == INF)
        cout << -1 << endl;
    else
        cout << d[t] << endl;

    return 0;
}
```
