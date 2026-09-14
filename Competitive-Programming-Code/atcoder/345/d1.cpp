#include <bits/stdc++.h>

using i64 = long long;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, H, W;
    std::cin >> N >> H >> W;

    std::vector<int> A(N), B(N);
    for (int i = 0; i < N; i++)
    {
        std::cin >> A[i] >> B[i];
    }

    std::vector f(H, std::vector<int>(W));

    std::vector<int> vis(N);
    auto dfs = [&](auto self, int x, int y) -> void
    {
        if (x == H)
        {
            std::cout << "Yes\n";
            std::exit(0);
        }
        if (y == W)
        {
            return self(self, x + 1, 0);
        }
        if (f[x][y])
        {
            return self(self, x, y + 1);
        }
        for (int i = 0; i < N; i++)
        {
            if (!vis[i])
            {
                vis[i] = 1;
                for (int t = 0; t < 2; t++)
                {
                    if (x + A[i] <= H && y + B[i] <= W)
                    {
                        int ok = 1;
                        for (int u = 0; u < A[i]; u++)
                        {
                            for (int v = 0; v < B[i]; v++)
                            {
                                if (f[x + u][y + v])
                                {
                                    ok = 0;
                                }
                            }
                        }
                        if (ok)
                        {
                            for (int u = 0; u < A[i]; u++)
                            {
                                for (int v = 0; v < B[i]; v++)
                                {
                                    f[x + u][y + v] = 1;
                                }
                            }
                            self(self, x, y + 1);
                            for (int u = 0; u < A[i]; u++)
                            {
                                for (int v = 0; v < B[i]; v++)
                                {
                                    f[x + u][y + v] = 0;
                                }
                            }
                        }
                    }
                    std::swap(A[i], B[i]);
                }
                vis[i] = 0;
            }
        }
    };
    dfs(dfs, 0, 0);

    std::cout << "No\n";

    return 0;
}