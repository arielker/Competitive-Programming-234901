#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <cmath>

using namespace std;

typedef long long ll;

// bool
typedef pair<bool, bool> bb;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<bb> vbb;
typedef vector<vbb> vvbb;

// int
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

// double
typedef pair<double, double> dd;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef vector<dd> vdd;
typedef vector<vdd> vvdd;

// ll
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;

// set
typedef set<int> si;
typedef set<ll> sll;
typedef set<vii> svii;
typedef vector<si> vsi;

const int INF = 1e9;
#define EPS 1e-9

int main() {
    ll n;
    cin >> n;

    ll colors[3] = {0}, values[3] = {0};
    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        values[i % 3] += x;
    }

    for (int i = 0; i < n; ++i) {
        ll x;
        cin >> x;
        colors[i % 3] += values[i % 3] * x;
        colors[(i + 1) % 3] += x * values[(i + 2) % 3];
        colors[(i + 2) % 3] += x * values[(i + 1) % 3];
    }

    for (int i = 2; i >= 0; --i) {
        cout << colors[i] << " ";
    }
    cout << endl;
    return 0;
}

/*
3
1 1 1
1 1 1

7
6 2 4 5 1 1 4
2 5 1 4 2 3 4

 */