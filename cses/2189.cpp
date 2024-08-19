#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;

int t;

ll sol(ll x1, ll y1, ll x, ll y, ll x2, ll y2) {
    return (y-y1)*(x-x2)-(y-y2)*(x-x1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> t;
    while (t--) {
        ll x1, y1, x2, y2, x, y; cin >> x1 >> y1 >> x2 >> y2 >> x >> y;
        ll res = sol(x1, y1, x, y, x2, y2);
        cout << (res < 0 ? "LEFT" : res > 0 ? "RIGHT" : "TOUCH") << endl;
    }
}