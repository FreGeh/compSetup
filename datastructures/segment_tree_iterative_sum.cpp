#include "bits/stdc++.h"
using namespace std;
#define ll long long

template <class T> class Segment_Tree_Sum {
// Index 0 unused, 1 = Root, 1 to len-1 = Internal, len to 2*len-1 = Leaves

private:
    const T DEFAULT = 0;
    int len;
    vector<T> tree;

public:
    Segment_Tree_Sum(const vector<T>& initial_values) : len(initial_values.size()), tree(len * 2, DEFAULT) {
        for (int i = 0; i < len; ++i) {
            tree[len + i] = initial_values[i];
        }
        for (int i = len - 1; i > 0; --i) {
            tree[i] = tree[i*2] + tree[i*2+1];
        }
    }

    void set(int index, T new_val) {
        index += len;
        tree[index] = new_val;
        for (index /= 2; index >= 1; index /= 2) {
            tree[index] = tree[index*2] + tree[index*2+1];
        }
    }

    // [left,right) interval
    T query(int left, int right) {
        T sum = DEFAULT;
        for (left += len, right += len; left < right; left /= 2, right /= 2) {
            if (left % 2 == 1) { sum += tree[left++]; }
            if (right % 2 == 1) { sum += tree[--right]; }
        }
        return sum;
    }
};