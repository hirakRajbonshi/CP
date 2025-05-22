#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main(){
    ll t;
    cin >> t;
    while(t--){
        ll n,k;
        cin >> n >> k;
        vector <ll> v(n);
        for(ll i = 0; i < n; i++) cin >> v[i];
        sort(v.begin(),v.end());
        priority_queue <ll> pq;
        for(ll i = 1; i < n; i++){
            pq.push(v[i]-v[i-1]);
        }
        ll d,c,p;
        cin >> d >> c >> p;
        while(k > 0){
            ll dis = pq.top();
            if(dis/2 <= d && p < c) break;
            pq.pop();
            if((dis)/2 <= d){
                p -= c;
            }
            pq.push(dis/2);
            pq.push((dis+1)/2);
        }
        cout << pq.top() << endl;
    }
    return 0;
}