const int N = 2e5 + 10;
int n, q;
vector<int> adj[N];
vector<int> a, top, depth, sz, idxs;

namespace sgtree {
    int DEFAULT = 0;
    vector<int> st;
    int merge(int a, int b) {
        return a + b;
    }

    void set(int idx, int val) {
        st[idx += n] = val;
        for(; idx >>= 1; )
            st[idx] = merge(st[idx << 1], st[idx << 1 | 1]);
    }
    // query in the first k ancestor of v including v in the same chain
    // if k is greater than the chain then it will not work
    int query(int v, int k) {
        int r = idxs[v] + 1 + n, l = r - k;
        int res = DEFAULT;
        for(; l < r; l >>= 1, r >>= 1) {
            if(l & 1) res = merge(res, st[l++]);
            if(r & 1) res = merge(res, st[--r]);
        }
        return res;
    }
}

int dfs_sz(int v, int p) {
    sz[v] = 1;
    depth[v] = depth[p] + 1;
    for(auto &u : adj[v]) if(u ^ p) {
        sz[v] += dfs_sz(u, v);
    }
    sort(adj[v].begin(), adj[v].end(), [&] (int &i, int &j) {
        return sz[i] > sz[j];
    });
    return sz[v];
}

int pos = 1;
void dfs_hld(int v, int p, int tp) {
    top[v] = tp;
    idxs[v] = pos++;
    sgtree::set(idxs[v], a[v]);
    for(auto &u : adj[v]) if(u ^ p) {
        dfs_hld(u, v, tp);
        tp = v;
    }
}

int query(int u, int v) {
    if(depth[u] - depth[v] == idxs[u] - idxs[v]) {
        if(depth[u] > depth[v]) swap(u, v);
        return sgtree::query(v, depth[v] - depth[u] + 1);
    } 
    if(depth[top[u]] > depth[top[v]]) swap(u, v);
    return sgtree::merge(query(u, top[v]), sgtree::query(v, depth[v] - depth[top[v]]));
}

void init() {
    a.resize(n + 1, 0);
    sz.resize(n + 1, 0);
    top.resize(n + 1, 0);
    depth.resize(n + 1, 0);
    idxs.resize(n + 1, 0);
    sgtree::st.resize(2 * (n + 1));
    for(int i = 0; i <= n; i++) adj[i].clear();

}

void solve() {
    cin >> n >> q;
    init();
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 2; i <= n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs_sz(1, 0);
    dfs_hld(1, 0, 0);

    while(q--) {
        int c; cin >> c;
        if(c == 1) {
            int s, x; cin >> s >> x;
            a[s] = x;
            sgtree::set(idxs[s], a[s]);
        } else {
            int s; cin >> s;
            int res = query(1, s);
            cout << res << "\n";
        }
    }
}


// EyadBT's HLD
struct HLD{
    vector<vector<int>> adj;
    vector<int> sz, head, par, depth, ve, in, out;
    int n;
    int Time = -1;
    HLD() {}
    HLD(int n) : n(n + 1){
        n++;
        adj.resize(n);
        sz.resize(n);
        head.resize(n);
        par.resize(n);
        depth.resize(n);
        in.resize(n);
        out.resize(n);
    }
    void add_edge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void build(int r = 1){
        init(r, r);
        DFS(r, r, r);
    }
    void init(int u, int p, int d = 0){
        sz[u] = 1;
        par[u] = p;
        depth[u] = d;
        for(int v : adj[u]){
            if(v == p) continue;
            init(v, u, d + 1);
            sz[u] += sz[v];
        }
    }
 
    void DFS(int u, int p, int h){
        int mx = 0, nd = -1;
        head[u] = h;
        ve.push_back(u);
        in[u] = ++Time;
        for(int v : adj[u]){
            if(v == p) continue;
            if(sz[v] > mx){
                mx = sz[v];
                nd = v;
            }
        }
        if(nd != -1) DFS(nd, u, h);
        for(int v : adj[u]){
            if(v == p || v == nd) continue;
            DFS(v, u, v);
        }
        out[u] = Time;
    }
    
    bool is_parent(int u, int v){
        return in[v] >= in[u] && in[v] <= out[u];
    }
 
    int jump(int u, int k){
        k = min(k, depth[u]);
        while(in[u] - in[head[u]] < k){
            k -= in[u] - in[head[u]] + 1;
            u = par[head[u]];
        }
        return ve[in[u] - k];
    }
 
    int LCA(int u, int v){
        while(head[u] != head[v]){
            if(depth[head[u]] < depth[head[v]]) swap(u, v);
            u = par[head[u]];
        }
        if(depth[u] < depth[v]) return u;
        return v;
    }
} t;




// 2026
struct SegmentTree {
    int n;
    vector<int> tree;
    int merge(int a, int b) { return a + b; }

    SegmentTree(int _n) {
        n = _n;
        tree.resize(n << 1);
    }
    SegmentTree(const vector<int>& a) {
        n = a.size();
        tree.resize(n << 1);
        for (int i = 0; i < n; i++) tree[i + n] = a[i];
        for (int i = n - 1; i > 0; i--) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
    }
    void update(int idx, int v) {
        idx += n;
        tree[idx] = v;
        while (idx > 1) {
            tree[idx >> 1] = merge(tree[idx], tree[idx ^ 1]);
            idx >>= 1;
        }
    }
    int query(int l, int r) {
        int sum = 0;
        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) sum = merge(sum, tree[l++]);
            if (!(r & 1)) sum = merge(sum, tree[r--]);
        }        
        return sum;
    }
};

struct HLD {
    int n;
    vector<vector<int>> adj;
    vector<int> depth, size, parent, heavy, head, pos, a, arr;
    int cur;

    HLD(int _n) {
        n = _n;
        adj.assign(n + 1, vector<int>());
        depth.assign(n + 1, 0);
        size.assign(n + 1, 0);
        parent.assign(n + 1, 0);
        heavy.assign(n + 1, -1); // heavy[v] = heavy child of v
        head.assign(n + 1, 0); // head[v] = top most node of the heavy chain of v
        pos.assign(n + 1, 0);
        arr.assign(n, 0);
        a.assign(n + 1, 0);
        cur = 0; 
    }

    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }

    int dfs(int v, int p) {
        parent[v] = p;
        size[v] = 1;
        int mx = -1;
        heavy[v] = -1;
        for (int &u : adj[v]) if (u != p) {
            depth[u] = depth[v] + 1;
            int sz = dfs(u, v);
            size[v] += sz;
            if (sz > mx) {
                mx = sz;
                heavy[v] = u;
            }
        }
        return size[v];
    }

    void dfs_hld(int v, int h) {
        head[v] = h;
        pos[v] = cur;
        arr[cur] = a[v];
        cur++;
        if (~heavy[v]) {
            dfs_hld(heavy[v], h);
            for (int &u : adj[v]) if (u != parent[v] && u != heavy[v]) 
                dfs_hld(u, u);
        }
    }
    void build() {
        dfs(1, 0);
        dfs_hld(1, 1);
    }
    int query(int u, int v, SegmentTree &st) {
        int res = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                swap(u, v); // now v is lower so gonna move v up
            }
            // segment tree query from head[v] to v
            res = st.merge(res, st.query(pos[head[v]], pos[v]));
            v = parent[head[v]];
        }
        if (depth[u] > depth[v]) swap(u, v);
        // segment tree query from u to v
        res =  st.merge(res, st.query(pos[u], pos[v]));
        return res;
    }
};
