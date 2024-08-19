#include <bits/stdc++.h>
using namespace std;

using ll = long long;

class DSU {
private:
	vector<ll> p, sz, sum;
	// stores all history info related to merges
	vector<pair<ll &, ll>> history;
public:
	DSU(int n) : p(n), sz(n, 1), sum(n) { iota(p.begin(), p.end(), 0); }
	void init_sum(const vector<ll> a) {
		for (int i = 0; i < (int)a.size(); i++) { sum[i] = a[i]; }
	}
	int get(int x) { return (p[x] == x) ? x : get(p[x]); }
	ll get_sum(int x) { return sum[get(x)]; }
	void unite(int a, int b) {
		a = get(a);
		b = get(b);
		if (a == b) { return; }
		if (sz[a] < sz[b]) { swap(a, b); }

		// add to history
		history.push_back({p[b], p[b]});
		history.push_back({sz[a], sz[a]});
		history.push_back({sum[a], sum[a]});

		p[b] = a;
		sz[a] += sz[b];
		sum[a] += sum[b];
	}
	void add(int x, ll v) {
		x = get(x);
		history.push_back({sum[x], sum[x]});
		sum[x] += v;
	}
	int snapshot() { return history.size(); }
	void rollback(int until) {
		while (snapshot() > until) {
			history.back().first = history.back().second;
			history.pop_back();
		}
	}
};

struct Query { int t, u, v, x; }

const int MAXN = 2e5+5;
int n, q;
ll res[MAXN];

vector<Query> tr[4*MAXN];
void update(Query& q, int a, int b, int p, int l, int r) {
    if (b < p || r < a) return;
    if (a <= l && r <= b) {
        t[p].push_back(q);
        return;
    }
    int h = (l+r)/2;
    update(q, a, b, p*2, l, h), update(q, a, b, p*2+1, h+1, r);
}

void dfs(int p, int l, int r) {
    int save = dsu.snapshot();
    if (l == r) {
        for (auto& q: tr[p]) {
            if (q.t == 3) res[l] = dsu.get_sum(q.v);
        }
    } else {
        int h = (l+r)/2;
        dfs(p*2, l, h), dfs(p*2+1, h+1, r);
    }
    dsu.rollback(save);
}

int main() {
    memset(res, -1, sizeof res);
    cin >> n >> q;

    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    dsu.init_sum(a);

    map<pair<int, int>, int> start;
    for (int i = 0; i < q; ++i) {
        int t; cin >> t;
        if (t == 0) {
            int i, j; cin >
        }
    }

    for (int i = 0; res[i] >= 0; ++i) {
        cout << res[i] << endl;
    }
}