#include <bits/stdc++.h>
using namespace std;

void compress(int* l, int* r) {
    vector<int> v(l, r);
    sort(begin(v), end(v));
    v.erase(unique(begin(v), end(v)), end(v));
    map<int, int> inv;
    for (int i = 0; i < v.size(); ++i) {
        inv[v[i]] = i;
    }
    while (l != r) *(l++) = inv[*l];
}

struct Tree {
    int n;
    vector<int> t;
    Tree(int n): n(n), t(n*2) {}
    void update(int i, int v) {
        for (t[i += n] += v; i /= 2;) t[i] = t[i*2] + t[i*2+1];
    }
    int query(int l, int r) {
        int res = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l&1) res += t[l++];
            if (r&1) res += t[--r];
        }
        return res;
    }
};

const int N = 1e5+5;
int n;
int x[N], y[N];
vector<int> ys[N];
Tree t1(N), t2(N);

int query(int h) {
    return max({t1.query(0, h), t2.query(0, h), t1.query(h, n), t2.query(h, n)});
}

int sol() {
    int l = 0, r = n;
    while (l < r) {
        int h = (l+r)/2;
        if (max(t1.query(0, h), t2.query(0, h)) >= max(t1.query(h, n), t2.query(h, n))) r = h;
        else l = h+1;
    }
    return min(query(l), query(l-1));
}

int main() {
    ifstream cin("balancing.in");
    ofstream cout("balancing.out");
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    compress(x, x+n);
    compress(y, y+n);
    for (int i = 0; i < n; ++i) {
        ys[x[i]].push_back(y[i]);
        t2.update(y[i], 1);
    }
    int res = sol();
    for (int i = 0; i < n; ++i) {
        for (int v: ys[i]) {
            t2.update(v, -1);
            t1.update(v, 1);
        }
        res = min(res, sol());
    }
    cout << res << endl;
}