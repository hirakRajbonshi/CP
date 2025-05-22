#include <bits/stdc++.h>
using namespace std;

int n, l;
vector<vector<int>> adj;

int timer;
vector<int> Enter, Exit;
vector<vector<int>> up;

void dfs(int v, int p)
{
    Enter[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];

    for (int u : adj[v])
    {
        if (u != p)
            dfs(u, v);
    }

    Exit[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return Enter[u] <= Enter[v] && Exit[u] >= Exit[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i)
    {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root)
{
    Enter.resize(n + 1);
    Exit.resize(n + 1);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    preprocess(1);
}

void solve()
{

    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int timer = 0;
    vector<int> tin(n), tout(n);
    int LG = ceil(log2(n));
    vector<vector<int>> up(n, vector<int>(LG + 1));
    vector<int> height(n);
    auto dfs = [&](auto dfs, int v, int p) -> void
    {
        tin[v] = timer++;
        up[v][0] = p;
        for (int i = 1; i <= LG; i++)
        {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }
        for (auto &u : adj[v])
        {
            if (u ^ p)
            {
                height[u] = height[v] + 1;
                dfs(dfs, u, v);
            }
        }
        tout[v] = timer++;
    };
    dfs(dfs, 0, 0);
    auto is_ancestor = [&](int u, int v)
    {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    };
    auto lca = [&](int u, int v)
    {
        if (is_ancestor(u, v))
            return u;
        if (is_ancestor(v, u))
            return v;
        for (int i = LG; i >= 0; i--)
        {
            if (!is_ancestor(up[u][i], v))
                u = up[u][i];
        }
        return up[u][0];
    };
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        int _lca = lca(a, b);
        cout << height[a] + height[b] - 2 * height[_lca] << "\n";
    }
}