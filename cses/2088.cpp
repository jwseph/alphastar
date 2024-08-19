#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 5003;
int n;
ll p[N], dp[N][N], opt[N][N];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i+1];
        p[i+1] += p[i];
        opt[i][i+1] = i;
    }
    for (int w = 2; w <= n; ++w) {
        for (int i = 0; i+w <= n; ++i) {
            int j = i+w;
            dp[i][j] = 1e18;
            for (int h = opt[i][j-1]; h <= opt[i+1][j]; ++h) {
                auto cur = dp[i][h]+dp[h][j];
                if (dp[i][j] > cur) {
                    dp[i][j] = cur;
                    opt[i][j] = h;
                }
            }
            dp[i][j] += p[j]-p[i];
        }
    }
    cout << dp[0][n] << endl;
}