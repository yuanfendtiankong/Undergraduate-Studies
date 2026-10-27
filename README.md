# 📦 Undergraduate Studies

> 个人学习代码仓库，涵盖 **竞赛刷题**、**模式识别课程实验** 与 **计算机网络课程设计** 三大模块。

---

## 📁 目录结构

```
Undergraduate Studies/
├── Competitive-Programming-Code/ # 竞赛刷题代码
│   ├── PTA/                      # PTA 平台题目（C++）
│   ├── acwing/                   # AcWing 平台
│   ├── atcoder/                  # AtCoder 平台（ABC 328 / 345 / 347 / 455 ~ 457 / 475 ~ 480）
│   ├── codeforces/               # Codeforces 平台
│   ├── leetcode/                 # LeetCode 本地刷题（附本地测试模板）
│   └── Algorithms/               # 算法专题练习
│       ├── Binary_Search/        # 二分查找
│       ├── DFS/                  # 深度优先搜索
│       ├── Graph/                # 图论（Tarjan 强连通分量）
│       └── IntervalMerging/      # 区间合并（贪心）
├── NetworkCourseDesign/          # 计算机网络课程设计
│   ├── v2/                       # 当前版本（C++ 下位机 + Python 上位机）
│   │   ├── client.cpp            # 下位机客户端（C++，Winsock）
│   │   └── server.py             # 上位机服务端（Python）
│   └── v1/                       # 早期 Python 版本
│       ├── sever.py              # 早期服务端
│       └── user.py               # 早期客户端
└── Pattern Recognition/          # 模式识别课程作业（Python）
    ├── code/                     # 各章节实验代码
    ├── page/
    └── picture/                  # 实验图片资源
```

---

## 🏆 ACM 竞赛刷题

### 平台概览

