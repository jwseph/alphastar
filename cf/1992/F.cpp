#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;
int q, n, x;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> q;
    while (q--) {
        cin >> n >> x;
        int res = 1;
        set<int> s;
        s.insert(1);
        for (int i = 0; i < n; ++i) {
            int a; cin >> a;
            if (x%a) continue;
            if (s.count(x/a)) {
                ++res;
                s = {};
                s.insert(1);
            }
            set<int> t;
            for (int b: s) {
                if (x%((long long)b*a)) continue;
                t.insert(b*a);
            }
            s.insert(t.begin(), t.end());
        }
        cout << res << endl;
    }
}