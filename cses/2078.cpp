#include <bits/stdc++.h>
using namespace std;

// 2**(m-n+1)

const int N = 1e5+5, mod = 1e9+7;
int n, m, cnt = 0;
vector<int> a[N];
bool v[N];

void dfs(int i) {
    if (v[i]) return;
    v[i] = 1;
    for (int j: a[i]) {
        dfs(j);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int e = 0; e < m; ++e) {
        int i, j; cin >> i >> j;
        a[i].push_back(j), a[j].push_back(i);
    }
    cnt = m-n;
    for (int i = 1; i <= n; ++i) {
        cnt += !v[i];
        dfs(i);
    }
    int res = 1;
    while (cnt--) res *= 2, res %= mod;
    cout << res << endl;
}