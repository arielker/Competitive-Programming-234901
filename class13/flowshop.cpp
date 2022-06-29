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
    ll N, M;
    cin >> N >> M;

    vvll P(N + 1, vll(M + 1, 0));
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            cin >> P[i][j];
        }
    }


    vvll T(N + 1, vll(M + 1, 0));
    for (int i = 1; i <= N; ++i) {
        T[i][1] = T[i - 1][1] + P[i][1];
    }
    for (int j = 1; j <= M; ++j) {
        T[1][j] = T[1][j - 1] + P[1][j];
    }
    for (int i = 1; i <= N; ++i) {
        for (int j = 2; j <= M; ++j) {
            T[i][j] = max(T[i][j - 1] + P[i][j], T[i - 1][j] + P[i][j]);
        }
    }
    for (int i = 1; i <= N; ++i) {
        cout << T[i][M] << " ";
    }
    return 0;
}

/*
2 3
1 2 3
3 2 1

 */