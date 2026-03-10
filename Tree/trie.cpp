const int N = 26;
struct Node {
    int cnt;
    int children[N];

    Node() {
        cnt = 0;
        for (int i = 0; i < N; i++) children[i] = -1;
    }

    bool containsKey(char c) {
        return children[c - 'a'] != -1;
    }

    void add(char c, int node) {
        children[c - 'a'] = node;
    }

    int get(char c) {
        return children[c - 'a'];
    }
};

struct Trie {
    vector<Node> trie;
    Trie() {
        trie.push_back(Node()); 
    }
    void clear() {
        trie.clear();
        trie.push_back(Node());
    }
    void insert(string word) {
        int node = 0;
        for (char &c : word) {
            if (!trie[node].containsKey(c)) {
                trie[node].add(c, trie.size());
                trie.push_back(Node());
            }
            node = trie[node].get(c);
            trie[node].cnt++;
        }
    }
    ll search(string word) {
        int node = 0;
        ll res = 0;
        for (char &c : word) {
            if (!trie[node].containsKey(c)) break;

            node = trie[node].get(c);
            res += 2ll * trie[node].cnt;
        }

        return res;
    }
};
