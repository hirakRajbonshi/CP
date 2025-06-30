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
