#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    struct node {
        int lazy;
        int sum;
        node() {
            lazy = 0;
            sum = 0;
        }
    };
    node merge(node a, node b) {
        node ans;
        ans.sum = a.sum + b.sum;
        return ans;
    }
    int n;
    vector<node> t;
    SegmentTree(int N) {
        n = N;
        t.resize(4*N+5);
    }  
    void print() {
        for(auto &e : t) {
            cerr << "[" << e.sum << " " << e.lazy << "] ";
        }
        cerr << "\n";
    }
    void push(int id, int l, int r) {
        if(t[id].lazy) {
            //if there is lazy then apply and push down
            t[id].sum += (r-l+1)*t[id].lazy;
            //push down logic if not leaf
            if(l != r) {
                t[id<<1].lazy += t[id].lazy;
                t[id<<1|1].lazy += t[id].lazy;
            }
            //clear
            t[id].lazy = 0;
        }
    }
    void build(vector<int> &a, int id, int l, int r) {
        if(l == r) {
            //leaf node
            t[id].sum = a[l];
            t[id].lazy = 0;
        } else {
            int mid = l+r>>1;
            build(a, id<<1, l, mid);
            build(a, id<<1|1, mid+1, r);
            t[id] = merge(t[id<<1], t[id<<1|1]); 
        }
    }
    void update(int id, int l, int r, int lq, int rq, int val) {
        push(id, l, r);
        //no overlap
        if(lq > r || l > rq) return;
        if(lq <= l && r <= rq) {
            //compete overlap
            t[id].lazy += val;
            push(id, l, r);
        } else {
            //partial overlap
            int mid = l+r>>1;
            update(id<<1, l, mid, lq, rq, val);
            update(id<<1|1, mid+1, r, lq, rq, val);
            t[id] = merge(t[id<<1], t[id<<1|1]); 
        }
    }
    node query(int id, int l, int r, int lq, int rq) {
        push(id, l, r);
        //no overlap
        if(lq > r || l > rq) return node();
        //complete overlap
        if(lq <= l && r <= rq) return t[id];
        //partial overlap
        int mid = l+r>>1;
        node left = query(id<<1, l, mid, lq, rq);
        node right = query(id<<1|1, mid+1, r, lq, rq);
        return merge(left, right);
    }
    int query(int lq, int rq) {
        node ans = query(1, 0, n-1, lq, rq);
        return ans.sum;
    }
    void update(int lq, int rq, int val) {
        update(1, 0, n-1, lq, rq, val);
    }
};

int main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    SegmentTree st(n);
    st.build(a, 1, 0, n-1);
    for(int i = 0; i < 4*n+1; i++) {
        cout << st.t[i].sum << " ";
    }
    cout << st.query(0, 2) << endl;
    st.update(0, 2, 2);
    cout << st.query(0, 2) << endl;
}