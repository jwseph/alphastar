#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
using ll = long long;
using pt = pair<ll, ll>;

// intersect if rectangles intersect and endpoints are on different sides

int t;

int turn(pt a, pt b, pt c) {
    ll res = (b.y-a.y)*(b.x-c.x) - (b.y-c.y)*(b.x-a.x);
    return (res > 0) - (res < 0);
}

bool intersects(pt a, pt b, pt c, pt d) {
    if (max(a.x, b.x) < min(c.x, d.x) || max(c.x, d.x) < min(a.x, b.x)) return 0;
    if (max(a.y, b.y) < min(c.y, d.y) || max(c.y, d.y) < min(a.y, b.y)) return 0;
    return turn(a, c, b)*turn(a, d, b) <= 0 && turn(c, a, d)*turn(c, b, d) <= 0;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> t;
    while (t--) {
        pt a, b, c, d; cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
        cout << (intersects(a, b, c, d) ? "YES" : "NO") << '\n';
    }
}