# AtCoder 常用 C++ 模板

这套模板主要供 ABC 练习和比赛时取用。先理解「什么时候能用、接口是什么意思」，再熟悉实现，不需要一次背完。

**类的作用是把数据和操作放在一起。** 比如 `DSU d(n)` 自己管理父节点和集合大小，题目代码只负责调用 `merge`、`same`。不同对象互不影响，也减少多组数据忘记清空全局数组的问题。`struct` 同样可以封装，和 `class` 的主要区别是默认访问权限。二分、LIS 这种不需要长期保存状态的算法，用函数就很合适。

## 1. 先学哪些

下面是建议学习顺序，不是题号或难度保证。

| 阶段 | 内容 | 看到什么需求时想到它 |
| --- | --- | --- |
| 先熟练 | STL、前缀和、差分、二分、离散化 | 查找边界、区间统计、把大数映射成下标 |
| 核心 | 并查集、BFS、Dijkstra、树状数组 | 连通性、最短路、动态区间和 |
| 核心 | 普通线段树、模运算、组合数 | 自定义区间信息、取模计数 |
| 再扩展 | 拓扑排序、单调栈、LIS、质数筛 | 依赖关系、最近更小值、序列与数论 |
| 遇到再深入 | 懒标记线段树、LCA、KMP | 区间修改、树上多次询问、字符串匹配 |

DP、贪心、双指针、DFS/回溯也很重要，但它们更依赖题目的状态和条件，不适合靠一个通用类解决。SCC、网络流、卷积等可以在需要时先查 ACL，暂时不用全塞进自己的模板。

## 2. 统一约定

- 使用 C++17，头文件依赖 GCC 常用的 `bits/stdc++.h`，适合当前本机 g++。不是面向 MSVC 的标准头文件版本。
- 数组、图的点编号均从 **0** 开始；区间均为 **左闭右开 `[l, r)`**。
- 题目给 1 起始闭区间 `[L, R]`，调用时用 `[L - 1, R)`，即只对 `L` 减一。
- 默认求和、距离使用 `long long`。需要保证中间运算也不溢出；`int * int` 要提前写成 `1LL * a * b`。
- 所有大小必须非负，下标必须合法；LCA 要求至少一个点。代码中的 `assert` 用来帮助发现误用，不是输入修复机制。
- 下面的短用法放在 `main` / `solve` 中；线段树的 `op`、`e` 等全局定义单独标明。

每个 `.hpp` 可以独立引用。本地调试时，在同目录的代码里写：

```cpp
#include "fenwick.hpp"
```

**AtCoder 提交的是单份源代码，不会带上你的本地头文件。** 提交自写模板时，将需要的类/函数复制到 [main.cpp](main.cpp) 的 `solve()` 前面，并去掉对应本地 `#include "xxx.hpp"`。`#pragma once` 不必复制。也可以使用平台提供的 ACL。

## 3. 基础工具：前缀和、差分、离散化、二分

源文件：[basic.hpp](basic.hpp)。

**前缀和**适合数组不变、多次问区间和：预处理 `O(n)`，查询 `O(1)`。

```cpp
std::vector<long long> a{2, 5, 3, 7};
PrefixSum<long long> pre(a);
std::cout << pre.sum(1, 4) << '\n'; // 5 + 3 + 7 = 15
```

**二维前缀和**适合矩形区域求和：预处理 `O(h * w)`，查询 `O(1)`。参数顺序为「左上行、左上列、右下行、右下列」，右下边界不包含。

```cpp
std::vector<std::vector<long long>> grid{{1, 2, 3}, {4, 5, 6}};
PrefixSum2D<long long> pre(grid);
std::cout << pre.sum(0, 1, 2, 3) << '\n'; // 2 + 3 + 5 + 6 = 16
```

**差分**适合先做完所有区间加，再取最终数组：每次加 `O(1)`，还原 `O(n)`。不适合每次修改后立即查询区间和。

