struct PersistentSegTree {
    // change 
    struct Node { 
        int mn, left, right;
        Node() : mn(INT_MAX), left(0), right(0) {}
        Node(int val) : mn(val), left(0), right(0) {}
        Node(int val, int l, int r) : mn(val), left(l), right(r) {}
    };

    const int n; 
    vector<Node> tree;
    int time = 1;

    // change
    Node merge(int l, int r) { return Node(min(tree[l].mn, tree[r].mn), l, r); }

    int build(int l, int r) { // change 
        if (l == r) {
            tree[time] = Node(); 
            return time++;
        }
        int m = l + r >> 1;
        tree[time] = merge(build(l, m), build(m + 1, r));
        return time++;
    }

    int update(int v, int pos, int val, int l, int r) {
        if (l == r) {
            tree[time] = Node(val);
            return time++;
        }
        int m = l + r >> 1;
        if (pos > m) tree[time] = merge(tree[v].left, update(tree[v].right, pos, val, m + 1, r));
        else tree[time] = merge(update(tree[v].left, pos, val, l, m), tree[v].right);
        return time++;
    }
    int query(int v, int ql, int qr, int l, int r) {
        if (l > r || ql > r || l > qr) return INT_MAX; // change
        if (ql <= l && r <= qr) return tree[v].mn;
        int m = l + r >> 1;
        return min(query(tree[v].left, ql, qr, l, m), query(tree[v].right, ql, qr, m + 1, r)); // change
    }

    PersistentSegTree(int n, int mx_node) : n(n), tree(mx_node) {}
    int build() { return build(0, n - 1); }
    int update(int root, int pos, int val) { return update(root, pos, val, 0, n - 1); }
    int query(int root, int l, int r) { return query(root, l, r, 0, n - 1); }
};
// int mx_node = 2 * n + q * (2 + __lg(n));
// PersistentSegTree sg(n, mx_node);
