#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[200][200], p[200][201];

int main() {
    ifstream cin("fortmoo.in");
    ofstream cout("fortmoo.out");
    cin >> n >> m;
    for (int r = 0; r < n; ++r) {
        string s; cin >> s;
        for (int c = 0; c < m; ++c) {
            a[r][c] = s[c] == 'X';
            p[r][c+1] = p[r][c] + a[r][c];
        }
    }
    int res = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            for (int w = 2; w+c <= m; ++w) {
                if (a[r][c+w-2] || a[r][c+w-1]) break;
                for (int h = 2; h+r <= n; ++h) {
                    if (a[r+h-2][c] || a[r+h-2][c+w-1]) break;
                    if (p[r+h-1][c+w] - p[r+h-1][c]) continue;
                    res = max(res, w*h);
                }
            }
        }
    }
    cout << res << endl;
}