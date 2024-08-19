#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 2e5+5;
int t, n, ar[N];

ll sol() {
    sort(ar, ar+n);
    ll res = 0;
    for (int i = 0; i < n-1; ++i) {
        res += ar[i]*2-1;
    }
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> t;
    while (t--) {
        cin >> n >> n;
        for (int i = 0; i < n; ++i) cin >> ar[i];
        cout << sol() << endl;
    }
}