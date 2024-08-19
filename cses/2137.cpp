#include <bits/stdc++.h>
using namespace std;
#pragma GCC target("popcnt")

int n;
bitset<3000> a[3000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    long long res = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        for (int j = 0; j < i; ++j) {
            int x = (a[i]&a[j]).count();
            res += x*(x-1)/2;
        }
    }
    cout << res << endl;
}