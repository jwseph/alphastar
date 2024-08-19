#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pi = array<int, 2>;
using pl = array<ll, 2>;
const ll mod = 1e9+7;

pl operator+(const pl& a, const pl& b) {
    return {(a[0]+b[0])%mod, (a[1]+b[1])%mod};
}
pl operator+=(pl& a, const pl& b) {
    return a = a+b;
}
pl operator*(const pl& a, const pl& b) {
    return {(a[0]*b[1]%mod+a[1]*b[0]%mod)%mod, a[1]*b[1]%mod};
}

int n, m, x, y, k;
vector<pi> ad[1501];
pl res[2501], cur[2501];
bool vst[1501];
vector<int> comp, dist;

void dfs1(int i) {
    if (vst[i]) return;
    vst[i] = 1;
    comp.push_back(i);
    for (auto [j, w]: ad[i]) {
        dfs1(j);
    }
}

void dfs2(int i, int p, int og, int d) {
    if (i < og) dist.push_back(d);
    for (auto [j, w]: ad[i]) {
        if (j == p) continue;
        dfs2(j, i, og, d+w);
    }
}

int main() {
    ifstream cin("mooriokart.in");
    ofstream cout("mooriokart.out");
    cin >> n >> m >> x >> y; k = n-m;
    for (int e = 0; e < m; ++e) {
        int i, j, w; cin >> i >> j >> w;
        ad[i].push_back({j, w});
        ad[j].push_back({i, w});
    }
    res[min(k*x, y)] = {k*x, 1};
    for (int i = 1; i <= n; ++i) {
        if (vst[i]) continue;
        comp = {};
        dfs1(i);
        dist = {};
        for (int j: comp) dfs2(j, j, j, 0);
        map<int, pl> solo;
        for (int d: dist) solo[min(d, y)] += pl{d, 1};
        for (int l = 0; l <= y; ++l) cur[l] = {0, 0};
        for (auto [d, p]: solo) {
            for (int l = 0; l <= y; ++l) {
                cur[min(d+l, y)] += p*res[l];
            }
        }
        for (int l = 0; l <= y; ++l) {
            res[l] = cur[l];
        }
    }
    ll r = res[y][0];
    for (int i = 1; i < k; ++i) {
        r *= i*2, r %= mod;
    }
    cout << r << endl;
}