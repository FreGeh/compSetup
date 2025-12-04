#include "bits/stdc++.h"
using namespace std;
using ll = long long;

struct Treap {
    struct Node {
        int key, prio;
        int sz;
        Node *l, *r;
        Node(int k, int p) : key(k), prio(p), sz(1), l(nullptr), r(nullptr) {}
    };
    Node* root = nullptr;
    mt19937 rng{(uint32_t)chrono::steady_clock::now().time_since_epoch().count()};

    static int sz(Node* t) { return t ? t->sz : 0; }

    static void pull(Node* t) { 
        if (t) {
            t->sz = 1 + sz(t->l) + sz(t->r);
        }
    }

    static pair<Node*, Node*> split(Node* v, int x) { // split into (< x) and (>= x)
        if (!v) return {nullptr, nullptr};
        if (v->key < x) {
            auto [rl, rr] = split(v->r, x);
            v->r = rl;
            pull(v);
            return {v, rr};
        } else {
            auto [sl, sr] = split(v->l, x);
            v->l = sr;
            pull(v);
            return {sl, v};
        }
    }

    static Node* merge(Node* a, Node* b) { // merge assumes all keys in a are < all keys in b
        if (!a) return b;
        if (!b) return a;
        if (a->prio < b->prio) { // priority min-heap
            a->r = merge(a->r, b);
            pull(a);
            return a;
        } else {
            b->l = merge(a, b->l);
            pull(b);
            return b;
        }
    }

    void insert(int x) {
        auto [a, b] = split(root, x);
        root = merge(merge(a, new Node(x, rng())), b);
    }
};