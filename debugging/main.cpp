//HIRAK RAJBONSHI 2312020

#include <bits/stdc++.h>
using namespace std;

#define md                  1000000007
#define pb                  push_back
#define endl                "\n"
#define F                   first
#define S                   second
#define sz(x)               (int)(x).size()   
#define inp(v)              for(auto &x: v) cin>>x  
#define all(x)              (x).begin(), (x).end()
#define rep(i, a, b)        for (int i = a; i < (b); ++i)
#define fast_io             cin.tie(0)->sync_with_stdio(0);cin.exceptions(cin.failbit);
 
using ll  = long long;
using ull = unsigned long long;
using lld = long double;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using vl  = vector<ll>;
using vi  = vector<int>;
 

void solve(){
    string n;
    cin >> n;
    ll sum = 0, c2 = 0, c3 = 0;
    for(auto i:n) {
        ll x = i - '0';
        if(x==2) c2++;
        else if(x==3) c3++;
        sum += x;
    }
    // c2 %= 9;
    // c3 %= 9;
    for(int i=0; i<=c2; i++) {
        for(int j=0; j<=c3; j++) {
            ll tm = sum + 2*i + 6*j;
            if(tm%9==0) {
                cout << "YES";
                return;
            }
        }
    }
    cout << "NO";

}


int32_t main() {
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);

    solve();
    cout << "\n";


}