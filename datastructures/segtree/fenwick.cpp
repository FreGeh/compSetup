template <class T>
struct Fenwick { // 0-indexed
    int n;
    vector<T> bit;

    Fenwick() : n(0) {}
    Fenwick(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        bit.assign(n+1, T(0));
    }

    void add(int i, T delta) { // a[i] += delta
        for (i++; i<=n; i+=i&-i) bit[i] += delta;
    }

    T query(int i) const { // sum of a[0..i-1]
        T res = T(0);
        for (; i>0; i-=i&-i) res += bit[i];
        return res;
    }

    T query(int l, int r) const { // sum of a[l..r-1]
        return query(r) - query(l);
    }

    // Returns smallest i such that sum([0, i]) >= k
    // Requires: bit values >= 0
    int lower_bound(T k) const {
        if (k <= 0) return 0;

        int idx = 0;
        T cur = T(0);

        int step = 1;
        while ((step<<1) <= n) step<<=1;

        for (; step > 0; step>>=1) {
            int nxt = idx+step;
            if (nxt <= n && cur+bit[nxt] < k) {
                cur += bit[nxt];
                idx = nxt;
            }
        }
        return idx; // Returns n if sum < k
    }

    T total() const { return query(n); }
};
