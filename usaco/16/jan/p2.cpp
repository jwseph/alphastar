#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5+5;

struct Range {
    static constexpr ll def = 0;
    Range* c[2]{};
    ll val = 0;
    ll query(int a, int b, int l = 0, int r = N) {
        if (a < l && r < b) return val;
        if (r <= a || b <= l || l == r) return def;
        int h = (l+r)/2;
        return get(0)->query(a, b, l, h) + get(1)->query(a, b, h+1, r);
    }
    void add(int i, ll v, int l = 0, int r = N) {
        val += v;
        if (l == r) return;
        int h = (l+r)/2;
        i <= h ? get(0)->add(i, v, l, h) : get(1)->add(i, v, h+1, r);
    }
    Range* get(int i) {
        if (!c[i]) c[i] = new Range;
        return c[i];
    }
    ~Range() { delete c[0]; delete c[1]; }
};

struct BIT {
    Range* t[N];
    void init() {
        for (int i = 0; i < N; ++i) {
            delete t[i];
            t[i] = new Range;
        }
    }
    void add(int i, int j, ll v) {
        i++;
        while (i < N) {
            t[i]->add(j, v);
            i += i&-i;
        }
    }
    ll query(int i, int l, int r) {
        i++;
        ll res = 0;
        while (i) {
            res += t[i]->query(l, r);
            i -= i&-i;
        }
        return res;
    }
} bit;

void compress(int* l, int* r) {
    vector<int> v(l, r);
    sort(begin(v), end(v));
    v.erase(unique(begin(v), end(v)), end(v));
    map<int, int> inv;
    for (int i = 0; i < v.size(); ++i) {
        inv[v[i]] = i;
    }
    while (l != r) *(l++) = inv[*l];
}

int n, k;
int x[N], y[N];
vector<array<int, 2>> open[N], close[N];
vector<array<int, 3>> planes[N];
ll res = 0;

int main() {
    ifstream cin("mowing.in");
    ofstream cout("mowing.out");
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    compress(x, x+n);
    compress(y, y+n);
    for (int z = 0; z < 2; ++z) {
        for (int p = 0; p < N; ++p) {
            open[p] = {};
            close[p] = {};
            planes[p] = {};
        }
        // Be very careful about not including endpoints
        for (int i = 0; i+1 < n; ++i) {
            if (y[i] == y[i+1]) {
                open[min(x[i], x[i+1])].push_back({i+k, y[i]});
                close[max(x[i], x[i+1])].push_back({i+k, y[i]});
                continue;
            }
            planes[x[i]].push_back({i, min(y[i], y[i+1]), max(y[i], y[i+1])});
        }
        bit.init();
        for (int x = 0; x < n; ++x) {
            for (auto [t, y]: close[x]) {
                bit.add(t, y, -1);
            }
            for (auto [t, y1, y2]: planes[x]) {
                res += bit.query(t, y1, y2);
            }
            for (auto [t, y]: open[x]) {
                bit.add(t, y, 1);
            }
        }
        swap(x, y);
    }
    cout << res << endl;
}