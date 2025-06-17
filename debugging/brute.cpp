#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    set<string> st;
    st.insert(s);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            string str = s.substr(0, i);
            // debug(str)
            str += s.substr(i + 1, j - i);
            str += s[i];
            str += s.substr(j + 1);
            st.insert(str);
        }
    }
    string ans = *st.begin();
    cout << ans << "\n";
}
int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output2.txt", "w", stdout);

    solve();
}