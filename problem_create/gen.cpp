#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define endl '\n'
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll uid(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rng); }

// Tree generation
vector<pair<int, int>> tree(int n)
{
    vector<pair<int, int>> edges;
    int prufer[n - 2];
    for (int i = 0; i < n; i++)
    {
        prufer[i] = uid(1, n);
    }
    int m = n - 2;
    int vertices = m + 2;
    int vertex_set[vertices];
    for (int i = 0; i < vertices; i++)
        vertex_set[i] = 0;
    for (int i = 0; i < vertices - 2; i++)
        vertex_set[prufer[i] - 1] += 1;
    int j = 0;
    for (int i = 0; i < vertices - 2; i++)
    {
        for (j = 0; j < vertices; j++)
        {
            if (vertex_set[j] == 0)
            {
                vertex_set[j] = -1;
                edges.push_back({j + 1, prufer[i]});
                vertex_set[prufer[i] - 1]--;
                break;
            }
        }
    }
    j = 0;
    for (int i = 0; i < vertices; i++)
    {
        if (vertex_set[i] == 0 && j == 0)
        {
            edges.push_back({i + 1, -1});
            j++;
        }
        else if (vertex_set[i] == 0 && j == 1)
            edges.back().second = i + 1;
    }
    return edges;
}

// coneected graph generation
vector<pair<int, int>> connected_graph(int n, int m)
{
    vector<pair<int, int>> edges = tree(n);
    set<pair<int, int>> s = set<pair<int, int>>(edges.begin(), edges.end());
    while (edges.size() < m)
    {
        int u = uid(1, n);
        int v = uid(1, n);
        if (u == v)
            continue;
        if (s.find({u, v}) != s.end())
            continue;
        if (s.find({v, u}) != s.end())
            continue;
        s.insert({u, v});
        edges.push_back({u, v});
    }
    return edges;
}

void gen(int _t = -1)
{
    int n = uid(1, 100);
    int k = uid(1, n);
    cout << n << " " << k << endl;
    for (int i = 0; i < n; i++)
    {
        int x = uid(1, 1e4);
        cout << x << " ";
    }
    cout << endl;
}

int32_t main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif

    // int t = uid(1, 100);
    int t = 10;
    cout << t << endl;
    for (int i = 1; i <= t; i++)
    {
        gen(i);
    }
}