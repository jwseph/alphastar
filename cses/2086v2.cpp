#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 3003;
int n, m;
ll p[N], dp[N][N];

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int a; cin >> a;
        p[i+1] = p[i] + a;
    }
    for (int k = 0; k <= m; ++k) {
        for (int i = 0; i <= n; ++i) {
            dp[k][i] = 1e18;
        }
    }
    dp[0][0] = 0;
    for (int k = 1; k <= m; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < i; ++j) {
                dp[k][i] = min(dp[k][i], dp[k-1][j] + (p[i]-p[j])*(p[i]-p[j]));
            }
        }
    }
    cout << dp[m][n] << endl;
}
