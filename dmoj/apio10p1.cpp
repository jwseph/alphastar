#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

int n;
ll a, b, c;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> a >> b >> c;
    LineContainer hull;
    hull.add(0, 0);
    ll p = 0, dp = 0;
    for (int i = 1; i <= n; ++i) {
        ll x; cin >> x; p += x;
        dp = hull.query(p) + (a*p+b)*p+c;
        hull.add(-2*a*p, dp + (a*p-b)*p);
    }
    cout << dp << endl;
}