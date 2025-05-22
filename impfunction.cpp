#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define pb push_back
#define ppb pop_back
#define pf push_front
#define ppf pop_front
#define eb emplace_back
#define get(a) for(auto &e : a) cin>>e;
#define put(a) for(auto e : a) cout << e << " "; cout << endl;
#define fr(i, n) for(int i = 0; i < n; i++)
#define fri(i, a, b) for(int i = a; i <= b; i++)
#define endl "\n" 
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define YES cout << "YES" << endl
#define NO cout << "NO" << endl
#define allEqual(a) *max_element(all(a))==*min_element(all(a))
#define MOD 1000000007
#define INF 1e18
#define ff first
#define ss second
#define set_bits __builtin_popcountll
#define ordered_set tree<int , null_type, less<int> , rb_tree_tag , tree_order_statistics_node_update>



bool secVal(const pair<int, int>& a, const pair<int, int>& b) { return a.ss < b.ss; }
ll lcm(ll a, ll b) { return (a*b)/__gcd(a, b); }
ll ceil(int a, int b) {return (a-1)/b + 1; }
int maxElmIdx(vector<auto> a) { return max_element(all(a))-a.begin(); }
int minElmIdx(vector<auto> a) { return min_element(all(a))-a.begin(); }
int maxElm(vector<auto> a) { return *max_element(all(a)); }
int minElm(vector<auto> a) { return *min_element(all(a)); }
void upMul(ll &a, ll b, ll m) { a = (a*b)%m; }
void upAdd(ll &a, ll b, ll m) { a = (a+b)%m; }
ll power(ll a, ll b) { ll res = 1;while (b > 0) { if (b & 1) res = res * a; a = a * a; b >>= 1;}  return res; }
ll powerMod(ll a, ll b, ll m) { a %= m; ll res = 1; while(b > 0) { if (b & 1) res = res * a % m; a = a * a % m; b >>= 1; } return res; }
