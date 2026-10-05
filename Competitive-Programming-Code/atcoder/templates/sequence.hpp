#pragma once
#include <bits/stdc++.h>

// 最长上升子序列长度，默认严格递增；false 表示非递减（允许相等）。
template <class T>
int lis_length(const std::vector<T>& a, bool strict = true)
{
    std::vector<T> tails;
    for (const T& x : a)
    {
        auto it = strict ? std::lower_bound(tails.begin(), tails.end(), x)
                         : std::upper_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return static_cast<int>(tails.size());
}

// 单调栈：每个位置左侧最近的、严格小于它的元素下标；没有则为 -1。
template <class T>
std::vector<int> previous_less(const std::vector<T>& a)
{
    std::vector<int> answer(a.size(), -1), stack;
    for (int i = 0; i < static_cast<int>(a.size()); ++i)
    {
        while (!stack.empty() && a[stack.back()] >= a[i]) stack.pop_back();
        if (!stack.empty()) answer[i] = stack.back();
        stack.push_back(i);
    }
    return answer;
}
