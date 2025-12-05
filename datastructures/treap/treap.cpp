#include "bits/stdc++.h"
using namespace std;
using ll = long long;

struct Treap {
    // currently allows duplicates but doesn't support them properly
    // if you want set: enforce uniqueness in insert
    // if you want multiset: keep keys unique and store a count per node
    struct Node {
        int key, prio;
        int sz;
        ll sum;
        int mn,mx;
        Node *l, *r;
        Node(int k, int p) : key(k), prio(p), sz(1), sum(k), mn(k), mx(k), l(nullptr), r(nullptr) {}
    };
    Node* root = nullptr;
    mt19937 rng{(uint32_t)chrono::steady_clock::now().time_since_epoch().count()};

    static int sz(Node* t) { return t ? t->sz : 0; }
    static ll sum(Node* t) { return t ? t->sum : 0LL; }
    static int mn(Node* t) { return t ? t->mn : INT_MAX; }
    static int mx(Node* t) { return t ? t->mx : INT_MIN; }

    static void pull(Node* t) { 
        if (t) {
            t->sz = 1 + sz(t->l) + sz(t->r);
            t->sum = sum(t->l) + sum(t->r) + (ll)t->key;
            t->mn = min(min(mn(t->l),mn(t->r)),t->key);
            t->mx = max(max(mx(t->l),mx(t->r)),t->key);
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

    static Node* merge(Node* a, Node* b) { // assuming all keys in a < all keys in b
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
        root = merge(merge(a, new Node(x, (int)rng())), b);
    }

    static Node* erase(Node* t, int x){
        if(!t) return nullptr;
        if(x < t->key){
            t->l = erase(t->l, x); 
            pull(t); 
            return t;
        }else if(x > t->key){
            t->r = erase(t->r, x); 
            pull(t); 
            return t;
        }else{
            Node* res = merge(t->l, t->r);
            t->l = t->r = nullptr;
            delete t;
            return res;
        }
    }
    void erase(int x){ root = erase(root, x); }

    static Node* kth(Node* t, int k) {
        if(!t || k <= 0 || k > sz(t)) return nullptr;
        int left_sz = sz(t->l);
        if(k <= left_sz) return kth(t->l, k);
        if(k == left_sz+1) return t;
        return kth(t->r, k-left_sz-1);
    }
    int kth(int k) const {
        Node* res = kth(root, k);
        return res ? res->key : -1;
    }

    static bool contains(Node* t, int x) {
        while(t){
            if(x < t->key) t = t->l;
            else if(x > t->key) t = t->r;
            else return true;
        }
        return false;
    }
    bool contains(int x) const { return contains(root, x); }

    static int order_of_key(Node* t, int x) { // # of keys < x
        if(!t) return 0;
        if(x <= t->key) return order_of_key(t->l, x);
        return 1 + sz(t->l) + order_of_key(t->r, x);
    }
    int order_of_key(int x) const { return order_of_key(root, x); }

    static void destroy(Node* t) {
        if(!t) return;
        destroy(t->l);
        destroy(t->r);
        delete t;
    }

    ~Treap() { destroy(root); }
};