#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pt = pair<ll, ll>;
#define x first
#define y second
const ll inf = 1e9;

int turn(pt a, pt b, pt c) {
    ll res = (a.y-b.y)*(c.x-b.x) - (c.y-b.y)*(a.x-b.x);
    return (res > 0) - (res < 0);
}
int line_line(pt a, pt b, pt p, pt q) {
    if (max(a.x, b.x) < min(p.x, q.x) || max(p.x, q.x) < min(a.x, b.x)) return 0;
    if (max(a.y, b.y) < min(p.y, q.y) || max(p.y, q.y) < min(p.x, q.x)) return 0;
    return turn(a, p, b) * turn(a, q, b) <= 0 && turn(p, a, q) * turn(p, b, q) <= 0;
}
bool point_line(pt p, pt a, pt b) {
    return line_line(p, p, a, b);
}

const int N = 1e3+3;
int n, t;
pt pg[N];

string raycast(pt p) {
    pt q = {2563210877, 2568130541};
    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (point_line(p, pg[i], pg[i+1])) return "BOUNDARY";
        res ^= line_line(p, q, pg[i], pg[i+1]);
    }
    return res ? "INSIDE" : "OUTSIDE";
}

int main() {
    cin >> n >> t;
    for (int i = 0; i < n; ++i) {
        cin >> pg[i].x >> pg[i].y;
    }
    pg[n] = pg[0];
    while (t--) {
        pt p; cin >> p.x >> p.y;
        cout << raycast(p) << endl;
    }
}