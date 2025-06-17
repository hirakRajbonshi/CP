// HIRAK RAJBONSHI 2312020

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
    if (n == 1 && cout << s << "\n")
        return;
    string ans = "";
    for (int i = 0; i < n - 1; i++)
    {
        if (s[i] > s[i + 1])
        {
            int j = i + 1;
            while (j < n && s[j] <= s[i])
            {
                ans += s[j];
                j++;
            }
            ans += s[i];
            while (j < n)
            {
                ans += s[j];
                j++;
            }
            break;
        }
        else
            ans += s[i];
    }
    if (ans.size() != n)
        cout << s << "\n";
    else
        cout << ans << "\n";
}

int32_t main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output1.txt", "w", stdout);

    solve();
}