#include <bits/stdc++.h>
using namespace std;

int n, k;
int a[20004];

int read_bin() {
    int res = 0;
    for (char c; (c = getchar()) != '\n';) {
        res <<= 1;
        res ^= c-'0';
    }
    return res;
}

int main() {
    cin >> n >> k; cin.get();
    int res = k;
    for (int i = 0; i < n; ++i) {
        a[i] = read_bin();
        for (int j = 0; j < i; ++j) {
            res = min(res, __builtin_popcount(a[i]^a[j]));
        }
    }
    cout << res << endl;
}