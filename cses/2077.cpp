#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+5;
int n, m;
vector<int> a[N], res;
int d[N], low[N];

void dfs(int i, int p) {
    low[i] = d[i] = d[p]+1;
    int ok = 0, c = 0;
    for (int j: a[i]) {
        if (j == p) continue;
        if (d[j]) {
            low[i] = min(low[i], d[j]);
            continue;
        }
        dfs(j, i);
        low[i] = min(low[i], low[j]);
        ok |= low[j] >= d[i];
        ++c;
    }
    if (p ? ok : c >= 2) res.push_back(i);
}

int main() {
    cin >> n >> m;
    for (int e = 0; e < m; ++e) {
        int i, j; cin >> i >> j;
        a[i].push_back(j), a[j].push_back(i);
    }
    dfs(1, 0);
    cout << res.size() << endl;
    for (int i: res) cout << i << ' ';
    cout << endl;
}