#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;


//give the path from t to v, reverse it if neccessary
vector<int> dfs(int v, int p, int t) {
    if(v == t) return {v};
    for(auto u : adj[v]) {
        if(u^p) {
            vector<int> path = dfs(u, v, t);
            if(path.size()) {
                path.push_back(v);
                return path;
            }
        }
    } 
    return {};
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