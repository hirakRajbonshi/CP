#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin>>n>>m;
    int flag = 1;
    vector<int> adj[n+1], vis(n+1), dfsVis(n+1), ts;
    for(int i = 0; i < m; i++) {
        int u, v; cin>>u>>v;
        adj[u].push_back(v);
    }
    function<void(int)> dfs = [&] (int v) {
        vis[v] = 1;
        dfsVis[v] = 1;
        for(int &u : adj[v]) {
            if(vis[u] && dfsVis[u]) flag = 0;
            else if(!vis[u]) dfs(u);
        }
        dfsVis[v] = 0;
        ts.push_back(v);
    };
    for(int i = 1; i <= n; i++) {
        if(!vis[i]) dfs(i);
    }
    reverse(ts.begin(), ts.end());
    if(!flag) cout<<"IMPOSSIBLE\n";
    else {
        for(int &i : ts) cout<<i<<" ";
        cout<<"\n";
    }
    return 0;
}