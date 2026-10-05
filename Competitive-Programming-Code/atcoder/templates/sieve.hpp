#pragma once
#include <bits/stdc++.h>

// 线性筛；factorize 只能分解不超过预处理上限的正整数。
class PrimeSieve
{
    int n;
    std::vector<int> least, primes;

public:
    explicit PrimeSieve(int limit) : n(limit), least(n + 1, 0)
    {
        assert(n >= 0);
        for (int i = 2; i <= n; ++i)
        {
            if (least[i] == 0) { least[i] = i; primes.push_back(i); }
            for (int p : primes)
            {
                if (1LL * p * i > n) break;
                least[p * i] = p;
                if (p == least[i]) break;
            }
        }
    }

    bool is_prime(int x) const
    {
        assert(0 <= x && x <= n);
        return x >= 2 && least[x] == x;
    }

    std::vector<std::pair<int, int>> factorize(int x) const
    {
        assert(1 <= x && x <= n);
        std::vector<std::pair<int, int>> answer;
        while (x > 1)
        {
            int p = least[x], count = 0;
            do { x /= p; ++count; } while (x % p == 0);
            answer.push_back({p, count});
        }
        return answer; // 1 的质因数分解为空。
    }

    const std::vector<int>& prime_list() const { return primes; }
};
