#include <bits/stdc++.h>
using namespace std;

struct FenwickTree
{
    int n;
    vector<int> bit;
    FenwickTree(int n)
    {
        this->n = n;
        bit.assign(n, 0);
    }
    FenwickTree(vector<int> const &a) : FenwickTree(a.size())
    {
        for (size_t i = 0; i < a.size(); i++)
            add(i, a[i]);
    }
    int sum(int r)
    {
        int ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }
    int sum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }
    void add(int idx, int delta)
    {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};

void solve()
{
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    vector<set<int>> at(26);
    for (int i = 0; i < n; i++)
    {
        at[s[i] - 'a'].insert(i);
    }
    vector<int> ans;
    FenwickTree bit(n);
    for (int i = 0; i < n; i++)
        bit.add(i, 1);
    int rem = k, start = 0;
    for (int q = 0; q < n / k; q++)
    {
        start = -1;
        rem = k;
        vector<int> v;
        for (int j = 0; j < k; j++)
        {
            for (int i = 0; i < 26; i++)
            {
                auto it = at[i].upper_bound(start);
                if (it == at[i].end())
                    continue;
                int sum = bit.sum(n - 1 - *it);
                if (sum >= rem)
                {
                    ans.push_back(*it);
                    start = *it;
                    v.push_back(i);
                    rem--;
                    break;
                }
            }
        }
        reverse(v.begin(), v.end());
        int p = n + 1;
        for (auto i : v)
        {
            auto it = prev(at[i].lower_bound(p));
            p = *it;
            bit.add(n - 1 - *it, -1);
            at[i].erase(it);
        }
    }
    for (int &e : ans)
        cout << s[e];
    cout << "\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
}