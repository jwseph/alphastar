#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pt = pair<ll, ll>;
#define x first
#define y second

int turn(pt a, pt b, pt c) {
    ll res = (a.y-b.y)*(c.x-b.x) - (c.y-b.y)*(a.x-b.x);
    return (res > 0) - (res < 0);
}
bool point_line(pt p, pt a, pt b) {
    if (max(a.x, b.x) < p.x || p.x < min(a.x, b.x)) return 0;
    if (max(a.y, b.y) < p.y || p.y < min(a.y, b.y)) return 0;
    return turn(a, p, b) == 0;
}
bool ray_line(pt p, pt a, pt b) {
    if (a.y > b.y) swap(a, b);
    return a.y <= p.y && p.y < b.y && turn(p, a, b) < 0;
}

const int N = 1e3+3;
int n, t;
pt pg[N];

string raycast(pt p) {
    int res = 0;
    for (int i = 0; i < n; ++i) {
        if (point_line(p, pg[i], pg[i+1])) return "BOUNDARY";
        res ^= ray_line(p, pg[i], pg[i+1]);
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