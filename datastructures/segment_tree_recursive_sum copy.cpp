#include "bits/stdc++.h"
using namespace std;
#define ll long long

vector<ll> tree;
//then
//tree.assign(4*n,0);
//build(inp, 1, 0, n-1);

void build(vector<int> &inp, int node, int l, int r) {
    if (l == r) {
        tree[node] = inp[l];
    } else {
        int mid = (l + r) / 2;
        build(inp, node*2, l, mid);
        build(inp, node*2+1, mid+1, r);
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}

ll query(int node, int l, int r, int q_l, int q_r) {
    if (q_l > q_r) {
        return 0;
    }
    else if (l == q_l && r == q_r) {
        return tree[node];
    }
    int mid = (l + r) / 2;
    return query(node*2, l, mid, q_l, min(q_r, mid))
        + query(node*2+1, mid+1, r, max(q_l, mid+1), q_r);
}

void update(int node, int l, int r, int pos, int new_val) {
    if (l == r) {
        tree[node] = new_val;
    } else {
        int mid = (l + r)/2;
        if (pos <= mid) {
            update(node*2, l, mid, pos, new_val);
        } else {
            update(node*2+1, mid+1, r, pos, new_val);
        }
        tree[node] = tree[node*2] + tree[node*2+1];
    }
}