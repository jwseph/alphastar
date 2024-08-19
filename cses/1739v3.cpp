#include <bits/stdc++.h>
using namespace std;

const int N = 1e3+5;
int n, q;

struct BIT {
    int a[N][N], t[N][N];
    void update(int r, int c, int v) {
        a[r][c] += v;
        for (int i = r+1; i <= n; i += i&-i) {
            for (int j = c+1; j <= n; j += j&-j) {
                t[i][j] += v;
            }
        }
    }
    void set(int r, int c, int v) {
        update(r, c, v-a[r][c]);
    }
    int query(int r, int c) {
        int res = 0;
        for (int i = r; i; i -= i&-i) {
            for (int j = c; j; j -= j&-j) {
                res += t[i][j];
            }
        }
        return res;
    }
    int query(int r1, int c1, int r2, int c2) {
        return query(r2, c2) - query(r2, c1) - query(r1, c2) + query(r1, c1);
    }
} bit;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        for (int j = 0; j < n; ++j) {
            bit.set(i, j, s[j] == '*');
        }
    }
    while (q--) {
        int t, r, c; cin >> t >> r >> c; --r, --c;
        if (t == 1) {
            bit.set(r, c, !bit.a[r][c]);
            continue;
        }
        int r2, c2; cin >> r2 >> c2;
        cout << bit.query(r, c, r2, c2) << endl;
    }
}