```cpp
Difference<long long> diff(5); // 初始全为 0
diff.add(1, 4, 3);
diff.add(2, 5, 2);
auto a = diff.values(); // {0, 3, 5, 5, 2}
```

若初始数组不是 0，把 `values()` 得到的增量加回原数组即可。

**离散化**：预处理 `O(n log n)`，查询编号 `O(log n)`。只保留大小顺序，不保留数值间距。

```cpp
Compressor<long long> comp({100, -5, 100, 800});
int p = comp.index(100);      // 1；index 只接受原来出现过的值
long long x = comp.value(0);  // -5
int k = comp.lower_bound(50); // 1；允许传未出现过的值
```

**整数二分**：在非负整数 `[l, r)` 中找第一个合法值；不存在则返回原来的 `r`。判断结果必须先假后真，调用次数 `O(log(r - l + 1))`，总耗时还要乘上一次判断的代价。

```cpp
long long answer = first_true(0, 101, [](long long x)
{
    return x * x >= 50; // 本例 x <= 100，不会乘法溢出
}); // 8
```

如果只是找有序数组里第一个 `>= x` 或 `> x`，直接用 STL 的 `lower_bound` / `upper_bound`，不必手写二分。

## 4. 并查集：维护连通块

源文件：[dsu.hpp](dsu.hpp)。初始化 `O(n)`，合并/查询均摊 `O(α(n))`，可近似看作常数。

```cpp
DSU d(5);
bool merged = d.merge(0, 1); // true，真正合并了两个集合
d.merge(1, 2);
bool connected = d.same(0, 2); // true
int size = d.size(0);           // 3
int components = d.count();    // 3
```

