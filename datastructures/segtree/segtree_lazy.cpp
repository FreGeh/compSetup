#include "bits/stdc++.h"
using namespace std;
#define ll long long

struct SegTree_Lazy {
    int n;
    vector<ll> seg, lazy;
    vector<ll> mx, bloom;

    SegTree_Lazy() : n(0) {}
    explicit SegTree_Lazy(int n_) { 
        init(n_); 
    }

    void init(int n_) { 
        n=n_; 
        seg.assign(4*n,0); 
        lazy.assign(4*n,0); 

        mx.assign(4*n, LLONG_MIN);
        bloom.assign(4*n, LLONG_MAX);
    }

    // always (v=1,l=0,r=n-1)

    void build(int v, int l, int r, const vector<ll>& a) {
        if(l==r){ 
            seg[v] = mx[v] = bloom[v] = a[l];
            return; 
        }
        int m=(l+r)/2;
        build(v*2,l,m,a);
        build(v*2+1,m+1,r,a);
        pull(v);
    }

    inline void apply(int v, int l, int r, ll add) {
        seg[v]+=add*(r-l+1);
        lazy[v]+=add;

        mx[v] += add;
        bloom[v] += add;
    }

    inline void push(int v, int l, int r) { //forward pending lazy tag 
        if(lazy[v]==0 || l==r) return;
        int m=(l+r)/2;
        apply(v*2,l,m,lazy[v]);
        apply(v*2+1,m+1,r,lazy[v]);
        lazy[v]=0;
    }

    inline void pull(int v) { // recompute stats
        seg[v] = seg[v*2] + seg[v*2+1];
        mx[v] = max(mx[v*2], mx[v*2+1]);
        bloom[v] = min(bloom[v*2], bloom[v*2+1]);
    }

    void update(int v, int l, int r, int ql, int qr, ll add_val) {
        if(ql>qr) return;
        if(ql==l && qr==r){ 
            apply(v,l,r,add_val); 
            return; 
        }
        push(v, l, r);
        int m=(l+r)/2;
        update(v*2,l,m,ql,min(qr,m),add_val);
        update(v*2+1,m+1,r,max(ql,m+1),qr,add_val);
        pull(v);
    }

    ll query_sum(int v, int l, int r, int ql, int qr) {
        if (ql > qr) return 0;
        if (ql == l && qr == r) return seg[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return query_sum(v*2, l, m, ql, min(qr, m)) + query_sum(v*2+1, m+1, r, max(ql, m+1), qr);
    }

    ll query_max(int v, int l, int r, int ql, int qr) {
        if (ql > qr) return LLONG_MIN;
        if (ql == l && qr == r) return mx[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return max(query_max(v*2, l, m, ql, min(qr, m)), query_max(v*2+1, m+1, r, max(ql, m+1), qr));
    }

    ll query_min(int v, int l, int r, int ql, int qr) {
        if (ql > qr) return LLONG_MAX;
        if (ql == l && qr == r) return bloom[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return min(query_min(v*2, l, m, ql, min(qr, m)), query_min(v*2+1, m+1, r, max(ql, m+1), qr));
    }

    int first_geq(int v, int l, int r, int ql, int qr, ll x) {
        if (qr < l || r < ql || mx[v] < x) return -1;
        if (l == r) return l;
        push(v, l, r);
        int m = (l + r) / 2;
        int left = first_geq(v*2, l, m, ql, qr, x);
        if (left != -1) return left;
        return first_geq(v*2+1, m+1, r, ql, qr, x);
    }

    int sum_geq_k(ll k) { // smallest i with prefix sum a[0 ... i] >= k, if none -> n
        if (k <= 0 || seg[1] < k) return n;
        int v = 1, l = 0, r = n-1;
        while (l != r) {
            push(v, l, r);
            int m = (l + r) / 2;
            if (seg[v*2] >= k) { v = v*2; r = m; }
            else { k -= seg[v*2]; v = v*2+1; l = m+1; }
        }
        return l;
    }
};
