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
int n, m;
vector<ll> w;
ll wei[N], cost[N], dp[N][9], res = 1e18;

int main() {
    ifstream cin("cbarn.in");
    ofstream cout("cbarn.out");
    cin >> n >> m; m = min(m, n);
    w.resize(n);
    for (int i = 0; i < n; ++i) cin >> w[i];
    reverse(w.begin(), w.end());
    for (int i = 0; i < n; ++i) {
        wei[0] = cost[0] = 0;
        for (int i = 0; i < n; ++i) {
            wei[i+1] = wei[i] + w[i];
            cost[i+1] = cost[i] + wei[i+1];
        }
        LCDeque h1, h2;
        h1.add(0 ,0);
        for (int k = 1; k <= m; ++k) {
            h2.add(0, 0);
            for (int i = 0; i < n; ++i) {
                dp[i][k] = h1.query(i) + cost[i];
                h2.add(-wei[i+1], dp[i][k]+wei[i+1]*(i+1)-cost[i+1]);
            }
            h1 = h2;
            h2 = {};
        }
        res = min(res, dp[n-1][m]);
        w.push_back(w[0]);
        w.erase(w.begin());
    }
    cout << res << endl;
}