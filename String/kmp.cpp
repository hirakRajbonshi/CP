#include <bits/stdc++.h>
using namespace std;

//returns the longest lenght of prefix which is equal to prefix
int prefix_function(string s) {
    int n = s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi.back();
}

int main() {

}