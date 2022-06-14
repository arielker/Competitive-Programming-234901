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

vd trees;

double dist(double a, double b) {
    return sqrt(a * a + b * b);
}

double fun(ll N, ll L, ll W) {
    ll half = N / 2;
    vvd cache(half + 1, vd(half + 1, INF));
    cache[0][0] = 0;

    double pair_spacing = double(L) / (double(N) / 2.0 - 1.0);
    for (int r = 0; r < half; ++r) {
        for (int l = 0; l < half; ++l) {
            if (l == 0) {
                double r_y_delta = pair_spacing * r - trees[r];
                cache[r + 1][l] = cache[r][l] + dist(W, r_y_delta);
            }

            if (r == 0) {
                double l_y_delta = pair_spacing * l - trees[l];
                cache[r][l + 1] = cache[r][l] + dist(0.0, l_y_delta);
            }

            double r_y_delta = pair_spacing * r - trees[r + l + 1];
            double r_dist = cache[r][l + 1] + dist(W, r_y_delta);

            double l_y_delta = pair_spacing * l - trees[r + l + 1];
            double l_dist = cache[r + 1][l] + dist(0.0, l_y_delta);

            cache[r + 1][l + 1] = min(l_dist, r_dist);
        }
    }

    return cache[half][half];
}

int main() {
    ll N, L, W;
    cin >> N >> L >> W;

    trees = vd(N);
    for (int i = 0; i < N; ++i) {
        cin >> trees[i];
    }
    sort(trees.begin(), trees.end());

    printf("%.9lf", fun(N, L, W));

    return 0;
}
