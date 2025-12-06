struct SegTreeLazy {
    struct Info {
        ll sum, mn, mx;
        Info(ll s=0, ll a=0, ll b=0) : sum(s), mn(a), mx(b) {}
    };
    struct Tag {
        ll add;
        Tag(ll a=0) : add(a) {}
        bool empty() const { return add == 0; }
    };

    int n = 0;
    vector<Info> st;
    vector<Tag> lz;

    void init(int n_) {
        n = n_;
        int S = 4 * max(1, n) + 5;
        st.assign(S, Info(0, 0, 0));
        lz.assign(S, Tag(0));
    }

    void build(const vector<ll>& a) {
        init((int)a.size());
        if (n == 0) return;
        build(1, 0, n, a);
    }

    void range_add(int l, int r, ll val) {
        if (l >= r || n == 0 || val == 0) return;
        update(1, 0, n, l, r, Tag(val));
    }

    ll range_sum(int l, int r) {
        if (l >= r || n == 0) return 0;
        return query(1, 0, n, l, r).sum;
    }
    ll range_min(int l, int r) {
        if (l >= r || n == 0) return LLONG_MAX;
        return query(1, 0, n, l, r).mn;
    }
    ll range_max(int l, int r) {
        if (l >= r || n == 0) return LLONG_MIN;
        return query(1, 0, n, l, r).mx;
    }

    int first_geq(int l, int r, ll x) { //first index in [l, r) with value >= x
        if (l >= r || n == 0) return -1;
        return first_geq(1, 0, n, l, r, x);
    }

    int lower_bound_prefix(ll k) { //smallest i with prefix sum a[0..i) >= k (all vals must be pos)
        if (n == 0) return 0;
        if (k <= 0) return 0;
        if (st[1].sum < k) return n;
        int v = 1, l = 0, r = n;
        while (r - l > 1) {
            push(v, l, r);
            int m = (l + r) / 2;
            if (st[v * 2].sum >= k) { v = v * 2; r = m; }
            else { k -= st[v * 2].sum; v = v * 2 + 1; l = m; }
        }
        return l;
    }

    // maximal r where pred is true for Info([l,r)) (e.g. max_right(l, [&](Info cur){ return cur.mx < X; }))
    template <class F> 
    int max_right(int l, F pred) { // 
        Info cur(0, LLONG_MAX, LLONG_MIN);
        return max_right(1, 0, n, l, pred, cur);
    }

    Info unite(const Info& A, const Info& B) {
        Info C;
        C.sum = A.sum + B.sum;
        C.mn = min(A.mn, B.mn);
        C.mx = max(A.mx, B.mx);
        return C;
    }

    void apply_tag(int v, int l, int r, const Tag& t) {
        if (t.empty()) return;
        ll add = t.add;
        st[v].sum += add * (ll)(r - l);
        st[v].mn  += add;
        st[v].mx  += add;
        lz[v].add += add;
    }

    void push(int v, int l, int r) {
        if (lz[v].empty() || r - l == 1) return;
        int m = (l + r) / 2;
        apply_tag(v * 2, l, m, lz[v]);
        apply_tag(v * 2 + 1, m, r, lz[v]);
        lz[v] = Tag(0);
    }

    void pull(int v) {
        st[v] = unite(st[v * 2], st[v * 2 + 1]);
    }

    void build(int v, int l, int r, const vector<ll>& a) {
        if (r - l == 1) {
            ll x = a[l];
            st[v] = Info(x, x, x);
            return;
        }
        int m = (l + r) / 2;
        build(v * 2, l, m, a);
        build(v * 2 + 1, m, r, a);
        pull(v);
    }

    void update(int v, int l, int r, int ql, int qr, const Tag& t) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) { apply_tag(v, l, r, t); return; }
        push(v, l, r);
        int m = (l + r) / 2;
        update(v * 2, l, m, ql, qr, t);
        update(v * 2 + 1, m, r, ql, qr, t);
        pull(v);
    }

    Info query(int v, int l, int r, int ql, int qr) {
        if (qr <= l || r <= ql) return Info(0, LLONG_MAX, LLONG_MIN);
        if (ql <= l && r <= qr) return st[v];
        push(v, l, r);
        int m = (l + r) / 2;
        return unite(query(v * 2, l, m, ql, qr), query(v * 2 + 1, m, r, ql, qr));
    }

    int first_geq(int v, int l, int r, int ql, int qr, ll x) {
        if (qr <= l || r <= ql || st[v].mx < x) return -1;
        if (r - l == 1) return l;
        push(v, l, r);
        int m = (l + r) / 2;
        int left = first_geq(v * 2, l, m, ql, qr, x);
        if (left != -1) return left;
        return first_geq(v * 2 + 1, m, r, ql, qr, x);
    }

    template <class F>
    int max_right(int v, int l, int r, int ql, F pred, Info& cur) {
        if (r <= ql) return ql;
        if (ql <= l) {
            Info nxt = unite(cur, st[v]);
            if (pred(nxt)) { cur = nxt; return r; }
            if (r - l == 1) return l;
        }
        push(v, l, r);
        int m = (l + r) / 2;
        int res = max_right(v * 2, l, m, ql, pred, cur);
        if (res < m) return res;
        return max_right(v * 2 + 1, m, r, ql, pred, cur);
    }
};
