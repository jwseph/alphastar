#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LCDeque : deque<Line> {  // assume k increasing, m decreasing (or opposite if want == -1)
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX, want = -1;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
        k *= want, m *= want;
        push_back({k, m, 0});
		auto z = prev(end()), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
        while (front() < x) pop_front();
		return (front().k * x + front().m) * want;
	}
};

/*

zero to hill:
    x
   xx
  xxx
 xxxx
=========
j   i
1   5
dp[i] = dp[j] + p2[i]-p2[j]-j*(p[i]-p[j])
> dp[i] = (dp[j]-p2[j]+jp[j]) + (-j)p[i] + p2[i]

hill to zero:
    xo
   xxoo
  xxxooo
 xxxxoooo
=============
    j    i
    5    9
dp[i+1] = dp[j] + q2[i]-q2[j]-(n-i)*(p[i]-p[j])
> dp[i+1] = (dp[j]-q2[j]+np[j]) + (-p[j])i + (i-n)*p[i]+q2[i]

*/

const int N = 3003;
int n, m;
ll a[N], p[N], p2[N], q2[N], dp[N];
LCDeque lc[N*2];

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        p[i+1] = p[i] + a[i];
        p2[i+1] = p2[i] + (i+1)*a[i];
        q2[i+1] = q2[i] + (n-i)*a[i];
    }
    for (int k = 0; k <= 2*m; k += 2) lc[k].add(0, -q2[0]);
    for (int k = 1; k <= 2*m; ++k) {
        for (int i = 1; i <= n; ++i) {
            if (k&1) {
                dp[i] = lc[k-1].query(i-1) + (i-1-n)*p[i-1]+q2[i-1];
                lc[k].add(-i, dp[i]-p2[i]+(i)*p[i]);
            } else {
                dp[i] = lc[k-1].query(p[i]) + p2[i];
                lc[k].add(-p[i], dp[i]-q2[i]+n*p[i]);
            }
        }
    }
    cout << dp[n] << endl;
}