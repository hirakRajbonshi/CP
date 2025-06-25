#include <bits/stdc++.h>
using namespace std;

// Grid
void solve() {
    int n, m; cin>>n>>m;
    vector<vector<int>> grid(n, vector<int>(m));
    for(auto &row : grid) for(auto &e : row) cin>>e;

    vector<pair<int, int>> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    vector<vector<bool>> vis(n, vector<bool>(m));
    vector<vector<int>> up(n, vector<int>(m));
    vector<vector<int>> h(n, vector<int>(m));
    set<pair<int, int>> articulationPoints;
    auto dfs = [&] (auto dfs, int x, int y, int px = -1, int py = -1) -> void {
        vis[x][y] = 1;
        up[x][y] = h[x][y];
        int children = 0;
        for(auto &[dx, dy] : dirs) {
            int nx = x+dx, ny = y+dy;
            if(nx < 0 || ny < 0 || nx > n-1 || ny > m-1 || (nx == px && ny == py) || !grid[nx][ny]) 
                continue;
            if(!vis[nx][ny]) {
                children++;
                h[nx][ny] = h[x][y]+1;
                dfs(dfs, nx, ny, x, y);
                up[x][y] = min(up[x][y], up[nx][ny]);
                if(px != -1 && up[nx][ny] >= h[x][y])
                    articulationPoints.insert({x, y});
            } else {
                up[x][y] = min(up[x][y], h[nx][ny]);
            }
        }
        if(px == -1 && children > 1)
            articulationPoints.insert({x, y});
    };
    int cnt = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] && !vis[i][j]) {
                cnt++;
                dfs(dfs, i, j, i, j);
                // debug(i, j)
            }
        }
    }
    cout << cnt << "\n";


} 
// 
void solve(int __tt = -1) {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> up(n), h(n, 0);
    vector<bool> vis(n, false);
    vector<pair<int, int>> bridges;
    set<int> articulation_points;
    auto dfs = [&] (auto dfs, int v, int p = -1) -> void {
        vis[v] = true;
        up[v] = h[v];
        int children = 0;
        for(auto &u : adj[v]) {
            if(u == p) continue;
            if(vis[u]) up[v] = min(up[v], h[u]);
            else {
                h[u] = h[v] + 1;    
                dfs(dfs, u, v);
                up[v] = min(up[v], up[u]);
                if(up[u] >= h[v]) bridges.emplace_back(u, v); 
                if(up[u] >= h[v] && ~p) articulation_points.insert(v);
                children++;
            }
        }
            if(p == -1 && children > 1) articulation_points.insert(v);
    };
    for(int i = 0; i < n; i++) if(!vis[i]) dfs(dfs, i);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
