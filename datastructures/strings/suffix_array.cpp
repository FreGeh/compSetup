template <typename T>
vector<int> sort_cyclic_shifts(const T& s) {
    int n = s.size();
    int alphabet = max(n, 256); 
    vector<int> p(n), c(n), cnt(alphabet, 0);

    // sort by single characters
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int i, int j) {
        return s[i] < s[j];
    });

    c[p[0]] = 0;
    for (int i=1; i<n; i++) // init equivalence classes
        c[p[i]] = c[p[i-1]] + (s[p[i]] != s[p[i-1]]);

    vector<int> pn(n), cn(n);
    for (int k=0; (1<<k) < n; k++) {
        int val = (1<<k);
        
        // sort by second half (shift)
        for (int i=0; i<n; i++) {
            pn[i] = p[i] - val;
            if (pn[i] < 0) pn[i] += n;
        }

        // stable sort by first half
        fill(cnt.begin(), cnt.begin() + c[p[n-1]] + 1, 0);
        for (int i=0; i<n; i++) cnt[c[pn[i]]]++; // count freq
        for (int i=1; i<=c[p[n-1]]; i++) cnt[i] += cnt[i-1]; // partial sums
        for (int i=n-1; i>=0; i--) p[--cnt[c[pn[i]]]] = pn[i]; // fill new p

        // update equivalence classes
        cn[p[0]] = 0;
        for (int i=1; i<n; i++) {
            pair<int, int> curr = {c[p[i]], c[(p[i] + val) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + val) % n]};
            cn[p[i]] = cn[p[i-1]] + (curr != prev);
        }
        c = cn;
    }
    return p;
}

template <typename T>
vector<int> suffix_array(T s) {
    s.push_back(0); // sentinel
    auto sa = sort_cyclic_shifts(s);
    sa.erase(sa.begin()); // remove sentinel
    return sa;
}

template <typename T> // kasai
vector<int> build_lcp(const T& s, const vector<int>& p) {
    int n = s.size(), k = 0;
    vector<int> rank(n), lcp(n-1);
    
    for (int i=0; i<n; i++) rank[p[i]] = i;

    for (int i=0; i<n; i++) {
        if (rank[i] == n - 1) { // last suffix has no next
            k = 0; 
            continue;
        }
        int j = p[rank[i] + 1]; // next suffix in sorted order

        while (i+k < n && j+k < n && s[i+k] == s[j+k]) k++;
        lcp[rank[i]] = k;

        if (k > 0) k--;
    }
    return lcp;
}