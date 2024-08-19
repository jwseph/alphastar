#include <bits/stdc++.h>
using namespace std;

using ld = long double;

const int N = 1e6+6;
int n;
ld p[N], scale = 1e6;

int main() {
    ifstream cin("cowdate.in");
    ofstream cout("cowdate.out");
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i]; p[i] /= scale;
    }
    ld P = 1, S = 0, res = 0;
    for (int i = 0, j = 0; j < n; ++j) {
        P *= 1-p[j], S += p[j]/(1-p[j]);
        res = max(res, P*S);
        while (i <= j && S >= 1) {
            P /= 1-p[i], S -= p[i]/(1-p[i]);
            i++;
            res = max(res, P*S);
        }
    }
    cout << int(res*scale) << endl;
}