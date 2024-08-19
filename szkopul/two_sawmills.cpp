#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LCDeque : deque<Line> {  // assume k increasing, m decreasing
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

const int N = 2e4+4;
int n;
ll wei[N], pos[N], cost[N], dp[N][4];
LCDeque hull[4];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int w, d; cin >> w >> d;
        wei[i+1] = wei[i] + w;
        pos[i+1] = pos[i] + d;
        cost[i+1] = cost[i] + wei[i+1]*d;
    }
    for (int k = 0; k <= 3; ++k) hull[k].add(0, 0);
    for (int i = 0; i <= n; ++i) {
        for (int k = 3; k >= 1; --k) {
            dp[i][k] = hull[k-1].query(pos[i]) + cost[i];
            hull[k].add(-wei[i+1], dp[i][k]+wei[i+1]*pos[i+1]-cost[i+1]);
        }
    }
    cout << dp[n][3] << endl;
}