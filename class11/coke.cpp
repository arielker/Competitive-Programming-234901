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


vector<string> string_tokenizer(const string &sentence) {
    vector<string> words;
    stringstream ss(sentence);
    string word;
    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

vector<ll> int_tokenizer(const string &sentence) {
    vector<ll> words;
    stringstream ss(sentence);
    ll word;
    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

const ll INF = 1e9;
const ll NOT_VISITED = -1;
const ll COKE_PRICE = 8;

vector<vvll> cache;

ll fun(ll C, ll n1, ll n5, ll n10) {
    if (C < 0 || n1 < 0 || n5 < 0 || n10 < 0) {
        return INF;
    }
    if (cache[C][n5][n10] != NOT_VISITED) {
        return cache[C][n5][n10];
    }
    if (C == 0) {
        return 0;
    }

    ll res = COKE_PRICE * C;
    res = min(res,
              4 + fun(C - 1, n1 - 3, n5 - 1, n10)); // use one 5 and three 1
    res = min(res, 2 + fun(C - 1, n1 + 2, n5 - 2, n10)); // use two 5
    res = min(res, 4 + fun(C - 1, n1 - 3, n5 + 1,
                           n10 - 1)); // exchange five 1 with one 5
    res = min(res, 1 + fun(C - 1, n1 + 2, n5, n10 - 1)); // use one 10

    cache[C][n5][n10] = res;
    return res;
}

int main() {
    ll T;
    cin >> T;

    for (ll i = 0; i < T; ++i) {
        cache = vector<vvll>(151, vvll(151, vll(51, NOT_VISITED)));
        ll C, n1, n5, n10;
        cin >> C >> n1 >> n5 >> n10;

        cout << fun(C, n1, n5, n10) << endl;
    }

    return 0;
}
