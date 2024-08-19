#include <bits/stdc++.h>
using namespace std;

struct node {
    char v;
    int order, sz;
    node *l, *r;
    node(char v): v(v), order(rand()), sz(1), l(0), r(0) {};
} *root;
using treap = node*;
int sz(treap t) {
    return t ? t->sz : 0;
}
void split(treap t, int v, treap& l, treap& r) {
    if (!t) {
        l = r = 0; return;
    }
    if (v >= sz(t->l)+1) {
        split(t->r, v-sz(t->l)-1, t->r, r), l = t;
    } else {
        split(t->l, v, l, t->l), r = t;
    }
    t->sz = sz(t->l) + sz(t->r) + 1;
}
void merge(treap& t, treap l, treap r) {
    if (!l || !r) {
        t = l ? l : r; return;
    }
    if (l->order < r->order) {
        merge(l->r, l->r, r), t = l;
    } else {
        merge(r->l, l, r->l), t = r;
    }
    t->sz = sz(t->l) + sz(t->r) + 1;
}
ostream& operator<<(ostream& out, treap t) {
    if (!t) return out;
    return out << t->l << t->v << t->r;
}

int n, q;
string s;

int main() {
    cin >> n >> q >> s;
    for (char c: s) merge(root, root, new node(c));
    while (q--) {
        int a, b; cin >> a >> b; --a;
        treap l = 0, h = 0, r = 0;
        split(root, b, root, r);
        split(root, a, l, h);
        merge(root, l, r);
        merge(root, root, h);
    }
    cout << root << endl;
}