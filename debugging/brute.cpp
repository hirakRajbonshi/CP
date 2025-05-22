#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
void solve()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    int one=0;
    int two=0;
    for (int i = 0; i <n; i++){
        if(s[i]=='-'){
            one++;
        }
        else two++;
    }
    cout<<(one/2)*(two)*(ceil((one*1.0)/2))<<endl;
 
}
int32_t main() {
    freopen("input.txt", "r", stdin);
    freopen("output2.txt", "w", stdout);

    solve();


}