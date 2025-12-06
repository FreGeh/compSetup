struct Treap {
    struct Node {
        int val, prio;
        int sz;
        ll sum;
        int mn,mx;
        bool rev;
        Node *l, *r;
        Node(int v, int p) : val(v), prio(p), sz(1), sum(val), mn(val), mx(val), rev(false), l(nullptr), r(nullptr) {}
    };

    ~Treap() { delete root; }

    Node* make_node(int v) {
        return new Node(v, (int)rng());
    }

    Node* root = nullptr;
    mt19937 rng{(uint32_t)chrono::steady_clock::now().time_since_epoch().count()};

    static int sz(Node* t) { return t ? t->sz : 0; }
    static ll sum(Node* t) { return t ? t->sum : 0LL; }
    static int mn(Node* t) { return t ? t->mn : INT_MAX; }
    static int mx(Node* t) { return t ? t->mx : INT_MIN; }

    static void apply_rev(Node* t) {
        if (t) {
            t->rev ^= 1;
            swap(t->l, t->r);
        }
    }

    static void push(Node* t){
        if (!t || !t->rev) return;
        apply_rev(t->l);
        apply_rev(t->r);
        t->rev = false;
    }

    static void pull(Node* t) {
        if (t) {
            t->sz = 1 + sz(t->l) + sz(t->r);
            t->sum = (ll)t->val + sum(t->l) + sum(t->r);
            t->mn = min(min(mn(t->l),mn(t->r)),t->val);
            t->mx = max(max(mx(t->l),mx(t->r)),t->val);
        }
    }

    static pair<Node*, Node*> split(Node* t, int k) {
        if (!t) return {nullptr, nullptr};
        push(t);
        if (sz(t->l) >= k) { // first k elements
            auto [a, b] = split(t->l, k);
            t->l = b;
            pull(t);
            return {a, t};
        } else { // remaining elemnts
            auto [a, b] = split(t->r, k - sz(t->l) - 1);
            t->r = a;
            pull(t);
            return {t, b};
        }
    }

    static Node* merge(Node* a, Node* b) { // concatenate b onto a
        if (!a) return b;
        if (!b) return a;
        if (a->prio < b->prio) { // min-heap on prio
            push(a);
            a->r = merge(a->r, b);
            pull(a);
            return a;
        } else {
            push(b);
            b->l = merge(a, b->l);
            pull(b);
            return b;
        }
    }

    void insert_at(int pos, int v) { // insert value v at pos 
        auto [a, b] = split(root, pos);
        root = merge(merge(a, make_node(v)), b);
    }

    void push_back(int v) { root = merge(root, make_node(v)); }

    void delete_at(int pos) {
        auto [a, rest] = split(root, pos);
        auto [selected, rest_new] = split(rest, 1);
        root = merge(a, rest_new);
        delete selected;
    }

    void print_at(int pos) {
        auto [a, rest] = split(root, pos);
        auto [selected, rest_new] = split(rest, 1);
        cout<<selected->val<<"\n";
        root = merge(a, merge(selected, rest_new));
    }

    void replace_at(int pos, int val) {
        auto [a, rest] = split(root, pos);
        auto [selected, rest_new] = split(rest, 1);
        root = merge(merge(a, make_node(val)), rest_new);
        delete selected;
    }

    ll sum_range(int l, int r) {
        if (l<=r) {
            auto [a, rest] = split(root,l);
            auto [m, b] = split(rest, r-l+1);
            ll sol = m? m->sum: 0;
            root=merge(merge(a,m),b);
            return sol;
        }
        return 0;
    }

    int min_range(int l, int r) {
        if (l<=r) {
            auto [a, rest] = split(root,l);
            auto [m, b] = split(rest, r-l+1);
            int sol = m? m->mn: INT_MAX;
            root=merge(merge(a,m),b);
            return sol;
        }
        return 0;
    }

    int max_range(int l, int r) {
        if (l<=r) {
            auto [a, rest] = split(root,l);
            auto [m, b] = split(rest, r-l+1);
            int sol = m? m->mx: INT_MIN;
            root=merge(merge(a,m),b);
            return sol;
        }
        return 0;
    }

    void move_range(int l, int r, int pos) { // pos is in the array after removing [l,r]
        if (l<=r) {
            auto [a, rest] = split(root,l);
            auto [m, b] = split(rest, r-l+1);

            auto glued = merge(a,b);
            auto [start, end] = split(glued,pos);
            root=merge(merge(start,m),end);
        }
    }

    void reverse_range(int l, int r) {
        if (l<=r) {
            auto [a, rest] = split(root,l);
            auto [m, b] = split(rest, r-l+1);

            apply_rev(m);
            root=merge(merge(a,m),b);
        }
    }

    void output(Node* t) {
        if (!t) return;
        push(t);
        output(t->l);
        cout<<t->val<<" ";
        output(t->r);
    }

    void print() {
        output(root);
        cout<<endl;
    }
};