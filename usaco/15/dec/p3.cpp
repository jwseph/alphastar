#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll inf = 1e18;

struct Tree {
    int n;
    vector<ll> lazy, sums, mins;  // sums and mins don't include lazy
    Tree(int n): n(n), lazy(4*n), sums(4*n), mins(4*n, 0) {}
    void upd(int l, int r, int k) {
        int h = (l+r)/2;
        sums[k] = query_sum(l, h, l, h, k*2) + query_sum(h+1, r, h+1, r, k*2+1);
        mins[k] = min(query_min(l, h, l, h, k*2), query_min(h+1, r, h+1, r, k*2+1));
    }
    void add(int a, int b, ll v, int l = 0, int r = -1, int k = 1) {
        if (r < 0) r = n-1;
        if (b < l || r < a) return;
        if (a <= l && r <= b) {
            lazy[k] += v;
            return;
        }
        int h = (l+r)/2;
        add(a, b, v, l, h, k*2), add(a, b, v, h+1, r, k*2+1);
        upd(l, r, k);
    }
    void push(int l, int r, int k) {
        if (l == r) { cout << "RUH ROH" << endl; }
        lazy[k*2] += lazy[k];
        lazy[k*2+1] += lazy[k];
        lazy[k] = 0;
        upd(l, r, k);
    }
    ll query_sum(int a, int b, int l = 0, int r = -1, int k = 1) {
        if (r < 0) r = n-1;
        if (b < l || r < a) return 0;
        if (a <= l && r <= b) {
            return sums[k] + lazy[k]*(r-l+1);
        }
        push(l, r, k);
        int h = (l+r)/2;
        return query_sum(a, b, l, h, k*2) + query_sum(a, b, h+1, r, k*2+1);
    }
    ll query_min(int a, int b, int l = 0, int r = -1, int k = 1) {
        if (r < 0) r = n-1;
        if (b < l || r < a) return inf;
        if (a <= l && r <= b) {
            return mins[k] + lazy[k];
        }
        push(l, r, k);
        int h = (l+r)/2;
        return min(query_min(a, b, l, h, k*2), query_min(a, b, h+1, r, k*2+1));
    }
};

int n, m;

int main() {
    ifstream cin("haybales.in");
    ofstream cout("haybales.out");
    cin >> n >> m;
    Tree tr(n);
    for (int i = 0; i < n; ++i) {
        int a; cin >> a;
        tr.add(i, i, a);
    }
    while (m--) {
        char q; int a, b; cin >> q >> a >> b; --a, --b;
        if (q == 'M') {
            cout << tr.query_min(a, b) << endl;
            continue;
        }
        if (q == 'S') {
            cout << tr.query_sum(a, b) << endl;
            continue;
        }
        int v; cin >> v;
        tr.add(a, b, v);
    }
}