适合无向图连通性、分组，以及 Kruskal 最小生成树里判断是否成环。普通并查集不支持删边，也不能回答两点的距离。**本模板的 `merge` 返回是否成功合并；ACL 的 `merge` 返回合并后代表节点编号，不能混用返回值含义。** [ACL DSU 文档](https://atcoder.github.io/ac-library/production/document_en/dsu.html)

练习入口：[AtCoder Library Practice A - Disjoint Set Union](https://atcoder.jp/contests/practice2/tasks/practice2_a)。

## 5. 树状数组：单点加、区间和

源文件：[fenwick.hpp](fenwick.hpp)。建树 `O(n)`，修改/查询 `O(log n)`。

```cpp
std::vector<long long> a{2, 5, 3, 7};
Fenwick<long long> bit(a);
bit.add(1, 4);                      // a[1] 从 5 变成 9
std::cout << bit.sum(1, 3) << '\n'; // 9 + 3 = 12
std::cout << bit.prefix(2) << '\n'; // a[0] + a[1] = 11
```

`add(p, x)` 是 **加上 x**。如果要把 `a[p]` 改成 `value`，使用 `add(p, value - a[p])`，并同步修改保存的原数组。

也适合配合离散化求逆序对：从左到右处理，已经出现的数量减去 `prefix(rank + 1)`，就是前面严格大于当前值的数量。这个版本不提供任意区间最值。

练习入口：[AtCoder Library Practice B - Fenwick Tree](https://atcoder.jp/contests/practice2/tasks/practice2_b)。

## 6. 普通线段树：单点改、区间信息

源文件：[segtree.hpp](segtree.hpp)。建树 `O(n)`，修改/查询 `O(log n)`；复杂度假设合并一个节点是 `O(1)`。

你只需要定义：

1. `S`：一个节点存什么。
2. `op(a, b)`：怎样合并左、右两段。
3. `e()`：空区间对应什么值。

下面是区间最小值，先把这两个函数放在全局：

```cpp
long long min_op(long long a, long long b) { return std::min(a, b); }
long long min_e() { return LLONG_MAX; }
```

再在 `main` 中使用：

```cpp
std::vector<long long> a{4, 7, 2, 9};
SegTree<long long, min_op, min_e> seg(a);
std::cout << seg.prod(1, 4) << '\n'; // 2
seg.set(2, 8);                       // 直接赋值 a[2] = 8
std::cout << seg.prod(1, 4) << '\n'; // 7
```

| 维护信息 | 合并 `op` | 空区间 `e()` |
| --- | --- | --- |
| 和 | `a + b` | `0` |
| 最小值 | `min(a, b)` | `LLONG_MAX` |
| 最大值 | `max(a, b)` | `LLONG_MIN` |
| 非负整数 gcd | `gcd(a, b)` | `0` |
| 最值及其位置 | `pair` 或自定义结构体 | 对应的最值哨兵 |

**合并要满足结合律**，也就是先合并哪两段不影响结果；空节点不能改变结果。直接存平均数再取两个平均数的平均值不对，应存 `{总和, 个数}`。不要随意对无穷大哨兵做加法。

### 从你现有的最小值/最大值交换题入手

完整可运行示例：[minmax_swap.cpp](minmax_swap.cpp)，对应你之前 `Min-Max-Swap.cpp` 里的维护方式。

节点保存 `{最小值及位置, 最大值及位置}`。题目主流程只需做四件事：查询区间 → 找到两个位置 → 交换原数组 → 更新两片叶子。模板负责树的内部操作。相同值时，示例选择最小值的最左位置和最大值的最右位置；排列题没有平局问题。

该通用模板提供 `set/get/prod/all_prod`。需要树上二分 `max_right/min_left` 时可使用 ACL；本地版本没有这两个接口。[ACL Segtree 文档](https://atcoder.github.io/ac-library/production/document_en/segtree.html)

## 7. 懒标记线段树：区间加、区间和

源文件：[lazy_segtree.hpp](lazy_segtree.hpp)。建树 `O(n)`，修改/查询 `O(log n)`。

```cpp
RangeAddSum seg(std::vector<long long>{1, 2, 3, 4});
seg.add(1, 4, 10);
std::cout << seg.sum(0, 4) << '\n'; // 40
```

理解重点：给一段的每个数加 `x`，这一段的总和就增加 `x * 长度`。先把这次修改记在整段上，真正访问子区间时再向下传。

**这个版本只做区间加、区间和。** 区间赋值、乘法、仿射变换需要不同的标记规则，不能只改函数名就套用。复杂操作可以学习 [ACL Lazy Segtree](https://atcoder.github.io/ac-library/production/document_en/lazysegtree.html)，其中标记组合 `composition(f, g)` 表示先做 `g` 再做 `f`。

## 8. 模运算和组合数

源文件：[modint.hpp](modint.hpp)。这个轻量版本要求 **MOD 是质数，且 `2 <= MOD <= 1000000007`**；没有自动验证质数。

```cpp
using mint = ModInt<998244353>;
mint a = -1; // 自动变成 998244352
mint b = 2;
std::cout << (a + b).val() << '\n';  // 1
std::cout << mint(2).pow(10).val() << '\n'; // 1024
std::cout << (mint(6) / 2).val() << '\n';   // 3

Combinations<998244353> comb(200000);
std::cout << comb.C(5, 2).val() << '\n'; // 10
```

- 加减乘 `O(1)`；快速幂 `O(log exponent)`；求逆/除法 `O(log MOD)`。
- 组合数预处理 `O(N + log MOD)`，查询 `O(1)`，空间 `O(N)`。
- 模意义下的除法是乘逆元，不是普通整除。除数模 MOD 后不能为 0。
- 组合数要求 `0 <= n <= 预处理上限 < MOD`；合法 n 下，`k < 0` 或 `k > n` 返回 0。
- 当 `n >= MOD` 或模数为合数时，不能使用这套组合数公式。
- 读入时先读普通整数再构造 `mint`，输出使用 `.val()`。

## 9. 图论：BFS、Dijkstra、拓扑排序

源文件：[graph.hpp](graph.hpp)。点编号从 0 开始，`add_edge` 默认加无向边。

**BFS**：无权图/每条边代价相同，求边数最少的路径。`O(n + m)`，不可达返回 `-1`。

```cpp
Graph g(4);
g.add_edge(0, 1);
g.add_edge(1, 2);
auto dist = g.bfs(0); // {0, 1, 2, -1}
```

**Dijkstra**：边权非负。堆实现的宽松复杂度界为 `O((n + m) log(n + m + 1))`；简单图中通常记作 `O((n + m) log n)`。不可达返回 `Dijkstra::INF`。

```cpp
Dijkstra g(4);
g.add_edge(0, 1, 5, true); // true：只添加 0 -> 1
g.add_edge(1, 2, 2, true);
g.add_edge(0, 2, 10, true);
auto dist = g.run(0); // {0, 5, 7, INF}
```

有用的最短距离必须小于 `INF`，否则这个模板无法和不可达区分。遇到负权边不能使用 Dijkstra；权重全为 0/1 时还可以进一步学习 0-1 BFS。

**拓扑排序**：有向图的依赖顺序，`O(n + m)`。如果结果长度小于 n，则存在有向环。

```cpp
Graph g(3);
g.add_edge(0, 2, true);
g.add_edge(1, 2, true);
auto order = g.topological_sort();
bool has_cycle = (static_cast<int>(order.size()) != 3);
```

拓扑排序务必使用有向边。BFS 和 Dijkstra 的当前接口只返回距离，不返回完整路径。

## 10. LCA：树上最近公共祖先

源文件：[lca.hpp](lca.hpp)。预处理和空间 `O(n log n)`，每次查询 `O(log n)`。

```cpp
LCA tree(5);
tree.add_edge(0, 1);
tree.add_edge(0, 2);
tree.add_edge(1, 3);
tree.add_edge(1, 4);
tree.build(0);
int ancestor = tree.query(3, 4); // 1
int distance = tree.distance(3, 2); // 3 条边
int parent = tree.jump(3, 1); // 1；越过根则返回 -1
```

适用的是**一棵静态、连通、无环的无权树**；不是一般图/森林。先加完 `n - 1` 条边，再 `build(root)`，再查询。不同根会改变 LCA，但不会改变两点距离。

## 11. 线性筛：质数与质因数分解

源文件：[sieve.hpp](sieve.hpp)。预处理时间/空间 `O(N)`，判断质数 `O(1)`，一次分解最多 `O(log x)`。

```cpp
PrimeSieve sieve(1000000);
bool prime = sieve.is_prime(97); // true
auto factors = sieve.factorize(360); // {{2, 3}, {3, 2}, {5, 1}}
```

`factorize(x)` 只接受 `1 <= x <= 预处理上限`。`1` 的分解为空；不能把 `10^12` 直接传给只筛到 `10^6` 的这个接口。

## 12. KMP、LIS、单调栈

源文件：[kmp.hpp](kmp.hpp)、[sequence.hpp](sequence.hpp)。

**KMP**：模式串预处理 `O(m)`，查找 `O(n)`，结果包含重叠匹配。模式串不能为空，文本可以为空。

```cpp
KMP matcher("aba");
auto positions = matcher.find_all("ababa"); // {0, 2}
```

**LIS**：求最长上升子序列长度，`O(n log n)`。子序列不要求连续；当前接口只返回长度，不还原序列。

```cpp
std::vector<int> a{1, 2, 2, 3};
int strict = lis_length(a);        // 3，严格递增
int nondecreasing = lis_length(a, false); // 4，允许相等
```

**单调栈**：求每个位置左边最近的严格更小元素，`O(n)`。

```cpp
auto indices = previous_less(std::vector<int>{3, 1, 1, 2}); // {-1, -1, -1, 2}
```

遇到「更小/小于等于」「左边/右边」的变化，要重新检查弹栈条件和遍历方向，尤其注意重复值。

## 13. AtCoder 官方库 ACL 怎么用

ACL 已有并查集、树状数组、线段树、模运算等组件。在提供 ACL 的 AtCoder C++ 环境中可以直接引用，不需要粘贴这些实现。[官方文档入口](https://atcoder.github.io/ac-library/production/document_en/)

| 需求 | ACL 头文件 | 主要类型/接口 |
| --- | --- | --- |
| 并查集 | `atcoder/dsu` | `atcoder::dsu`，`merge/same/size` |
| 树状数组 | `atcoder/fenwicktree` | `atcoder::fenwick_tree<long long>`，`add/sum` |
| 单点修改、区间查询 | `atcoder/segtree` | `atcoder::segtree<S, op, e>`，`set/prod` |
| 区间修改、区间查询 | `atcoder/lazysegtree` | `atcoder::lazy_segtree` |
| 取模运算 | `atcoder/modint` | `atcoder::modint998244353` / `modint1000000007` |

一个完整的 ACL 用法示例：

```cpp
#include <bits/stdc++.h>
#include <atcoder/dsu>
#include <atcoder/fenwicktree>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint998244353;

int main()
{
    atcoder::dsu d(4);
    d.merge(0, 1);
    cout << d.same(0, 1) << '\n'; // 1
    atcoder::fenwick_tree<long long> bit(4);
    bit.add(0, 3);
    cout << bit.sum(0, 4) << '\n'; // 3
    cout << mint(2).pow(10).val() << '\n'; // 1024
}
```

ACL 树状数组的 `sum(l, r)` 也是 `[l, r)`；模数已固定时可选择对应 `modint` 类型，输出用 `.val()`。[Fenwick 文档](https://atcoder.github.io/ac-library/production/document_en/fenwicktree.html)、[Modint 文档](https://atcoder.github.io/ac-library/production/document_en/modint.html)

当前本机 g++ 的默认包含路径没有找到 `atcoder/all`，**上面的 ACL 示例未在本机编译**。本目录的自写模板均不依赖 ACL，已经实际编译测试。以后要本地使用 ACL，可从[官方仓库](https://github.com/atcoder/ac-library)获取，并在编译时用 `-I` 指向包含 `atcoder` 文件夹的目录；只写 `using namespace atcoder` 不会安装库。

## 14. 怎么用模板提高能力

每学一个模板，做完这几个检查就够了：

1. 能说出它解决什么问题、不能处理什么情况。
2. 能解释每个接口的参数、返回值、下标和区间含义。
3. 自己写一次实现，再用短例子和边界例子验证。
4. 做一道直接应用题，再做一道需要把题意转成这个模型的题。
5. 复盘时记录「为什么想到它」「哪里用了题目条件」，不要只收藏代码。

对你来说，可以从现有的最值交换题开始，把手写线段树的外部调用换成 `SegTree`，比较题目主流程和数据结构内部实现各自负责什么。

## 15. 本地验证

在本目录终端运行：

```powershell
g++ -std=c++17 -O2 -Wall -Wextra -Wshadow -pedantic tests.cpp -o template_tests.exe
if ($LASTEXITCODE -eq 0) { .\template_tests.exe }
```

固定随机种子 `20260926`，已经通过 **11 组、327675 次检查**。验证包含朴素数组对拍、最短路和 Floyd 对拍、组合数和 Pascal 三角对拍、LCA 和逐级找祖先对拍、KMP 和逐位置匹配对拍，以及空区间、负数、重复值、10 万点链等边界。

此外，18 个本地调用片段已合并编译并核对输出，比赛起手式已编译运行，最值交换示例通过 120 组随机输入的端到端对拍。ACL 示例不在本地编译验证范围内。

这是本地验证结果，不代表这些文件已经在线提交 AC。后续修改模板时，重新运行对应测试即可。
