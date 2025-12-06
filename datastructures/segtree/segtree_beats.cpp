struct SegTree_Beats {
    int n;
    vector<ll> seg, max1, max2, min1, min2, lazy;
    vector<int> cntMax, cntMin;

    void init(int n_) { // seg.init(n);
        n = n_;
        seg.assign(4*n, 0);
        max1.assign(4*n, LLONG_MIN);
        max2.assign(4*n, LLONG_MIN);
        min1.assign(4*n, LLONG_MAX);
        min2.assign(4*n, LLONG_MAX);
        cntMax.assign(4*n, 0);
        cntMin.assign(4*n, 0);
        lazy.assign(4*n, 0);
    }

    void build(int v, int l, int r, const vector<ll> &a) { // seg.build(1, 0, n-1, a);
        lazy[v] = 0;
        if (l == r) {
            ll x = a[l];
            seg[v] = x;
            max1[v] = min1[v] = x;
            max2[v] = LLONG_MIN;
            min2[v] = LLONG_MAX;
            cntMax[v] = cntMin[v] = 1;
            return;
        }
        int m = (l+r)/2;
        build(v*2, l, m, a);
        build(v*2+1, m+1, r, a);
        pull(v);
    }

    inline void pull(int v) { // recompute node based on children
        int L = v*2, R = v*2+1;
        seg[v] = seg[L] + seg[R];

        if (max1[L] == max1[R]) {
            max1[v] = max1[L];
            max2[v] = max(max2[L], max2[R]);
            cntMax[v] = cntMax[L] + cntMax[R];
        } else if (max1[L] > max1[R]) {
            max1[v] = max1[L];
            max2[v] = max(max2[L], max1[R]);
            cntMax[v] = cntMax[L];
        } else {
            max1[v] = max1[R];
            max2[v] = max(max1[L], max2[R]);
            cntMax[v] = cntMax[R];
        }

        if (min1[L] == min1[R]) {
            min1[v] = min1[L];
            min2[v] = min(min2[L], min2[R]);
            cntMin[v] = cntMin[L] + cntMin[R];
        } else if (min1[L] < min1[R]) {
            min1[v] = min1[L];
            min2[v] = min(min2[L], min1[R]);
            cntMin[v] = cntMin[L];
        } else {
            min1[v] = min1[R];
            min2[v] = min(min1[L], min2[R]);
            cntMin[v] = cntMin[R];
        }
    }

    inline void apply_add(int v, int l, int r, ll a) { // add value lazy way
        if (a == 0) return;
        seg[v] += a*(r-l+1);
        max1[v] += a;
        min1[v] += a;
        if (max2[v] != LLONG_MIN) max2[v] += a;
        if (min2[v] != LLONG_MAX) min2[v] += a;
        lazy[v] += a;
    }

    inline void push_max_cap(int v, ll x, bool leaf) { // all max elements reduced to x (must x > max2[v])
        if (x >= max1[v]) return;
        seg[v] -= (ll)cntMax[v]*(max1[v]-x);
        max1[v] = x;
        if (leaf) {
            min1[v] = max1[v];
        } else {
            if (max1[v] <= min1[v]) min1[v] = max1[v];
            else if (max1[v] < min2[v]) min2[v] = max1[v];
        }
    }

    inline void push_min_cap(int v, ll x, bool leaf) { // all max elements increased to x (must x < min2[v])
        if (x <= min1[v]) return;
        seg[v] += (ll)cntMin[v]*(x-min1[v]);
        min1[v] = x;
        if (leaf) {
            max1[v] = min1[v];
        } else {
            if (min1[v] >= max1[v]) max1[v] = min1[v];
            else if (min1[v] > max2[v]) max2[v] = min1[v];
        }
    }

    void push(int v, int l, int r) { // push info down to children
        if (l == r) { lazy[v] = 0; return; }
        int m = (l+r)/2, L = v*2, R = v*2+1;
        if (lazy[v] != 0) {
            apply_add(L, l, m, lazy[v]);
            apply_add(R, m+1, r, lazy[v]);
            lazy[v] = 0;
        }
        push_max_cap(L, max1[v], l == m);
        push_max_cap(R, max1[v], m+1 == r);
        push_min_cap(L, min1[v], l == m);
        push_min_cap(R, min1[v], m+1 == r);
    }

    // updates (1, 0, n-1, L, R, val)
    void update_add(int v, int l, int r, int ql, int qr, ll val) { // add val to range
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { apply_add(v, l, r, val); return; }
        push(v, l, r);
        int m = (l+r)/2;
        update_add(v*2, l, m, ql, qr, val);
        update_add(v*2+1, m+1, r, ql, qr, val);
        pull(v);
    }

    void update_chmin(int v, int l, int r, int ql, int qr, ll x) { // change range to min(a[i], x)
        if (qr < l || r < ql || x >= max1[v]) return;
        if (ql <= l && r <= qr && x > max2[v]) { push_max_cap(v, x, l == r); return; }
        push(v, l, r);
        int m = (l+r)/2;
        update_chmin(v*2, l, m, ql, qr, x);
        update_chmin(v*2+1, m+1, r, ql, qr, x);
        pull(v);
    }

    void update_chmax(int v, int l, int r, int ql, int qr, ll x) { // change range to max(a[i], x)
        if (qr < l || r < ql || x <= min1[v]) return;
        if (ql <= l && r <= qr && x < min2[v]) { push_min_cap(v, x, l == r); return; }
        push(v, l, r);
        int m = (l+r)/2;
        update_chmax(v*2, l, m, ql, qr, x);
        update_chmax(v*2+1, m+1, r, ql, qr, x);
        pull(v);
    }

    // queries (1, 0, n-1, L, R)
    ll query_sum(int v, int l, int r, int ql, int qr) { // sum of range
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return seg[v];
        push(v, l, r);
        int m = (l+r)/2;
        return query_sum(v*2, l, m, ql, qr) + query_sum(v*2+1, m+1, r, ql, qr);
    }

    ll query_max(int v, int l, int r, int ql, int qr) { // max of range
        if (qr < l || r < ql) return LLONG_MIN;
        if (ql <= l && r <= qr) return max1[v];
        push(v, l, r);
        int m = (l+r)/2;
        return max(query_max(v*2, l, m, ql, qr), query_max(v*2+1, m+1, r, ql, qr));
    }

    ll query_min(int v, int l, int r, int ql, int qr) { // min of range
        if (qr < l || r < ql) return LLONG_MAX;
        if (ql <= l && r <= qr) return min1[v];
        push(v, l, r);
        int m = (l+r)/2;
        return min(query_min(v*2, l, m, ql, qr), query_min(v*2+1, m+1, r, ql, qr));
    }
};
