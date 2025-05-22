#include <bits/stdc++.h> 
using namespace std;

//count number of pairs such that i < j and a[i] > a[j]
//number of swaps in bubble sort
int inversions(vector<int>& a, int l, int r) {
    if(l == r) return 0;
    vector<int> ans(r-l+1);
    int m = (l+r)/2;
    int x = inversions(a, l, m);
    int y = inversions(a, m+1, r);
    int i = l, j = m+1, inv = 0, k = 0;
    while(i <= m && j <= r) {
        if(a[i] < a[j]) {
            inv += j-m-1;
            ans[k++] = a[i++];
        } else {
            ans[k++] = a[j++];
        }
    }
    while(i <= m) {
        inv += j-m-1;
        ans[k++] = a[i++];
    }
    while(j <= r) ans[k++] = a[j++];
    for(int k = l; k <= r; k++) a[k] = ans[k-l];
    return inv+x+y;
 
}

int main() {
    vector<int> v(5);
    for(int &e : v) cin>>e;
    cout << inversions(v, 0, 5) << endl;

    return 0;
}