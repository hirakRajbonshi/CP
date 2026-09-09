// QUESTION: https://codeforces.com/group/wlb0UYQSQF/contest/712791/problem/C
const long long INF = 1e18;
struct Graph {
    int n;
    vector<vector<pair<int, long long>>> adj;

    Graph() {}
    Graph(int _n) : n(_n) {
        adj.resize(n);
    }

    void add_edge(int u, int v, long long w) {
        adj[u].emplace_back(v, w);
    }

    vector<long long> dijkstra(int src) {
        vector<long long> dist(n, INF);
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

        auto relax = [&] (int v, long long d) {
            if (d < dist[v]) {
                dist[v] = d;
                pq.emplace(d, v);
            }
        };
        relax(src, 0);
        while (!pq.empty()) {
            auto [d, v] = pq.top(); pq.pop();
            if (d > dist[v]) continue;
            for (auto &[u, w] : adj[v]) {
                relax(u, d + w);
            }
        }
        return dist;
    }
};

struct SegmentTree {
    int n;
    vector<int> in, out;
    int node;
    Graph g;

    SegmentTree(int _n) : n(_n), node(_n) {
        in.resize(n << 2);
        out.resize(n << 2);
        g = Graph(n + 2 * 4 * n);
    }

    void add_edge(int u, int v, long long w) {
        g.add_edge(u, v, w);
    }

    void build(int id, int l, int r) {
        if (l == r) {
            in[id] = l;
            out[id] = l;
            return;
        }
        in[id] = node++;
        out[id] = node++;

        int m = l + r >> 1;
        build(id << 1, l, m);
        build(id << 1 | 1, m + 1, r);

        g.add_edge(in[id], in[id << 1], 0);
        g.add_edge(in[id], in[id << 1 | 1], 0);

        g.add_edge(out[id << 1], out[id], 0);
        g.add_edge(out[id << 1 | 1], out[id], 0);
    }

    void add_edge_to_range(int id, int l, int r, int ql, int qr, int v, long long w) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            g.add_edge(v, in[id], w);
            return;
        }
        int m = l + r >> 1;
        add_edge_to_range(id << 1, l, m, ql, qr, v, w);
        add_edge_to_range(id << 1 | 1, m + 1, r, ql, qr, v, w);
    }

    void add_edge_from_range(int id, int l, int r, int ql, int qr, int v, long long w) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            g.add_edge(out[id], v, w);
            return;
        }
        int m = l + r >> 1;
        add_edge_from_range(id << 1, l, m, ql, qr, v, w);
        add_edge_from_range(id << 1 | 1, m + 1, r, ql, qr, v, w);
    }
};
