#include <bits/stdc++.h>
using namespace std;

template<typename Node>
struct sparse {
    vector<vector<Node>> table;
    vector<int> LOG;
    int n;
    int MAXLOG;
    vector<int> a;
    sparse(int n1, vector<int> &arr) {
        n = n1;
        a = arr;
        table.resize(n);
        LOG.resize(n + 1);
        MAXLOG = log2(n);
        LOG[1] = 0;
        for (int i = 2; i <= n; i++) {
            LOG[i] = LOG[i / 2] + 1;
        }
        for (int i = 0; i < n; i++) {
            table[i].resize(MAXLOG + 1);
            fill(table[i].begin(), table[i].end(), Node());
        }
        build();
    }
    void build() {
        for (int i = 0; i < n; i++) {
            table[i][0] = Node(a[i]);
        }
        for (int i = 1; i <= MAXLOG; i++) {
            for (int j = 0; (j + (1 << i)) <= n; j++) {
                table[j][i].merge(table[j][i - 1], table[j + (1 << (i - 1))][i - 1]);
            }
        }
    }
    //O(logN)
    Node queryNormal(int left, int right) {
        if(right < left) return Node();
        Node ans = Node();
        for (int j = LOG[right - left + 1]; j >= 0; j--) {
            if ((1 << j) <= right - left + 1) {
                ans.merge(ans, table[left][j]);
                left += (1 << j);
            }
        }
        return ans;
    }
    // O(1)
    Node queryIdempotent(int left, int right) {  
        if(right < left) return Node();
        int j = LOG[right - left + 1];      
        Node ans = Node();
        ans.merge(table[left][j], table[right - (1 << j) + 1][j]);
        return ans;
    }
};

struct node {
    int val; 
    node() { 
        val = 0;
    }
    node(ll v) {
        val = v;
    }
    void merge(node &l, node &r) {
        val = __gcd(l.val, r.val);
    }
};

int main () {
    int n, q; cin>>n>>q;
    vector<int> a(n), dif;

    for(int &e : a) cin>>e;
    for(int i = 1; i < n; i++) dif.push_back(abs(a[i]-a[i-1]));

    if(n == 1) {
        while(q--) {
            int l, r; cin>>l>>r;
            cout << "0 ";
        }
        cout << "\n";
        return;
    }

    sparse<node> st(n, dif);
    while(q--) {
        int l, r; cin>>l>>r;
        cout << st.queryIdempotent(l-1, r-2).val << " ";
    }
    cout << "\n";
    return 0;
}