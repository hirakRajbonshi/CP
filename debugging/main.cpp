#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

#define ll long long
#define int long long

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
    FenwickTree bit(n);
    for (int i = 0; i < n; i++)
        bit.add(i, 1);

    auto update = [&](int idx, int del)
    {
        bit.add(n - 1 - idx, del);
    };
    auto isPossible = [&](int start, int req)
    {
        int sum = bit.sum(n - 1 - start);
        if (sum >= req)
        {
            update(start, -1);
            return true;
        }
        return false;
    };
    int rem = k, start = 0;
    vector<int> ans, a;
    ans.reserve(n);
    a.reserve(k);
    for (int j = 0; j < n; j++)
    {
        if (rem == 0)
        {
            assert(a.size() == k);
            debug(a) int end = n;
            for (int i = a.size() - 1; i >= 0; i--)
            {
                int idx = s[a[i]] - 'a';
                if (at[idx].empty())
                {
                    end = a[i];
                    continue;
                }
                auto it = at[idx].upper_bound(end);
                if (it != at[idx].begin())
                    it--;

                if ((*it) <= a[i])
                {
                    end = a[i];
                    continue;
                }
                update(*it, -1);
                int t = a[i];
                a[i] = *it;
                at[idx].erase(it);
                at[idx].insert(t);
                update(t, 1);
                end = a[i];
            }
            debug(a) for (int &e : a) ans.push_back(e);
            rem = k, start = 0;
            a.clear();
        }
        for (int i = 0; i < 26; i++)
        {
            if (at[i].empty())
                continue;
            auto it = at[i].lower_bound(start);
            if (it == at[i].end())
                continue;
            if (isPossible(*it, rem))
            {
                a.push_back(*it);
                start = *it;
                rem--;
                at[i].erase(it);
                break;
            }
        }
    }
    debug(a) for (int &e : a) ans.push_back(e);
    for (int &e : ans)
        cout << s[e];
    cout << "\n";
}

int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int _TEST = 1;
    // cin>>_TEST;
    for (int _ = 1; _ <= _TEST; _++)
    {
        solve();
    }
}