| 平台 | 目录 | 语言 | 说明 |
|------|------|------|------|
| [PTA](https://pintia.cn/) | `Competitive-Programming-Code/PTA/` | C++ | 国内 OJ，含 PAT / 天梯赛题库 |
| [AcWing](https://www.acwing.com/) | `Competitive-Programming-Code/acwing/` | C++ | 周赛 & 每日一题 |
| [AtCoder](https://atcoder.jp/) | `Competitive-Programming-Code/atcoder/` | C++ | 日本 OJ，ABC 328 ~ 480，475 场起附题解 |
| [Codeforces](https://codeforces.com/) | `Competitive-Programming-Code/codeforces/` | C++ | Div.2 / Div.3 / EDU / 每日题 |
| [LeetCode](https://leetcode.com/) | `Competitive-Programming-Code/leetcode/` | C++ | 本地刷题模板（`run.ps1` + 测试入口）|

### AtCoder 近期场次

ABC 475 ~ 480 每场目录下均附有题解文档（`atcoderXXX.md`），记录题意、思路推导与 AC 代码：

| 场次 | 题解 | 亮点题目 |
|------|------|---------|
| ABC 475 | `475/atcoder475.md` | C - Walk the Line（O(N²) → 二分 → 双指针 O(N)）、D - Alphametic Prime（全排列枚举 + 素数判定）|
| ABC 476 | `476/atcoder476.md` | D - Automat（枚举饮料数量 + 局部贪心）、E - Min-Max Swap（线段树维护区间最值与位置）|
| ABC 477 | `477/atcoder477.md` | C - Range Search Query（子串出现位置预处理 + 二分）、D - Masking Tape（倒序处理 / 染色版本号懒更新）|
| ABC 478 | `478/atcoder478.md` | C - Sort Subarray（定位与目标有序数组不一致的区间）、D - Range Set Insertion Query（区间合并）|
| ABC 479 | `479/atcoder479.md` | C - Bento Packing（DFS / 位运算枚举子集）、D - Back and Forth Distance（前缀 / 后缀最小值）|
| ABC 480 | `480/atcoder480.md` | C - Self-Stopping Shower（区间合并 + 空档贪心）、D - Concatenation of Prefixes（前缀和 + 二分）|

> 更早的场次（328 / 345 / 347 / 455 ~ 457）仅保留代码，暂无题解文档。

### 算法专题

| 专题 | 目录 | 包含内容 |
|------|------|---------|
| 二分查找 | `Competitive-Programming-Code/Algorithms/Binary_Search/` | 整数二分模板 |
| 深度优先搜索 | `Competitive-Programming-Code/Algorithms/DFS/` | 全排列、指数型枚举、组合 DFS |
| 图论 | `Competitive-Programming-Code/Algorithms/Graph/` | Tarjan 强连通分量（SCC）|
| 区间合并 | `Competitive-Programming-Code/Algorithms/IntervalMerging/` | 贪心区间处理、区间合并与剩余区间 |

---

## 🤖 Pattern Recognition（模式识别课程）

基于 Python 实现的模式识别算法，对应课程各章节实验内容。

### 环境依赖

```bash
pip install numpy opencv-python matplotlib sympy scikit-learn
```

### 代码说明

| 文件 | 主要内容 |
|------|---------|
| `1.py` | 极限计算（sympy 符号运算）|
| `2.2.py` ~ `2.8.py` | 第 2 章：概率与统计基础 |
| `3.8.py` ~ `3.11.py` | 第 3 章：图像复原（运动模糊 PSF、CLS 去模糊）|
| `5.9.py` / `5.91.py` | 第 5 章：分类器设计 |
| `6.4.py` / `write_6.4.py` | 第 6 章实验 |
| `7.1.py` ~ `7.6.py` | 第 7 章实验 |
| `8.2.py` ~ `8.7.py` | 第 8 章实验 |
| `9.py` ~ `9.4.py` | 第 9 章实验 |
| `noise+filter.py` | 图像加噪与滤波处理 |

> **运动模糊复原**（`3.11.py`）：利用 PSF 模拟运动模糊，叠加高斯噪声后使用 **CLS（约束最小二乘）滤波器** 进行图像去模糊复原。

---

## 🖧 NetworkCourseDesign（计算机网络课程设计）

模拟**矿井安全监控系统**，基于 C/S 架构实现上下位机网络通信，包含传感器数据上报、异常报警、继电器控制、时钟校正等功能。

### 版本说明

| 版本 | 文件 | 语言 | 端口 | 说明 |
|------|------|------|------|------|
| v2（当前）| `v2/client.cpp` + `v2/server.py` | C++ / Python | 12345 | C++ 下位机 + Python 上位机 |
| v1（早期）| `v1/sever.py` + `v1/user.py` | Python / Python | 50000 | 纯 Python C/S 实现 |

### 通信协议（v2）

| 方向 | 格式 |
|------|------|
| 下位机 → 上位机（上报）| `TIME:<ts>,METHANE:<val>,TEMP:<val>,OXYGEN:<val>,FAN:<val>,POWER:<val>,...` |
| 上位机 → 下位机（指令）| `<fan>#<time_correct>#<relay_main>#<relay_trans>#<fan_state>#` |
| 下位机 → 上位机（回执）| `<alarm1>#<alarm2>` |

> 📌 `client.cpp` 已从原 GBK 编码转换为 **UTF-8**，编译时建议添加 `/utf-8`（MSVC）或 `-finput-charset=utf-8`（MinGW/GCC）选项。

---

## 🛠️ 开发环境

| 工具 | 说明 |
|------|------|
| 编译器 | GCC / MinGW（C++17）|
| Python | 3.x |
| IDE | VSCode / CLion / PyCharm |

---

## 📌 备注

- 竞赛代码以 **C++** 为主，课程实验以 **Python** 为主。
- 各代码仅供学习参考，如有错误欢迎提 Issue 或 PR。
- Pattern Recognition 图片资源位于 `Pattern Recognition/picture/`，运行前请确认路径是否正确。

---

<p align="center">
  <img src="https://img.shields.io/badge/language-C%2B%2B%20%7C%20Python-blue" alt="language"/>
  <img src="https://img.shields.io/badge/platform-Codeforces%20%7C%20AtCoder%20%7C%20AcWing%20%7C%20PTA-orange" alt="platform"/>
  <img src="https://img.shields.io/badge/license-MIT-green" alt="license"/>
</p>
