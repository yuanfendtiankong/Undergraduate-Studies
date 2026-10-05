# 在本地写 LeetCode：保留 Solution，自己补测试入口

你感觉 LeetCode 的题目特殊，主要是因为：**AtCoder 通常让你提交整个程序，LeetCode 大部分算法题让你实现平台会调用的方法。** 本地调试时，把平台替你做的「构造输入、调用方法、检查结果」补出来就行。

| 对比 | AtCoder 常见题 | LeetCode 常见算法题 |
| --- | --- | --- |
| 入口 | 自己写 `main()` | 平台的测试程序调用你的方法 |
| 输入 | 从 `cin` 读取 | 从方法参数获取 |
| 输出 | 向 `cout` 打印 | `return` 返回，或按要求原地修改 |
| 提交内容 | 包含 `main` 的完整程序 | `Solution` / 题目要求的类及依赖代码 |
| 链表、树 | 自己设计表示 | 按题面提供的 `ListNode` / `TreeNode` 接口 |

本目录用 **C++17 + 一个本地头文件 + 每题一个测试 main**。有三个已写好的例子，可以直接运行。

## 1. 先运行一个例子

在仓库根目录的 PowerShell 中执行：

```powershell
.\leetcode\run.ps1 0001_two_sum.cpp
.\leetcode\run.ps1 0206_reverse_list.cpp
.\leetcode\run.ps1 0104_max_depth.cpp
```

也可以进入本目录执行 `./run.ps1 0001_two_sum.cpp`。脚本使用系统路径中的 `g++`，自动启用本地测试开关，编译失败就停止，生成物放在 `.build/`。

若你的终端不允许运行 PowerShell 脚本，在本目录直接执行等价命令即可：

```powershell
g++ -std=c++17 -g -O0 -Wall -Wextra -DLOCAL 0001_two_sum.cpp -o two_sum.exe
if ($LASTEXITCODE -eq 0) { .\two_sum.exe }
```

当前验证结果：两数之和 6 个用例、反转链表 5 个用例、二叉树深度 7 个用例及稀疏树结构检查通过。另外，关闭 `LOCAL`、只由模拟评测入口提供标准头文件和节点类型时，三个解法也编译运行通过，没有依赖本地助手。

示例作为单独程序分别编译，不要把所有 `.cpp` 一起编译，否则会有多个 `main`。

## 2. 一道题的文件怎么放

复制 [template.cpp](template.cpp)，改名为 `题号_简短英文题名.cpp`，再从题面复制函数签名。文件分成三部分：

```cpp
#ifdef LOCAL
#include "local.hpp"
#endif

class Solution
{
public:
    // 在这里保留题目要求的方法名、参数和返回类型。
};

#ifdef LOCAL
int main()
{
    // 构造输入 -> 调用 Solution -> 检查返回值。
}
#endif
```

`-DLOCAL` 相当于在**本次编译**定义 `LOCAL`。这样本地才会带上头文件和测试入口。不要在源码顶部写死 `#define LOCAL`。

