#include <bits/stdc++.h>
using namespace std;

template<class T>
struct Tree {
    static constexpr T def = 0;
    T f(T a, T b) { return max(a, b); }
    vector<T> t; int n;
    Tree(int n): t(2*n, def), n(n) {}
    void update(int i, T v) {
        for (t[i += n] = v; i /= 2;) t[i] = f(t[i*2], t[i*2+1]);
    }
    T query(int l, int r) {
        l = max(l, 0), r = min(r, n);
        T al = def, ar = def;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l&1) al = f(al, t[l++]);
            if (r&1) ar = f(t[--r], ar);
        }
        return f(al, ar);
    }
};

using ll = long long;
const ll M = 1e9, mod = 1e9+7;

const int N = 1e5+5;
int n, k;
int ar[N];

ll sol(ll cur, ll cnt) {
    if (!cnt) return 1;
    ll x = M-cur, xk = 1;
    for (int i = 0; cnt-k >= 0 && i < k; ++i) xk *= x, xk %= mod;
    vector<ll> dp(cnt+k+1);
    dp[cnt] = dp[cnt+1] = 1;
    for (int i = cnt-1; i >= 0; --i) {
        dp[i] = (dp[i+1]*(x+1)%mod - dp[i+k+1]*xk%mod + mod) % mod;
    }
    return dp[0];
}

int main() {
    ifstream cin("tracking2.in");
    ofstream cout("tracking2.out");
    cin >> n >> k;
    Tree<int> tr(n-k+1);
    for (int i = 0; i < n-k+1; ++i) {
        int v; cin >> v;
        tr.update(i, v);
    }
    for (int i = 1; i <= n; ++i) {
        ar[i] = tr.query(i-k, i);
    }
    int cur = 0, cnt = 0;
    ll res = 1;
    for (int i = 1; i <= n; ++i) {
        bool skip = ar[i-1] > ar[i] || ar[i] < ar[i+1];
        if (ar[i] != cur || skip) {
            res *= sol(cur, cnt), res %= mod;
            cnt = 0;
        }
        if (skip) continue;
        cur = ar[i], cnt++;
    }
    res *= sol(cur, cnt), res %= mod;
    cout << res << endl;
}