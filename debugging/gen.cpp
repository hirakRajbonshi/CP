#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll uid(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rng); }

int32_t main()
{
    // freopen("input.txt", "w", stdout);
    // srand(atoi(argv[1]));
    int n = uid(1, 10);
    cout << n << "\n";
    string s = "";
    while (n--)
    {
        char c = 'a' + uid(0, 25);
        s += c;
    }
    cout << s << "\n";
    return 0;
}