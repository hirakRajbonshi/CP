#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> depth(n+1);

void dfs(int v, int p) {
    for(auto u : adj[v]) {
        if(u^p) {
            depth[u] = depth[v]+1;
            dfs(u, v);
        }
    }
}



int main() {
    cin>>n;
    for(int i = 0; i < n; i++) {
        int u, v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    preprocess(1);
}