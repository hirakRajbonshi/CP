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
