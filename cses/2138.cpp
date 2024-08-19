#include <bits/stdc++.h>
using namespace std;

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

int n, m;
bitset<50001> res[50001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    SCC g(n);
    while (m--) {
        int i, j; cin >> i >> j; --i, --j;
        g.add(i, j);
    }
    g.sol();
    for (int i: g.O) {
        res[g.C[i]][i] = 1;
        for (int j: g.A[0][i]) {
            res[g.C[i]] |= res[g.C[j]];
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << res[g.C[i]].count() << ' ';
    }
    cout << endl;
}