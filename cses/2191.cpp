#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e3+3;
int n;
ll x[N], y[N];

int main() {
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    x[n] = x[0], y[n] = y[0];
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        res += x[i]*y[i+1] - x[i+1]*y[i];
    }
    cout << abs(res) << endl;
}