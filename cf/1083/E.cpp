#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 1e6+6;
int n;
vector<array<ll, 3>> ar;
ll dp[N];

struct CHT {
    void add(ll m, ll b) {
        // SIMON LINDHOLM DYNAMIC CHT
        // https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
    }
};

int main() {
    cin >> n;
    ar.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> ar[i][0] >> ar[i][1] >> ar[i][2];
    }
    sort(ar.begin(), ar.end());
    for (auto [w, h, a]: ar) {
        cout << w << ' ' << h << ' ' << a << endl;

    }
}