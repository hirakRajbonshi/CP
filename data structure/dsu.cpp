#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
    }
    DSU(vector<int> &v) {
        int n = v.size();
        parent.resize(n);
        rank.resize(n);
        for(int i = 0; i < n; i++) {
            make_set(v[i]);
        }
    }

    void make_set(int v) {
        parent[v] = v;
        rank[v] = 0;
    }

    int find_set(int v) {
        if(v == parent[v]) {
            return v;
        }
        return parent[v] = find_set(parent[v]); 
    }

    void unite_set(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if(a != b) {
            if(rank[a] < rank[b]) {
                swap(a, b);
            }
            parent[b] = a;
            if(rank[a] == rank[b]) 
                rank[a]++;
        }
    }

};




// by size
struct DSU {
    int n; 
    vector<int> p;
    vector<int> size;

    DSU(int _n) {
        n = _n;
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        size.assign(n, 1);
    }

    int get(int x) {
        return x == p[x] ? x : (p[x] = get(p[x]));
    }

    bool merge(int x, int y) {
        x = get(x), y = get(y);
        if(x == y) return false;
        size[x] += size[y];
        p[y] = x;
        return true;
    }

    int get_size(int x) {return size[get(x)];}
};





