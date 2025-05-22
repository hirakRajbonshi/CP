#include <bits/stdc++.h>
using namespace std;

template <class T>
struct MergeSortTree {
    int n;
    vector<vector<T>> t;
    MergeSortTree(int N) {
        n = N;
        t.resize(4*n + 5);
    }

    void build(vector<T> &a, int v, int l, int r) {
        if(l == r) {
            t[v].push_back(a[l]);
        } else {
            int m = l+r>>1;
            build(a, v<<1, l, m);
            build(a, v<<1|1, m+1, r);
            //two pointer for merge two verctor
            int i = 0, j = 0;
            while(i < t[v<<1].size() && j < t[v<<1|1].size()) {
                if(t[v<<1][i] < t[v<<1|1][j]) t[v].push_back(t[v<<1][i++]);
                else t[v].push_back(t[v<<1|1][j++]);
            }
            while(i < t[v<<1].size()) t[v].push_back(t[v<<1][i++]);
            while(j < t[v<<1|1].size()) t[v].push_back(t[v<<1|1][j++]);
        }
    }

    T query(int v, int l, int r, int lq, int rq, int x) {
        // outside
        if(lq > r || l > rq) return 0;
        // inside do binary search
        if(lq <= l && r <= rq) {
            int low = 0, high = t[v].size()-1;
            int ans = 0;
            while(low <= high) {
                int mid = low+high>>1;
                if(t[v][mid] < x) {
                    ans = mid+1;
                    low = mid+1;
                } else high = mid-1;
            }
            return ans;
        }
        int m = l+r>>1;
        return query(v<<1, l, m, lq, rq, x) + query(v<<1|1, m+1, r, lq, rq, x);
    } 
};

//given an array a1,a2,a3...an and an integer q. The i_th of the next q lines has three integers li,ri,xi. The answer for this query is how many aj such that li≤j≤ri and aj<x

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &e : a) cin >> e;
    MergeSortTree<int> mst(n);
    mst.build(a, 1, 0, n-1);
    int q;
    cin >> q;
    while(q--) {
        int l, r, x;
        cin >> l >> r >> x;
        cout << mst.query(1, 0, n-1, l-1, r-1, x) << "\n";
    }
    return 0;
}