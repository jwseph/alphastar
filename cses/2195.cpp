#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pt = pair<ll, ll>;
#define f first
#define s second

struct ConvexHull {
    vector<pt> v, h;
    void add(ll x, ll y) { v.push_back({x, y}); }
    void init() {
        sort(v.begin(), v.end());
        for (int t = 0; t < 2; ++t) {
            for (pt p: v) {
                while (h.size() >= 2 && turn(h[h.size()-2], h.back(), p) < 0) h.pop_back();
                h.push_back(p);
            }
            h.pop_back();
            reverse(v.begin(), v.end());
        }
    }
    int turn(pt a, pt b, pt c) {
        ll res = (b.s-a.s)*(c.f-b.f) - (c.s-b.s)*(b.f-a.f);
        return (res > 0) - (res < 0);
    }
};

int n;
ConvexHull ch;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        ch.add(x, y);
    }
    ch.init();
    cout << ch.h.size() << endl;
    for (pt p: ch.h) {
        cout << p.f << ' ' << p.s << endl;
    }
}