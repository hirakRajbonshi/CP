#include <btis/stdc++.h>
using namespace std;

void sieve(int N) {
    vector<bool> ret(N+1, true);
    for(int i = 2; i*i <= N; i++) {
        if(ret[i]) {
            for(int j = i; j <= N; j += i) {
                ret[j] = false;
            }
        }
    }
    return ret;
}
vector<int> spf(int n) {
    vector<int> ret(n+1, 0);
    iota(ret.begin(), ret.end(), 0);
    for(int i = 2; i*i <= n; i++) {
        if(ret[i] == i) {
            for(int j = i*i; j <= n; j += i) {
                if(ret[j] == j) {
                    ret[j] = i;
                }
            }
        }
    }
    return ret;
} 


// function to count number of numbers from 1 to n which are coprime with x
int f(int n, int x) {
    vector<int> a;
    for(int i = 2; i*i <= x; i++) {
        if(x%i == 0) {
            a.push_back(i);
            while(x%i == 0) x /= i;
        }
    }
    if(x > 1) a.push_back(x);
    int m = a.size();
    int cnt = 0;
    for(int mask = 0; mask < (1ll << mask); mask++) {
        int pro = 1;
        for(int i = 0; i < m; i++) {
            if(mask & (1 << i)) {
                pro *= a[i];
            }
        }
        int sign = __builtin_popcount(mask) & 1 ? -1 : 1;
        cnt += sign * (n/pro);
    }
    return cnt;
}