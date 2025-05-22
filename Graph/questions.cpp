#include <bits/stdc++.h>

using namespace std;




//Break Up - Shayan's solution
{
    const int N = 1005, M = 30005, INF = 1e9;

    struct edge {
        int u, v, w;
    } e[M];

    int n, m, s, t, res = INF;
    int h[N], up[N];
    bool vis[N];
    vector<int> adj[N], ans;
    vector<int> path, cut_edge;


    bool dfs1(int v, int dest) {
        vis[v] = 1;
        if(v == dest) return true;
        for(auto ed : adj[v]) {
            int u = e[ed].u ^ e[ed].v ^ v; // u = nei
            if(vis[u]) continue;
            if(dfs1(u, dest)) {
                path.push_back(ed);
                return true;
            }
        }
        return false;
    }

    bool dfs2(int v, int dest, int dead, int parent_edge = -1) {
        vis[v] = 1;
        up[v] = h[v];
        int has_dest = (v == dest);
        for(auto ed : adj[v]) {
            if(ed == dead || ed == parent_edge) continue;
            int u = e[ed].u ^ e[ed].v ^ v;
            if(vis[u]) up[v] = min(up[v], h[u]);
            else {
                h[u] = h[v]+1;
                has_dest |= dfs2(u, dest, dead, ed);
                up[v] = min(up[v], up[u]);
            }

        }
        if(h[v] == up[v] && parent_edge != -1 && has_dest) 
            cut_edge.push_back(parent_edge);
        return has_dest;

    }

    void solve() {
        cin>>n>>m>>s>>t; s--, t--;
        for(int i = 0; i < m; i++) {
            int &u = e[i].u, &v = e[i].v, &w = e[i].w;
            cin>>u>>v>>w; u--, v--;
            adj[u].push_back(i);
            adj[v].push_back(i);
        }
        if(!dfs1(s, t)) {
            cout << "0\n0\n";
            return;
        }
        for(auto ed : path) {
            int dead = ed, w = e[ed].w;
            
            cut_edge.clear();
            memset(vis, 0, sizeof vis);

            if(!dfs2(s, t, ed)) {
                if(res > w) {
                    res = w;
                    ans = {ed};
                }
            }
            for(auto ed2 : cut_edge) {
                int w2 = e[ed2].w;
                if(res > w + w2) {
                    res = w + w2;
                    ans = {ed, ed2};
                }
            }
        }
        if(ans.empty() && cout << "-1\n") return;
        cout << res << "\n" << ans.size() << "\n";
        for(auto ed: ans) cout << ed + 1 << " ";
        cout << "\n";


    }
}
 



int32_t main() {
#ifndef ONLINE_JUDGE
    freopen("./files/input.txt", "r", stdin);
    freopen("./files/output.txt", "w", stdout);
    freopen("./files/error.txt", "w", stderr);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int _TEST = 1;
    // cin>>_TEST;
    for(int _ = 1; _ <= _TEST; _++) {
        solve();
    }
    return 0;
        
}


