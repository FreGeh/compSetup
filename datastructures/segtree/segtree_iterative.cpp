#include "bits/stdc++.h"
using namespace std;
#define ll long long

struct SegTree {
    int len = 0;
    vector<ll> sum_t, min_t, max_t;

    void pull(int v) {
        sum_t[v] = sum_t[v * 2] + sum_t[v * 2 + 1];
        min_t[v] = min(min_t[v * 2], min_t[v * 2 + 1]);
        max_t[v] = max(max_t[v * 2], max_t[v * 2 + 1]);
    }

    SegTree(int n = 0) {
        if (n > 0) init(n);
    }

    void init(int n) {
        len = n;
        sum_t.assign(2 * len, 0);
        min_t.assign(2 * len, LLONG_MAX);
        max_t.assign(2 * len, LLONG_MIN);
    }

    void build(const vector<ll>& a) {
        init((int)a.size());
        for (int i = 0; i < len; ++i) {
            sum_t[len + i] = min_t[len + i] = max_t[len + i] = a[i];
        }
        for (int i = len - 1; i > 0; --i) {
            pull(i);
        }
    }

    void set(int index, ll new_val) {
        index += len;
        sum_t[index] = min_t[index] = max_t[index] = new_val;
        for (index /= 2; index >= 1; index /= 2) {
            pull(index);
        }
    }

    // range queries [left, right)

    ll query_sum(int left, int right) {
        ll res = 0;
        for (left += len, right += len; left < right; left /= 2, right /= 2) {
            if (left % 2 == 1) res += sum_t[left++];
            if (right % 2 == 1) res += sum_t[--right];
        }
        return res;
    }

    ll query_min(int left, int right) {
        ll res = LLONG_MAX;
        for (left += len, right += len; left < right; left /= 2, right /= 2) {
            if (left % 2 == 1) res = min(res, min_t[left++]);
            if (right % 2 == 1) res = min(res, min_t[--right]);
        }
        return res;
    }

    ll query_max(int left, int right) {
        ll res = LLONG_MIN;
        for (left += len, right += len; left < right; left /= 2, right /= 2) {
            if (left % 2 == 1) res = max(res, max_t[left++]);
            if (right % 2 == 1) res = max(res, max_t[--right]);
        }
        return res;
    }
};