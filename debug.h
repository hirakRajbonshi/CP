#pragma once
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define ll long long
#define ff first
#define ss second

#define debug(...) debug_out(#__VA_ARGS__, __VA_ARGS__);

struct FileIO {
    FileIO() {
        freopen("./files/input.txt", "r", stdin);
        freopen("./files/output.txt", "w", stdout);
        freopen("./files/error.txt", "w", stderr);
    }
} _fileio;



template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
template <class T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

void _print(bool t) {cerr << t;}
void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(float t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(long double t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(vector <vector <T>> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T> void _print(ordered_set<T> v);
template <class T> void _print(ordered_multiset<T> v);

template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(vector <vector <T>> v) {cerr << "[\n  "; for(auto e : v) {cerr << "[ "; for (T i : e) {_print(i); cerr << " ";} cerr << "],\n  " ;} cerr <<"]";}
template <class T> void _print(ordered_set<T> v) {cerr << "[ "; for(T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(ordered_multiset<T> v) {cerr << "[ "; for(T i : v) {_print(i); cerr << " ";} cerr << "]";}

template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}

template <class T, size_t N>
void _print(T (&arr)[N]) {
    cerr << "[ ";
    for (size_t i = 0; i < N; i++) {
        _print(arr[i]);
        cerr << " ";
    }
    cerr << "]";
}

template <class T, size_t N>
void _print(vector<T> (&arr)[N]) {
    cerr << "[ ";
    for (size_t i = 0; i < N; i++) {
        _print(arr[i]);
        cerr << " ";
    }
    cerr << "]";
}

template <class T, size_t N>
void _print(set<T> (&arr)[N]) {
    cerr << "[ ";
    for (size_t i = 0; i < N; i++) {
        _print(arr[i]);
        cerr << " ";
    }
    cerr << "]";
}

template <class T, class V, size_t N>
void _print(map<T, V> (&arr)[N]) {
    cerr << "[ ";
    for (size_t i = 0; i < N; i++) {
        _print(arr[i]);
        cerr << " ";
    }
    cerr << "]";
}


template <typename T>
void debug_out(const char* name, T&& arg) {
    cerr << name << " = ";
    _print(arg);
    cerr << "\n";
}

template <typename T, typename... Args>
void debug_out(const char* names, T&& arg, Args&&... args) {
    const char* comma = strchr(names, ',');
    cerr.write(names, comma - names) << " = ";
    _print(arg);
    cerr << ", ";
    debug_out(comma + 1, args...);
}

