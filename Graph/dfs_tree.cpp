#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin>>n>>m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int x, y; cin>>x>>y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    //Finding bridges in a graph
    vector<int> h(n), up(n);
    vector<bool> vis(n);
    set<pair<int, int>> bridges;
    auto dfs = [&] (auto self, int v, int p = -1) -> void {
        vis[v] = 1;
        up[v] = h[v];
        for(auto u : adj[v]) {
            if(u == p) continue;
            if(vis[u]) up[v] = min(up[v], h[u]);
            else {
                h[u] = h[v]+1;
                self(self, u, v);
                up[v] = min(up[v], up[u]);
                if(up[u] > h[v]) {
                    bridges.insert({u, v});
                }
            }
        }
    }; 
    for(int i = 0; i < n; i++) {
        if(!vis[i]) dfs(dfs, i);
    }

    //Compressing all the cyles in to a node
    vis.assign(n, false);
    vector<int> ids(n);
    auto compress = [&] (auto self, int v, int p = -1, int id) -> void {
        ids[v] = id;
        vis[v] = 1;
        for(auto &u : adj[v]) {
            if(!vis[u] && !bridges.count({u, v}) && !bridges.count({v, u})) {
                self(self, u, v, id);
            }
        }
    };
    int id = 0;
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            compress(compress, i, -1, id);
            id++;
        }
    }

    //Constructing the dfs tree
    vector<vector<int>> dfs_tree(id);
    vector<pair<int, int>> dfs_tree_edges;
    for(auto &[u, v] : bridges) {
        dfs_tree[ids[u]].push_back(ids[v]);
        dfs_tree[ids[v]].push_back(ids[u]);
        dfs_tree_edges.emplace_back(ids[u], ids[v]);
    }
    for(auto &[u, v] : dfs_tree_edges) {
        cout << u << " " << v << "\n";
    }
 
}   

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}