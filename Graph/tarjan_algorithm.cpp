struct Tarjan {
    const vector<vector<int>> &adj;
    vector<vector<int>> radj;
    vector<int> post, comp;
    vector<bool> vis;
    int timer = 0, id = 0;

    void fill_post(int v) {
        vis[v] = true;
        for (int u : radj[v]) if (!vis[u]) fill_post(u);
        post[v] = timer++;
    }

    void find_comp(int v) {
        vis[v] = true;
        comp[v] = id;
        for (int u : adj[v]) if (!vis[u]) find_comp(u);
    }

    Tarjan(const vector<vector<int>>& adj) :
            adj(adj), radj(adj.size()), post(adj.size()), comp(adj.size()), vis(adj.size()) {
        
        vector<int> nodes(adj.size());
        for (int i = 0; i < adj.size(); i++) {
            nodes[i] = i;
            for (int j : adj[i]) radj[j].push_back(i);
        }
        for (int i = 0; i < adj.size(); i++) {
            if (!vis[i]) fill_post(i);
        }
        sort(nodes.begin(), nodes.end(), [&] (int i, int j) {
            return post[i] > post[j];
        });
        vis.assign(adj.size(), false);
        for (int &v : nodes) if (!vis[v]) {
            id++;
            find_comp(v);
        }
    }

    int comp_num() { return id; }
    int get_comp(int v) { return comp[v]; }

};

