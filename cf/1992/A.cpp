#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll sol(ll a, ll b, ll c) {
    ll res = 0;
    for (int i = 0; i <= 5; ++i) {
        for (int j = 0; j <= 5-i; ++j) {
            int k = 5-i-j;
            res = max(res, (a+i)*(b+j)*(c+k));
        }
    }
    return res;
}

int main() {

    int t; cin >> t;
    while (t--) {
        int a, b, c; cin >> a >> b >> c;
        cout << sol(a, b, c) << endl;
    }
}