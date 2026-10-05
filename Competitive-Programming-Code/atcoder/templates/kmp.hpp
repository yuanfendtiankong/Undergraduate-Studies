#pragma once
#include <bits/stdc++.h>

// 固定非空模式串，可在多个文本中查找；保留重叠匹配。
class KMP
{
    std::string pattern;
    std::vector<int> pi;

public:
    explicit KMP(std::string s) : pattern(std::move(s)), pi(pattern.size(), 0)
    {
        assert(!pattern.empty());
        for (int i = 1; i < static_cast<int>(pattern.size()); ++i)
        {
            int j = pi[i - 1];
            while (j > 0 && pattern[i] != pattern[j]) j = pi[j - 1];
            if (pattern[i] == pattern[j]) ++j;
            pi[i] = j;
        }
    }

    std::vector<int> find_all(const std::string& text) const
    {
        std::vector<int> positions;
        int j = 0, m = static_cast<int>(pattern.size());
        for (int i = 0; i < static_cast<int>(text.size()); ++i)
        {
            while (j > 0 && text[i] != pattern[j]) j = pi[j - 1];
            if (text[i] == pattern[j]) ++j;
            if (j == m)
            {
                positions.push_back(i - m + 1);
                j = pi[j - 1];
            }
        }
        return positions;
    }
};