提交时复制 `Solution` 类和它真正依赖的辅助函数/模板即可，不复制本地 `main` 和 `local.hpp`。设计类题按题面要求提交对应类，不一定叫 `Solution`。网站预定义的节点类型不要重复提交。[LeetCode 官方测试说明](https://support.leetcode.com/hc/en-us/articles/32442719377939-How-to-create-test-cases-on-LeetCode)

## 3. 数组和字符串：直接构造参数

以 [0001_two_sum.cpp](0001_two_sum.cpp) 为例，题目方法是：

```cpp
vector<int> twoSum(vector<int>& nums, int target);
```

在本地 `main` 里这样调用：

```cpp
vector<int> nums{2, 7, 11, 15};
int target = 9;
Solution solution;
auto answer = solution.twoSum(nums, target);
```

**不用把 `[2,7,11,15]` 写成一行字符串，再折腾输入解析。** 平台展示的样例在本地直接写成 C++ 的 `vector` 就够了。`string`、二维 `vector` 也一样。

若方法接收 `vector<int>&`，先定义变量再传入，不要直接把 `{2, 7, 11, 15}` 传给这个非常量引用。

判断结果应遵守题目要求。两数之和允许任意顺序，所以例子验证两个下标不同、合法、对应数之和正确，而不是只允许某个固定的下标顺序。[两数之和题面](https://leetcode.com/problems/two-sum/description/)

## 4. 链表：把数组构造成节点

平台显示的 `head = [1,2,3]`，实际传入的是链表头指针，不是 `vector<int>`。本地助手已经提供常见节点定义和构造/转回数组的方法。

参考 [0206_reverse_list.cpp](0206_reverse_list.cpp)，对应[反转链表题面](https://leetcode.com/problems/reverse-linked-list/description/)：

```cpp
ListNode* head = local::make_list({1, 2, 3});
Solution solution;
ListNode* answer = solution.reverseList(head);
assert((local::list_values(answer) == vector<int>{3, 2, 1}));
local::free_list(answer);
```

反转后头节点改变了，要从返回的新头释放节点。普通链表助手不用于有环、共享尾部或随机指针的链表；这些题应按照题面专门连接指针。例如判断环题里的 `pos` 用于构造环，不是你的 `hasCycle` 方法参数。对于有环链表，先断环再使用普通释放函数。

## 5. 二叉树：层序数组里的 null 是缺失节点

参考 [0104_max_depth.cpp](0104_max_depth.cpp)，对应[二叉树最大深度题面](https://leetcode.com/problems/maximum-depth-of-binary-tree/description/)：

```cpp
TreeNode* root = local::make_tree({3, 9, 20, nullopt, nullopt, 15, 7});
Solution solution;
assert(solution.maxDepth(root) == 3);
local::free_tree(root);
```

本地用 `std::nullopt` 对应题面里的 `null`。`local::tree_values(root)` 可以把普通二叉树转回层序数组，方便检查构造树/修改树的题目。

容易误解的例子是 `[1,null,2,3]`：根 1 没有左孩子，右孩子是 2，**3 是 2 的左孩子**。它不是完全二叉树的下标数组，不能机械套 `left = 2*i+1`。这些表示规则见[官方输入格式说明](https://support.leetcode.com/hc/en-us/articles/32442719377939-How-to-create-test-cases-on-LeetCode)。

构造与释放助手只处理普通树。题目给出 `Node`、N 叉树、带 `next` 的树等其他类型时，应以该题定义为准，在本地另补对应类型。

## 6. 原地修改、设计题、特殊判定怎么测

| 类型 | 本地做法 |
| --- | --- |
| 返回普通值/数组 | `auto answer = solution.method(input)` 后检查 `answer` |
| `void` 原地修改 | 调用后检查原来的 `nums` / `matrix` 等参数 |
| 返回有效长度 | 同时检查长度与题目要求的有效前缀；忽略题面允许忽略的尾部 |
| 设计类题，例如栈或缓存 | 构造一次对象，再按样例顺序调用各方法，逐次检查结果 |
| 允许不同答案顺序 | 按题目要求比较集合、多重集合或验证答案性质 |
| 浮点结果 | 按题目误差要求比较，不直接用 `==` |
| 环、相交链表、图节点 | 验证指针关系/身份，不能仅比较节点值 |
| 交互式接口，如 `guess` | 本地实现符合题意的接口模拟，不把隐藏答案变成解法参数 |

设计题的输入通常是在描述一串方法调用。例如先创建队列，再 `push(1)`、`push(2)`、检查 `pop()` 的结果；本地直接写这些调用，不必先实现一个通用字符串调度器。

## 7. 平时建议怎样刷

1. 保留题面函数签名，实现算法。
2. 先写样例，再补空输入（题面允许时）、单元素、重复值、边界值等用例。
3. 用 `assert` 检查，不只看打印结果。这里的运行脚本没有关闭断言，不要加 `-DNDEBUG`。
4. 每个用例重新构造输入，避免前一个用例已经原地修改了数组或链表。成员变量也要按题目要求初始化，防止多次调用残留状态。
5. 本地调试后，复制提交部分到网页 Run / Submit。这里的测试不会自动上传或提交代码。

VS Code 的编译/调试任务也需要包含 `-DLOCAL`，并让调试器运行对应的生成文件；只点一个不带这个参数的默认运行按钮，会缺少本地头文件和 `main`。本目录的运行脚本已经包含这一参数。

本地通过不等于完整评测通过，仍需网站的边界数据与特殊判定；语言环境以[LeetCode 官方环境说明](https://support.leetcode.com/hc/en-us/articles/360011833974-What-are-the-environments-for-the-programming-languages)为准。这里的示例仅使用 C++17 功能，未进行在线提交。
