#include "bits/stdc++.h"
using namespace std;
using ll = long long;

struct Treap {
    struct Node {
        int key;
        uint32_t pr;
        int sz;
        Node *l, *r;
        Node(int k, uint32_t p) : key(k), pr(p), sz(1), l(nullptr), r(nullptr) {}
    };
    using P = Node*;

    static int sz(P t) { return t ? t->sz : 0; }
    static void pull(P t) { if (t) t->sz = 1 + sz(t->l) + sz(t->r); }

    // split into (< x) and (>= x)
    static pair<P, P> split(P v, int x) {
        if (!v) return {nullptr, nullptr};
        if (v->key < x) {
            auto [rl, rr] = split(v->r, x);
            v->r = rl;
            pull(v);
            return {v, rr};
        } else {
            auto [ll, lr] = split(v->l, x);
            v->l = lr;
            pull(v);
            return {ll, v};
        }
    }

    // merge assumes all keys in a are < all keys in b
    static P merge(P a, P b) {
        if (!a) return b;
        if (!b) return a;
        if (a->pr < b->pr) {              // min heap by priority, like your slides
            a->r = merge(a->r, b);
            pull(a);
            return a;
        } else {
            b->l = merge(a, b->l);
            pull(b);
            return b;
        }
    }
};
