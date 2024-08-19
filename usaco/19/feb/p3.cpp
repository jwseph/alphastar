// Straight-up copied version of koosaga's sol
// https://github.com/koosaga/olympiad/blob/master/USACO/feb19_mowing.cpp

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
const int N = 2e5+5, M = 1e6+6;

struct BIT {
    int t[M];
    void update(int i, int v) {
        i++;
        while (i) {
            t[i] = max(t[i], v);
            i -= i&-i;
        }
    }
    int query(int i) {
        i++;
        int res = 0;
        while (i < M) {
            res = max(res, t[i]);
            i += i&-i;
        }
        return res;
    }
} bit;

int n;
pi a[N];
int dp[N];
vector<int> comp[N];
vector<ll> res[N];

struct Query {
    pi p;
    int s, e, i;
};

void dnc(int s, int e, int c, vector<Query>& proc, int l, int r) {
    // TC: (e-s)log(e-s)
    int h = (l+r)/2;
    ll ret = 1e18;
    int split = -1;
    for (int i = s; i <= e; ++i) {  // can't ternary search because of equal values
        ll val = res[c][i] + (ll) (a[comp[c][i]].first - proc[h].p.first) * (a[comp[c][i]].second - proc[h].p.second);
        // monotically matching
        if (ret > val) {
            ret = val;
            split = i;
        }
    }
    res[c+1][proc[h].i] = min(res[c+1][proc[h].i], ret);
    if (h+1 <= r) dnc(s, split, c, proc, h+1, r);
    if (l <= h-1) dnc(split, e, c, proc, l, h-1);
}

void solve(int s, int e, int c, vector<Query>& qs) {
    // TC: qlog(e-s) + log(e-s) * (e-s)log(e-s)
    if (!qs.size()) return;
    int h = (s+e)/2;
    vector<Query> proc, l, r;
    for (auto& q: qs) {
        if (q.s <= s && e <= q.e) {
            proc.push_back(q);
            continue;
        }
        if (q.s <= h) l.push_back(q);
        if (h < q.e) r.push_back(q);
    }
    if (proc.size()) dnc(s, e, c, proc, 0, proc.size()-1);
    solve(s, h, c, l);
    solve(h+1, e, c, r);
}

int main() {
    ifstream cin("mowing.in");
    ofstream cout("mowing.out");
    cin >> n;
    cin >> a[n+1].first;
    a[n+1].second = a[n+1].first;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a, a+n+2, greater<pi>());
    for (int i = 0; i <= n+1; ++i) {
        dp[i] = 1 + bit.query(a[i].second);
        bit.update(a[i].second, dp[i]);
        comp[dp[i]].push_back(i);
    }
    res[1].push_back(0);
    for (int c = 2; c <= dp[n+1]; ++c) {
        res[c].resize(comp[c].size(), 1e18);
        vector<Query> qs;
        int q = 0, l = 0, r = 0;
        for (int i: comp[c]) {
            // comp has decreasing y and increasing x
            while (l < comp[c-1].size() && a[i].second > a[comp[c-1][l]].second) l++;
            while (r < comp[c-1].size() && a[i].first < a[comp[c-1][r]].first) r++;
            qs.push_back({a[i], l, r-1, q++});
        }
        solve(0, comp[c-1].size()-1, c-1, qs);
    }
    cout << res[dp[n+1]][0] << endl;
}