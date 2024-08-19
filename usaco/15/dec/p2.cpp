#include <bits/stdc++.h>
using namespace std;

const int N =5e4+5;
int n;
int ar[N], l[N], r[N];
set<int> b1, b2;

int main() {
    ifstream cin("cardgame.in");
    ofstream cout("cardgame.out");
    cin >> n;
    for (int i = 1; i <= 2*n; ++i) {
        b1.insert(i);
        b2.insert(i);
    }
    for (int i = 0; i < n; ++i) {
        cin >> ar[i];
        b1.erase(ar[i]);
        b2.erase(ar[i]);
    }
    for (int i = 0; i < n; ++i) {
        auto it = b1.lower_bound(ar[i]);
        if (it != b1.end()) {
            b1.erase(it);
            l[i+1]++;
        }
        l[i+1] += l[i];
    }
    int res = l[n];
    for (int i = n-1; i >= 0; --i) {
        auto it = b2.upper_bound(ar[i]);
        if (it != b2.begin()) {
            b2.erase(--it);
            r[i]++;
        }
        r[i] += r[i+1];
        res = max(res, l[i]+r[i]);
    }
    cout << res << endl;
}