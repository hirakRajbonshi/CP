#include <bits/stdc++.h>
using namespace std;

template <class T>
struct MergeSortTree {
    int n;
    vector<multiset<T>> t;
    MergeSortTree(int N) {
        n = N;
        t.resize(4*N + 5);
    }

    void build(vector<T> &a, int v, int l, int r) {
        if(l == r) {
            t[v].insert(a[l]);
        } else {
            int m = l+r>>1;
            build(a, v<<1, l, m);
            build(a, v<<1|1, m+1, r);
            for(int i = l; i <= r; i++)
                t[v].insert(a[i]);
        }
    }

    void update(int v, int l, int r, int pos, int val) {
        if(l == r) {
            t[v].erase(a[pos]);
            t[v].insert(val);
        } else {
            int m = l+r>>1;
            if(pos <= m) update(v<<1, l, m, pos, val);
            else update(v<<1|1, m+1, r, pos, val);
            t[v].erase(a[pos]);
            t[v].insert(val);
        }
    }

    T query(int v, int l, int r, int lq, int rq, int x) {
        if(l > rq || lq > r) return INT_MAX;
        if(lq <= l && r <= rq) {
            auto it = t[v].lower_bound(x);
            if(it == t[v].end()) return INT_MAX;
            return *it;
        }
        int m = l+r>>1;
        T left = query(v<<1, l, m, lq, rq, x);
        T right = query(v<<1|1, m+1, r, lq, rq, x);
        return min(left, right);
    }
};
//given an array a1,a2,a3...an and an integer q. The i_th of the next q lines has three integers li,ri,xi. The answer for this query is how many aj such that li≤j≤ri and aj<x

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &e : a) cin >> e;
    return 0;
}