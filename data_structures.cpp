#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<class K, class V> using umap = unordered_map<K, V, chash>;
template<class K> using uset = unordered_set<K, chash>;
template<class K> using heap = priority_queue<K, vector<K>, greater<>>;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class K> using oset = tree<K, null_type, less<K>, rb_tree_tag, tree_order_statistics_node_update>; // i == order_of_key(v), v == *find_by_order(i)
template<class K, class V> using hmap = gp_hash_table<K, V, chash>;

struct DSU {
    vector<int> p;
    DSU(int n) { p.assign(n, -1); }
    int size(int i) { return -p[find(i)]; }
    int find(int i) { return p[i] < 0 ? i : p[i] = find(p[i]); }
    int unite(int i, int j) {
        i = find(i), j = find(j);
        if (i == j) return i;
        if (p[i] > p[j]) swap(i, j);
        p[i] += p[j], p[j] = i;
        return i;
    }
};

template<class T>
struct Tree {
    static constexpr T def{};
    T f(T a, T b) { return a+b; }
    vector<T> t; int n;
    Tree(int n): t(2*n, def), n(n) {}
    void update(int i, T v) {
        for (t[i += n] = v; i /= 2;) t[i] = f(t[i*2], t[i*2+1]);
    }
    T query(int l, int r) {
        T al = def, ar = def;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l&1) al = f(al, t[l++]);
            if (r&1) ar = f(t[--r], ar);
        }
        return f(al, ar);
    }
};
struct Node {
    int w;
    Node(): w(0) {}
    Node(int w): w(w) {}
    friend Node operator+(const Node& a, const Node& b) {
        return {
            a.w+b.w
        };
    }
};


struct BIT {
    vector<ll> t; int n;
    BIT(int n): t(n), n(n) {}
    void update(int i, int v) {
        for (; i < n; i |= i+1) t[i] += v;
    }
    ll query(int r) {
        ll res = 0;
        for (r = max(0, min(n, r)); r; r &= r-1) res += t[r-1];
        return res;
    }
    ll query(int l, int r) {
        return query(r) - query(l);
    }
};

struct SCC {
    int N, NC = 0;
    vector<vector<int>> A[2];
    vector<int> C, O;
    vector<bool> V;
    SCC(int N): N(N), V(N), C(N, -1) {
        A[0].resize(N), A[1].resize(N);
    }
    void add(int i, int j) {
        A[0][i].push_back(j), A[1][j].push_back(i);
    }
    void dfs1(int i) {
        if (V[i]) return;
        V[i] = 1;
        for (int j: A[1][i]) dfs1(j);
        O.push_back(i);
    }
    void dfs2(int i, int c) {
        if (C[i] >= 0) return;
        C[i] = c;
        for (int j: A[0][i]) dfs2(j, c);
    }
    void sol() {
        for (int i = 0; i < N; ++i) dfs1(i);
        reverse(begin(O), end(O));
        for (int i: O) if (C[i] < 0) dfs2(i, NC++);
    }
};

struct Lift {
    int n, l, timer = 0;
    vector<vector<int>> a, p;
    vector<int> tin, tout;
    Lift(int n): n(n), a(n), tin(n), tout(n) {
        l = ceil(log2(n))+1;
        p.resize(n, vector<int>(l, -1));
    }
    void add(int i, int j) { a[i].push_back(j), a[j].push_back(i); }
    void dfs(int i) {
        tin[i] = ++timer;
        if (p[i][0] < 0) p[i][0] = i;
        for (int k = 1; k < l; ++k) {
            p[i][k] = p[p[i][k-1]][k-1];
        }
        for (int j: a[i]) {
            if (j == p[i][0]) continue;
            p[j][0] = i;
            dfs(j);
        }
        tout[i] = ++timer;
    }
    bool is_a(int a, int i) {
        return tin[a] <= tin[i] && tout[i] <= tout[a];
    }
    int top_before(int i, int j) {
        for (int k = l-1; k >= 0; --k) {
            if (!is_a(p[i][k], j)) i = p[i][k];
        }
        return i;
    }
    int lca(int i, int j) {
        if (is_a(i, j)) return i;
        if (is_a(j, i)) return j;
        return p[top_before(i, j)][0];
    }
};

