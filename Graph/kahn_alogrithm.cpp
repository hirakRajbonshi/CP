#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m; cin>>n>>m;
    vector<int> adj[n+1], inDegree(n+1), ts;
    for(int i = 0; i < m; i++) {
        int u, v; cin>>u>>v;
        adj[u].push_back(v);
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i = 1; i <= n; i++) {
        for(int &u : adj[i]) {
            inDegree[u]++;
        }
    }
    for(int i = 1; i <= n; i++) {
        if(inDegree[i] == 0) pq.push(i);
    }
    while(!pq.empty()) {
        int v = pq.top();
        pq.pop();
        ts.push_back(v);
        for(int &u : adj[v]) {
            inDegree[u]--;
            if(inDegree[u] == 0) pq.push(u);
        }
    }
    if(ts.size() != n) cout<<"IMPOSSIBLE\n";
    else {
        for(int &i : ts) cout<<i<<" ";
        cout<<"\n";
    }
}
