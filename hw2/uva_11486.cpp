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

struct Matrix {
    vvll matrix;
    ll row, column;
    ll mod;

    Matrix(ll row, ll column, ll val = 0, ll mod = 1000000007) : row(row), column(column), mod(mod) {
        matrix = vvll(row, vll(column, 0));
        for (int i = 0; i < min(row, column); ++i) {
            matrix[i][i] = val;
        }
    }

    Matrix operator*(Matrix mat) {
        Matrix res(row, mat.column, 0);
        for (int i = 0; i < row; ++i) {
            for (int m = 0; m < column; ++m) {
                if (matrix[i][m] == 0) continue;

                for (int j = 0; j < mat.column; ++j) {
                    res.matrix[i][j] += matrix[i][m] * mat.matrix[m][j];
                    res.matrix[i][j] %= mod;
                }
            }
        }
        return res;
    }

    Matrix operator^(ll n) {
        assert(row == column);
        Matrix res(row, row, 1);
        Matrix A = *this;
        for (ll i = n; i > 0; i = i >> 1) {
            if (i & 1) {
                res = res * A;
            }
            A = A * A;
        }
        return res;
    }

    ll sum_row(ll i) {
        ll res = 0;
        for (int j = 0; j < column; j++) {
            res = (res + matrix[i][j]) % mod;
        }
        return res % mod;
    }

    ll sum() {
        ll res = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < column; j++) {
                res = (res + matrix[i][j]) % mod;
            }
        }
        return res % mod;
    }
};

#define columns 7

map<vll, ll> state_to_idx; // state -> idx
vvll possible_states; // {p1_pos, p2_pos, p3_pos, p4_pos}

Matrix initialize(){
    ll idx = 0;
    for (int p1_pos = 0; p1_pos < columns; ++p1_pos) {
        for (int p2_pos = p1_pos + 1; p2_pos < columns; ++p2_pos) {
            for (int p3_pos = p2_pos + 1; p3_pos < columns; ++p3_pos) {
                for (int p4_pos = p3_pos + 1; p4_pos < columns; ++p4_pos) {
                    vll state = {p1_pos, p2_pos, p3_pos, p4_pos};
                    state_to_idx[state] = idx;
                    ++idx;
                    possible_states.push_back(state);
                }
            }
        }
    }

    Matrix ways_amount(possible_states.size(), possible_states.size());
    for (int i = 0; i < possible_states.size(); i++) {
        for (int j = 0; j < possible_states.size(); j++) {
            vll state_permutation = possible_states[j];
            do {
                if ((abs(state_permutation[0] - possible_states[i][0]) == 1) &&
                    (abs(state_permutation[1] - possible_states[i][1]) == 1) &&
                    (abs(state_permutation[2] - possible_states[i][2]) == 1) &&
                    (abs(state_permutation[3] - possible_states[i][3]) == 1)) {
                    // check legal move
                    ways_amount.matrix[i][j]++;
                }
            } while (next_permutation(state_permutation.begin(), state_permutation.end()));
        }
    }

    return ways_amount;
}

ll find_amount(ll N, Matrix &ways_amount){
    vll initial_positions(4);
    for (int j = 0; j < columns; ++j) {
        ll r_j;
        cin >> r_j;

        if (0 != r_j)
            initial_positions[r_j - 1] = j;
    }

    Matrix res = ways_amount ^ (N - 1);
    ll idx = state_to_idx[initial_positions];
    return res.sum_row(idx);
}

int main() {
    Matrix ways_amount = initialize();

    ll T;
    cin >> T;
    for (int i = 0; i < T; ++i) {
        ll N;
        cin >> N;

        cout << find_amount(N, ways_amount) << endl;
    }

    return 0;
}

/*
3
1
1 0 2 0 3 0 4
2
1 0 2 0 3 0 4
2
1 2 3 4 0 0 0

 */
