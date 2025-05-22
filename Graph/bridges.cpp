#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> adj;
vector<bool> vis;
vector<int> tin, low;
int timer;
vector<pair<int, int>> brides;

void dfs(int v, int p = -1)
{
    vis[v] = 1;
    tin[v] = low[v] = timer++;

    for (int &to : adj[v])
    {
        if (to == p)
            continue;
        if (vis[to])
        {
            low[v] = min(low[v], tin[to]);
        }
        else
        {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])
            {
                brides.emplace_back(v, to);
            }
        }
    }
}

void find_bridges()
{
    timer = 0;
    vis.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    brides.clear();
    for (int i = 0; i < n; ++i)
    {
        if (!vis[i])
            dfs(i);
    }
}

void solve()
{
    cin >> n >> m;
    adj.resize(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        // x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    find_bridges();
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<int> h(n), up(n);
    vector<bool> vis(n);
    vector<pair<int, int>> bridges;

    auto dfs = [&](auto self, int v, int p = -1) -> void
    {
        vis[v] = 1;
        up[v] = h[v];
        for (auto u : adj[v])
        {
            if (u == p)
                continue;
            if (vis[u])
                up[v] = min(up[v], h[u]);
            else
            {
                h[u] = h[v] + 1;
                self(self, u, v);
                up[v] = min(up[v], up[u]);
                if (up[u] > h[v])
                {
                    bridges.emplace_back(u + 1, v + 1);
                }
            }
        }
    };
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
            dfs(dfs, i);
    }
}

int32_t main()
{
    solve();
}
