#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct node {
    int v, order = rand(), sz = 1;
    ll tot;
    bool rev = 0;
    node *l = 0, *r = 0;
    node(int v): v(v), tot(v) {};
} *root;
using treap = node*;
int sz(treap t) { return t ? t->sz : 0; }
ll tot(treap t) { return t ? t->tot : 0; }
void prop(treap t) {
    if (t && t->rev) {
        swap(t->l, t->r);
        t->rev ^= 1;
        if (t->l) t->l->rev ^= 1;
        if (t->r) t->r->rev ^= 1;
    }
}
void split(treap t, int v, treap& l, treap& r) {
    prop(t);
    if (!t) {
        l = r = 0; return;
    }
    if (v >= sz(t->l)+1) {
        split(t->r, v-sz(t->l)-1, t->r, r), l = t;
    } else {
        split(t->l, v, l, t->l), r = t;
    }
    t->sz = sz(t->l) + sz(t->r) + 1;
    t->tot = tot(t->l) + tot(t->r) + t->v;
}
void merge(treap& t, treap l, treap r) {
    prop(l);
    prop(r);
    if (!l || !r) {
        t = l ? l : r; return;
    }
    if (l->order < r->order) {
        merge(l->r, l->r, r), t = l;
    } else {
        merge(r->l, l, r->l), t = r;
    }
    t->sz = sz(t->l) + sz(t->r) + 1;
    t->tot = tot(t->l) + tot(t->r) + t->v;
}
ostream& operator<<(ostream& out, treap t) {
    if (!t) return out;
    prop(t);
    return out << t->l << t->v << t->r;
}

int n, q;
string s;

int main() {
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        int a; cin >> a;
        merge(root, root, new node(a));
    }
    while (q--) {
        int t, a, b; cin >> t >> a >> b; --a;
        treap l = 0, h = 0, r = 0;
        split(root, b, root, r);
        split(root, a, l, h);
        if (t == 1) h->rev ^= 1;
        else cout << tot(h) << endl;
        merge(root, l, h);
        merge(root, root, r);
    }
}