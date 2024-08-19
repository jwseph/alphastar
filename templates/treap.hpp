/**
 * Author: Joseph Jackson
 * Date: 2024-07-18
 * License: CC0
 * Time: O(nlogn)
 * Description: Simple treap
 * Usage: treap root;
 *        for (int x: sorted_set) root = merge(root, new node(x));
 *        // For indices swap "t->v <= v" with "sz(t->l)+1 <= v" and "v" with "v-sz(t->l)-1"
 * Status: tested
 */

struct node {
    int v, order, sz;
    node *l, *r;
    node(int v): v(v), order(rand()), sz(1), l(0), r(0) {};
} *root;
using treap = node*;
int sz(treap t) {
    return t ? t->sz : 0;
}
void split(treap t, int v, treap& l, treap& r) {
    if (!t) {
        l = r = 0; return;
    }
    if (t->v <= v) {
        split(t->r, v, t->r, r), l = t;
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