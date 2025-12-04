#include "bits/stdc++.h"
using namespace std;
using ll = long long;

struct Treap {
    struct Node {
        int val, prio;
        int sz;
        Node *l, *r;
        Node(int v, int p) : val(v), prio(p), sz(1), l(nullptr), r(nullptr) {}
    };

    Node* root = nullptr;
    mt19937 rng{(uint32_t)chrono::steady_clock::now().time_since_epoch().count()};

    static int sz(Node* t) { return t ? t->sz : 0; }

    static void pull(Node* t) {
        if (t) t->sz = 1 + sz(t->l) + sz(t->r);
    }

    static pair<Node*, Node*> split(Node* v, int k) {
        if (!v) return {nullptr, nullptr};
        if (sz(v->l) >= k) { // first k elements
            auto [a, b] = split(v->l, k);
            v->l = b;
            pull(v);
            return {a, v};
        } else { // remaining elemnts
            auto [a, b] = split(v->r, k - sz(v->l) - 1);
            v->r = a;
            pull(v);
            return {v, b};
        }
    }

    static Node* merge(Node* a, Node* b) { // concatenate b onto a
        if (!a) return b;
        if (!b) return a;
        if (a->prio < b->prio) { // min-heap on prio
            a->r = merge(a->r, b);
            pull(a);
            return a;
        } else {
            b->l = merge(a, b->l);
            pull(b);
            return b;
        }
    }

    void insert_at(int pos, int v) { // insert value v at pos 
        auto [a, b] = split(root, pos);
        root = merge(merge(a, new Node(v, (int)rng())), b);
    }

    void push_back(int v) { insert_at(sz(root), v); }
};
