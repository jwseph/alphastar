#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 25e3+5;
int n, m, a, b;
int row[N], col[N], cnt[2], sz[2];
vector<array<int, 2>> clear;

int main() {
    ifstream cin("fencedin.in");
    ofstream cout("fencedin.out");
    cin >> a >> b >> n >> m;
    sz[0] = n, sz[1]= m;
    row[n+1] = a, col[m+1] = b;
    for (int r = 1; r <= n; ++r) cin >> row[r];
    for (int c = 1; c <= m; ++c) cin >> col[c];
    sort(row, row+n+2);
    sort(col, col+m+2);
    for (int r = 0; r <= n; ++r) clear.push_back({row[r+1]-row[r], 0});
    for (int c = 0; c <= m; ++c) clear.push_back({col[c+1]-col[c], 1});
    sort(begin(clear), end(clear));
    ll res = 0;
    for (auto [w, d]: clear) {
        res += (ll) w * (cnt[d] && cnt[d^1] ? sz[d^1]-cnt[d^1]+1 : sz[d^1]);
        cnt[d]++;
    }
    cout << res << endl;
}