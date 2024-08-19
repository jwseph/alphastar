#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9+7;

struct Modular {
    int n;
    vector<ll> fac, inv;
    Modular(int n): n(n), fac(n+1), inv(n+1) {
        fac[0] = 1;
        for (int i = 1; i <= n; ++i) fac[i] = fac[i-1] * i % mod;
        inv[n] = exp(fac[n], mod-2);
        for (int i = n; i >= 1; --i) inv[i-1] = inv[i] * i % mod;
    }
    ll exp(ll a, ll b) {
        ll res = 1;
        while (b) {
            if (b&1) res *= a, res %= mod;
            a *= a, a %= mod;
            b >>= 1;
        }
        return res;
    }
    ll choose(int n, int k) {
        if (k > n || k < 0) return 0;
        return fac[n] * inv[k] % mod * inv[n-k] % mod;
    }
};

const int N = 5e3+5;
int q, n;
Modular md(N);
ll sol() {
    ll res = 0;
    for (int k = 0; k <= n; ++k) {
        for (int l = 0; l <= k; ++l) {
            int t = k+1+l;
            res += t * md.choose(min(t-1, n), l) % mod * md.choose(max(n-t, 0), k-l);
            res %= mod;
        }
    }
    return res;
}

int main() {
    cin >> q;
    while (q--) {
        cin >> n;
        cout << sol() << endl;
    }
}