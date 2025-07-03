#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;


template<typename node>
struct SegmentTree {
    int n;
    vector<node> t;
    SegmentTree(int N) {
        t.resize(N<<2|1);
        n = N;
    }

    SegmentTree(vector<int> &v) : SegmentTree((int)v.size()) {
        build(v, 1, 0, n - 1);
    }

    void print(int id, int l, int r) {
        debug(l, r)
        t[id].print();
        if(l == r) return;
        int m = l+r>>1;
        print(id<<1, l, m);
        print(id<<1|1, m+1, r);
    }

    void build(vector<int> &a, int id, int l, int r) {
        if(l == r) {
            t[id] = node(a[l]);
            return;
        }
        int mid = (l+r)/2;
        build(a, id<<1, l, mid);
        build(a, id<<1|1, mid+1, r);
        t[id].merge(t[id<<1], t[id<<1|1]);
    }

    void update(int id, int l, int r, int pos, int val) {
        if(pos < l || pos > r) return; 
        if(l == r) {
            t[id] = node(val);
            return;
        }
        int mid = (l+r)/2;
        update(id*2, l, mid, pos, val);
        update(id*2+1, mid+1, r, pos, val);
        t[id].merge(t[id*2], t[id*2+1]);
    }

    node query(int id, int l, int r, int lq, int rq) {
        if(lq > r || l > rq) return node(); //no intersection
        if(lq <= l && r <= rq) return t[id]; //total intersection
        int mid = (l+r)/2;
        node left = query(id*2, l, mid, lq, rq);
        node right = query(id*2+1, mid+1, r, lq, rq);
        node res;
        res.merge(left, right);
        return res;
    }

    
    void update(int pos, int val) {
        update(1, 0, n-1, pos, val);
    }
    int query(int l, int r) {
        node res = query(1, 0, n-1, l, r);
        return res.mx;
    }
};

struct node {
    int mn, mx;
    node() {
        mn = INT_MAX;
        mx = INT_MIN;
    }
    node(int val) {
        mn = mx = val;
    }
    void merge(node &a, node &b) {
        mn = min(a.mn, b.mn);
        mx = max(a.mx, b.mx);
    }
};


int main() {
    int n; cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    SegmentTree<node> st(n);
    st.build(a, 1, 0, n-1);
    for(int i = 0; i < 4*n+1; i++) {
        cout << st.t[i] << " ";
    }
    cout << st.sum(1, 0, n-1, 0, 2) << endl;
}



struct node {
    int sum;
    node () {
        sum = 0;
    }
}
node merge(node a, node b) {
    node res;
    res.sum = a.sum + b.sum;
    return res;
}
node t[4*MAXN];
void build(int id, int l, int r) {
    if(l == r) {
        t[id].sum = a[l]; 
        return;
    }
    int mid = (l+r)/2;
    build(id*2, l, mid);
    build(id*2+1, mid+1, r);
    t[id] = merge(t[id*2], t[id*2+1]);
}
void update(int id, int l, int r, int pos, int val) {
    if(pos < l || pos > r) return; 
    if(l == r) {
        t[id].sum += val;
        return;
    }
    int mid = (l+r)/2;
    update(id*2, l, mid, pos, val);
    update(id*2+1, mid+1, r, pos, val);
    t[id] = merge(t[id*2], t[id*2+1]);
}
node query(int id, int l, int r, int lq, int rq) {
    if(lq > r || l > rq) return node(); //no intersection
    if(lq <= l && r <= rq) return t[id]; /  /total intersection
    int mid = (l+r)/2;
    return merge(query(id*2, l, mid, lq, rq), query(id*2+1, mid+1, r, lq, rq));
}




// Iterative 
template<typename node>
struct SegmentTree {
    int n;
    vector<node> t;

    SegmentTree(int N) {
        n = N;
        t.resize(N << 1);
    }

    void set(int idx, int val) {
        idx += n;
        t[idx] = node(val);
        for(; idx > 1; idx >>= 1) {
            t[idx >> 1].merge(t[idx], t[idx ^ 1]);
        }
    }

    // This is also correct
    // void set(int idx, int val) {
    //     for(t[idx += n] = node(val); idx >>= 1; ) {
    //         t[idx].merge(t[idx << 1], t[idx << 1 | 1]);
    //     }
    // }

    // [start, end)
    node query(int start, int end) {
        node res = node();
        for(start += n, end += n; start < end; start >>= 1, end >>= 1) {
            if(start & 1) res.merge(res, t[start++]);
            if(end & 1) res.merge(res, t[--end]);
        }
        return res;
    }

};

struct Node {
    int sum;
    Node() {
        sum = 0;
    }
    Node(int val) {
        sum = val;
    }
    void merge(Node &a, Node &b) {
        sum = a.sum + b.sum;
    }
};
