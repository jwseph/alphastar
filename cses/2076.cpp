#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/blog/entry/68138
// DFS Tree, all cycle creating edges will reach an ancestor of the node

const int N = 1e5+5;
int n, m;
vector<int> a[N];
int pre[N], v[N];
vector<array<int, 2>> res;

int dfs(int i, int p) {
    if (v[i] == 2) return 0;
    if (v[i] == 1) {
        --pre[i];
        return 1;
    }
    v[i] = 1;
    for (int j: a[i]) {
        if (j == p) continue;
        pre[i] += dfs(j, i);
    }
    v[i] = 2;
    if (!pre[i] && p > 0) res.push_back({i, p});
    return pre[i];
}

int main() {
    cin >> n >> m;
    for (int e = 0; e < m; ++e) {
        int i, j; cin >> i >> j;
        a[i].push_back(j), a[j].push_back(i);
    }
    dfs(1, 0);
    cout << res.size() << endl;
    for (auto [a, b]: res) cout << a << ' ' << b << endl;
}