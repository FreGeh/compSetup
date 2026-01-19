struct AhoCorasick { // find all occurrences of specific set of words in single pass
    static const int A = 26; // alphabet size
    static const int OFF = 'a';
    
    struct Vert {
        array<int, A> next = {}; // Transitions
        int count = 0; // marked
    };

    vector<Vert> trie;

    AhoCorasick() { trie.emplace_back(); } // init

    void add_string(const string& s) {
        int v = 0;
        for(char c : s) {
            int i = c - OFF;
            if(!trie[v].next[i]) {
                trie[v].next[i] = trie.size();
                trie.emplace_back();
            }
            v = trie[v].next[i];
        }
        trie[v].count++; // mark end of word
    }

    void finalize() {
        queue<array<int,4>> q; // {current_node, parent, parent_link, char_from_parent}
        q.push({0, 0, 0, 0});

        while(!q.empty()) {
            auto [v, p, plink, pch] = q.front(); q.pop();
            
            int link = (p == 0) ? 0 : trie[plink].next[pch]; // suffix link

            if (v != 0) trie[v].count += trie[link].count; // propagate counts

            for(int c = 0; c < A; ++c) {
                if(trie[v].next[c]) { // child exists
                    q.push({trie[v].next[c], v, link, c});
                } else { // no child
                    trie[v].next[c] = trie[link].next[c];
                }
            }
        }
    }
    
    long long query(const string& s) {
        long long res = 0;
        int v = 0;
        for(char c : s) {
            v = trie[v].next[c - OFF];
            res += trie[v].count;
        }
        return res;
    }
};