# 📦 MyCodeRepository

> 个人学习代码仓库，涵盖 **ACM 竞赛刷题**、**模式识别课程实验** 与 **计算机网络课程设计** 三大模块。

---

## 📁 目录结构

```
MyCodeRepository/
├── ACM/                          # ACM 竞赛练习代码
│   ├── PTA/                      # PTA 平台题目（C++）
│   ├── acwing/                   # AcWing 平台
│   │   ├── Weekly141/            # 第 141 场周赛
│   │   └── daily_problem/        # 每日一题
│   ├── atcoder/                  # AtCoder 平台（328 / 345 / 347 / 455 / 456 / 457 场）
│   ├── codeforces/               # Codeforces 平台
│   │   ├── div2/                 # Div.2 场次（1946 场等）
│   │   ├── div3/
│   │   ├── daily/
│   │   └── EDU/
│   ├── Algorithms/               # 算法专题练习
│   │   ├── DFS/                  # 深度优先搜索
│   │   └── IntervalMerging/      # 区间合并（贪心）
│   └── NetworkCourseDesign/      # 计算机网络课程设计
│       ├── client.cpp            # 下位机客户端（C++，Winsock）
│       ├── server.py             # 上位机服务端（Python，v2）
│       └── v1_legacy/            # 早期 Python 版本
│           ├── sever.py          # 早期服务端
│           └── user.py           # 早期客户端
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
| [PTA](https://pintia.cn/) | `ACM/PTA/` | C++ | 国内 OJ，含 PAT / 天梯赛题库 |
| [AcWing](https://www.acwing.com/) | `ACM/acwing/` | C++ | 周赛 & 每日一题 |
| [AtCoder](https://atcoder.jp/) | `ACM/atcoder/` | C++ | 日本 OJ，328 ~ 457 场 |
| [Codeforces](https://codeforces.com/) | `ACM/codeforces/` | C++ | Div.2 / Div.3 / EDU / 每日题 |

### 算法专题

| 专题 | 目录 | 包含内容 |
|------|------|---------|
| 深度优先搜索 | `ACM/Algorithms/DFS/` | 全排列、指数型枚举、组合 DFS |
| 区间合并 | `ACM/Algorithms/IntervalMerging/` | 贪心区间处理 |

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
| v2（当前）| `client.cpp` + `server.py` | C++ / Python | 12345 | C++ 下位机 + Python 上位机 |
| v1（早期）| `v1_legacy/sever.py` + `v1_legacy/user.py` | Python / Python | 50000 | 纯 Python C/S 实现 |

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
| 构建工具 | Code::Blocks（部分题目）|

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
