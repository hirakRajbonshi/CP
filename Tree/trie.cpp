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


// trie implementation for finding MEX
template <typename node, size_t N, size_t B> 
struct Trie {
  vector<node> tree;
  Trie() {
    tree.clear();
    tree.reserve(N * B);
    tree.push_back(node());
  }
  void insert(int x) {
    stack<int> st;
    int cur = 0;
    for (int i = B - 1; i >= 0; i--) {
      int b = x >> i & 1;
      if (!tree[cur].have(b)) {
        tree[cur].add(b, tree.size());
        tree.push_back(node());
      }
      cur = tree[cur].get(b);
      st.push(cur);
    }
    st.pop();
    tree[cur].present = true;
    tree[cur].cnt++;
    while (!st.empty()) {
      cur = st.top(); st.pop();
      tree[cur].cnt = 0;
      for (int b = 0; b < 2; b++) 
        if (tree[cur].have(b))
            tree[cur].cnt += tree[tree[cur].get(b)].get_cnt();
    }
  }
  void erase(int x) {
    stack<int> st;
    int cur = 0;
    for (int i = B - 1; i >= 0; i--) {
        int b = x >> i & 1;
        assert(tree[cur].have(b));
        cur = tree[cur].get(b);
        st.push(cur);
    }
    st.pop();
    tree[cur].cnt--;
    if (!tree[cur].cnt) tree[cur].present = false;
    while (!st.empty()) {
        cur = st.top(); st.pop();
        tree[cur].cnt = 0;
        for (int b = 0; b < 2; b++) 
        if (tree[cur].have(b))
            tree[cur].cnt += tree[tree[cur].get(b)].get_cnt();
    }
  }
  int find() {
    int cur = 0, res = 0;
    for (int i = B - 1; i >= 0; i--) {
      bool ok = false;
      if (tree[cur].have(0)) {
        int cnt = tree[tree[cur].get(0)].get_cnt();
        ok = cnt == (1 << i);
      }
      if (ok) {
        res ^= (1 << i);
        if (tree[cur].have(1)) cur = tree[cur].get(1);
        else break;
      } else {
        if (tree[cur].have(0)) cur = tree[cur].get(0);
        else break;
      }
    }
    return res;
  }
};
struct node {
  int cnt;
  bool present;
  int children[2];
  node() {
    cnt = 0;
    present = false;
    children[0] = children[1] = -1;
  }
  bool have(int b) { return ~children[b]; }
  int get(int b) { return children[b]; }
  void add(int b, int idx) { children[b] = idx; }
  int get_cnt() { return present ? 1 : cnt; }
};
