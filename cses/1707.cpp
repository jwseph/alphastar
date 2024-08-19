#include <bits/stdc++.h>
using namespace std;

const int N = 2503, inf = 1e9;
int n, m;
vector<int> ad[N];

int sol(int i0) {
    int vs[N]{};
    queue<int> q;
    vs[i0] = 1;
    q.push(i0);
    int res = inf;
    while (q.size()) {
        int i = q.front(); q.pop();
        for (int j: ad[i]) {
            if (vs[j]) {
                if (vs[i] <= vs[j]) res = min(res, vs[i]+vs[j]-1);
                continue;
            }
            vs[j] = vs[i]+1;
            q.push(j);
        }
    }
    return res;
}

int main() {
    cin >> n >> m;
    for (int e = 0; e < m; ++e) {
        int i, j; cin >> i >> j;
        ad[i].push_back(j);
        ad[j].push_back(i);
    }
    int res = inf;
    for (int i = 1; i <= n; ++i) {
        res = min(res, sol(i));
    }
    cout << (res < inf ? res : -1) << endl;
}