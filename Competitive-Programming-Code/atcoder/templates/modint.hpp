#pragma once
#include <bits/stdc++.h>

// 轻量质数模数版；MOD 必须是质数，本类不检查素性。
template <int MOD>
class ModInt
{
    static_assert(2 <= MOD && MOD <= 1000000007, "unsupported modulus");
    int v;

public:
    ModInt(long long x = 0)
    {
        x %= MOD;
        if (x < 0) x += MOD;
        v = static_cast<int>(x);
    }

    int val() const { return v; }
    static constexpr int mod() { return MOD; }

    ModInt& operator+=(const ModInt& b)
    {
        v += b.v;
        if (v >= MOD) v -= MOD;
        return *this;
    }
    ModInt& operator-=(const ModInt& b)
    {
        v -= b.v;
        if (v < 0) v += MOD;
        return *this;
    }
    ModInt& operator*=(const ModInt& b)
    {
        v = static_cast<int>(1LL * v * b.v % MOD);
        return *this;
    }

    ModInt pow(long long exponent) const
    {
        assert(exponent >= 0);
        ModInt a = *this, answer = 1;
        while (exponent > 0)
        {
            if (exponent & 1) answer *= a;
            a *= a;
            exponent >>= 1;
        }
        return answer;
    }

    ModInt inv() const
    {
        assert(v != 0); // 0 没有逆元。
        return pow(MOD - 2);
    }

    ModInt& operator/=(const ModInt& b) { return *this *= b.inv(); }
    ModInt operator-() const { return ModInt(-v); }
    friend ModInt operator+(ModInt a, const ModInt& b) { return a += b; }
    friend ModInt operator-(ModInt a, const ModInt& b) { return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt& b) { return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt& b) { return a /= b; }
    friend bool operator==(const ModInt& a, const ModInt& b) { return a.v == b.v; }
    friend bool operator!=(const ModInt& a, const ModInt& b) { return !(a == b); }
};

// 阶乘 + 逆阶乘；只支持 0 <= n <= 预处理上限 < MOD。
template <int MOD>
class Combinations
{
    using mint = ModInt<MOD>;
    std::vector<mint> fact, inverse_fact;

public:
    explicit Combinations(int limit)
    {
        assert(0 <= limit && limit < MOD);
        fact.assign(limit + 1, 1);
        inverse_fact.assign(limit + 1, 1);
        for (int i = 1; i <= limit; ++i) fact[i] = fact[i - 1] * i;
        inverse_fact[limit] = fact[limit].inv();
        for (int i = limit; i >= 1; --i)
            inverse_fact[i - 1] = inverse_fact[i] * i;
    }

    mint C(int n, int k) const
    {
        assert(0 <= n && n < static_cast<int>(fact.size()));
        if (k < 0 || k > n) return 0;
        return fact[n] * inverse_fact[k] * inverse_fact[n - k];
    }
};
