#include <bits/stdc++.h>
using namespace std;

struct Lift {
    int N, L, timer = 0;
    vector<vector<int>> A, P;
    vector<int> tin, tout;
    Lift(int N): N(N), A(N), tin(N), tout(N) {
        L = ceil(log2(N))+1;
        P.resize(N, vector<int>(L));
    }
    void add(int i, int j) { A[i].push_back(j), A[j].push_back(i); }
    void dfs(int i, int p = -1) {
        tin[i] = timer++;
        P[i][0] = p >= 0 ? p : i;
        for (int k = 1; k < L; ++k) {
            P[i][k] = P[P[i][k-1]][k-1];
        }
        for (int j: A[i]) {
            if (j == p) continue;
            dfs(j, i);
        }
        tout[i] = timer++;
    }
    bool is_ans(int a, int i) {
        return tin[a] <= tin[i] && tout[i] <= tout[a];
    }
    int lca(int i, int j) {
        if (is_ans(i, j)) return i;
        if (is_ans(j, i)) return j;
        return P[top_before(i, j)][0];
    }
    int top_before(int i, int a) {
        for (int k = L-1; k >= 0; --k) {
            if (!is_ans(P[i][k], a)) i = P[i][k];
        }
        return i;
    }
};

using pii = pair<int, int>;

// Count pairs of overlapping paths

const int N = 2e5+5;
int n, m, pre[N];
long long res = 0;
Lift g(N);
vector<pii> edges;
map<pii, int> dup;

void dfs_pre(int i, int p = 0) {
    pre[i] += pre[p];
    for (int j: g.A[i]) {
        if (j == p) continue;
        dfs_pre(j, i);
    }
}

int main() {
    ifstream cin("exercise.in");
    ofstream cout("exercise.out");
    cin >> n >> m; m -= n-1;
    for (int e = 0; e < n-1; ++e) {
        int i, j; cin >> i >> j;
        g.add(i, j);
    }
    g.dfs(1);
    for (int e = 0; e < m; ++e) {
        int i, j; cin >> i >> j;
        edges.push_back({i, j});
        int a = g.lca(i, j), i0 = g.top_before(i, a), j0 = g.top_before(j, a);
        if (i0 != a) res -= ++pre[i0];  // avoid counting paths starting at the same point (n*(n-1)/2 == n*n - n*(n+1)/2)
        if (j0 != a) res -= ++pre[j0];
        if (i0 != a && j0 != a) {
            if (i0 > j0) swap(i0, j0);
            res -= dup[pii{i0, j0}]++;
        }
    }
    dfs_pre(1);
    for (auto [i, j]: edges) {
        int a = g.lca(i, j);
        res += pre[i] + pre[j] - 2*pre[a];
    }
    cout << res << endl;
}