#include "basic.hpp"
#include "dsu.hpp"
#include "fenwick.hpp"
#include "segtree.hpp"
#include "lazy_segtree.hpp"
#include "modint.hpp"
#include "graph.hpp"
#include "lca.hpp"
#include "sieve.hpp"
#include "kmp.hpp"
#include "sequence.hpp"
using namespace std;
using ll = long long;

mt19937 rng(20260926);
long long checks = 0;
void check(bool ok, const char* expression, int line)
{
    ++checks;
    if (!ok)
    {
        cerr << "FAIL line " << line << ": " << expression << '\n';
        exit(1);
    }
}
#define CHECK(...) check((__VA_ARGS__), #__VA_ARGS__, __LINE__)
int rnd(int lo, int hi) { return uniform_int_distribution<int>(lo, hi)(rng); }
ll sum_op(ll a, ll b) { return a + b; }
ll sum_e() { return 0; }
ll min_op(ll a, ll b) { return min(a, b); }
ll min_e() { return LLONG_MAX; }
string concat_op(string a, string b) { return a + b; }
string concat_e() { return ""; }

void test_basic()
{
    for (int n = 0; n <= 30; ++n)
    {
        vector<ll> a(n);
        for (ll& x : a) x = rnd(-50, 50);
        PrefixSum<ll> pre(a);
        for (int l = 0; l <= n; ++l)
            for (int r = l; r <= n; ++r)
                CHECK(pre.sum(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
        Difference<ll> diff(n);
        vector<ll> expected(n, 0);
        for (int q = 0; q < 100; ++q)
        {
            int l = rnd(0, n), r = rnd(l, n), delta = rnd(-30, 30);
            diff.add(l, r, delta);
            for (int i = l; i < r; ++i) expected[i] += delta;
        }
        CHECK(diff.values() == expected);
        CHECK(diff.values() == expected); // 还原不会消耗差分数组。
        Compressor<ll> comp(a);
        set<ll> distinct(a.begin(), a.end());
        CHECK(comp.size() == static_cast<int>(distinct.size()));
        for (ll x : a)
        {
            CHECK(comp.value(comp.index(x)) == x);
            CHECK(comp.index(x) == distance(distinct.begin(), distinct.find(x)));
        }
        for (ll x = -60; x <= 60; ++x)
            CHECK(comp.lower_bound(x) == count_if(distinct.begin(), distinct.end(),
                                                  [x](ll value) { return value < x; }));
        for (int threshold = 0; threshold <= n + 1; ++threshold)
            CHECK(first_true(0, n, [threshold](ll x) { return x >= threshold; })
                  == min(threshold, n));
    }
    int calls = 0;
    CHECK(first_true(3, 3, [&](ll) { ++calls; return true; }) == 3 && calls == 0);
    CHECK(first_true(0, LLONG_MAX, [](ll x) { return x >= LLONG_MAX - 7; }) == LLONG_MAX - 7);
    CHECK(first_true(0, LLONG_MAX, [](ll) { return false; }) == LLONG_MAX);
    for (int h = 0; h <= 8; ++h)
        for (int w = 0; w <= (h == 0 ? 0 : 8); ++w)
        {
            vector<vector<ll>> a(h, vector<ll>(w));
            for (auto& row : a) for (ll& x : row) x = rnd(-20, 20);
            PrefixSum2D<ll> pre(a);
            for (int q = 0; q < 100; ++q)
            {
                int r1 = rnd(0, h), r2 = rnd(r1, h), c1 = rnd(0, w), c2 = rnd(c1, w);
                ll expected = 0;
                for (int i = r1; i < r2; ++i)
                    for (int j = c1; j < c2; ++j) expected += a[i][j];
                CHECK(pre.sum(r1, c1, r2, c2) == expected);
            }
        }
}

void test_dsu()
{
    CHECK(DSU(0).count() == 0);
    for (int trial = 0; trial < 60; ++trial)
    {
        int n = rnd(1, 20);
        DSU d(n);
        vector<vector<int>> adj(n);
        auto reachable = [&](int source)
        {
            vector<int> visited(n, 0), queue{source};
            visited[source] = 1;
            for (int i = 0; i < static_cast<int>(queue.size()); ++i)
                for (int v : adj[queue[i]])
                    if (!visited[v]) { visited[v] = 1; queue.push_back(v); }
            return visited;
        };
        for (int q = 0; q < 100; ++q)
        {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            auto before = reachable(u);
            CHECK(d.merge(u, v) == !before[v]);
            adj[u].push_back(v);
            adj[v].push_back(u);
            auto after = reachable(u);
            CHECK(d.size(u) == accumulate(after.begin(), after.end(), 0));
            for (int x = 0; x < n; ++x) CHECK(d.same(u, x) == (after[x] != 0));
            int count = 0;
            vector<int> seen(n, 0);
            for (int x = 0; x < n; ++x)
                if (!seen[x])
                {
                    ++count;
                    auto component = reachable(x);
                    for (int y = 0; y < n; ++y) seen[y] |= component[y];
                }
            CHECK(d.count() == count);
        }
    }
}

void test_fenwick()
{
    Fenwick<ll> empty(0);
    CHECK(empty.sum(0, 0) == 0);
    for (int trial = 0; trial < 80; ++trial)
    {
        int n = rnd(1, 50);
        vector<ll> a(n);
        for (ll& x : a) x = rnd(-100, 100);
        Fenwick<ll> bit(a);
        for (int q = 0; q < 200; ++q)
        {
            if (rnd(0, 1))
            {
                int p = rnd(0, n - 1), delta = rnd(-100, 100);
                a[p] += delta;
                bit.add(p, delta);
            }
            int l = rnd(0, n), r = rnd(l, n);
            CHECK(bit.sum(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
            CHECK(bit.prefix(r) == accumulate(a.begin(), a.begin() + r, 0LL));
        }
    }
}

void test_segtree()
{
    SegTree<ll, sum_op, sum_e> empty(0);
    CHECK(empty.prod(0, 0) == 0 && empty.all_prod() == 0);
    for (int trial = 0; trial < 80; ++trial)
    {
        int n = rnd(1, 50);
        vector<ll> a(n);
        for (ll& x : a) x = rnd(-100, 100);
        SegTree<ll, sum_op, sum_e> sum(a);
        SegTree<ll, min_op, min_e> minimum(a);
        for (int q = 0; q < 200; ++q)
        {
            int p = rnd(0, n - 1);
            a[p] = rnd(-100, 100);
            sum.set(p, a[p]);
            minimum.set(p, a[p]);
            CHECK(sum.get(p) == a[p]);
            int l = rnd(0, n), r = rnd(l, n);
            CHECK(sum.prod(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
            CHECK(minimum.prod(l, r) == (l == r ? LLONG_MAX : *min_element(a.begin() + l, a.begin() + r)));
            CHECK(sum.all_prod() == accumulate(a.begin(), a.end(), 0LL));
        }
    }
    // 字符串拼接满足结合律但不满足交换律，用来检查查询方向。
    vector<string> a{"a", "bc", "d", "ef", "g"};
    SegTree<string, concat_op, concat_e> seg(a);
    seg.set(2, "XYZ");
    a[2] = "XYZ";
    for (int l = 0; l <= 5; ++l)
        for (int r = l; r <= 5; ++r)
            CHECK(seg.prod(l, r) == accumulate(a.begin() + l, a.begin() + r, string{}));
}

void test_lazy()
{
    RangeAddSum empty(0);
    empty.add(0, 0, 42);
    CHECK(empty.sum(0, 0) == 0);
    for (int trial = 0; trial < 80; ++trial)
    {
        int n = rnd(1, 50);
        vector<ll> a(n);
        for (ll& x : a) x = rnd(-100, 100);
        RangeAddSum seg(a);
        for (int q = 0; q < 200; ++q)
        {
            int l = rnd(0, n), r = rnd(l, n), delta = rnd(-30, 30);
            seg.add(l, r, delta);
            for (int i = l; i < r; ++i) a[i] += delta;
            l = rnd(0, n); r = rnd(l, n);
            CHECK(seg.sum(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
            CHECK(seg.sum(0, n) == accumulate(a.begin(), a.end(), 0LL));
        }
    }
    RangeAddSum large(vector<ll>{1000000000000LL, 1000000000000LL});
    large.add(0, 2, 1000000000000LL);
    CHECK(large.sum(0, 2) == 4000000000000LL);
}

void test_modint()
{
    using mint = ModInt<101>;
    auto normalize = [](ll x) { return (x % 101 + 101) % 101; };
    for (int a = -110; a <= 110; ++a)
        for (int b = -15; b <= 15; ++b)
        {
            CHECK((mint(a) + mint(b)).val() == normalize(a + b));
            CHECK((mint(a) - mint(b)).val() == normalize(a - b));
            CHECK((mint(a) * mint(b)).val() == normalize(1LL * a * b));
            if (normalize(b) != 0)
            {
                int inverse = 1;
                while (normalize(1LL * b * inverse) != 1) ++inverse;
                CHECK((mint(a) / mint(b)).val() == normalize(1LL * a * inverse));
            }
        }
    for (int a = -10; a <= 10; ++a)
    {
        ll expected = 1;
        for (int exponent = 0; exponent <= 30; ++exponent)
        {
            CHECK(mint(a).pow(exponent).val() == expected);
            expected = normalize(expected * a);
        }
        CHECK((-mint(a)).val() == normalize(-a));
    }
    Combinations<101> comb(60);
    vector<vector<int>> pascal(61, vector<int>(61, 0));
    for (int n = 0; n <= 60; ++n)
    {
        pascal[n][0] = pascal[n][n] = 1;
        for (int k = 1; k < n; ++k) pascal[n][k] = (pascal[n - 1][k - 1] + pascal[n - 1][k]) % 101;
        for (int k = -1; k <= n + 1; ++k)
            CHECK(comb.C(n, k).val() == (k < 0 || k > n ? 0 : pascal[n][k]));
    }
    CHECK(Combinations<2>(0).C(0, 0).val() == 1);
    CHECK(Combinations<2>(1).C(1, 1).val() == 1);
    CHECK(ModInt<1000000007>(LLONG_MIN).val() == (LLONG_MIN % 1000000007 + 1000000007) % 1000000007);
    CHECK((ModInt<1000000007>(1000000006) * 1000000006).val() == 1);
    CHECK((ModInt<998244353>(998244352) + 998244352).val() == 998244351);
    CHECK(Combinations<998244353>(100).C(5, 2).val() == 10);
}

void test_graph()
{
    CHECK(Graph(0).topological_sort().empty());
    constexpr ll unreachable = 1000000000000LL;
    for (int trial = 0; trial < 100; ++trial)
    {
        int n = rnd(1, 12);
        bool directed = trial % 2;
        Graph graph(n);
        Dijkstra weighted(n);
        vector<vector<ll>> dist(n, vector<ll>(n, unreachable));
        vector<vector<int>> steps(n, vector<int>(n, 1000000)), reach(n, vector<int>(n, 0));
        vector<pair<int, int>> edges;
        for (int i = 0; i < n; ++i) dist[i][i] = steps[i][i] = 0;
        int m = rnd(0, n * n);
        for (int i = 0; i < m; ++i)
        {
            int u = rnd(0, n - 1), v = rnd(0, n - 1), w = rnd(0, 30);
            graph.add_edge(u, v, directed);
            weighted.add_edge(u, v, w, directed);
            edges.push_back({u, v});
            dist[u][v] = min(dist[u][v], static_cast<ll>(w));
            steps[u][v] = min(steps[u][v], 1);
            reach[u][v] = 1;
            if (!directed)
            {
                dist[v][u] = min(dist[v][u], static_cast<ll>(w));
                steps[v][u] = min(steps[v][u], 1);
                reach[v][u] = 1;
            }
        }
        for (int k = 0; k < n; ++k)
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    steps[i][j] = min(steps[i][j], steps[i][k] + steps[k][j]);
                    reach[i][j] |= reach[i][k] && reach[k][j];
                }
        for (int source = 0; source < n; ++source)
        {
            auto actual = weighted.run(source);
            auto bfs = graph.bfs(source);
            for (int v = 0; v < n; ++v)
            {
                CHECK(actual[v] == (dist[source][v] == unreachable ? Dijkstra::INF : dist[source][v]));
                CHECK(bfs[v] == (steps[source][v] == 1000000 ? -1 : steps[source][v]));
            }
        }
        if (directed)
        {
            bool cycle = false;
            for (int i = 0; i < n; ++i) cycle |= reach[i][i] != 0;
            auto order = graph.topological_sort();
            CHECK((static_cast<int>(order.size()) < n) == cycle);
            if (!cycle)
            {
                vector<int> rank(n);
                for (int i = 0; i < n; ++i) rank[order[i]] = i;
                for (auto [u, v] : edges) CHECK(rank[u] < rank[v]);
            }
        }
    }
    Dijkstra huge(3);
    huge.add_edge(0, 1, Dijkstra::INF - 2, true);
    huge.add_edge(1, 2, 1, true);
    huge.add_edge(2, 0, Dijkstra::INF - 1, true);
    CHECK(huge.run(0)[2] == Dijkstra::INF - 1);
}

void test_lca()
{
    for (int trial = 0; trial < 80; ++trial)
    {
        int n = rnd(1, 40);
        LCA tree(n);
        vector<vector<int>> adj(n);
        for (int v = 1; v < n; ++v)
        {
            int u = rnd(0, v - 1);
            tree.add_edge(u, v);
            adj[u].push_back(v); adj[v].push_back(u);
        }
        for (int pass = 0; pass < 2; ++pass)
        {
            int root = rnd(0, n - 1);
            tree.build(root);
            vector<int> parent(n, -1), depth(n, -1), queue{root};
            depth[root] = 0;
            for (int i = 0; i < static_cast<int>(queue.size()); ++i)
                for (int v : adj[queue[i]])
                    if (depth[v] == -1)
                    {
                        parent[v] = queue[i];
                        depth[v] = depth[queue[i]] + 1;
                        queue.push_back(v);
                    }
            for (int q = 0; q < 100; ++q)
            {
                int u = rnd(0, n - 1), v = rnd(0, n - 1), k = rnd(0, n + 1);
                set<int> ancestors;
                for (int x = u; x != -1; x = parent[x]) ancestors.insert(x);
                int answer = v;
                while (!ancestors.count(answer)) answer = parent[answer];
                CHECK(tree.query(u, v) == answer);
                CHECK(tree.distance(u, v) == depth[u] + depth[v] - 2 * depth[answer]);
                int ancestor = u;
                for (int step = 0; step < k && ancestor != -1; ++step) ancestor = parent[ancestor];
                CHECK(tree.jump(u, k) == ancestor);
            }
        }
    }
    LCA chain(100000);
    for (int v = 1; v < 100000; ++v) chain.add_edge(v - 1, v);
    chain.build();
    CHECK(chain.distance(0, 99999) == 99999);
    CHECK(chain.query(12345, 99999) == 12345);
}

void test_sieve()
{
    CHECK(PrimeSieve(0).prime_list().empty());
    PrimeSieve sieve(2000);
    vector<int> expected_primes;
    for (int x = 0; x <= 2000; ++x)
    {
        bool prime = x >= 2;
        for (int p = 2; p * p <= x; ++p) if (x % p == 0) prime = false;
        CHECK(sieve.is_prime(x) == prime);
        if (prime) expected_primes.push_back(x);
        if (x == 0) continue;
        vector<pair<int, int>> factors;
        int remaining = x;
        for (int p = 2; p <= remaining; ++p)
        {
            if (remaining % p != 0) continue;
            int exponent = 0;
            while (remaining % p == 0) { remaining /= p; ++exponent; }
            factors.push_back({p, exponent});
        }
        CHECK(sieve.factorize(x) == factors);
    }
    CHECK(sieve.prime_list() == expected_primes);
}

void test_kmp()
{
    CHECK(KMP("aa").find_all("aaaa") == vector<int>({0, 1, 2}));
    CHECK(KMP("abc").find_all("").empty());
    for (int trial = 0; trial < 1200; ++trial)
    {
        string text(rnd(0, 80), 'a'), pattern(rnd(1, 12), 'a');
        for (char& c : text) c = static_cast<char>('a' + rnd(0, 2));
        for (char& c : pattern) c = static_cast<char>('a' + rnd(0, 2));
        vector<int> expected;
        for (int p = 0; p + static_cast<int>(pattern.size()) <= static_cast<int>(text.size()); ++p)
            if (text.compare(p, pattern.size(), pattern) == 0) expected.push_back(p);
        CHECK(KMP(pattern).find_all(text) == expected);
    }
}

void test_sequence()
{
    CHECK(lis_length(vector<int>{}) == 0);
    CHECK(previous_less(vector<int>{}).empty());
    for (int trial = 0; trial < 300; ++trial)
    {
        int n = rnd(1, 50);
        vector<int> a(n);
        for (int& x : a) x = rnd(-10, 10);
        for (bool strict : {true, false})
        {
            vector<int> dp(n, 1);
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < i; ++j)
                    if (strict ? a[j] < a[i] : a[j] <= a[i]) dp[i] = max(dp[i], dp[j] + 1);
            CHECK(lis_length(a, strict) == *max_element(dp.begin(), dp.end()));
        }
        vector<int> expected(n, -1);
        for (int i = 0; i < n; ++i)
            for (int j = i - 1; j >= 0; --j)
                if (a[j] < a[i]) { expected[i] = j; break; }
        CHECK(previous_less(a) == expected);
    }
}

int main()
{
    vector<pair<string, void (*)()>> tests{
        {"basic", test_basic}, {"dsu", test_dsu}, {"fenwick", test_fenwick},
        {"segtree", test_segtree}, {"lazy_segtree", test_lazy}, {"modint", test_modint},
        {"graph", test_graph}, {"lca", test_lca}, {"sieve", test_sieve},
        {"kmp", test_kmp}, {"sequence", test_sequence}
    };
    for (const auto& [name, run] : tests)
    {
        run();
        cout << "PASS " << name << '\n';
    }
    cout << "All " << tests.size() << " groups passed; " << checks
         << " checks; seed=20260926\n";
}
