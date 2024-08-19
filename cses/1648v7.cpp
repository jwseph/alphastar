#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Range {
    static constexpr ll def = 0;
    Range* c[2]{};
    ll val = 0;
    ll query(int a, int b, int l, int r) {
        if (a <= l && r <= b) return val;
        if (r < a || b < l || l == r) return def;
        int h = (l+r)/2;
        return get(0)->query(a, b, l, h) + get(1)->query(a, b, h+1, r);
    }
    void add(int i, ll v, int l, int r) {
        val += v;
        if (l == r) return;
        int h = (l+r)/2;
        i <= h ? get(0)->add(i, v, l, h) : get(1)->add(i, v, h+1, r);
    }
    Range* get(int i) {
        if (!c[i]) c[i] = new Range;
        return c[i];
    }
};

int n, q;

int main() {
    cin >> n >> q;
    Range r;
    for (int i = 1; i <= n; ++i) {
        int v; cin >> v;
        r.add(i, v, 1, n);
    }
    while (q--) {
        int t; cin >> t;
        if (t == 1) {
            int i, v; cin >> i >> v;
            r.add(i, v - r.query(i, i, 1, n), 1, n);
            continue;
        }
        int a, b; cin >> a >> b;
        cout << r.query(a, b, 1, n) << endl;
    }
}