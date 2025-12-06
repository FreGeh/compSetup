// use like this: SparseTable<int, function<int(int,int)>> st(a,[](int x, int y){ return ...(x, y); });
template <class T, class F>
struct SparseTable {
    int n = 0;
    vector<vector<T>> M;
    F function; // (only idempotent functions, like min, max, gcd, and, or)

    SparseTable(const vector<T>& a, F f) : n((int)a.size()), function(f) { 
        assert(n > 0);
        int K = bit_width((unsigned)n); // floor(log2(n)) + 1
        // int K = 32 - __builtin_clz((unsigned)n);
        M.resize(K);
        M[0] = a;

        for (int k = 1; k < K; ++k) {
            int len = 1 << k;
            M[k].resize(n-len+1);
            for (int i = 0; i+len <= n; ++i) {
                M[k][i] = function(M[k-1][i], M[k-1][i+(len >> 1)]);
            }
        }
    }

    // inclusive range [l, r]
    T query(int l, int r) const {
        assert(0 <= l && l <= r && r < n);
        int len = r-l+1;
        int k = bit_width((unsigned)len) - 1; // floor(log2(len))
        // int k = 31 - __builtin_clz((unsigned)len);
        return function(M[k][l], M[k][r-(1 << k)+1]);
    }
};
