// 0-indexed, queries on [l, r)
struct SegTree {
    int n = 0;
    vector<ll> sumt, mint, maxt;

    void init(int n_) {
        n = n_;
        sumt.assign(2 * n, 0);
        mint.assign(2 * n, LLONG_MAX);
        maxt.assign(2 * n, LLONG_MIN);
    }

    void build(const vector<ll>& a) {
        init((int)a.size());
        for (int i = 0; i < n; i++) {
            sumt[n + i] = a[i];
            mint[n + i] = a[i];
            maxt[n + i] = a[i];
        }
        for (int i = n - 1; i >= 1; i--) pull(i);
    }

    void pull(int v) {
        sumt[v] = sumt[v * 2] + sumt[v * 2 + 1];
        mint[v] = min(mint[v * 2], mint[v * 2 + 1]);
        maxt[v] = max(maxt[v * 2], maxt[v * 2 + 1]);
    }

    void set_point(int i, ll val) { // set a[i] = val
        int v = i + n;
        sumt[v] = val;
        mint[v] = val;
        maxt[v] = val;
        for (v /= 2; v >= 1; v /= 2) pull(v);
    }

    void add_point(int i, ll delta) { // add a[i] += delta
        int v = i + n;
        sumt[v] += delta;
        mint[v] += delta;
        maxt[v] += delta;
        for (v /= 2; v >= 1; v /= 2) pull(v);
    }

    ll range_sum(int l, int r) const {
        ll res = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) res += sumt[l++];
            if (r % 2 == 1) res += sumt[--r];
        }
        return res;
    }

    ll range_min(int l, int r) const {
        ll res = LLONG_MAX;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) res = min(res, mint[l++]);
            if (r % 2 == 1) res = min(res, mint[--r]);
        }
        return res;
    }

    ll range_max(int l, int r) const {
        ll res = LLONG_MIN;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2 == 1) res = max(res, maxt[l++]);
            if (r % 2 == 1) res = max(res, maxt[--r]);
        }
        return res;
    }
};