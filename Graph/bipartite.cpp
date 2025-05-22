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
    vector<int> side(n, -1);
    int is_bipartite = 1;
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(side[i] == -1) {
            q.push(i);
            side[i] = 0;
            while(!q.empty()) {
                int v = q.front(); q.pop();
                for(auto &u : adj[v]) {
                    if(~side[u]) {
                        is_bipartite &= (side[u] != side[v]);
                    } else {
                        side[u] = side[v]^1;
                        q.push(u);
                    }
                }
            }
        }
    }
    cout << (is_bipartite ? "YES" : "NO") << "\n";
}