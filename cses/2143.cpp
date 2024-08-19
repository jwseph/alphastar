#include <bits/stdc++.h>
using namespace std;

struct SCC {
    int N, NC = 0;
    vector<vector<int>> A[2];
    vector<int> C, O;
    vector<bool> V;
    vector<set<int>> dag;
    SCC(int N): N(N), V(N), C(N, -1), dag(N) {
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
        for (int j: A[0][i]) {
            dfs2(j, c);
            if (c != C[j]) dag[c].insert(C[j]);
        }
    }
    void sol() {
        for (int i = 0; i < N; ++i) dfs1(i);
        reverse(begin(O), end(O));
        for (int i: O) if (C[i] < 0) dfs2(i, NC++);
    }
};

const int N = 5e4;
int n, m, q;
bool vst[N];
bitset<N> res[N];
SCC g(0);

bitset<N>& sol(int c) {
    if (vst[c]) return res[c];
    vst[c] = 1;
    for (int d: g.dag[c]) {
        res[c] |= sol(d);
    }
    return res[c];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> q;
    g = SCC(n);
    while (m--) {
        int i, j; cin >> i >> j; --i, --j;
        g.add(i, j);
    }
    g.sol();
    for (int c = 0; c < g.NC; ++c) {
        sol(c);
        res[c][c] = 1;
    }
    while (q--) {
        int i, j; cin >> i >> j; --i, --j;
        cout << (res[g.C[i]][g.C[j]] ? "YES" : "NO") << endl;
    }
}