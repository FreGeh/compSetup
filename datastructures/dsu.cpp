struct DSU {
// Index 0 unused, 1 = Root, 1 to len-1 = Internal, len to 2*len-1 = Leaves
    vector<int> parent,size;
    DSU() {}
    DSU(int n) { init(n); }

    void init(int n) {
        parent.resize(n);
        size.assign(n, 1);
    }

    void make_set(int v) {
        parent[v] = v;
        size[v] = 1;
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }

    int find(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }

    int get_size(int v) {
        return size[find(v)];
    }
};