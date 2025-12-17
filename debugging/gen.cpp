#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll uid(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rng); }

void gen(int __)
{
    int k = uid(1, 4);
    int n = k * uid(2, 4);
    cout << n << " " << k << "\n";
    string s;
    for (int i = 0; i < n; i++)
        s.push_back(char('a' + uid(0, 6)));
    cout << s << "\n";
}
#undef int
int main(int argc, char *argv[])
{
    int t = 1;
    // cout << t << "\n";
    for (int i = 1; i <= t; i++)
    {
        gen(i);
    }
    return 0;
}
