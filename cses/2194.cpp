#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pl = pair<ll, ll>;
#define f first
#define s second

pl rev(const pl& p) {
    return {p.s, p.f};
}
ll dist(const pl& a, const pl& b) {
    ll d1 = a.f-b.f, d2 = a.s-b.s;
    return d1*d1 + d2*d2;
}

const int N = 2e5+1;
int n;
set<pl> ys;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    vector<pl> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i].f >> a[i].s;
    sort(begin(a), end(a));
    ll d = 9e18, i = 0;
    for (auto& p: a) {
        for (;;) {
            while (i < n && p.f-a[i].f > sqrt(d)) ys.erase(rev(a[i++]));
            bool done = 1;
            for (auto it = ys.lower_bound({p.s-sqrt(d), LLONG_MIN}); it != end(ys) && it->f <= p.s+d; ++it) {
                ll d2 = dist(p, rev(*it));
                if (d > d2) {
                    d = d2;
                    done = 0;
                    break;
                }
            }
            if (done) break;
        }
        ys.insert(rev(p));
    }
    cout << d << endl;
}