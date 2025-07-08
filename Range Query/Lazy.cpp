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









template<typename node>
struct SegmentTree {
    int n;
    vector<node> t;

    SegmentTree(int N) {
        t.resize(N << 2 | 3);
        n = N;
    }
    SegmentTree(vector<int> &a) : SegmentTree((int)a.size()) {
        build(a, 1, 0, n - 1);
    }

    void build(vector<int>& a, int id, int l, int r) {
        if (l == r) {
            t[id] = node(a[l]);
        } else {
            int m = l + r >> 1, idL = id << 1, idR = id << 1 | 1;
            build(a, idL, l, m);
            build(a, idR, m + 1, r);
            t[id].merge(t[idL], t[idR]);
        }
    }


    void push(int id, int l, int r) {
        if (l == r) {
            t[id].apply(l, r);
            return;
        }
        int idL = id << 1, idR = id << 1 | 1;
        t[idL].set(t[id]);
        t[idR].set(t[id]);
        t[id].apply(l, r);

    }
    void update(int id, int l, int r, int lq, int rq, int val, int type) { // here
        push(id, l, r);
        if (lq > r || l > rq) return;
        if (lq <= l && r <= rq) {
            t[id].set(type, val); // here
            push(id, l, r);
            return;
        }
        int idL = id << 1, idR = id << 1 | 1;
        int m = l + r >> 1;
        update(idL, l, m, lq, rq, val, type);
        update(idR, m + 1, r, lq, rq, val, type);
        t[id].merge(t[idL], t[idR]);
    }

    node query(int id, int l, int r, int lq, int rq) {
        push(id, l, r);
        if (lq > r || l > rq) return node();
        if (lq <= l && r <= rq) {
            return t[id];
        }
        int m = l + r >> 1;
        int idL = id << 1, idR = id << 1 | 1;
        node res = node();
        node left = query(idL, l, m, lq, rq);
        node right = query(idR, m + 1, r, lq, rq); 
        res.merge(left, right);
        return res;
    }   


    void update(int l, int r, int val, int type) { // here
        update(1, 0, n - 1, l, r, val, type);
    }
    int query(int l, int r) {
        node res = query(1, 0, n - 1, l, r);
        return res.sum; // here
    }

};

struct Node {
    int sum;
    int pendingSet, pendingInc;
    Node() {
        sum = 0;
        pendingSet = 0;
        pendingInc = 0;
    }
    Node(int &val) : Node() {
        sum = val;
    }
    void merge(Node &a, Node &b) {
        sum = a.sum + b.sum;
    }
    void set(Node &par) {
        if (par.pendingSet) {
            pendingSet = par.pendingSet;
            pendingInc = 0;
        } else if(par.pendingInc) {
            if (pendingSet) {
                pendingSet += par.pendingInc;
            } else {
                pendingInc += par.pendingInc;
            }
        }
    }
    void set(int type, int val) {
        if (type == 1) {
            pendingSet = val;
            pendingInc = 0;
        } else {
            if (pendingSet) pendingSet += val;
            else pendingInc += val;
        }
    }
    void apply(int l, int r) {
        if (pendingSet) {
            sum = (r - l + 1) * pendingSet;
            pendingSet = 0;
        } else if(pendingInc) {
            sum += (r - l + 1) * pendingInc;
            pendingInc = 0;
        }
    }
};
