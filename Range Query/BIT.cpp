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
