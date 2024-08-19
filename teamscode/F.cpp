#include <bits/stdc++.h>
using namespace std;

const int M = 5e1+1;
int n, x;
int a[502];
bitset<M> dp[2], zero;

int main() {
    cin >> n >> x;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    dp[0][x] = 1;
    for (int i = 1; i <= n; ++i) {
        dp[i%2] = dp[(i+1)%2]<<a[i];

        int d = 0;
        while (a[i]) {
            d += a[i]%10, a[i] /= 10;
        }

        // zero.reset();
        for (int p = 0; p < M; ++p) {
            zero[p] = !(p>>d&1);
        }

        int w = 1<<d;
        dp[i%2] |= (dp[(i+1)%2]&zero)<<w;
        dp[i%2] |= (dp[(i+1)%2]&~zero)>>w;

        int res = 0, q; cin >> q;
        zero.reset();
        zero = ~zero;
        zero >>= (M-q-1);
        res += (dp[i%2]&zero).count();
        cout << res << endl;
    }
}