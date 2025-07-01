const int N = 2e5 + 10;
int n, q;
vector<int> adj[N], sz, level, cPar;

int dfs_sz(int v, int p) {
    sz[v] = 1;
    for(auto &u : adj[v]) if(u != p && !level[u])
        sz[v] += dfs_sz(u, v);
    return sz[v];
}

int dfs_centroid(int v, int p, int n) {
    for(int &u : adj[v]) 
        if(u != p && !level[u] && sz[u] > n / 2) 
            return dfs_centroid(u, v, n);
    return v;
}

int dfs_decom(int v, int lvl) {
    int cent = dfs_centroid(v, -1, dfs_sz(v, -1));
    level[cent] = lvl;
    for(auto &u : adj[cent]) if(!level[u])
        cPar[dfs_decom(u, lvl + 1)] = cent;
    return cent;
}

void init() {
    sz.resize(n);
    level.resize(n);
    cPar.resize(n, -1);
    for(int i = 0; i < n; i++) adj[i].clear();
}

// call dfs(decom(any node, 1);
