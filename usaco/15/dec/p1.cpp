#include <bits/stdc++.h>
using namespace std;

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

const int N = 5e4+5;
int n, k;
Lift g(N);
int res[N], pre[N];

int dfs(int i) {
    for (int j: g.a[i]) {
        if (j == g.p[i][0]) continue;
        pre[i] += dfs(j);
    }
    res[i] += pre[i];
    return pre[i];
}

int main() {
    ifstream cin("maxflow.in");
    ofstream cout("maxflow.out");
    cin >> n >> k;
    for (int e = 0; e < n-1; ++e) {
        int i, j; cin >> i >> j;
        g.add(i, j);
    }
    g.dfs(1);
    for (int e = 0; e < k; ++e) {
        int i, j; cin >> i >> j;
        int a = g.lca(i, j);
        pre[i]++;
        pre[j]++;
        pre[a] -= 2;
        res[a]++;
    }
    dfs(1);
    cout << *max_element(res+1, res+n+1) << endl;
}