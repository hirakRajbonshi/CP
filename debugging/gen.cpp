#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll uid(ll l, ll r) {return uniform_int_distribution<ll>(l, r)(rng);}

int32_t main() {
    freopen("input.txt", "w", stdout);
    // srand(atoi(argv[1])); 
    int n = uid(1, 100);
    for(int i = 0; i < n; i++) {
        cout << uid(0, 9);
    }
    cout << "\n";
    return 0;
} 