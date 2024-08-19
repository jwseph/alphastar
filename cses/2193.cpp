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
    ll a2 = 0;
    for (int i = 0; i < n; ++i) {
        a2 += x[i]*y[i+1] - x[i+1]*y[i];
    }
    a2 = abs(a2);
    ll b = 0;
    for (int i = 0; i < n; ++i) {
        b += gcd(abs(x[i]-x[i+1]), abs(y[i]-y[i+1]));
    }
    ll i = (a2-b)/2 + 1;
    cout << i << ' ' << b << endl;
}