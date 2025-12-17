struct BIT {
    int N;
    vector<int> fenwick;
    
    BIT(int n) {
        N = n;
        fenwick.resize(n + 1);
    }

    BIT(vector<int> &v) : BIT((int)v.size()) {
        for(int i = 0; i < v.size(); i++) 
            update(i + 1, v[i]);
    }

    void update(int pos, int val) {
        while (pos <= N) {
            fenwick[pos] += val;
            pos += (pos & -pos);
        }
    }


    // sum in [1, pos]
    int query(int pos) {
        int sum = 0;
        while (pos > 0) {
            sum += fenwick[pos];
            pos -= (pos & -pos);
        }
        return sum;
    }

};

// CP Algo
struct FenwickTree {
    vector<int> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    FenwickTree(vector<int> const &a) : FenwickTree(a.size()) {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }

    int sum(int r) {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
