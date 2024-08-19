#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll n, res = 0;

int main() {
    cin >> n; ++n;
    for (ll k = 1; k <= n; k *= 2) {
        res += n/(k*2)*k + max(n%(k*2)-k, 0ll);
    }
    cout << res << endl;
}