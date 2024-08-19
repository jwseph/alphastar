#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5, inf = 1e9;
int t, n, m, k;
int dp[N];
string s;

int sol() {
    dp[n+1] = 0;
    for (int i = n; i >= 0; --i) {
        if (s[i] == 'C') {
            dp[i] = inf;
            continue;
        }
        if (s[i] == 'W') {
            dp[i] = dp[i+1]+1;
            continue;
        }
        dp[i] = inf;
        for (int j = i+1; j <= min(i+m, n+1); ++j) {
            dp[i] = min(dp[i], dp[j]);
        }
    }
    return dp[0];
}

int main() {
    cin >> t;
    while (t--) {
        cin >> n >> m >> k >> s;
        s = 'L'+s;
        cout << (sol() <= k ? "YES" : "NO") << endl;
    }
}