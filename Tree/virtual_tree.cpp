#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

#define ll long long
#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    const int LG = 20;
    vector<vector<int>> up(n, vector<int>(LG)), at(n);
    vector<int> tin(n), tout(n);
    int timer = 0;
    auto dfs = [&](auto dfs, int v, int p) -> void
    {
        tin[v] = timer++;
        up[v][0] = p;
        for (int i = 1; i < LG; i++)
            up[v][i] = up[up[v][i - 1]][i - 1];
        for (int &u : adj[v])
            if (u != p)
                dfs(dfs, u, v);
        tout[v] = timer++;
    };
    dfs(dfs, 0, 0);
    auto is_ancestor = [&](int u, int v)
    {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    };
    auto lca = [&](int u, int v) -> int
    {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        for (int i = LG - 1; i >= 0; i--)
            if (!is_ancestor(up[u][i], v))
                u = up[u][i];
        return up[u][0];
    };

    vector<vector<int>> vadj(n);
    // Returns the nodes of the virtual tree for the given nodes in 'a'.
    // The virtual tree is stored in 'vadj'.
    auto vtree = [&](vector<int> &a) -> vector<int>
    {
        if (a.empty())
            return {};
        sort(a.begin(), a.end(), [&](const int &u, const int &v)
             { return tin[u] < tin[v]; });

        auto res = a;
        for (int i = 1; i < a.size(); i++)
            res.push_back(lca(a[i - 1], a[i]));

        sort(res.begin(), res.end(), [&](const int &u, const int &v)
             { return tin[u] < tin[v]; });
        res.erase(unique(res.begin(), res.end()), res.end());

        for (int &e : res)
            vadj[e].clear();

        for (int i = 1; i < res.size(); i++)
            vadj[lca(res[i - 1], res[i])].push_back(res[i]);

        return res;
    };
}