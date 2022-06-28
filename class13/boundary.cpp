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


int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        vector<int> R(m), W(m);
        int r = 0, w = 0;
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &R[i], &W[i]);
            r = max(r, R[i]);
            w = max(w, W[i]);
        }
        if (r + w > n) {
            puts("IMPOSSIBLE");
        } else {
            for (int i = 0; i < r; i++) printf("R");
            for (int i = 0; i < n - r; i++) printf("W");
            puts("");
        }
    }
}


/*
3
3 5
12 12
314159265 358979323

 */