#include <bits/stdc++.h>
using namespace std;

#define sz(x) int(x.size())

const int N = 1e6+5;
int q, n;
string s;
int A[N], B[N];

int sol() {
    int res = 0;
    for (int a = 1; a <= 10000; ++a) {
        for (int b = a*sz(s)-7; b <= a*sz(s); ++b) {
            if (b > 10000 || b > a*n || b < 1) continue;
            string t = to_string(a*n-b);
            bool ok = t.size() == a*sz(s)-b && a*sz(s)-b > 0;
            for (int i = 0; i < t.size() && ok; ++i) {
                if (t[i] != s[i%sz(s)]) {
                    ok = 0;
                }
            }
            if (ok) {
                A[res] = a;
                B[res] = b;
                ++res;
            }
        }
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> q;
    while (q--) {
        cin >> n;
        s = to_string(n);
        n = sol();
        cout << n << endl;
        for (int i = 0; i < n; ++i) {
            cout << A[i] << ' ' << B[i] << endl;
        }
    }
}