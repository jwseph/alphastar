#include <bits/stdc++.h>
using namespace std;

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
    T f(T a, T b) { return max(a, b); }
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
    void update(int i, int j, int v) {
        tr.update(max(V[i], V[j]), v);
    }
    T query(int i, int j) {
        T res = tr.def;
        while (R[i] != R[j]) {
            if (D[R[i]] < D[R[j]]) swap(i, j);
            res = tr.f(res, tr.query(V[R[i]], V[i]+1));
            i = P[R[i]];
        }
        if (D[i] < D[j]) swap(i, j);
        res = tr.f(res, tr.query(V[j]+1, V[i]+1));
        return res;
    }
};

const int N = 2e5+5;
int n, m, nq;
DSU dsu(N);
HeavyLight<int> hl(N+1);
vector<array<int, 3>> updates;

int main() {
    cin >> n >> m >> nq;
    for (int e = 0; e < m; ++e) {
        int i, j; cin >> i >> j;
        if (dsu.find(i) == dsu.find(j)) continue;
        dsu.unite(i, j);
        hl.add(i, j);
        updates.push_back({i, j, e});
    }
    for (int i = 1; i <= n; ++i) {
        if (i != dsu.find(i)) continue;
        hl.dfs_sz(i), hl.dfs_hl(i);
    }
    for (auto [i, j, e]: updates) {
        hl.update(i, j, e+1);
    }
    for (int q = 0; q < nq; ++q) {
        int i, j; cin >> i >> j;
        cout << (dsu.find(i) == dsu.find(j) ? hl.query(i, j) : -1) << endl;
    }
}