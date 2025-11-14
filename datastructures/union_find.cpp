#include "bits/stdc++.h"
using namespace std;
#define ll long long

template <class T> class Union_Find {
// Index 0 unused, 1 = Root, 1 to len-1 = Internal, len to 2*len-1 = Leaves

private:
    const T DEFAULT = 0;
    vector<T> parent,size;

public:
    void make_set(int v) {
        parent[v] = v;
        size[v] = 1;
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set(parent[v]);
    }
};