#include <bits/stdc++.h>
using namespace std;

int t, n, m, k;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        for (int i = n; i > m; --i) {
            cout << i << ' ';
        }
        for (int i = 1; i <= m; ++i) {
            cout << i << " ";
        }
        cout << endl;
    }
}