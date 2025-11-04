#include "bits/stdc++.h"
using namespace std;
#define ll long long

template <class T> class Segment_Tree_Sum {

private:
const T DEFAULT = 0;
int len;
vector<T> tree;

public:
Segment_Tree_Sum(int len) : len(len), tree(len * 4, DEFAULT) {}

void set(int index, T val) {
    index += len;
    tree[index] = val;
    for (index >>= 1; index >= 1; index >>= 1) {
        tree[index] = tree[index<<1] + tree[index<<1|1];
    }
}

T query(int left, int right) {
    T sum = DEFAULT;
    for (left += len, right += len; left < right; left /= 2, right /= 2) {
        if (left % 2 == 1) { sum += tree[left++]; }
        if (right % 2 == 1) { sum += tree[--right]; }
	}
	return sum;
}
};