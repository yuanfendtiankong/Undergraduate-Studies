#include <bits/stdc++.h>
#define ll long long
using namespace std;

// 矩阵定义
struct MAT
{
    ll rows, cols;
    vector<vector<ll>> data;

    MAT() = default;
    MAT(ll rows, ll cols) : rows(rows),
                            cols(cols),
                            data(rows, vector<ll>(cols, 0))
    {
    }
};

// 矩阵乘法
MAT mul(const MAT &x, const MAT &y)
{

    MAT z(x.rows, y.cols);

    for (int i = 0; i < x.rows; i++)
    {
        for (int k = 0; k < x.cols; k++)
        {
            for (int j = 0; j < y.cols; j++)
            {
                z.data[i][j] += x.data[i][k] * y.data[k][j];
            }
        }
    }
    return z;
}

// 单位矩阵
MAT ident(ll sz)
{
    MAT I(sz, sz);
    for (int i = 0; i < sz; i++)
    {
        I.data[i][i] = 1;
    }
    return I;
}

// 矩阵快速幂
MAT qpow(MAT base, ll exp)
{
    MAT res = ident(base.rows);
    while (exp > 0)
    {
        if (exp & 1)
            res = mul(res, base);
        base = mul(base, base);
        exp >>= 1;
    }
    return res;
}

int main()
{
    int n, m, t, act;
    cin >> n >> m >> t >> act;

    // 该vector存放网格的操作序列
    vector<string> s(n + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        // cout << s[i] << endl;
    }

    // 该vect存放至多十种操作序列
    vector<string> op(10);
    for (int i = 0; i < act; i++)
    {
        cin >> op[i];
        // cout << op[i] << endl;
    }

    // 该vector存放展开成一维的网格对应的操作序列
    vector<ll> oneOp((n * m) + 1, 0);
    // cout << s[0] << endl;
    int idx = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            oneOp[idx] = (int)(s[i][j] - '0');
            idx++;
            // cout << oneOp[idx-1];
        }
        // cout << endl;
    }

    // 这里要开始写矩阵了
    // sz是单秒矩阵的边界大小
    ll sz = n * m + 1;
    // 开一个循环的三维，存放60秒完整循环的矩阵。
    vector<MAT> A(60);
    for (int time = 0; time < 60; time++)
    {
        // 开一个单秒矩阵
        MAT oneSecond(sz, sz);
        // 石头源为 1
        oneSecond.data[0][0] = 1;
        // 外层循环对每一列进行处理
        // 即单秒共sz个位置应该如何变化的sz行1列矩阵组成的sz*sz的矩阵
        for (int i = 1; i < sz; i++)
        { // 这里特殊的，要跳过第0列，因为第0个格子始终为石头源1
            string ops = op[oneOp[i]];
            // 这里开始读取当前秒数t，进行状态分解。
            char ch = ops[time % ops.size()];
            oneSecond.data[i][i] = 1;
            if (ch >= '0' && ch <= '9')
            {
                oneSecond.data[0][i] += (int)(ch - '0');
            }
            else
            {
                // 'D'的情况只消除即可不用特殊处理
                oneSecond.data[i][i] = 0;
                if (ch == 'N')
                {
                    // 如果不是上临边界行
                    if (i - m >= 1)
                    {
                        oneSecond.data[i][i - m] += 1;
                    }
                }
                if (ch == 'W')
                {
                    // 如果不是左临边界行
                    if ((i - 1) % m != 0)
                    {
                        oneSecond.data[i][i - 1] += 1;
                    }
                }
                if (ch == 'S')
                {
                    // 如果不是上临边界行
                    if (i + m <= n * m)
                    {
                        oneSecond.data[i][i + m] += 1;
                    }
                }
                if (ch == 'E')
                {
                    if (i % m != 0)
                    {
                        oneSecond.data[i][i + 1] += 1;
                    }
                }
            }
        }
        A[time] = oneSecond;
    }

    // 开一个单位矩阵，开始计算一个大周期的变化。
    MAT all = ident(sz);
    for (int i = 0; i < 60; i++)
    {
        all = mul(all, A[i]);
    }

    // 拆时间
    ll q = t / 60;
    ll r = t % 60;

    // 补剩余r秒
    MAT lease = ident(sz);
    for (int i = 0; i < r; i++)
    {
        lease = mul(lease, A[i]);
    }

    // 总的
    MAT sum = mul(qpow(all, q), lease);

    // 遍历一遍找答案
    ll ans = 0;
    for (int i = 1; i < sz; i++)
    {
        ans = max(ans, sum.data[0][i]);
    }
    cout << ans << endl;
}