template<class T>
struct HeavyLight {
    int N, timer = 0;
    vector<vector<int>> A;
    vector<int> P, D, sz, R, V;  // parent, depth, size, root, visit time
    Tree<T> tr;
    HeavyLight(int N): N(N), A(N), P(N), D(N), sz(N), V(N), tr(N) {
        for (int i = 0; i < N; ++i) R.push_back(i);
    }
    void add(int i, int j) { A[i].push_back(j), A[j].push_back(i); }
    void dfs_sz(int i, int p = -1) {
        sz[i] = 1;
        for (int j: A[i]) {
            if (j == p) continue;
            P[j] = i, D[j] = D[i]+1;
            dfs_sz(j, i);
            sz[i] += sz[j];
        }
    }
    void dfs_hl(int i, int p = -1) {
        V[i] = timer++;
        int k = -1;
        for (int& j: A[i]) {
            if (j == p) continue;
            if (k < 0 || sz[k] < sz[j]) {
                k = j;
                swap(j, A[i][0]);
            }
        }
        if (k >= 0) R[k] = R[i];
        for (int j: A[i]) {
            if (j == p) continue;
            dfs_hl(j, i);
        }
    }
    void update(int i, int v) {
        tr.update(V[i], v);
    }
    T query(int i, int j) {
        T res = tr.def;
        while (R[i] != R[j]) {
            if (D[R[i]] < D[R[j]]) swap(i, j);
            res = tr.f(res, tr.query(V[R[i]], V[i]+1));
            i = P[R[i]];
        }
        if (D[i] < D[j]) swap(i, j);
        res = tr.f(res, tr.query(V[j], V[i]+1));
        return res;
    }
};

struct Centroid {
    int n;
    vector<vector<int>> ad;
    vector<vector<pair<int, int>>> an;
    vector<int> sz, pa, dp;
    Centroid(int n): n(n), ad(n), an(n), sz(n), pa(n, -1), dp(n, 1e9) {}
    void add(int i, int j) { ad[i].push_back(j), ad[j].push_back(i); }
    #define ADJ for (int j: ad[i]) if (j != p && pa[j] < 0)
    int dfs_sz(int i, int p) {
        sz[i] = 1;
        ADJ sz[i] += dfs_sz(j, i);
        return sz[i];
    }
    int dfs_ce(int i, int p, int k) {
        ADJ if (sz[j] > k/2) return dfs_ce(j, i, k);
        return i;
    }
    void dfs(int i, int p, int a, int d) {
        an[i].push_back({a, d});
        ADJ dfs(j, i, a, d+1);
    }
    void build(int i, int p = -1) {
        i = dfs_ce(i, -1, dfs_sz(i, -1));
        pa[i] = p >= 0 ? p : i;
        dfs(i, -1, i, 0);  // UPDATE THIS
        ADJ build(j, i);
    }
    #undef ADJ
    void update(int i) {
        dp[i] = 0;
        for (auto [a, d]: an[i]) {
            dp[a] = min(dp[a], d);
        }
    }
    int query(int i) {
        int res = 1e9;
        for (auto [a, d]: an[i]) {
            res = min(res, d+dp[a]);
        }
        return res;
    }
};

struct Matrix: public vector<vector<ll>> {
    using T = ll;
    static constexpr T z = 0, o = 1;
    static T upd(T a, T b) { return a+b; }
    static T con(T a, T b) { return a*b; }
    int n, m;
    using R = vector<T>;
    Matrix(int n, int m): n(n), m(m), vector<R>(n, R(m, z)) {};
    Matrix(initializer_list<R> l): vector<R>(l) {};
    friend Matrix operator*(const Matrix& a, const Matrix& b) {
        int k = a[0].size(), n = a.size(), m = b[0].size();
        if (k != b.size()) cout << "invalid product dimensions" << endl;
        Matrix p(n, m);
        for (int r = 0; r < n; ++r) {
            for (int i = 0; i < n; ++i) {
                if (a[r][i] == z) continue;
                for (int c = 0; c < m; ++c) {
                    p[r][c] = upd(p[r][c], con(a[r][i], b[i][c]));
                }
            }
        }
        return p;
    }
    friend Matrix operator^(Matrix x, ll b) {
        int n = x.size();
        Matrix r(n, n);
        for (int i = 0; i < n; ++i) r[i][i] = o;
        while (b) {
            if (b&1) r = r*x;
            x = x*x;
            b >>= 1;
        }
        return r;
    }
};

struct Modular {
    int n;
    vector<ll> fac, inv;
    Modular(int n): n(n), fac(n+1), inv(n+1) {
        fac[0] = 1;
        for (int i = 1; i <= n; ++i) fac[i] = fac[i-1] * i % mod;
        inv[n] = exp(fac[n], mod-2);
        for (int i = n; i >= 1; --i) inv[i-1] = inv[i] * i % mod;
    }
    ll exp(ll a, ll b) {
        ll res = 1;
        while (b) {
            if (b&1) res *= a, res %= mod;
            a *= a, a %= mod;
            b >>= 1;
        }
        return res;
    }
    ll choose(int n, int k) {
        return fac[n] * inv[k] % mod * inv[n-k] % mod;
    }
};

struct Primes {
    int n;
    vector<int> lp, pr;
    Primes(int n): n(n), lp(n+1) {
        lp[1] = 1;
        for (int i = 2; i <= n; ++i) {
            if (!lp[i]) {
                lp[i] = i;
                pr.push_back(i);
            }
            for (int j = 0; i*pr[j] <= n && pr[j] <= lp[i]; ++j) {
                lp[i*pr[j]] = pr[j];
            }
        }
    }
};

// debugging tips
// - check no ; on for() one-liner
// - modulo 10^9+7?
// - try #define int long long
// - try #define endl '\n'
// - try a small checker program