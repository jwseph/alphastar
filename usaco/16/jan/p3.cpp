// Source: https://usaco.org/current/data/sol_lightsout_platinum_jan16.html
// I don't understand this solution, but I copied it in hopes of doing so.

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pl = array<ll, 2>;

const int N = 205;
int n;
pl a[N];
int pre[N], reg[N];
int canon[N*2][N*2];
vector<int> lpar[N][N], rpar[N][N];
int dp[N][N][N][2];

int main() {
    ifstream cin("lightsout.in");
    ofstream cout("lightsout.out");
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1];
    }
    vector<int> s = {0};
    for (int i = 0; i < n; ++i) {
        int j = (i+1)%n, k = (i+2)%n;
        s.push_back(abs(a[i][0]-a[j][0]) + abs(a[i][1]-a[j][1]));
        bool turn = (a[j][1]-a[i][1])*(a[k][0]-a[j][0]) < (a[k][1]-a[j][1])*(a[j][0]-a[i][0]);
        s.push_back(turn ? -1 : -2);
    }
    s.back() = 0;
    for (int i = 0; i < n; ++i) {
        pre[i+1] = reg[i+1] = reg[i] + s[i*2+1];
    }
    reg[n] = 0;
    for (int i = n-1; i >= 0; --i) {
        reg[i] = min(reg[i], reg[i+1] + s[i*2+1]);
    }
    for (int l = 1; l <= s.size(); ++l) {
        for (int i = 0; i+l <= s.size(); ++i) {
            for (int& j = canon[i][l]; j < i; ++j) {
                if (canon[i][l-1] == canon[j][l-1] && s[i+l-1] == s[j+l-1]) break;
            }
        }
    }
    for (int i = 0; i < s.size(); i += 2) {
        for (int l = 3; i+l <= s.size(); l += 2) {
            if (i != canon[i][l]) continue;
            lpar[canon[i+2][l-2]/2][l/2].push_back(i/2);
            rpar[canon[i][l-2]/2][l/2].push_back(i/2);
        }
    }
    int res = 0;
    for (int l = n; l >= 1; --l) {
        for (int i = 0; i+l <= n+1; ++i) {
            if (i*2 != canon[i*2][2*l-1]) continue;
            int dist = pre[i+l-1] - pre[i];
            for (int start = 0; start < l; ++start) {
                for (int side = 0; side < 2; ++side) {
                    if (i == 0 || i+l == n+1) {
                        dp[i][l][start][side] = -reg[i+start];
                        continue;
                    }
                    int lcost = INT_MIN, rcost = INT_MIN;
                    for (int j: lpar[i][l]) {
                        lcost = max(lcost, s[j*2+1] + dp[j][l+1][start+1][0] + dist*side);
                    }
                    for (int j: rpar[i][l]) {
                        rcost = max(rcost, s[(j+l)*2-1] + dp[j][l+1][start][1] + dist*(1-side));
                    }
                    dp[i][l][start][side] = min(lcost, rcost);
                    if (l == 1) {
                        res = max(res, dp[i][l][start][side]);
                    }
                }
            }
        }
    }
    cout << res << endl;
}