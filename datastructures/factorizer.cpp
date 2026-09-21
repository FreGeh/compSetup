// credit: adapted from tourist_algos
struct Factorizer {
    int n;
    vector<int> spf; // smallest prime factor
    vector<int> primes;

    Factorizer() : n(0) {}
    Factorizer(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        spf.assign(n+1, 0);
        primes.clear();

        for (int i=2; i<=n; i++) {
            if (spf[i] == 0) {
                spf[i] = i;
                primes.push_back(i);
            }

            for (int p : primes) {
                if (p > spf[i] || 1LL*i*p > n) break;
                spf[i*p] = p;
            }
        }
    }

    bool is_prime(int x) const {
        return x >= 2 && spf[x] == x;
    }

    int smallest_prime_factor(int x) const {
        return spf[x];
    }

    int largest_prime_factor(int x) const {
        int p = 1;
        while (x > 1) {
            p = spf[x];
            x /= spf[x];
        }
        return p;
    }

    vector<pair<int,int>> factorize(int x) const {
        vector<pair<int,int>> res;

        while (x > 1) {
            int p = spf[x];
            int cnt = 0;

            while (x % p == 0) {
                x /= p;
                cnt++;
            }

            res.push_back({p, cnt});
        }

        return res;
    }

    vector<int> divisors(int x) const {
        auto fac = factorize(x);
        vector<int> res = {1};

        for (auto [p, cnt] : fac) {
            int sz = res.size();
            int mul = 1;

            for (int e=1; e<=cnt; e++) {
                mul *= p;
                for (int i=0; i<sz; i++)
                    res.push_back(res[i] * mul);
            }
        }

        sort(res.begin(), res.end());
        return res;
    }
};